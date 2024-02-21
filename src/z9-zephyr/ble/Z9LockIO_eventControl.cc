
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"
#include "Z9LockIO_eventControl.h"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

static void z9lockio_gen_challenge(void *arg);

void Z9LockIO_eventControl(void *arg, KCB& kcb, uint8_t encrypted)
{
    // validate encrypted = NOC

    // parse & save cred
    uint8_t uint64_buffer[sizeof(uint64_t)];
    kcb.readN(uint64_buffer, sizeof(uint64_buffer);
    mobileID = read64(uint64_buffer);

    auto mobileID = read64(&buf);
    auto lockID   = read64(&buf);
    //buf += 77;      // skip LockCred
    // read 4 bytes of UNID (for grant)
    unid = read32(&buf);

    buf += 50;      // skip to numCredBytes
    auto numCredBytes = *buf++;
    buf += numCredBytes;
    buf += 4;       // skip over pi
    auto n = *buf++ << 8;
    schedMask = n + *buf++;
    auto numSchedUnids = *buf++;
    buf += numSchedUnids * 4;       // skip unids
    auto sharedSecretLen = *buf++;
    mobileSharedSecret.set(sharedSecretLen, buf);
#if 0
    using T = LockCredAuthorization;

    auto reader = [&buf]() { return *buf++; };
    uint8_t scratch[128] = {};
    auto p = static_cast<T *>((void *)scratch);
    getFormatter<T>()->deserialize(reader, scratch, sizeof(scratch), sizeof(T));
#endif
 
    // save mobile key:
    // XXX may need to destroy old key for memory leak
    Z9Crypto_gcmSetKey(mobile_key_handle, mobileSharedSecret(), mobileSharedSecret.size());

    using IDX = meta::find_index<z9::protocols::z9lockio::FORMATS_TYPES, LockHol>;
    printk("%s: LockHol typeid is %u\n", __func__, IDX::value); 
    printk("%s: received CredAuthorization: lock: %llu, mobile: %llu, secret: %d bytes\n",
            __func__, mobileID, lockID, mobileSharedSecret.size());
    z9lockio_gen_challenge(arg); 
}

static void z9lockio_gen_challenge(void *arg)
{
    static uint8_t buf[100];

    auto kcb = z9lockio_create_bundle_header(0);
    LockMobileBleChallengeNonce::DISCRIMINATOR;
    sizeof(ble_challenge);
    std::memcpy(p, ble_challenge, sizeof(ble_challenge));
    p += sizeof(ble_challenge);
    
    printk("%s: challenge length = %u\n", __func__, len);
    z9lockio_send_bundle(kcb, headersize, 2);
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