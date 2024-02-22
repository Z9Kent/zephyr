
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

static void z9lockio_gen_challenge(void *arg);

void Z9LockIO_dbChange(KCB& kcb, uint8_t encrypted)
{
    uint8_t buf[sizeof(uint64_t)];
    auto requestID = read64(buf);
    printk("%s: Processing LockDbChange_Config: " PRIx64 "\n", __func__, requestID);
    //z9lock_gen_db_resp(requestID);
}

// validate 
#if 0
static void z9lockio_gen_challenge(void *arg)
{
    static uint8_t buf[100];

    auto kcb = z9lockio_create_bundle_header(0);
    LockMobileBleChallengeNonce::DISCRIMINATOR;
    sizeof(ble_challenge);
    std::memcpy(p, ble_challenge, sizeof(ble_challenge));
    p += sizeof(ble_challenge);
    
    printk("%s: challenge length = %u\n", __func__, len);
    z9lockio_send_bundle(kcb, headersize, 2);
}
#endif