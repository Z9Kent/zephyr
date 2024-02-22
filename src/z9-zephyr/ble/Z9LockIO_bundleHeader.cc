
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9LockIO_bundleHeader.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

//static void z9lockio_gen_challenge(void *arg);
uint8_t  sourceType, interType, destType;
uint64_t sourceID  , interID  , destID;
bool    opaque;
uint8_t packetCount;

void Z9LockIO_bundleHeader(KCB& kcb, uint8_t key)
{
    using T = LockBundleHeader;
    auto proto = getFormatter<T>();
    auto reader = [&kcb]() { return kcb.read(); };
    uint8_t scratch[128] = {};

    auto p = static_cast<T *>((void *)scratch);
    proto->deserialize(reader, scratch, sizeof(scratch), sizeof(T));
    
    sourceType  = p->origin;
    interType   = p->intermediary;
    destType    = p->destination;
    sourceID    = p->originId;
    interID     = p->intermediaryId;
    destID      = p->destinationId;
    opaque      = p->opaque;
    packetCount = p->packetCount;
    
    printk("Bundle: source=%llu, dest=%llu, opaque=%d, packetCount=%d\n",
        sourceID, destID, opaque, packetCount);
}    