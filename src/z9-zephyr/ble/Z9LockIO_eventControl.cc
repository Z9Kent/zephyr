
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

void Z9LockIO_eventControl(KCB& kcb, uint8_t key)
{
    using T = LockEvtControl;
    auto proto = getFormatter<T>();
    auto reader = [&kcb]() { return kcb.read(); };
    uint8_t scratch[128] = {};

    auto p = static_cast<T *>((void *)scratch);
    proto->deserialize(reader, scratch, sizeof(scratch), sizeof(T));
    printk("EvtControl: priority=%d, sendOneBatch=%d, start=", p->priority, p->sendOneBatch);
    printk("%d, stop=%d\n", p->consume.start.evtCode, p->consume.stop.evtCode);

    if (p->consume.start.evtCode)
        LockEventDb::instance().consume(p->priority, p->consume.start, p->consume.stop);
#if 0
    if (p->sendOneBatch)
        z9lock_gen_evt_batch(p->priority);
 #endif
}