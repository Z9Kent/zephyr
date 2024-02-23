
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"
#include "Z9LockIO_protocol.h"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

static void z9lock_gen_db_resp(uint64_t const& requestID);

void Z9LockIO_dbChange(KCB& kcb, uint8_t encrypted)
{
    uint8_t buf[sizeof(uint64_t)];
    auto requestID = read64(buf);
    printk("%s: Processing LockDbChange_Config: %" PRIx64 "\n", __func__, requestID);
    z9lock_gen_db_resp(requestID);
}

// validate 
static void z9lock_gen_db_resp(uint64_t const& requestID)
{
    static constexpr auto discriminator = LockDbChangeResp::DISCRIMINATOR;
    uint8_t buf[sizeof(uint64_t)];

    // packet is encrypted & to NOC
    auto& kcb = *Z9LockIO_createBundleHeader(discriminator);
    write64(buf, requestID);
    kcb.load(buf, sizeof(requestID));
    kcb.write(0).write(0);          // error code
    
    Z9LockIO_sendBundle(kcb);
}