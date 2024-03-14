
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9Crypto_gcm.h"
#include "EventDb.h"

#include <cstring>
#include <zephyr/kernel.h>

//#include <psa/crypto.h>
//#include <psa/crypto_extra.h>
//#include "mbedtls/sha256.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
#include "Z9LockIO_protocol.h"


using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

// generate eros headers: 
// first header is `leaf_ble_msg_t` which is 5 bytes
// begins with 0x82 0b [len16] [++n] ...data

// data next contains `passthru_value_t` which is 5 bytes
// passthru_id (?? 0 = module, 1 = host, 2 = echo, ...)
// fragment index (from zero)
// fragment total (from 1)
// fragment bytes (16 bits, network order)

// Z9LockIO header
// 2 bytes: z9
// 2 bytes: length
// 1 byte : descriminator
// data

// Z9Lock discriminators: LockIdent = 0, LockIdentResult = 1,
//      LockBUndleHeader = 40, LockPublicKeyExchange = 41,
//      LockAccessReq = 37, LockAccessResp = 38


// LockIdent:
// 2 bytes: protocol rev
// 1 byte : type of device
// 8 bytes: ident
// 1 byte : model #
// 1 byte : brand code
// 2 bytes: firmware rev
// 1 byte : licensed

// AccessReq:
// 2 bytes: request ID (incrementing)
// 8 bytes: mobileID (may be redundant)

// AccessRsp:
// 2 bytes: requestId
// 2 bytes: errorCode
// 1 byte:  granted

// LockBundleHeader
// 1 byte : origin
// 1 byte : intermediary
// 1 byte : destination
// 8 bytes: origin ID
// 8 bytes: intermediary ID
// 8 bytes: destination ID
// 7 bytes: expires (time-to-second) UTC
// 1 byte : opaque: if true, following pkts encrypted
// 1 byte : packets that follow: from 1

// From Mobile to Lock
// Origin = Mobile(3), Dest = Lock(1)
// OriginID: mobileID = 9999 (270F)
// LockID : DEVICE_ID (32-bit from AdVert)
// 


std::tuple<uint8_t, uint8_t const *>Z9Lock_ECDH(uint8_t const *msg);

// *** HEADER LENGTHS ***    
static constexpr auto eros_header_len = 10;
static constexpr auto z9_bundle_header_len = 41;
static constexpr auto z9_opaque_header_len = 5 + 2 + 12 + 16;

#if 0
uint8_t  sourceType, interType, destType;
uint64_t sourceID  , interID  , destID;
bool    opaque;
uint8_t packetCount;
uint16_t requestID;
uint64_t mobileID;
uint32_t unid;
uint16_t schedMask;
#endif
uint64_t read64(uint8_t *p)
{
    uint64_t value{};
    for (auto n = sizeof(value); n--; )
    {
        value <<= 8; 
        value += *p++;
    }
    return value;
}

uint32_t read32(uint8_t *p)
{
    uint32_t value{};
    for (auto n = sizeof(value); n--; )
    {
        value <<= 8; 
        value += *p++;
    }
    return value;
}
uint8_t *write64(uint8_t *p, uint64_t value)
{
    p += 8;
    for (auto n = sizeof(uint64_t); n--; value >>= 8)
        *--p = value;
    return p + 8;
}

#if 0
static uint8_t *z9lockio_create_bundle_header(uint8_t *p, bool toInter = false, bool opaque = false, uint8_t count = 1)
{
    auto first = p;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockBundleHeader::DISCRIMINATOR;
    if (!toInter)
    {
        *p++ = destType;
        *p++ = interType;
        *p++ = sourceType;
        p = write64(p, destID);
        p = write64(p, interID);
        p = write64(p, sourceID);
    }
    else
    {
        *p++ = destType;
        *p++ = 0;       // NONE
        *p++ = interType;
        p = write64(p, destID);
        p = write64(p, 0);
        p = write64(p, interID);
    }
    std::memset(p, 0, 7);
    p += 7;
    *p++ = opaque;
    *p++ = count;
    auto len = p - first;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: length = %u\n", __func__, len);
    return p;
}

static uint8_t *z9lockio_create_opaque(uint8_t *p, uint16_t bytes, gcm_key_id_t& key)
{
    // allocate our room
    auto msg = p - z9_opaque_header_len;
    msg[0] = 'z';
    msg[1] = '9';
    msg[2] = (bytes + z9_opaque_header_len) >> 8;
    msg[3] = (bytes + z9_opaque_header_len);
    msg[4] = LockOpaqueContent::DISCRIMINATOR;
    msg[5] = (bytes + 28) >> 8;
    msg[6] = (bytes + 28);
    auto iv = msg + 7;
    auto tag = iv + 12;
    std::memcpy(iv, Z9Crypto_random(), 12);
    Z9Crypto_gcm_encrypt(key, iv, {}, 0, p, bytes, tag, 16);
    return msg;
}

variableArray<16> mobileSharedSecret;
uint8_t ble_challenge[16] = "Z9 Challenge";

static void z9lockio_gen_challenge()
{
    static uint8_t buf[100];

    auto access_rsp = z9lockio_create_bundle_header(&buf[eros_header_len], true);
    auto p = access_rsp;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockMobileBleChallengeNonce::DISCRIMINATOR;
    *p++ = sizeof(ble_challenge);
    std::memcpy(p, ble_challenge, sizeof(ble_challenge));
    p += sizeof(ble_challenge);
    
    auto len = p - access_rsp;
    *len_p++ = len >> 8;
    *len_p = len;
    
    printk("%s: challenge length = %u\n", __func__, len);
    auto total = p - &buf[eros_header_len];
    eros_passthru_send(passthru_channel, &buf[eros_header_len], total);
}

extern bool access_button_state;
static void z9lockio_gen_access_rsp(LockEvtCode result)
{
    static uint8_t buf[200];

    // generate an event
    auto evt  = EVT(result, mobileGrant);
    auto xtra = LockEvtContent_CredUnid {
            .credTechnology = LockCredTechnology_BLUETOOTH_Z9_WAVELYNX,
            .credUnid       = unid };
    LockEventDb::instance().save(evt, xtra);

    // leave room for opaque + 1x bundler header + eros
    auto header_space = eros_header_len + 1 * z9_bundle_header_len + z9_opaque_header_len;

    auto begin_rsp = &buf[header_space];
    auto access_rsp = z9lockio_create_bundle_header(begin_rsp);
    auto p = access_rsp;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockAccessResp::DISCRIMINATOR;
    *p++ = requestID >> 8;
    *p++ = requestID;
    //uint16_t error = access_button_state ? 42 : 0;
    auto error = 0;
    *p++ = error >> 8;
    *p++ = error;
    *p++ = (result == LockEvtCode_DOOR_ACCESS_GRANTED);
    auto len = p - access_rsp;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: rsp length = %u\n", __func__, len);
#if 1
    // have unencrypted response. Add prototype `opaque` header & encrypt in place
    auto opaque_rsp = z9lockio_create_opaque(begin_rsp, p - begin_rsp, mobile_key_handle);

    // allocate space to prepend bundle header
    auto msg = &opaque_rsp[-z9_bundle_header_len];
    z9lockio_create_bundle_header(msg, false, true);

#else
    auto msg = begin_rsp;
#endif
    eros_passthru_send(passthru_channel, msg, p - msg);
}

// defaults: unencrypted & "to-NOC"
KCB z9lockio_create_bundle_header(bool toInter = false, bool opaque = false, uint8_t count=1)
{
    static constexpr uint8_t zeros[8] = {};
    // allow room for EROS header
    const auto headRoom = xxx;
    KCB kcb = kcb_alloc(headRoom);

    kcb.put('z').put.('9');
    kcb.put(LockBundlerHeader::MAX_SERIALZED_LEN >> 8);
    kcb.put(LockBundlerHeader::MAX_SERIALZED_LEN);
    kcb.put(LockBundleHeader::DISCRIMINATOR);
    
    if (!toInter)
    {
        kcb.put(destType).put(interType).put(sourceType);
        kcb.putN(destID  , sizeof(destID));
        kcb.putN(interID , sizeof(interID));
        kcb.putN(sourceID, sizeof(sourceID));
    }
    else
    {
        kcb.put(destType).put(0).put(interType);
        kcb.putN(destID , sizeof(destID));
        kcb.putN(zeros  , sizeof(uint64_t));
        kcb.putN(interID, sizeof(interID));
    }
    
    // 7 bytes of zero??
    kcb.putN(zeros, 7);
    kcb.putN(opaque).put(count);

    // if opaque, add room for opaque packet
    if (opaque)
    {
        LockOpaqueContent&& hdr;
        
        kcb.put('z').put('9');
        kcb.putN(zeros, 2);
        kcb.put(hdr.DISCRIMINATOR);
        kcb.skip(sizeof(hdr.count) + sizeof(hdr.iv) + sizeof(hdr.tag));
    }

    // now put start of next header
    kcb.put('z').put.['9'];
    kcb.putN(zeros, 2);     // length to be filled in later
    
    return kcb;
}

void z9lockio_send_bundle(KCB& kcb, uint16_t headerOffset, bool isOpaque)
{
    // calculate length of packet
    auto packetLength = kcb.length() - headerLength;

    // NB: know header in first block is contiguous memory
    auto p = kcb.getP(headerOffset);
    *p++ = packetLength >> 8;
    *p++ = packetLength;

    // if encrypted, backup to beginning 

}

void z9lock_gen_evt_batch(uint8_t priority)
{
    uint8_t buf[200] = {}, *p;
    auto writer = [&p](uint8_t c) { *p++ = c; };
    
    // leave room for opaque + 1x bundler header + eros
    auto header_space = eros_header_len + 1 * z9_bundle_header_len + z9_opaque_header_len;

    auto begin_rsp = &buf[header_space];
    auto rsp_payload = z9lockio_create_bundle_header(begin_rsp);
     p = rsp_payload;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    
    *p++ = LockEvtBatch::DISCRIMINATOR;
    *p++ = priority;
    auto count_p = p++;     // `writer` has side effects
    *count_p = LockEventDb::instance().extract(priority, 32, writer);

    // if no pending events, just ignore
    if (!*count_p) return;
    
    auto len = p - rsp_payload;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: payload length = %u\n", __func__, len);
#if 1
    // have unencrypted response. Add prototype `opaque` header & encrypt in place
    auto opaque_rsp = z9lockio_create_opaque(begin_rsp, p - begin_rsp, noc_key_handle);

    // allocate space to prepend bundle header
    auto msg = &opaque_rsp[-z9_bundle_header_len];
    z9lockio_create_bundle_header(msg, false, true);

#else
    auto msg = begin_rsp;
#endif
    eros_passthru_send(passthru_channel, msg, p - msg);
}

void z9lock_gen_db_resp(uint64_t const& requestID)
{
    uint8_t buf[200] = {}, *p;
    
    // leave room for opaque + 1x bundler header + eros
    auto header_space = eros_header_len + 1 * z9_bundle_header_len + z9_opaque_header_len;

    auto begin_rsp = &buf[header_space];
    auto rsp_payload = z9lockio_create_bundle_header(begin_rsp);
     p = rsp_payload;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    
    *p++ = LockDbChangeResp::DISCRIMINATOR;
     p = write64(p, requestID);
    *p++ = 0;       // error code (16-bits)
    *p++ = 0;
    
    auto len = p - rsp_payload;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: payload length = %u\n", __func__, len);
    printk("%s: payload = ", __func__);
    auto s     = begin_rsp;
    auto s_len = p - s;
    while(s_len--) printk("%02x", *s++);
    printk("\n");
#if 1
    // have unencrypted response. Add prototype `opaque` header & encrypt in place
    auto opaque_rsp = z9lockio_create_opaque(begin_rsp, p - begin_rsp, noc_key_handle);

    // allocate space to prepend bundle header
    auto msg = &opaque_rsp[-z9_bundle_header_len];
    z9lockio_create_bundle_header(msg, false, true);

#else
    auto msg = begin_rsp;
#endif
    eros_passthru_send(passthru_channel, msg, p - msg);
}

static void recv_trampoline(k_work *work);
static void do_z9lockio_recv(uint8_t *buf, uint16_t buf_len);

struct ble_recv_message
{
    K_WORK_DEFINE(recv_work, recv_trampoline);
    uint16_t  buf_len;
    uint8_t   buf[420];
};

static constexpr auto BLE_RECV_QUEUE_SIZE = 20;
static ble_recv_message ble_recv_queue[BLE_RECV_QUEUE_SIZE], *ble_queue_ptr = ble_recv_queue;

static void recv_trampoline(k_work *work)
{
    auto self = CONTAINER_OF(work, ble_recv_message, recv_work);
    do_z9lockio_recv((uint8_t *)self->buf, self->buf_len);
} 

static void z9lockio_recv(const uint8_t *buf, uint16_t buf_len)
{
    // get next circular queue location
    auto p = ble_queue_ptr++;
    if (ble_queue_ptr - ble_recv_queue == BLE_RECV_QUEUE_SIZE)
        ble_queue_ptr = ble_recv_queue;

    // just overwrite if busy
    // print message if overwriting
    if (p->recv_work.flags & K_WORK_MASK)
        printk("%s: overwriting previous message", __func__);

    p->buf_len = buf_len;
    memcpy(p->buf, buf, buf_len);
    k_work_submit(&p->recv_work);
}

#endif

void z9lockio_recv(KCB& kcb)
{
    int key = 0;

    printk("%s: Processing... (buf_len=%u)\n", __func__, kcb.length());

    // iterate over entire message
    while (kcb.length())
    {
        // validate z9lockio header
        if (kcb.read() != 'z') return;
        if (kcb.read() != '9') return;

        auto len  = kcb.read() << 8;
             len += kcb.read();;

        auto discriminator = kcb.read();
        len -= 5;       // remove Z9LockIO Header length from count

        printk("%s: discriminator: %u, len = %u\n", __func__, discriminator, len);
        switch (discriminator)
        {
            default:
                printk("%s: ignoring discriminator: %u\n", __func__, discriminator);
                kcb.skip(len);
                break;
            
            case LockBundleHeader::DISCRIMINATOR:
                Z9LockIO_bundleHeader(kcb, key);
                break;

            case LockOpaqueContent::DISCRIMINATOR:
                Z9LockIO_opaqueContent(kcb, key);
                break; 
            
            case LockEvtControl::DISCRIMINATOR:
                Z9LockIO_eventControl(kcb, key);
                break;
            
            case LockPublicKeyExchange::DISCRIMINATOR:
                Z9LockIO_keyExchange(kcb, key);
                break;
       
            case LockDbChange_Config::DISCRIMINATOR:
            case LockDbChange_Hol::DISCRIMINATOR:
            case LockDbChange_Sched::DISCRIMINATOR:
            case LockDbChange_SchedPolicy::DISCRIMINATOR:
                Z9LockIO_dbChange(kcb, key);
                break;

            case LockAccessReq::DISCRIMINATOR:
                Z9LockIO_accessReq(kcb, key);
                break;

            case LockCredAuthorization::DISCRIMINATOR:
                Z9LockIO_credAuthorization(kcb, key);
                break;

        }   // switch
    }       // while
    delete &kcb;        // release buffer
}           // function

