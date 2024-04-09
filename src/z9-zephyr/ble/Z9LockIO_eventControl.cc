
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

static void Z9LockIO_gen_evt_batch(bool priority);

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

    if (p->sendOneBatch)
        Z9LockIO_gen_evt_batch(p->priority);
}

static void Z9LockIO_gen_evt_batch(bool priority)
{
    static constexpr auto discriminator = LockEvtBatch::DISCRIMINATOR;
    static constexpr auto maxEvents     = 5;

    // packet is encrypted & to NOC
    auto& kcb = *Z9LockIO_createBundleHeader(discriminator);

    // packet data is priority + count + [count LockEvts]
    kcb.write(priority);
    kcb.write(0);                   // placeholder for count of events
    auto countOffset = kcb.size();  // remember where count stored

    auto writer =[&kcb](uint8_t c) { kcb.write(c); };
    auto count = LockEventDb::instance().extract(priority, maxEvents, writer);
    if (count == 0)
        delete &kcb;
    else
    {
        kcb.seek(countOffset-1);
        kcb.poke(count);
        {
            printk("%s: wrote %u at %u\n", __func__, count, countOffset);
            kcb.top();
            printk("%s: buffer: ", __func__);
            auto i = kcb.size();
            while(i--)
                printk("%02x ", kcb.read());
            printk("\n");
        }
        kcb.seek(kcb.length());
        Z9LockIO_sendBundle(kcb);
    }
}