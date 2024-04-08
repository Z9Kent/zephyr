
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9LockIO_protocol.h"
#include "Z9Crypto_gcm_KCB.h"
#include "Settings.h"       // noc_key_handle

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"
#include "Z9IO_Logic.h"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

//static void z9lockio_gen_challenge(void *arg);
#if 0
uint8_t  sourceType, interType, destType;
uint64_t sourceID  , interID  , destID;
bool    opaque;
uint8_t packetCount;
#endif

LockBundleHeader lastHeader;
    
// constants for dealing with serialized packets
static constexpr auto bundleSerializedLen          = 36;        // excludes packet
static constexpr auto opaqueSerializedLen          = 2 + 12 + 16;
static constexpr auto packetSerializedLen          = 5;
static constexpr auto packetSerializedLenOffset    = 2;
static constexpr auto bundleSerializedDestOffset   = 2;
static constexpr auto bundleSerializedOpaqueOffset = 35;
    
// XXX examine "alignment" to see if anything falls out...
static constexpr auto z9ioHeaderSize  = 16;      // Z9IO header requirements (none required for Eros)
static constexpr auto clearHeaderSize =  2 * packetSerializedLen + bundleSerializedLen;
static constexpr auto opaqueHeaderSize = 3 * packetSerializedLen + 
                                            2 * bundleSerializedLen +
                                            1 * opaqueSerializedLen;


void Z9LockIO_bundleHeader(KCB& kcb, uint8_t key)
{
    using T = LockBundleHeader;
    auto proto = getFormatter<T>();
    auto reader = [&kcb]() { return kcb.read(); };
    
    // deserialize right into `lastHeader`
    auto p = &lastHeader;
    proto->deserialize(reader, static_cast<uint8_t *>((void *)p), sizeof(T), sizeof(T));
    
    printk("Bundle: source=%llu, dest=%llu, opaque=%d, packetCount=%d\n",
        p->originId, p->destinationId, p->opaque, p->packetCount);
}    

// create an outgoing message that will have a bundle header prepended before transmsission.
// second LockBundleHeader. Fixup counts, etc, in `Z9LockIO_sendBundle()`
KCB *Z9LockIO_createBundleHeader(uint8_t discriminator, bool opaque, bool toIntermediate, uint8_t count)
{
    // preferences stored in KCB
    static constexpr auto preferencesSize = 4;

    // NB: Headers for opaque case don't fit in MBUF header. 
    //     prepend opaque headers in `_sendBundle`
#if 0
    // validate headers all fit in KCB base page
    static_assert((opaqueHeaderSize + z9ioHeaderSize) 
                    < (sizeof(KernelBuffer) - sizeof(kcb)),
                "Header won't fit in KCB base page");
    
    // select appropriate headroom in KCB
    auto headRoom = z9ioHeaderSize + (opaque ? opaqueHeaderSize : clearHeaderSize);

#else
    // validate headers all fit in KCB base page
    static_assert((clearHeaderSize + z9ioHeaderSize) 
                    < (sizeof(KernelBuffer) - sizeof(kcb)),
                "Header won't fit in KCB base page");
    
    auto headRoom = z9ioHeaderSize + clearHeaderSize;
#endif
    auto& kcb = *KCB_NEW(headRoom + preferencesSize); 

    // record preferences
    kcb.write(discriminator).write(opaque);
    kcb.write(toIntermediate).write(count);

    // fixup in `sendBundle()`
    return &kcb;
}

// fill in bundle header sizes, encrypt as required, and send onward
void Z9LockIO_sendBundle(KCB& kcb)
{
    auto prependPacketHeader = [&kcb](uint8_t discriminator, uint16_t len)
        {
            auto p = kcb.allocHeadroom(packetSerializedLen);
            len += packetSerializedLen;
            *p++ = 'z';
            *p++ = '9';
            *p++ = len >> 8;
            *p++ = len;
            *p   = discriminator;
        };

    auto prependBundleHeader = [&kcb, &prependPacketHeader](LockBundleHeader const& hdr)
        {
            auto p = kcb.allocHeadroom(bundleSerializedLen);
            auto proto = getFormatter<LockBundleHeader>();
            auto writer = [&p](uint8_t c) { *p++ = c; };
            const void *v = &hdr;
            proto->serialize(writer, (uint8_t const *)v, bundleSerializedLen, bundleSerializedLen);
            prependPacketHeader(LockBundleHeader::DISCRIMINATOR, bundleSerializedLen);
        };

    // first retrieve preferences stored at creation
    auto discriminator  = kcb.top().pop();
    auto opaque         = kcb.pop();
    auto toIntermediate = kcb.pop();
    auto count          = kcb.pop();

    // prepare the (unencrypted) bundle header
    auto hdr = lastHeader, *p = &hdr;
    
    // swap source & destination
    std::swap(p->origin  , p->destination);
    std::swap(p->originId, p->destinationId);
    
    // if `toIntermediate`, update addresses
    if (toIntermediate)
    {
        p->destination    = p->intermediary;
        p->destinationId  = p->intermediaryId;
        p->intermediary   = {};
        p->intermediaryId = {};
    }

    p->opaque = {};             // this is clear header
    p->packetCount = count;     // should this be 1 for opaqueContent


    // prepend packet header + bundle header
    prependPacketHeader(discriminator, kcb.size());
    prependBundleHeader(*p);

    // if encryption requested, now's the time
    if (opaque && 0)
    {
        // select key based on destination
        gcm_key_handle_t *key_p {};
        const char *keyName = "UNKNOWN KEY";
        switch (p->destination)
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

        auto len = kcb.top().size();              // encrypt rest of buffer
        printk("%s: Encrypting %u bytes using key: %s\n", __func__, len, keyName);
        
        // NB: opaque headers wont fit in MBUF.
        // allocated contigous buffer & process there
    #if 0
        // routine encrypts and prepends IV + TAG 
        Z9Crypto_gcm_encrypt_KCB(*key_p, kcb); 
    #else
        // copy data to be encrypted to appropriate location in static buffer
        // temp gcm implementation only takes whole buffers
        static uint8_t output_buffer[512];
        auto iv  = &output_buffer[0];
        auto tag = &iv[12];
        auto s   = &tag[16];
        static const auto dataOffset = s - output_buffer;

        // generate a tag 
        std::memcpy(iv, Z9Crypto_random(), 12);
        
        // copy MBUF to static buffer
        kcb_headroom_t available;
        while (auto p = kcb.currentBlock(available))
        {
            std::memcpy(s, p, available);
            s += available;
        }

        std::size_t encrypted = len;
        int result = Z9Crypto_gcm_encrypt(*key_p, iv, {}, 0, &output_buffer[dataOffset], encrypted, tag, 16);

        kcb.flush(z9ioHeaderSize + clearHeaderSize);
        s = output_buffer;
        encrypted += dataOffset;
        while (encrypted--)
            kcb.write(*s++);

#endif
        kcb.push(len);
        kcb.push(len >> 8);
        prependPacketHeader(LockOpaqueContent::DISCRIMINATOR, len + opaqueSerializedLen);

        // mark "initial" bundle header as opaque with count of 1
        p->opaque = true;
        p->packetCount = 1;
    
        // prepend final pack header & send
        prependBundleHeader(*p);
    }

    // packet send...
    int n = kcb.top().size();
    printk("%s: %2d bytes: ", __func__, n);
    if (n < 0)
        n = 50;
    while (n--) printk("%02x", kcb.read());
    printk("\n");

    send_passThru(kcb);
}