
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

static void Z9LockIO_accessReq_rsp(const uint8_t *key, uint16_t keyLength);

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

    //z9lockio_gen_access_rsp(result);
}

#if 0
static void z9lockio_accessReq_rsp(LockEvtCode result)
{
    // generate an event
    auto evt  = EVT(result, mobileGrant);
    auto xtra = LockEvtContent_CredUnid {
            .credTechnology = LockCredTechnology_BLUETOOTH_Z9_WAVELYNX,
            .credUnid       = unid };
    LockEventDb::instance().save(evt, xtra);

    // KCB prepared for protocol data
    auto kcb = z9lockio_create_bundle_header(2);
    kcb.put(LockAccessResp::DISCRIMINATOR);
    kcb.put(requestID >> 8);
    kcb.put(requestID);
    
    auto error = 0;
    kcb.put(error >> 8);
    kcb.put(error)
    kcb.put(result == LockEvtCode_DOOR_ACCESS_GRANTED);
    
    printk("%s: rsp length = %u\n", __func__, len);
    z9lockio_send_bundle(kcb, headersize, 2);
}
#endif