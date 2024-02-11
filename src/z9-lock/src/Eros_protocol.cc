
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9Crypto.h"
#include "EventDb.h"

#include <cstring>
#include <zephyr/kernel.h>

#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include "mbedtls/sha256.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
//#include "Z9LockIOProtocol_Serialize.cc"

using namespace z9;
using namespace z9::protocols;
using z9::protocols::z9lockio::getFormatter;

// generate eros headers: 
// first header is `leaf_ble_msg_t` which is 5 bytes
// begins with 0x82 0b [len16] [++n] ...data

// data next contains `passthru_value_t` which is 5 bytes
// passthru_id (?? 0 = module, 1 = host, 2 = echo, ...)
// fragment index (from zero)
// fragment total (from 1)
// fragment bytes (16 bits, network order)

// Z9LockIO header
// 2 bytes: z9
// 2 bytes: length
// 1 byte : descriminator
// data

// Z9Lock discriminators: LockIdent = 0, LockIdentResult = 1,
//      LockBUndleHeader = 40, LockPublicKeyExchange = 41,
//      LockAccessReq = 37, LockAccessResp = 38


// LockIdent:
// 2 bytes: protocol rev
// 1 byte : type of device
// 8 bytes: ident
// 1 byte : model #
// 1 byte : brand code
// 2 bytes: firmware rev
// 1 byte : licensed

// AccessReq:
// 2 bytes: request ID (incrementing)
// 8 bytes: mobileID (may be redundant)

// AccessRsp:
// 2 bytes: requestId
// 2 bytes: errorCode
// 1 byte:  granted

// LockBundleHeader
// 1 byte : origin
// 1 byte : intermediary
// 1 byte : destination
// 8 bytes: origin ID
// 8 bytes: intermediary ID
// 8 bytes: destination ID
// 7 bytes: expires (time-to-second) UTC
// 1 byte : opaque: if true, following pkts encrypted
// 1 byte : packets that follow: from 1

// From Mobile to Lock
// Origin = Mobile(3), Dest = Lock(1)
// OriginID: mobileID = 9999 (270F)
// LockID : DEVICE_ID (32-bit from AdVert)
// 


// flash memory keys & backing store
static struct nvs_fs fs;

enum NVS_KEY { KEY_mode = 1, KEY_lock_public, KEY_noc_public, KEY_noc_derived_key};
static uint8_t lock_public_key[65];
static uint8_t noc_public_key[65];
static uint8_t noc_derived_key[16];

// key handles for PSA
psa_key_id_t noc_key_handle;
psa_key_id_t mobile_key_handle;

std::tuple<uint8_t, uint8_t const *>Z9Lock_ECDH(uint8_t const *msg);

// read Flash to get mode
void set_lock_mode()
{
    struct flash_pages_info info;
    int rc = 0;

	/* define the nvs file system by settings with:
	 *	sector_size equal to the pagesize,
	 *	3 sectors
	 *	starting at NVS_PARTITION_OFFSET
	 */
    printk("%s: mounting circular data fs\n", __func__);
	fs.flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs.flash_device)) {
		printk("Flash device %s is not ready\n", fs.flash_device->name);
		goto construction;
	}
	fs.offset = NVS_PARTITION_OFFSET;
	rc = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (rc) {
		printk("Unable to get page info\n");
		goto construction;
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	rc = nvs_mount(&fs);
	if (rc) {
		printk("Flash Init failed\n");
		goto construction;
	}

    // read keys from flash
    rc = nvs_read(&fs, KEY_noc_public, noc_public_key, sizeof(noc_public_key));
    printk("%s: public_key result: %d\n", __func__, rc);
    if (rc <= 0)
        noc_public_key[0] = 0;      // not initialized
    rc = nvs_read(&fs, KEY_lock_public, lock_public_key, sizeof(lock_public_key));
    if (rc <= 0)
        noc_public_key[0] = 0;
    rc = nvs_read(&fs, KEY_noc_derived_key, noc_derived_key, sizeof(noc_derived_key));
    if (rc <= 0)
        noc_public_key[0] = 0;
    
    if (noc_public_key[0])
    {
        printk("%s: retrieved derived key: ", __func__);
        auto p = noc_derived_key;
        auto n = sizeof(noc_derived_key);
        while (n--)
            printk("%02x", *p++);
        printk("\n");

        Z9Crypto_gcmSetKey(noc_key_handle, noc_derived_key, sizeof(noc_derived_key));
        z9lock_status.mode = LockStatusMode::NORMAL;
    }
    else
    {
construction:
        printk("%s: shared secret is uninitialized\n", __func__);
        z9lock_status.mode = LockStatusMode::CONSTRUCTION;
    }
    z9lock_status.publish();
}     


void lock_mode_reset()
{
    printk("%s: clearing flash\n", __func__);
    nvs_clear(&fs);
}



static void z9lockio_recv(const uint8_t *buf, uint16_t buf_len);

// receive from BLE driver
static bt_conn *eros_conn;
static uint8_t passthru_channel;

void eros_ble_recv(bt_conn *conn, const void *buf_v, uint16_t buf_len)
{
    auto buf = static_cast<const uint8_t *>(buf_v);
    eros_conn = conn;
    
    // received eros pkt from mobile
    // only want unencrypted passthru
    if (*buf++ != 0x82) return;
    if (*buf++ != 0x0b) return;

    auto leaf_len = *buf++ << 8;
         leaf_len += *buf++;

    ++buf;

    if (leaf_len != (buf_len - 5))
    {
        printk("%s: eros leaf length: %u incorrect (expected %u)\n", __func__, leaf_len, buf_len - 5);
        return;
    }

    // eros passthru packet
    passthru_channel = *buf++;
    if (*buf++ != 0) return;        // must be first fragment
    if (*buf++ != 1) return;        // must be only fragment 

    auto len = *buf++ << 8;
         len += *buf++;

    if (len != (leaf_len - 5))
    {
        printk("%s: passthru message length: %u incorrect (expected %u)\n", 
                __func__, len, leaf_len - 5);
        return;
    }

    z9lockio_recv(buf, len);
}
    
// *** HEADER LENGTHS ***    
static constexpr auto eros_header_len = 10;
static constexpr auto z9_bundle_header_len = 41;
static constexpr auto z9_opaque_header_len = 5 + 2 + 12 + 16;

// send to BLE driver 
static void eros_passthru_send(uint8_t passthru_id, uint8_t *buf, uint8_t len)
{
    printk("%s: sending %u bytes\n", __func__, len + 10);
    static uint8_t seq_no;
    // NB: there is 10 bytes of room in header
    *--buf = len;
    *--buf = len >> 8;
    *--buf = 1;
    *--buf = 0;
    *--buf = passthru_id;

    // now the EROS header
    // modify LEN to include 7 passthru bytes and 1 seq# byte
    len += 6;
    *--buf = ++seq_no;
    *--buf = len;
    *--buf = len >> 8;
    *--buf = 0x0b;
    *--buf = 0x82;
    my_service_send(eros_conn, buf, len + 4);
    LockEventDb::instance().dump();
}


uint8_t  sourceType, interType, destType;
uint64_t sourceID  , interID  , destID;
bool    opaque;
uint8_t packetCount;
uint16_t requestID;
uint64_t mobileID;
uint32_t unid;
uint16_t schedMask;

uint64_t read64(uint8_t **p)
{
    uint64_t value{};
    for (auto n = sizeof(value); n--; )
    {
        value <<= 8; 
        value += *(*p)++;
    }
    return value;
}

uint32_t read32(uint8_t **p)
{
    uint32_t value{};
    for (auto n = sizeof(value); n--; )
    {
        value <<= 8; 
        value += *(*p)++;
    }
    return value;
}

uint8_t *write64(uint8_t *p, uint64_t value)
{
    p += 8;
    for (auto n = sizeof(uint64_t); n--; value >>= 8)
        *--p = value;
    return p + 8;
}

static uint8_t *z9lockio_create_bundle_header(uint8_t *p, bool toInter = false, bool opaque = false, uint8_t count = 1)
{
    auto first = p;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockBundleHeader::DISCRIMINATOR;
    if (!toInter)
    {
        *p++ = destType;
        *p++ = interType;
        *p++ = sourceType;
        p = write64(p, destID);
        p = write64(p, interID);
        p = write64(p, sourceID);
    }
    else
    {
        *p++ = destType;
        *p++ = 0;       // NONE
        *p++ = interType;
        p = write64(p, destID);
        p = write64(p, 0);
        p = write64(p, interID);
    }
    std::memset(p, 0, 7);
    p += 7;
    *p++ = opaque;
    *p++ = count;
    auto len = p - first;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: length = %u\n", __func__, len);
    return p;
}

static uint8_t *z9lockio_create_opaque(uint8_t *p, uint16_t bytes, psa_key_id_t& key)
{
    // allocate our room
    auto msg = p - z9_opaque_header_len;
    msg[0] = 'z';
    msg[1] = '9';
    msg[2] = (bytes + z9_opaque_header_len) >> 8;
    msg[3] = (bytes + z9_opaque_header_len);
    msg[4] = LockOpaqueContent::DISCRIMINATOR;
    msg[5] = (bytes + 28) >> 8;
    msg[6] = (bytes + 28);
    auto iv = msg + 7;
    auto tag = iv + 12;
    std::memcpy(iv, Z9Crypto_random(), 12);
    Z9Crypto_gcm_encrypt(key, iv, {}, 0, p, bytes, tag, 16);
    return msg;
}

variableArray<16> mobileSharedSecret;
uint8_t ble_challenge[16] = "Z9 Challenge";

static void z9lockio_gen_challenge()
{
    static uint8_t buf[100];

    auto access_rsp = z9lockio_create_bundle_header(&buf[eros_header_len], true);
    auto p = access_rsp;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockMobileBleChallengeNonce::DISCRIMINATOR;
    *p++ = sizeof(ble_challenge);
    std::memcpy(p, ble_challenge, sizeof(ble_challenge));
    p += sizeof(ble_challenge);
    
    auto len = p - access_rsp;
    *len_p++ = len >> 8;
    *len_p = len;
    
    printk("%s: challenge length = %u\n", __func__, len);
    auto total = p - &buf[eros_header_len];
    eros_passthru_send(passthru_channel, &buf[eros_header_len], total);
}

extern bool access_button_state;
static void z9lockio_gen_access_rsp(LockEvtCode result)
{
    static uint8_t buf[200];

    // generate an event
    auto evt  = EVT(result, mobileGrant);
    auto xtra = LockEvtContent_CredUnid {
            .credTechnology = LockCredTechnology_BLUETOOTH_Z9_WAVELYNX,
            .credUnid       = unid };
    LockEventDb::instance().save(evt, xtra);

    // leave room for opaque + 1x bundler header + eros
    auto header_space = eros_header_len + 1 * z9_bundle_header_len + z9_opaque_header_len;

    auto begin_rsp = &buf[header_space];
    auto access_rsp = z9lockio_create_bundle_header(begin_rsp);
    auto p = access_rsp;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockAccessResp::DISCRIMINATOR;
    *p++ = requestID >> 8;
    *p++ = requestID;
    //uint16_t error = access_button_state ? 42 : 0;
    auto error = 0;
    *p++ = error >> 8;
    *p++ = error;
    *p++ = (result == LockEvtCode_DOOR_ACCESS_GRANTED);
    auto len = p - access_rsp;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: rsp length = %u\n", __func__, len);
#if 1
    // have unencrypted response. Add prototype `opaque` header & encrypt in place
    auto opaque_rsp = z9lockio_create_opaque(begin_rsp, p - begin_rsp, mobile_key_handle);

    // allocate space to prepend bundle header
    auto msg = &opaque_rsp[-z9_bundle_header_len];
    z9lockio_create_bundle_header(msg, false, true);

#else
    auto msg = begin_rsp;
#endif
    eros_passthru_send(passthru_channel, msg, p - msg);
}

void z9lock_gen_keyExchange_rsp(uint8_t cnt, uint8_t const *msg)
{
    static uint8_t buf[100];

    printk("%s: %u bytes\n", __func__, cnt);

    auto access_rsp = z9lockio_create_bundle_header(&buf[eros_header_len]);
    auto p = access_rsp;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    *p++ = LockPublicKeyExchange::DISCRIMINATOR;
    *p++ = cnt;
    std::memcpy(p, lock_public_key, sizeof(lock_public_key));
    p += sizeof(lock_public_key);
    
    auto len = p - access_rsp;
    *len_p++ = len >> 8;
    *len_p = len;
    
    printk("%s: rsp length = %u\n", __func__, len);
    auto total = p - &buf[eros_header_len];
    eros_passthru_send(passthru_channel, &buf[eros_header_len], total);
}

void z9lock_gen_evt_batch(uint8_t priority)
{
    uint8_t buf[200] = {}, *p;
    auto writer = [&p](uint8_t c) { *p++ = c; };
    
    // leave room for opaque + 1x bundler header + eros
    auto header_space = eros_header_len + 1 * z9_bundle_header_len + z9_opaque_header_len;

    auto begin_rsp = &buf[header_space];
    auto rsp_payload = z9lockio_create_bundle_header(begin_rsp);
     p = rsp_payload;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    
    *p++ = LockEvtBatch::DISCRIMINATOR;
    *p++ = priority;
    auto count_p = p++;     // `writer` has side effects
    *count_p = LockEventDb::instance().extract(priority, 32, writer);

    // if no pending events, just ignore
    if (!*count_p) return;
    
    auto len = p - rsp_payload;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: payload length = %u\n", __func__, len);
#if 1
    // have unencrypted response. Add prototype `opaque` header & encrypt in place
    auto opaque_rsp = z9lockio_create_opaque(begin_rsp, p - begin_rsp, noc_key_handle);

    // allocate space to prepend bundle header
    auto msg = &opaque_rsp[-z9_bundle_header_len];
    z9lockio_create_bundle_header(msg, false, true);

#else
    auto msg = begin_rsp;
#endif
    eros_passthru_send(passthru_channel, msg, p - msg);
}

void z9lock_gen_db_resp(uint64_t const& requestID)
{
    uint8_t buf[200] = {}, *p;
    
    // leave room for opaque + 1x bundler header + eros
    auto header_space = eros_header_len + 1 * z9_bundle_header_len + z9_opaque_header_len;

    auto begin_rsp = &buf[header_space];
    auto rsp_payload = z9lockio_create_bundle_header(begin_rsp);
     p = rsp_payload;
    *p++ = 'z';
    *p++ = '9';
    auto len_p = p;
    p += 2;
    
    *p++ = LockDbChangeResp::DISCRIMINATOR;
     p = write64(p, requestID);
    *p++ = 0;       // error code (16-bits)
    *p++ = 0;
    
    auto len = p - rsp_payload;
    *len_p++ = len >> 8;
    *len_p = len;
    printk("%s: payload length = %u\n", __func__, len);
    printk("%s: payload = ", __func__);
    auto s     = begin_rsp;
    auto s_len = p - s;
    while(s_len--) printk("%02x", *s++);
    printk("\n");
#if 1
    // have unencrypted response. Add prototype `opaque` header & encrypt in place
    auto opaque_rsp = z9lockio_create_opaque(begin_rsp, p - begin_rsp, noc_key_handle);

    // allocate space to prepend bundle header
    auto msg = &opaque_rsp[-z9_bundle_header_len];
    z9lockio_create_bundle_header(msg, false, true);

#else
    auto msg = begin_rsp;
#endif
    eros_passthru_send(passthru_channel, msg, p - msg);
}

static void recv_trampoline(k_work *work);
static void do_z9lockio_recv(uint8_t *buf, uint16_t buf_len);

struct ble_recv_message
{
    K_WORK_DEFINE(recv_work, recv_trampoline);
    uint16_t  buf_len;
    uint8_t   buf[420];
};

static constexpr auto BLE_RECV_QUEUE_SIZE = 20;
static ble_recv_message ble_recv_queue[BLE_RECV_QUEUE_SIZE], *ble_queue_ptr = ble_recv_queue;

static void recv_trampoline(k_work *work)
{
    auto self = CONTAINER_OF(work, ble_recv_message, recv_work);
    do_z9lockio_recv((uint8_t *)self->buf, self->buf_len);
} 

static void z9lockio_recv(const uint8_t *buf, uint16_t buf_len)
{
    // get next circular queue location
    auto p = ble_queue_ptr++;
    if (ble_queue_ptr - ble_recv_queue == BLE_RECV_QUEUE_SIZE)
        ble_queue_ptr = ble_recv_queue;

    // just overwrite if busy
    // print message if overwriting
    if (p->recv_work.flags & K_WORK_MASK)
        printk("%s: overwriting previous message", __func__);

    p->buf_len = buf_len;
    memcpy(p->buf, buf, buf_len);
    k_work_submit(&p->recv_work);
}


static void do_z9lockio_recv(uint8_t *buf, uint16_t buf_len)
{
    printk("%s: Processing... (buf_len=%d)\n", __func__, buf_len);

    auto initial = buf;

    // validate z9lockio header
    if (*buf++ != 'z') return;
    if (*buf++ != '9') return;

    auto len = *buf++ << 8;
         len += *buf++;

    auto discriminator = *buf++;
    len -= 5;       // remove Z9LockIO Header length from count

    printk("%s: discriminator: %u, len = %u\n", __func__, discriminator, len);
    switch (discriminator)
    {
        case LockBundleHeader::DISCRIMINATOR:
        {
#if 0
            sourceType = *buf++;
            interType  = *buf++;
            destType   = *buf++;
            sourceID = read64(&buf);
            interID  = read64(&buf);
            destID   = read64(&buf);
            buf += 7;
            opaque      = *buf++;
            packetCount = *buf++;
#else
            using T = LockBundleHeader;
            //using T = LockDate;
            //auto proto = Z9Serialize_ptr<T>::value;
            auto proto = getFormatter<T>();
            auto reader = [&buf]() { return *buf++; };
            uint8_t scratch[128] = {};

            auto p = static_cast<T *>((void *)scratch);
            proto->deserialize(reader, scratch, sizeof(scratch), sizeof(T));
            #if 1
            sourceType = p->origin;
            interType  = p->intermediary;
            destType   = p->destination;
            sourceID = p->originId;
            interID  = p->intermediaryId;
            destID   = p->destinationId;
            opaque   = p->opaque;
            packetCount = p->packetCount;
            #endif
#endif
            printk("Bundle: source=%llu, dest=%llu, opaque=%d, packetCount=%d\n",
                sourceID, destID, opaque, packetCount);
            break;
        }

        case LockOpaqueContent::DISCRIMINATOR:
        {
            // read (actually get pointers to) IV + TAG
            auto count = *buf++ << 8;
            count += *buf++;
            len -= 2;
            auto iv = buf;
            buf += 12;
            auto tag = buf;
            buf += 16;
            len -= 12 + 16;     // encrypted data follows tag
            printk("LockOpaqueContent: count = %d, len = %d\n", count, len);

            psa_key_handle_t *key_p {};
            const char *keyName = "UNKNOWN KEY";
            switch (sourceType)
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

            printk("%s: Processing OpaqueContent %d bytes using key: %s\n", __func__, len, keyName);
            auto status = Z9Crypto_gcm_decrypt(*key_p, iv, nullptr, 0, buf, len, tag, 16);
            if (status)
                printk("%s: Decrypt failed: %d\n", __func__, status);

            break;
        }

        case LockAccessReq::DISCRIMINATOR:
        {
            extern bool privacy_state;

            requestID = *buf++ << 8;
            requestID += *buf++;
            mobileID = read64(&buf);
            printk("AccessReq: ID=%04x, mobile=%llu\n", requestID, mobileID);

            LockEvtCode result = LockEvtCode_DOOR_ACCESS_GRANTED;
            if (privacy_state)
                result = LockEvtCode_DOOR_ACCESS_DENIED_DOOR_PRIVACY;
            else if (!schedMask)
                result = LockEvtCode_DOOR_ACCESS_DENIED_INACTIVE;

            z9lockio_gen_access_rsp(result);
            break;
        }

        case LockPublicKeyExchange::DISCRIMINATOR:
        {
            // perform ECDH key derivation
            // send/receive packet format is [length][length bytes]
            printk("%s: received Key Exchange: buf_len = %d, KeyLen = %d, KeyHdr = %x\n", __func__, len, buf[0], buf[1]);

            // since we only save our public key, see if NOC sent same pulic key. If so we respond with
            // our saved key
            if (memcmp(&buf[1], noc_public_key, sizeof(noc_public_key)) == 0 && lock_public_key[0])
            {
                printk("%s: NOC_didn't change: replying with saved public key", __func__);
                z9lock_gen_keyExchange_rsp(sizeof(lock_public_key), lock_public_key);
            }
            else
            {
                auto [cnt, p] = Z9Lock_ECDH(buf);
                if (cnt)
                {
                    printk("%s: calculated secret\n", __func__);
                    z9lock_gen_keyExchange_rsp(cnt, p);
                    printk("%s: send response\n", __func__);
                }
            }
            break;
        }

        case LockCredAuthorization::DISCRIMINATOR:
        {
        #if 1
            // parse this
            // save cred
            auto mobileID = read64(&buf);
            auto lockID   = read64(&buf);
            //buf += 77;      // skip LockCred
            // read 4 bytes of UNID (for grant)
            unid = read32(&buf);

            buf += 50;      // skip to numCredBytes
            auto numCredBytes = *buf++;
            buf += numCredBytes;
            buf += 4;       // skip over pi
            auto n = *buf++ << 8;
            schedMask = n + *buf++;
            auto numSchedUnids = *buf++;
            buf += numSchedUnids * 4;       // skip unids
            auto sharedSecretLen = *buf++;
            mobileSharedSecret.set(sharedSecretLen, buf);
        #else
            using T = LockCredAuthorization;

            auto reader = [&buf]() { return *buf++; };
            uint8_t scratch[128] = {};
            auto p = static_cast<T *>((void *)scratch);
            getFormatter<T>()->deserialize(reader, scratch, sizeof(scratch), sizeof(T));



        #endif
            // save mobile key:
            // XXX may need to destroy old key for memory leak
            Z9Crypto_gcmSetKey(mobile_key_handle, mobileSharedSecret(), mobileSharedSecret.size());

            using IDX = meta::find_index<z9::protocols::z9lockio::FORMATS_TYPES, LockHol>;
            printk("%s: LockHol typeid is %u\n", __func__, IDX::value); 
            printk("%s: received CredAuthorization: lock: %llu, mobile: %llu, secret: %d bytes\n",
                    __func__, mobileID, lockID, mobileSharedSecret.size());
           z9lockio_gen_challenge(); 
           break;
        }

        case LockDbChange_Config::DISCRIMINATOR:
        case LockDbChange_Hol::DISCRIMINATOR:
        case LockDbChange_Sched::DISCRIMINATOR:
        case LockDbChange_SchedPolicy::DISCRIMINATOR:
        {
            auto requestID = read64(&buf);
            printk("%s: Processing LockDbChange_Config: %llx\n", __func__, requestID);
            z9lock_gen_db_resp(requestID);
            break;
        }

        case LockEvtControl::DISCRIMINATOR:
        {
            using T = LockEvtControl;
            auto proto = getFormatter<T>();
            auto reader = [&buf]() { return *buf++; };
            uint8_t scratch[128] = {};

            auto p = static_cast<T *>((void *)scratch);
            proto->deserialize(reader, scratch, sizeof(scratch), sizeof(T));
            printk("EvtControl: priority=%d, sendOneBatch=%d, start=", p->priority, p->sendOneBatch);
            printk("%d, stop=%d\n", p->consume.start.evtCode, p->consume.stop.evtCode);

            if (p->consume.start.evtCode)
                LockEventDb::instance().consume(p->priority, p->consume.start, p->consume.stop);
            if (p->sendOneBatch)
                z9lock_gen_evt_batch(p->priority);

           break;
        }
        default:
            printk("%s: ignoring discriminator: %u\n", __func__, discriminator);
            buf += len;
            break;
    }

    // recurse for next message
    if (auto remaining = buf_len - (buf - initial))
        do_z9lockio_recv(buf, remaining);
}

void derive_key_from_shared_secret_and_public_keys(
    const unsigned char *shared_secret, std::size_t shared_secret_len,
    const unsigned char *our_public_key, std::size_t our_public_key_len,
    const unsigned char *other_public_key, std::size_t other_public_key_len,
    unsigned char *output, std::size_t output_len)
{
    mbedtls_sha256_context sha256_ctx;
    unsigned char hash[32]; // SHA-256 outputs 32 bytes

    // Initialize SHA-256 context
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, 0); // 0 for SHA-256, not 224

    // Hash the shared secret
    mbedtls_sha256_update(&sha256_ctx, shared_secret, shared_secret_len);

    // Hash our public key
    mbedtls_sha256_update(&sha256_ctx, our_public_key, our_public_key_len);

    // Hash other public key
    mbedtls_sha256_update(&sha256_ctx, other_public_key, other_public_key_len);

    // Finalize and get the hash
    mbedtls_sha256_finish(&sha256_ctx, hash);

    // Clean up
    mbedtls_sha256_free(&sha256_ctx);

    // Copy the required number of bytes to the output
    memcpy(output, hash, output_len);
}

std::tuple<uint8_t, uint8_t const *>Z9Lock_ECDH(uint8_t const *msg)
{
    // remote public key should be 64 bytes
    if (*msg++ != 65)
        return {};

    auto& lock = z9lock_status;
    if (lock.mode != LockStatusMode::PAIRING)
    {
        printk("%s: not in pairing mode\n", __func__);
        return {};
    }

    // check if stored remote public key matches -- if so done
    if (std::memcmp(noc_public_key, msg, sizeof(noc_public_key)) == 0)
        return { sizeof(lock_public_key), lock_public_key };

    // need new public key for lock
    // 1) generate key pair
    psa_key_handle_t key_handle;
	psa_status_t status;
	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;

	/* Crypto settings for ECDH using the SHA256 hashing algorithm,
	 * the secp256r1 curve
	 */
    // these methods return void
	psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_DERIVE);
	psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_ECDH);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
	psa_set_key_bits(&key_attributes, 256);

	/* Generate a key pair */
	status = psa_generate_key(&key_attributes, &key_handle);
    if (status)
        printk("%s: psa_generate_key: error=%d\n", __func__, status);
	psa_reset_key_attributes(&key_attributes);

    // 2) export public key
    std::size_t olen;
    status = psa_export_public_key(key_handle, lock_public_key, sizeof(lock_public_key), &olen);
    if (status)
        printk("%s: psa_export_public_key: error=%d\n", __func__, status);

    // 3) save noc public key
    std::memcpy(noc_public_key, msg, sizeof(noc_public_key));

    // 4) perform ECDH
    uint32_t ecdh_len;
    uint8_t lock_ecdh_secret[32];
    status = psa_raw_key_agreement(PSA_ALG_ECDH, key_handle,
                                   noc_public_key, sizeof(noc_public_key),
                                   lock_ecdh_secret, sizeof(lock_ecdh_secret),
                                   &ecdh_len);

    if (status)
        printk("%s: psa_raw_key_agreement: error=%d\n", __func__, status);
    {
        uint8_t *p = lock_public_key;
        auto n = sizeof(lock_public_key);
        printk("%s: lock_public = ", __func__);
        while (n--)
            printk("%02x ", *p++);
        printk("\n");
    }
    {
        uint8_t *p = noc_public_key;
        auto n = sizeof(noc_public_key);
        printk("%s: noc_public = ", __func__);
        while (n--)
            printk("%02x ", *p++);
        printk("\n");
    }
    {
        uint8_t *p = lock_ecdh_secret;
        auto n = sizeof(lock_ecdh_secret);
        printk("%s: secret = ", __func__);
        while (n--)
            printk("%02x ", *p++);
        printk("\n");
    }
#if 1
    derive_key_from_shared_secret_and_public_keys(
        lock_ecdh_secret, sizeof(lock_ecdh_secret),
        lock_public_key, sizeof(lock_public_key),
        noc_public_key, sizeof(noc_public_key),
        noc_derived_key, sizeof(noc_derived_key)
    );
#else
    psa_key_derivation_operation_t op = PSA_KEY_DERIVATION_OPERATION_INIT;
    status = psa_key_derivation_setup(
            &op, 
            PSA_ALG_KEY_AGREEMENT(
                PSA_ALG_ECDH,
                PSA_ALG_HKDF(PSA_ALG_SHA_256)
            )
        );
    
    if (status != 0)
        printk("%s: psa_key_derivation_setup: %d\n", __func__, status);


    status = psa_key_derivation_key_agreement(
        &op,
        0,      // step
        key_handle,
        noc_public_key, sizeof(noc_public_key)
    );

    if (status != 0)
        printk("%s: psa_key_derivation_key_agreement: %d\n", __func__, status);

    psa_key_attributes_t d_attr = {};
	psa_set_key_type(&d_attr, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&d_attr, 128);

    status = psa_key_derivation_output_bytes(
        &op, 
        derived_key, sizeof(derived_key));
    
    if (status != 0)
        printk("%s: psa_key_derivation_output_bytes: %d\n", __func__, status);


#endif
    {
        uint8_t *p = noc_derived_key;
        auto n = sizeof(noc_derived_key);
        printk("%s: -> key = ", __func__);
        while (n--)
            printk("%02x", *p++);
        printk("\n");
    }
#if 0 
    // import derived key into PSA
    printk("%s: noc_key_handle (before): %d\n", __func__, noc_key_handle);
    Z9Crypto_gcmSetKey(noc_key_handle, derived_key, sizeof(derived_key));
    printk("%s: noc_key_handle (after): %d\n", __func__, noc_key_handle);
#endif
    // 5) destroy lock public key-pair
    psa_destroy_key(key_handle);
#if 1
    // 6) write to flash
	nvs_write(&fs, KEY_lock_public, lock_public_key, sizeof(lock_public_key));
	nvs_write(&fs, KEY_noc_public, noc_public_key, sizeof(noc_public_key));
	nvs_write(&fs, KEY_noc_derived_key, noc_derived_key, sizeof(noc_derived_key));
#endif
    // 7 retrieve key from FS & set paired mode
    set_lock_mode();
    //z9lock_status.mode = LockStatusMode::NORMAL;
    //z9lock_status.publish();

    // 8) return public key
    return { sizeof(lock_public_key), lock_public_key };
}
