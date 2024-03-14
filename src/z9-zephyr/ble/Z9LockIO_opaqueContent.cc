
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9LockIO_protocol.h"
#include "Settings.h"

#include "Z9Crypto_gcm_KCB.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;


void Z9LockIO_opaqueContent(KCB& kcb, uint8_t key)
{
    gcm_key_handle_t *key_p {};
    const char *keyName = "UNKNOWN KEY";
    switch (lastHeader.origin)
    {
        case LockIdentificationType_AUTHORITATIVE_SOURCE:
            key_p = &noc_key_handle;
            keyName = "NOC";
            break;
        case LockIdentificationType_MOBILE:
            key_p = &mobile_key_handle;
            keyName = "MOBILE";
            break;
        case LockIdentificationType_HUB_CONTROLLER:
        case LockIdentificationType_LOCK:
        case LockIdentificationType_NONE:
        default:
            break;
    }

    printk("%s: Processing OpaqueContent %u bytes using key: %s\n", __func__, kcb.length(), keyName);
    //printk("%s: CurrentPosition = %u\n", __func__, kcb.curPos());
    
    // "count" is first two bytes -- ignore & assume to end of KCB
    kcb.skip(2);
    kcb.consumeHeadroom(kcb.curPos());      // make front beginning of buffer
    printk("%s: Length =%u, CurrentPosition = %u\n", __func__, kcb.length(), kcb.curPos());
    auto status = Z9Crypto_gcm_decrypt_KCB(*key_p, kcb);

    if (status)
        printk("%s: Decrypt failed: %s\n", __func__, status);
}    