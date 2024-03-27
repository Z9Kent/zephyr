
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include "Z9LockIO_protocol.h"
#include "Z9LockIO_ECDH.h"

#include <zephyr/kernel.h>

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

// types for this module
using T = LockPublicKeyExchange;

static void Z9LockIO_keyExchange_rsp(const uint8_t *key, uint16_t keyLength)
{
    printk("%s: keyLength: %u bytes\n", __func__, keyLength);

    // KCB prepared for protocol data
    auto& kcb = *Z9LockIO_createBundleHeader(T::DISCRIMINATOR, false);    // unencrypted, return to source

    kcb.write(keyLength);
    while (keyLength--)
        kcb.write(*key++);

    Z9LockIO_sendBundle(kcb);
}

void Z9LockIO_keyExchange(KCB& kcb, uint8_t key)
{
    // perform ECDH key derivation
    
    // read info from packet
    auto buf_len = kcb.length();
    auto key_len = kcb.read();

    // read key to local buffer (if required)
    uint8_t publicKey[key_len];
    auto key_p = kcb.readN(publicKey, key_len);

    // send/receive packet format is [length][length bytes]
    printk("%s: received Key Exchange: buf_len = %d, KeyLen = %d, KeyHdr = %x\n", __func__, buf_len, key_len, key_p[0]);

    // forward to reader (if needed) for actual key deriviation
    Z9LockIO_performECDH(Z9LockIO_keyExchange_rsp, key_p, key_len);
}
