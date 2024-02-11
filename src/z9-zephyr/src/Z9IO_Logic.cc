//
// Original Z9-lock message sequence:
//
// >Hello (w/o encrypt)
// <Ack
// >Poll
// <BoardInfo (w/o encrypt)
// >KeyX 00
// <KeyX 01
// >KeyX 02
// <KeyX 03
// >Hello (w encrypt)
// <Ack
// >Poll
// <BoardInfo (w encrypt)
// >Poll
// <Ack
// > 13 BoardStatusQuery @07.628
// <Ack
// > 35 Encrypt (41 bytes: 16 IV, 9 data, + 16 GCM )
// <Ack
// > 35 Encrypt (36 bytes: 16 IV, 4 data, + 16 GCM )
// <Ack
//
// Boardinfo processing at Task_LockalIO.c:743


#include "Z9IO_Logic.h"
#include "Z9IOProtocol_Current.h"
#include "Z9Crypto_gcm_KCB.h"
#include "ModelInfo.h"

#include <zephyr/logging/log.h>
#include <cstring>






LOG_MODULE_DECLARE(z9io, CONFIG_Z9IO_LOG_LEVEL);

static Z9IO_Logic z9_logic[NUM_Z9IO_LINK];

// should be encrypted on xmit
static bool should_be_encrypted(uint8_t discriminator)
{
    switch (discriminator)
    {
        case Hello_DISCRIMINATOR:
        case BoardInfo_DISCRIMINATOR:
        case Poll_DISCRIMINATOR:
        case Ack_DISCRIMINATOR:
        case Nak_DISCRIMINATOR:
        case Ping_DISCRIMINATOR:
        case Pong_DISCRIMINATOR:
        case EncryptionKeyExchange_DISCRIMINATOR:
		case BoardStatusQuery_DISCRIMINATOR:
            return false;
		case AnalogInConfig_DISCRIMINATOR:
        case DigitalInConfig_DISCRIMINATOR:
		case Config_DISCRIMINATOR:
		case DigitalWrite_DISCRIMINATOR:
		case ApplicationEncryptionKeyExchange_DISCRIMINATOR:
		case HostInfo_DISCRIMINATOR:
		case HostStatus_DISCRIMINATOR:
        case ProtocolPassthru_DISCRIMINATOR:
            return true;
		default:
			LOG_WRN("%s: add explicit case for discriminator=%u", __FUNCTION__, (unsigned int) discriminator);
			return false;
    }
}

static bool must_be_encrypted(uint8_t discriminator)
{
    switch (discriminator)
    {
        default:
			//LOG_WRN("%s: add explicit case for discriminator=%u", __FUNCTION__, (unsigned int) discriminator)
			return false;
    }
}

// must pre-increment seq_number for each message generated
static KCB& gen_message(uint8_t cmd, uint8_t count = 0, uint8_t *data = {})
{
    LOG_INF("%s: cmd=%d", __func__, cmd);

    constexpr unsigned tx_headroom = 6;
    auto& kcb = *KCB_NEW(tx_headroom);
    kcb.write(cmd);
    while (count--)
        kcb.write(*data++);
    return kcb;
}

// generate responses
KCB& gen_boardStatusQuery(Z9IO_Logic& p)
{
    return gen_message(BoardStatusQuery_DISCRIMINATOR);
}
KCB& gen_digitalInConfig (Z9IO_Logic& p, uint8_t index, uint8_t enabled = 1, uint8_t inverted = 0)
{
    uint8_t data [7] = { index, enabled, inverted }; 
    return gen_message(DigitalInConfig_DISCRIMINATOR, sizeof(data), data);
}
KCB& gen_analogInConfig (Z9IO_Logic& p, uint8_t index, uint8_t enabled = 1, uint8_t inverted = 0)
{
    uint8_t data [18] = { index, enabled, inverted }; 
    return gen_message(AnalogInConfig_DISCRIMINATOR, sizeof(data), data);
}
KCB& gen_config(Z9IO_Logic&, uint32_t input, uint32_t output, uint32_t analog)
{
    uint8_t data [19], *p = data;
    auto add32 = [&](uint32_t info) 
                {
                    for (unsigned i = 0; i < sizeof(info); ++i)
                    {
                        p[sizeof(info) - i - 1] = info;
                        info >>= 8;
                    }
                    p += sizeof(info);
                };

    std::memset(data, 0, sizeof(data));
    ++p;        // skip reserved
    add32(input);
    add32(output);
    add32(analog);
    return gen_message(Config_DISCRIMINATOR, sizeof(data), data);
}

KCB& gen_appKeyExchange  (Z9IO_Logic&, uint8_t type = 0, uint8_t length = 0, uint8_t *key = NULL)
{
    uint8_t data[35], *p = data;
    std::memset(data, 0, sizeof(data));
    *p++ = type;
    *p++ = 33;
    std::memcpy(p, key, length); 
    return gen_message(ApplicationEncryptionKeyExchange_DISCRIMINATOR, sizeof(data), data);
}

// ctor: activate logic
Z9IO_Logic::Z9IO_Logic()
{
	static unsigned ordinal;
 
    LOG_INF("%s: %u", __func__, ordinal);
    _unit = ordinal++;
    pInstances.at(_unit) = this;
}


// convert instance to/from ordinal
Z9IO_Logic& Z9IO_Logic::get(unsigned ordinal)
{
    if (auto p = pInstances.at(ordinal))
        return *p;
    throw std::runtime_error{"Z9Logic::get: instance not initalized"};
}

void Z9IO_Logic::process_recv(KCB& kcb)
{
    // first decrypt if was encrypted
    bool wasEncrypted = false;
    if (kcb.peek() == EncryptedContent_DISCRIMINATOR)
    {
        kcb.consumeHeadroom(3);     // absorb cmd + count
        if (auto result = Z9Crypto_gcm_decrypt_KCB(psa_link_key, kcb))
        {
            LOG_ERR("%s: Decryption failed: %s", __func__, result);
            return;
        }
        wasEncrypted = true;
    }

    auto cmd = kcb.read();
    LOG_INF("%s: kcb=%u, cmd=%u, len=%u", __func__, kcb.id(), cmd, kcb.size());

    // require must be encrypted??

    // grab protocol passthru before switch
    if (cmd == ProtocolPassthru_DISCRIMINATOR)
    {
        auto id = kcb.read();
        auto fragments = kcb.read();    // starts at 1
        auto frag_index = kcb.read();   // starts at zero
        auto length     = kcb.read() << 8;
             length    |= kcb.read();
        if (id == 1)
            process_z9lockio(kcb);
        else
            LOG_ERR("%s: ProtocolPassthru: unknown protocol: %d", __func__, id);
        return;
    }

    // process according to recived command
    auto& m  = modelInfo;
    switch (cmd)
    {
        case BoardInfo_DISCRIMINATOR:
        {
            // process BoardInfo (just check model #)
            kcb.skip(3);
            auto model = kcb.peek();
            if (model != m.z9ioModel)
            {
                LOG_ERR("%s: invalid model: %d (expeced %d)", __func__, model, m.z9ioModel);
                break;
            }
            // NB: sample BoardInfo shows all inputs/outputs enabled

            // generate responses
            send(gen_boardStatusQuery(*this));

            // enable all digial inputs (first is zero)
            for (int i = 0; i <= MAX_INPUTS; ++i)
                send(gen_digitalInConfig (*this, i, true));

            // enable all analog inputs (first is zero)
            for (int i = 0; i <= MAX_ANALOG_INPUTS; ++i)
                send(gen_analogInConfig (*this, i, true));

            // generate bit masks for config
            uint32_t input{}, output{}, analog{};

            for (int i = 0; i <= MAX_INPUTS; ++i)
                input |= 1 << i;
            for (int i = 0; i <= MAX_ANALOG_INPUTS; ++i)
                analog |= 1 << i;
            for (int i = 0; i <= MAX_OUTPUTS; ++i)
                output |= 1 << i;

            //send(gen_config(*this, input, output, analog));
            send(gen_appKeyExchange (*this, ApplicationEncryptionKeyExchangeType_PUBLIC_KEY_REQ));
            break;
        }

        case RawRead_DISCRIMINATOR:
        {
            // process RawRead
            uint8_t data[kcb.length()], *p = data;
            while (!kcb.empty())
                *p++ = kcb.read();
            
            LOG_INF("%s: RawRead idx=%d, trim=%d, bytes=%d", __func__, data[0], data[1], data[2]);
            LOG_HEXDUMP_INF(&data[3], data[2], "RawRead data=");

            // applicationLogic->rawCred
            break;
        }

        case RawKey_DISCRIMINATOR:
        {
            // process RawKey
            auto idx = kcb.read();
            auto key = kcb.read();

            LOG_INF("%s: RawKey idx=%d, key=%02x", __func__, idx, key);

            // applicationLogic->rawCred
            break;
        }

        case DigitalRead_DISCRIMINATOR:
        {
            // process DigitalRead
            auto idx   = kcb.read();
            auto raw   = kcb.read();
            auto value = kcb.read();

            LOG_INF("%s: DigitalRead idx=%d, raw=%02x, value=%02x", __func__, idx, raw, value);

            // applicationLogic->rawCred
            break;
        }

        case AnalogRead_DISCRIMINATOR:
        {
            // process AnalogRead
            auto idx   = kcb.read();
            uint32_t raw;
            raw  = kcb.read() << 8;
            raw += kcb.read();
            auto value = kcb.read();

            LOG_INF("%s: DigitalRead idx=%d, raw=%d, value=%02x", __func__, idx, raw, value);

            // applicationLogic->rawCred
            break;
        }
            
        case ApplicationEncryptionKeyExchange_DISCRIMINATOR:
        {
            // dump the packet
            auto len = kcb.length();
            uint8_t data[kcb.length()], *p = data;
            while (!kcb.empty())
                *p++ = kcb.read();
            
            // dump the packet
            LOG_INF("%s: App KeyX, len = %d", __func__, len);
            LOG_HEXDUMP_INF(data, len, "AppKeyX data=");

            // validate type & length
            if (data[0] == ApplicationEncryptionKeyExchangeType_PUBLIC_KEY_RESP && data[1] == 33)
            {
                std::memcpy(raw_lock_public_key, &data[2], data[1]);
            }
            else if (data[0] == ApplicationEncryptionKeyExchangeType_KEY_AGREEMENT_RESP && data[1] == 16)
            {
                std::memcpy(raw_application_key, &data[2], data[1]);
            }
            else
            {
                LOG_ERR("%s: App KeyX: invalid response: %02x %02x", __func__, data[0], data[1]);
            }
            break;
        }

        case EncryptionKeyExchange_DISCRIMINATOR:
            // processed by link level
        default: 
            LOG_ERR("%s: Unexpected packet: cmd=%u, len=%u", __func__, cmd, kcb.length());
            break;
    }
}


void Z9IO_Logic::send(KCB& kcb)
{
    // encrypt if required

    // place to link xmit queue
    Z9IO_Link::get(_unit).xmit(kcb);
}


void Z9IO_Logic::recv(KCB& kcb)
{
    // add kcb to queue
    sys_slist_append(&recv_queue, &kcb.data.queue[0]);
    // schedule processing
    k_work_submit(&recv_work);
}

void Z9IO_Logic::recv_fn(struct k_work *w)
{
    auto self = CONTAINER_OF(w, Z9IO_Logic, recv_work);

    auto node_p = sys_slist_get(&self->recv_queue);
    if (node_p)
    {
        auto c_kcb  = CONTAINER_OF(node_p, kcb_t, queue[0]);
        auto kcb_p  = reinterpret_cast<KCB *>(c_kcb);
        self->process_recv(*kcb_p);
        delete kcb_p;
    }
}