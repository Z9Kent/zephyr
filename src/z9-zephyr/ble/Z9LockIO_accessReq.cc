
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
#include "Z9LockIO_protocol.h"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

static void z9lockio_gen_accessReq_rsp(uint16_t requestID, LockEvtCode result);
void Z9LockIO_accessReq(KCB& kcb, uint8_t encrypted)
{
    extern bool privacy_state;

    // validate encrypted = LOCK

    using T = LockAccessReq;
 
    uint16_t requestID  = kcb.read() << 8;
             requestID += kcb.read();

    uint8_t buf[sizeof(uint64_t)];
    kcb.readN(buf, sizeof(uint64_t));
    auto mobileID = read64(buf);

    printk("AccessReq: ID=%04" PRIx32 ", mobile=%" PRIu64 "\n", requestID, mobileID);

    LockEvtCode result = LockEvtCode_DOOR_ACCESS_GRANTED;
    if (privacy_state)
        result = LockEvtCode_DOOR_ACCESS_DENIED_DOOR_PRIVACY;
    else if (!schedMask)
        result = LockEvtCode_DOOR_ACCESS_DENIED_INACTIVE;

    z9lockio_gen_accessReq_rsp(requestID, result);
}

   //KCB *Z9LockIO_createBundleHeader(uint8_t discriminator, 
   //                             bool opaque = true, bool toIntermediate = false, uint8_t count = 1); 

static void z9lockio_gen_accessReq_rsp(uint16_t requestID, LockEvtCode result)
{
    // generate an event
    auto evt  = EVT(result, mobileGrant);
    auto xtra = LockEvtContent_CredUnid {
            .credTechnology = LockCredTechnology_BLUETOOTH_Z9_WAVELYNX,
            .credUnid       = unid };
    LockEventDb::instance().save(evt, xtra);

    // defaults work: encrypted back to sender
    static constexpr auto discriminator = LockMobileBleChallengeNonce::DISCRIMINATOR;
    auto& kcb = *Z9LockIO_createBundleHeader(discriminator);
    kcb.write(requestID >> 8);
    kcb.write(requestID);
    
    auto error = 0;
    kcb.write(error >> 8);
    kcb.write(error);
    kcb.write(result == LockEvtCode_DOOR_ACCESS_GRANTED);
    Z9LockIO_sendBundle(kcb);
}