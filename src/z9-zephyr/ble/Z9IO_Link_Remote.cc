
#include "Z9IO_Link.h"
#include "Z9IO_Device.h"
#include "Z9Crypto_gcm.h"       // key negotiation
#include "Z9IO_Logic.h"
#include "Z9IOProtocol_Current.h"
//#include "public-key.pem"
//#include "private-key.pem"

#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <cstring>

LOG_MODULE_REGISTER(z9io, LOG_LEVEL_DBG);

// temp home for support routines
uint8_t link_key[16], session_key[16];
// mimic old code
uint8_t local_seed[16], gcm_key[16];
gcm_key_id_t psa_link_key;

const struct device *dev_0 = DEVICE_DT_GET(DT_ALIAS(z9io_serial));
Z9IO_Link link{ 0, dev_0 };


bool key_isSet(const uint8_t *key)
{
    for (int i = 0; i < 16; ++i)
        if (*key++)
            return true;
    return false;
}

void key_clear(uint8_t *key)
{
    memset(key, 0, 16);
}

void key_set(uint8_t *key, const uint8_t *data)
{
    memcpy(key, data, 16);
}

void key_xor(uint8_t *key, const uint8_t *data)
{
    for (int i = 0; i < 16; ++i)
        *key++ ^= *data++;
}

// must pre-increment seq_number for each message generated
static KCB& gen_message(uint8_t& seq_number, uint8_t cmd, uint8_t count = 0, uint8_t *data = {})
{
    //LOG_INF("%s: cmd=%02x", __func__, cmd);

    constexpr unsigned tx_headroom = 6;
    auto& kcb = *KCB_NEW(tx_headroom);
    kcb.write(cmd);
    while (count--)
        kcb.write(*data++);
    return kcb;
}

// these definitions are not in "Z9IOProtocol_Current.h"
// were previously found in SerialEncrypt.h

#define Z9IO_PROTOCOL_VERSION_MAJOR   2
#define Z9IO_PROTOCOL_VERSION_MINOR   0

KCB& gen_hello(uint8_t& seq_number)
{
    bool is_multi_drop = true;
    bool is_encrypted = key_isSet(session_key);
    uint8_t data[] = { 
        Z9IO_PROTOCOL_VERSION_MAJOR,
        Z9IO_PROTOCOL_VERSION_MINOR,
        is_multi_drop,
        is_encrypted,
        };

    return gen_message(seq_number, Hello_DISCRIMINATOR, sizeof(data), data);
}

KCB& gen_boardInfo(uint8_t& seq_number)
{
    bool is_encrypted = key_isSet(session_key);
    uint8_t data[33] = 
    {
        Z9IO_PROTOCOL_VERSION_MAJOR,
        Z9IO_PROTOCOL_VERSION_MINOR,
        0,                              // model# HI
        20,                             // model# Low
    };
    data[4] = 0;    // FW Hi
    data[5] = 0;    // FW Low
    data[6] = is_encrypted;
    
    uint8_t sn[8] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    std::memcpy(&data[7], sn, 8);

    return gen_message(seq_number, BoardInfo_DISCRIMINATOR, sizeof(data), (uint8_t *)&data);
}


KCB& gen_key_exchange(uint8_t& seq_number, bool is_linked, bool is_remote = false)
{
    if (!is_remote)
        key_set(local_seed, Z9Crypto_random());

    uint8_t data[18] = { (uint8_t)(is_linked * 2 + is_remote), 16 };
    memcpy(&data[2], local_seed, sizeof(local_seed));
    return gen_message(seq_number, EncryptionKeyExchange_DISCRIMINATOR, sizeof(data), data);
}

KCB& gen_poll(uint8_t& seq_number)
{
    return gen_message(seq_number, Poll_DISCRIMINATOR);
}

KCB& gen_ack(uint8_t& seq_number)
{
    uint8_t data[] = { 0, seq_number };
    return gen_message(seq_number, Ack_DISCRIMINATOR, sizeof(data), data);
}

KCB& gen_nack(uint8_t& seq_number, uint8_t reason = 0)
{
    uint8_t data[] = { 0, seq_number, reason };
    return gen_message(seq_number, Nak_DISCRIMINATOR, sizeof(data), data);
}

// convert instance to/from ordinal
Z9IO_Link& Z9IO_Link::get(unsigned ordinal)
{
    if (auto p = pInstances.at(ordinal))
        return *p;
    throw std::runtime_error{"Z9Link::get: instance not initalized"};
}

unsigned Z9IO_Link::id() const
{
    for (unsigned i = 0; i < pInstances.max_size(); ++i)
        if (this == pInstances[i])
            return i;
    throw std::runtime_error{"Z9IO_Link:id: invalid instance"};
}

// ctor: activate link based on static global
Z9IO_Link::Z9IO_Link(unsigned ordinal, const struct device *_dev)
{
	//LOG_INF("%s: %u, dev = %s", __func__, ordinal, _dev->name);
    pInstances.at(ordinal) = this;

    dev = Z9IO_device_init(ordinal, _dev);
#ifdef CONFIG_Z9_CONTROLLER
    set_timeout();
#elif CONFIG_Z9_READER
    recv_kcb = KCB_NEW(6);
    recv_crc = 0;
    Z9IO_device_recv(dev, *recv_kcb, &recv_crc, &recv_work, 0);
#endif
}


static constexpr unsigned max_retry = 10;

void Z9IO_Link::xmit(KCB& kcb)
{
	//LOG_INF("%s: kcb=%d", __func__, kcb.id());
    sys_slist_append(&xmit_queue, &kcb.data.queue[0]);
}

void Z9IO_Link::xmit_fsm_loop()
{
	//LOG_INF("%s: state=%s", __func__, Z9IO_Link_State_str[state]);
    auto queue_pop = [](sys_slist_t *list_p) -> KCB *
        {
            auto node_p = sys_slist_get(list_p);
            if (node_p)
            {
                auto c_kcb = CONTAINER_OF(node_p, kcb_t, queue[0]);
                auto kcb_p = reinterpret_cast<KCB *>(c_kcb);
                return kcb_p;
            }
            return {};
        };

    // if already busy, ignore
    if (xmit_kcb || recv_kcb) return;

    // if link not completely initalized, flush the queue
    if (state < LS_IDLE)
        while (auto kcb_p = queue_pop(&xmit_queue))
            delete kcb_p;


    // send ACK if pending. otherwise next message depends on state
    if (ack_pending)
        xmit_kcb = &gen_ack(seq_number);
    else switch (state)
    {
        // start with HELLO message
        case LS_INIT:
            state       = LS_WAIT_HELLO;
            seq_number += 2;        // screw up sn
            xmit_kcb = &gen_ack(seq_number);
            break;

        // after hello, perform key exchange
        case LS_KEY_XCHANGE_PEND:
            {
                bool is_linked = key_isSet(session_key);
                xmit_kcb = &gen_key_exchange(seq_number, is_linked, CONFIG_Z9_READER);
                if (is_linked)
                    state = LS_IDLE;
            }
            break;

        // polling for BOARD_INFO
        case LS_PEND_BOARD_INFO:
            xmit_kcb = &gen_boardInfo(seq_number);
            if (!key_isSet(session_key))
                state = LS_KEY_XCHANGE_PEND;
            else
                state = LS_IDLE;
            
            break;

        // in normal response mode
        case LS_IDLE:
        default: 
            break;
    }

    if (!xmit_kcb)
        state = LS_IDLE;

    // if no initialization message pending, grab first off queue
    if (!xmit_kcb)
        xmit_kcb = queue_pop(&xmit_queue);
    
    // if no message pending, generate a POLL
    if (!xmit_kcb)
        xmit_kcb = &gen_ack(seq_number);

    ack_pending = false;        // no ack pending now

    // XXX eventually calculate CRC & push header
    xmit_kcb->push(seq_number++);
    xmit_kcb->push(0);
    xmit_kcb->top();
    uint16_t xmit_crc = 0;
    Z9IO_device_xmit(dev, *xmit_kcb, xmit_crc, &xmit_work);
}


// entrypoints returning from device driver
#ifdef CONFIG_Z9_CONTROLLER
#define Z9IO_RX_TIMEOUT 1000
#else
#define Z9IO_RX_TIMEOUT 0
#endif

void Z9IO_Link::xmit_return(KCB& kcb)
{
	//LOG_INF("%s: KCB=%u", __func__, kcb.id());

    if (xmit_kcb)
        delete xmit_kcb;
    xmit_kcb = {};
    
    // start receiver (with timeout)
    recv_kcb = KCB_NEW(6);
    recv_crc = 0;
    Z9IO_device_recv(dev, *recv_kcb, &recv_crc, &recv_work, Z9IO_RX_TIMEOUT);
}

// here when receive operation complete
bool Z9IO_Link::recv_return(KCB& kcb)
{
	//LOG_INF("%s: KCB=%u, size=%u, crc=%04x", __func__, kcb.id(), kcb.size(), recv_crc);

    // get information about receive operation
    auto size = kcb.size();
    auto c    = kcb.top().pop();      // retrieve first character: address or TIMEOUT flag

    if (c == Z9IO_FLAG)
    {
        LOG_INF("%s: receive timeout", __func__);
        // process timeout...
        // reset link
        return false;
    }

    // check CRC: include flag/size/first character

    // check length: minimum addr/seq/cmd
    if (size < 3)
    {
        LOG_INF("%s: short receive: %d bytes", __func__, size);
        return false;       // reset link
    }

    // save to validate
    auto rx_seq_number = kcb.pop();
    
    // command byte used later: leave in recv buffer
    auto cmd  = kcb.top().peek();

    // filter allowed cmds based on link FSM state
    // if cmd not allowed, replace with NULL command (zero)
    constexpr uint8_t NULL_DISCRIMINATOR = {};

    // always allow POLL to be correct
    if (cmd != Poll_DISCRIMINATOR)
    {
        switch (state)
        {
            case LS_INIT:
            default:
                cmd = NULL_DISCRIMINATOR;
                break;

            case LS_WAIT_HELLO:
                if (cmd != Hello_DISCRIMINATOR)
                    cmd = NULL_DISCRIMINATOR;
                break;
            case LS_KEY_XCHANGE_PEND:
            case LS_KEY_XCHANGE_WAIT:
                if (cmd == Poll_DISCRIMINATOR)
                    break;
                if (cmd != EncryptionKeyExchange_DISCRIMINATOR)
                    cmd = NULL_DISCRIMINATOR;
                break;
            
            case LS_IDLE:
                break;      // normal processing 
        }
    }

    // handle locally processed messages and forward others inbound
    // all but POLL acked
    ack_pending = true;
    switch (cmd)
    {
        case NULL_DISCRIMINATOR:
        case Poll_DISCRIMINATOR:
            ack_pending = false;
            break;

        case EncryptionKeyExchange_DISCRIMINATOR:
            // processed locally
            recv_keyexchange(kcb);
            break;
        
        case Hello_DISCRIMINATOR:
            // reset seq# to zero
            seq_number = 0;
            state = LS_PEND_BOARD_INFO;

            // record Hello shows "encrypted link"
            // skip to "encryption enabled byte"
            kcb.seek(4);        // NB: DISCRIMINATOR is index zero   
            encrypted_req = kcb.peek();
            break;
            
        default:
            // send inbound
            Z9IO_Logic::get(_unit).recv(kcb);
            recv_kcb = {};
            break;
    }
    return true;
}

void Z9IO_Link::recv_keyexchange(KCB& kcb)
{
    //LOG_INF("%s: ", __func__);
    state = LS_KEY_XCHANGE_PEND;

    // read data from buffer
    /* auto cmd      = */ kcb.read();
    auto response = kcb.read();
    uint8_t remote_seed[16], *p = remote_seed;

    kcb.read();     // skip length
    for (unsigned i = 0; i < sizeof(remote_seed); ++i)
        *p++ = kcb.read();

#ifdef CONFIG_Z9_READER
    key_set(local_seed, Z9Crypto_random());
#endif

    // process according to "response"
    // XXX mimic existing codebase
    uint8_t *key_ptr {};    
    switch (response)
    {
        case EncryptionKeyExchangeType_LINKING_SEED_REQ:
        case EncryptionKeyExchangeType_LINKING_SEED_RESP:
            // new LINKING SEED implicitly clears SESSION key
            key_clear(session_key);
            key_clear(link_key);
            key_ptr = link_key;
            break;
        case EncryptionKeyExchangeType_LINK_SESSION_SEED_REQ:
        case EncryptionKeyExchangeType_LINK_SESSION_SEED_RESP:
            key_set(session_key, link_key);
            key_ptr = session_key;
            break;

        default:
            // invalid message -- restart
            state = LS_INIT;
            return;
    }

    LOG_HEXDUMP_INF(local_seed, 16, "LOCAL_SEED");
    LOG_HEXDUMP_INF(remote_seed, 16, "REMOTE_SEED");
    LOG_HEXDUMP_INF(link_key, 16, "LINK_KEY");
    LOG_HEXDUMP_INF(session_key, 16, "SESSION_KEY");

    key_xor(key_ptr, local_seed);
    key_xor(key_ptr, remote_seed);

    LOG_HEXDUMP_INF(link_key, 16, "-> LINK_KEY");
    LOG_HEXDUMP_INF(session_key, 16, "-> SESSION_KEY");

    if (response >= EncryptionKeyExchangeType_LINK_SESSION_SEED_REQ)
    {
        key_set(gcm_key, session_key);
        LOG_HEXDUMP_INF(gcm_key, 16, "GCM_KEY:");
        auto result = Z9Crypto_gcmSetKey(psa_link_key, gcm_key, sizeof(gcm_key));
    }
}


// idle the link: receiver absorbs data for `msec`
void Z9IO_Link::set_timeout(unsigned msec)
{
    // NULL recv_kcb indicates just timeout
    Z9IO_device_recv_disable(dev);
    if (recv_kcb)
    {
        delete recv_kcb;
        recv_kcb = {};
    }
    Z9IO_device_recv(dev, 0, 0, &recv_work, msec);
}

// static functions for c++ trampoline (from `workq`)
void Z9IO_Link::xmit_trampoline(struct k_work *cb)
{
	//LOG_INF("%s", __func__);

    // static function: get instance
    auto self = CONTAINER_OF(cb, Z9IO_Link, xmit_work);
    self->xmit_return(*self->xmit_kcb);
}

void Z9IO_Link::recv_trampoline(struct k_work *cb)
{
	//LOG_INF("%s", __func__);
    
    // static function: get instance
    auto self = CONTAINER_OF(cb, Z9IO_Link, recv_work);

    // NB: recv_kcb is NULL for initial timeout
    // process recv buffer. if error, restart FSM
    if (self->recv_kcb)
        if (!self->recv_return(*self->recv_kcb))
            self->state = LS_INIT;
    
    // if KCB not consumed, release it
    if (self->recv_kcb)
        delete self->recv_kcb;
    self->recv_kcb = {};
    
    // recv processing complete, send response
    self->xmit_fsm_loop();
}