
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
#if 0
uint8_t  sourceType, interType, destType;
uint64_t sourceID  , interID  , destID;
bool    opaque;
uint8_t packetCount;
#endif

LockBundleHeader lastHeader;
    
// constants for dealing with serialized packets
static constexpr auto bundleSerializedLen          = 36;        // plus packet
static constexpr auto opaqueSerializedLen          = 2 + 12 + 16;
static constexpr auto packetSerializedLen          = 5;
static constexpr auto packetSerializedLenOffset    = 2;
static constexpr auto bundleSerializedDestOffset   = 2;
static constexpr auto bundleSerializedOpaqueOffset = 35;
    

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

// create an outgoing "LockBundleHeader" optionally followed by an "OpaqueContent" and a 
// second LockBundleHeader. Fixup counts, etc, in `Z9LockIO_sendBundle()`
KCB& Z9LockIO_createBundleHeader(uint8_t discriminator, bool opaque, bool toIntermediate, uint8_t count)
{
    // XXX examine "alignment" to see if anything falls out...
    static constexpr auto headerRoom = 10;      // Z9IO header requirements (none required for Eros)
    auto& kcb = *KCB_NEW(headerRoom); 

    // For serialize: need writer
    using T = LockBundleHeader;
    auto proto = getFormatter<T>();
    auto writer = [&kcb](uint8_t c) { kcb.write(c); };
#if 0 
    // deserialize right into `lastHeader`
    auto p = &lastHeader;
    proto->deserialize(reader, static_cast<uint8_t *>((void *)p), sizeof(T), sizeof(T));
#endif

    // Add Z9LockIO protocol header (discriminator + size)
    auto addPacketHeader = [&kcb](uint8_t discriminator, uint16_t length = 0)
        {
            length += packetSerializedLen;
            kcb.write('z').write('9');
            kcb.write(length >> 8).write(length);
            kcb.write(discriminator);
        };

    // start by swapping addresses in header
    LockBundleHeader bundle = lastHeader, *p = &bundle;

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

    p->opaque = opaque;
    p->packetCount = opaque ? 1 : count;    // should this be 1 for opaqueContent

    // write first LockBundleHeader packet
    addPacketHeader(LockBundleHeader::DISCRIMINATOR, bundleSerializedLen);
    // XXX needs to be "seralize" routine
    kcb.load(p, bundleSerializedLen);

    // if packet is opaque, add more headers
    if (opaque)
    {
        // need to add room for LockOpaqueContent + second LockBundleHeader
        addPacketHeader(LockOpaqueContent::DISCRIMINATOR);
        kcb.load(p, opaqueSerializedLen);   // NB: unitialized data that will be overwritten
        p->opaque = {};             // embedded packets are not encrypted
        p->packetCount = count;
        addPacketHeader(LockBundleHeader::DISCRIMINATOR, bundleSerializedLen);
    
        // XXX needs to be "seralize" routine
        kcb.load(p, bundleSerializedLen);
    }

    // add new header for actual DISCRIMINATOR
    addPacketHeader(discriminator);
    return kcb;
}

// fill in bundle header sizes, encrypt as required, and send onward
void Z9LockIO_sendBundle(KCB& kcb)
{
    // see if opaque: if so, we need to encrypt
    kcb.top().seek(packetSerializedLen + bundleSerializedOpaqueOffset);
    auto isOpaque = kcb.peek();

    // if clear, just need to set second packet length
    static constexpr auto firstPacketLen  = packetSerializedLen + bundleSerializedLen;
    auto secondPacketLen = kcb.size() - firstPacketLen;
    kdb.seek(firstPacketLen + packetSerializedLenOffset);
    kcb.put(secondPacketLen >> 8).put(secondPacketLen);
    
    // if opaque, need to set final packet length, as well as encrypted length
    if (isOpaque)
    {
        // choose encryption based on destination
        kcb.seek(packetSerializedLen + bundleSerializedDestOffset);
        auto dest = kcb.peek();

        // assume data format after initial bundle header is OpaqueContent, BundleHeader, BusinessPacket
        auto businessPacketOffset = (packetSerializedLen * 3) + 
                                    (bundleSerializedLen * 2) +
                                     opaqueSerializedLen;
        auto businessPacketLen = kcb.size() - businessPacketOffset;
        kcb.seek(businessPacketOffset + packetSerializedLen);
        kcb.put(businessPacketLen >> 8).put(businessPacketLen);

        // now store encrypted packet length
        auto encryptedBytes = secondPacketLen - (packetSerializedLen + opaqueSerializedLen);
        kcb.seek(firstPacketLen + packetSerializedLen);
        kcb.put(encryptedBytes >> 8).put(encryptedBytes);

        // now encrypt. Conventiently KCB positioned at IV, so just pass to KCB encrypt
        GcmCrypto_encrypt_KCB(key, kcb);
    }

    // packet send...
}