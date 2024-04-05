
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"
#include "Z9LockIO_protocol.h"
#include "Z9Crypto_gcm.h"


using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

uint64_t mobileID;
uint32_t unid;
uint8_t  schedMask;
gcm_key_id_t mobile_key_handle;

static void Z9LockIO_gen_challenge();

void Z9LockIO_credAuthorization(KCB& kcb, uint8_t encrypted)
{
    // validate encrypted = NOC

    // parse & save cred
    uint8_t buf[16];            // big enough for shared secret
    kcb.readN(buf, sizeof(uint64_t));
    mobileID = read64(buf);

    kcb.readN(buf, sizeof(uint64_t));
    auto lockID   = read64(buf);

    // read 4 bytes of UNID (for grant)
    kcb.readN(buf, sizeof(uint32_t));
    unid = read32(buf);

    kcb.skip(50);
    auto numCredBytes = kcb.read();
    kcb.skip(numCredBytes);
    kcb.skip(4);        // skip over pi
    
    auto n = kcb.read() << 8;
    schedMask = n + kcb.read();
    auto numSchedUnids = kcb.read(); 
    kcb.skip(numSchedUnids * 4);    // skip unids
    auto sharedSecretLen = kcb.read();
    kcb.readN(buf, sharedSecretLen);
 
    // save mobile key:
    // XXX may need to destroy old key for memory leak
    Z9Crypto_gcmSetKey(mobile_key_handle, buf, sharedSecretLen);

    printk("%s: received CredAuthorization: lock: %llu, mobile: %llu, secret: %d bytes\n",
            __func__, lockID, mobileID, sharedSecretLen);
    Z9LockIO_gen_challenge(); 
}


static void Z9LockIO_gen_challenge()
{
    static constexpr auto discriminator = LockMobileBleChallengeNonce::DISCRIMINATOR;
    static constexpr auto challengeLen  = 16;

    // packet is unencrypted & to intermediary
    auto& kcb = *Z9LockIO_createBundleHeader(discriminator, false, true);
    kcb.write(challengeLen);
    kcb.load(Z9Crypto_random(), challengeLen);
    Z9LockIO_sendBundle(kcb);
}
