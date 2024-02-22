
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include "Z9LockIO_protocol.h"

#include <zephyr/kernel.h>

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

static void Z9LockIO_keyExchange_rsp(const uint8_t *key, uint16_t keyLength);

void Z9LockIO_keyExchange(KCB& kcb, uint8_t key)
{
    // perform ECDH key derivation
    
    // read info from packet
    using T = LockPublicKeyExchange;

    auto buf_len = kcb.length();
    auto key_len = kcb.read();
    uint8_t publicKey[key_len], *p;
    p = kcb.readN(publicKey, key_len);

    // send/receive packet format is [length][length bytes]
    printk("%s: received Key Exchange: buf_len = %d, KeyLen = %d, KeyHdr = %x\n", __func__, buf_len, key_len, p[0]);

    // forward to reader (if needed) for actual key deriviation
    //Z9LockIO_performECDH(Z9LockIO_keyExchange_rsp, p, key_len);
}

#if 0
static void Z9LockIO_keyExchange_rsp(void *arg, const uint8_t *key, uint16_t keyLength);
{
    static uint8_t buf[100];
    printk("%s: %u bytes\n", __func__, cnt);

    // KCB prepared for protocol data
    auto kcb = z9lockio_create_bundle_header(0);    // defaults: unencrypted, to NOC
    auto headerSize = kcb.length();
    
    kcb.put(LockPublicKeyExchange::DISCRIMINATOR);
    kcb.put(keyLength);
    kcb.putN(key, keyLength);

    printk("%s: rsp length = %u\n", __func__, kcb.length());
    z9lockio_send_bundle(kcb, headersize);
}
#endif