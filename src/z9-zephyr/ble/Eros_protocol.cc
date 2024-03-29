
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
//#include "Z9LockIO_protocol.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9Crypto_gcm.h"
#include "KernelCharacterBuffer.h"
#include "Z9IO_Logic.h"
#include "z9_ble_driver.h"

#include <cstring>
#include <zephyr/kernel.h>

#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include "mbedtls/sha256.h"

//#include "Z9Message.h"
//#include "ProtocolMetadata.h"
//#include "Z9Serialize.h"
//#include "variableArray.h"

using namespace z9;
//using namespace z9::protocols;
//using z9::protocols::z9lockio::getFormatter;

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


// receive from BLE driver
static bt_conn *eros_conn;
static uint8_t passthru_channel;

void eros_ble_recv(bt_conn *conn, const void *buf_v, uint16_t buf_len)
{
    auto buf = static_cast<const uint8_t *>(buf_v);
    eros_conn = conn;
    
    // received eros pkt from mobile
    // only want unencrypted passthru
    if (*buf++ != 0x82) return;
    if (*buf++ != 0x0b) return;

    auto leaf_len = *buf++ << 8;
         leaf_len += *buf++;

    ++buf;

    if (leaf_len != (buf_len - 5))
    {
        printk("%s: eros leaf length: %u incorrect (expected %u)\n", __func__, leaf_len, buf_len - 5);
        return;
    }

    // eros passthru packet
    passthru_channel = *buf++;
    if (*buf++ != 0) return;        // must be first fragment
    if (*buf++ != 1) return;        // must be only fragment 

    auto len = *buf++ << 8;
         len += *buf++;

    if (len != (leaf_len - 5))
    {
        printk("%s: passthru message length: %u incorrect (expected %u)\n", 
                __func__, len, leaf_len - 5);
        return;
    }

    // put message in a KCB
    auto& kcb = *KCB_NEW(16);        // Z9IO headroom
    while (len--) kcb.write(*buf++);
#ifndef CONFIG_Z9_READER
    z9lockio_recv(kcb.top());
#else
    send_passThru(kcb);
#endif
}
    
static constexpr auto z9_bundle_header_len = 41;
static constexpr auto z9_opaque_header_len = 5 + 2 + 12 + 16;

// send to BLE driver 
void eros_passthru_send(uint8_t passthru_id, uint8_t *buf, uint8_t len)
{
    printk("%s: sending %u bytes\n", __func__, len + 10);
    static uint8_t seq_no;
    // NB: there is 10 bytes of room in header
    *--buf = len;
    *--buf = len >> 8;
    *--buf = 1;
    *--buf = 0;
    *--buf = passthru_id;

    // now the EROS header
    // modify LEN to include 7 passthru bytes and 1 seq# byte
    len += 6;
    *--buf = ++seq_no;
    *--buf = len;
    *--buf = len >> 8;
    *--buf = 0x0b;
    *--buf = 0x82;
    lock_service_send(eros_conn, buf, len + 4);
}

void eros_send(KCB& kcb)
{
    static constexpr auto eros_headRoom = 12;
    uint8_t buf[400];

    auto *p = &buf[eros_headRoom];
    auto first = p;
    auto len = kcb.length();
    while (len--) *p++ = kcb.read();
    len = p - first;
    p = first;
    printk("%s: sending %u bytes: ", __func__, len);
    while (len--) printk("%02x", *p++);
    printk("\n");
    eros_passthru_send(1, first, p - first);
}