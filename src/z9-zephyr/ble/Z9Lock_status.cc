// Z9Lock_status.cc

#include "Z9Lock_status.h"
#include "z9lockio_ble.h"
#include <cstring>
#include <iterator>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/hwinfo.h>

#include "Z9IO_Logic.h"

// instantiate object
Z9Lock_status z9lock_status;

#ifdef CONFIG_Z9_CONTROLLER
static uint64_t get_hw_serialNumber()
{
    // read serial number
    uint64_t serial_number = 0;
    uint8_t  temp_buffer[sizeof(serial_number)] = {};
    
    auto sn_len = hwinfo_get_device_id(temp_buffer, sizeof(temp_buffer));
    std::memcpy(&serial_number, temp_buffer, sizeof(serial_number));
    printk("DeviceID = %" PRIu64 ", len=%d, [%" PRIx64 "], [%08" PRIx32 " %08" PRIx32 "]\n"
                                            , (uint64_t)serial_number
                                            , sn_len
                                            , (uint64_t)serial_number
                                            , uint32_t(serial_number>>32)
                                            , uint32_t(serial_number));
    return serial_number;
}

void Z9Lock_status::set_mode(LockStatusMode new_mode)
{
    // don't use ctor: mode needs to be retrieved from NVM settings
    // first time mode is set, retrieve hardware serial number
    if (!lockID)
    {
        lockID = get_hw_serialNumber();
    }

    mode = new_mode;
    publish();
}
#endif

void Z9Lock_status::publish() const
{
    // send to z9io or ble module
#if CONFIG_Z9_CONTROLLER
    send_hostInfo(lockID);
    send_hostStatus(*this);
#endif
}

#ifdef CONFIG_Z9_READER
// convert to `name` format: only needed on reader
std::tuple<uint8_t const *, unsigned> Z9Lock_status::encode() const
{
    // this is the basic Base64 encoding (per Wikipedia)
    // leave full algorithm in, but optimizer should reduce to 7 lookups + 1 pad
    static constexpr uint8_t sEncodingTable[] = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    static constexpr uint8_t sEncodePadding = '=';

    // constants for WaveLynx BLE protocol
    constexpr auto INBUF_LEN  = 5;      // per WaveLynx Lock BLE profile
    constexpr auto OUTBUF_LEN = ((INBUF_LEN + 2)/3) * 4;
    static uint8_t outbuf[OUTBUF_LEN];
    
    // create the input buffer and populate from end -> beginning (ie. network order)
    uint8_t inbuf[INBUF_LEN];
    auto in_p = std::end(inbuf);
    
    // add 32 bits of "lock" (ie lower 32 bits in network order)
    for (auto [n, v] = std::tuple(sizeof(uint32_t), lockID); n--; v >>= 8)
        *--in_p = v;

    // add one byte of "bitmask" as first byte
    auto bitmask = static_cast<uint8_t>(mode);
    if (sync_req)    bitmask |= 1 << 2;
    if (battery_low) bitmask |= 1 << 3;
    if (tamper)      bitmask |= 1 << 4;
    *--in_p = bitmask;

    // basic base64 algorithm (for 3 byte input blocks, generate 4 byte output blocks)
    auto out_p  = std::begin(outbuf);   // not `for` loop variable: need for residual values
    auto in_len = sizeof(inbuf);        // not `for` loop variable: need for residual values
    for (; in_len >= 3; in_len -= 3, in_p += 3)
    {
        *out_p++ = sEncodingTable[in_p[0] >> 2];        // NB: `and` not needed
        *out_p++ = sEncodingTable[0x3f & (in_p[0] << 4 | in_p[1] >> 4)];
        *out_p++ = sEncodingTable[0x3f & (in_p[1] << 2 | in_p[2] >> 6)];
        *out_p++ = sEncodingTable[0x3f & (in_p[2])];
    }

    // output data length must be multiple of 4: pad as required
    if (in_len != 0)
    {
        *out_p++ = sEncodingTable[in_p[0] >> 2];        // NB: `and` not needed
        if (in_len == 1)
        {
            *out_p++ = sEncodingTable[0x3f & (in_p[0] << 4)];
            *out_p++ = sEncodePadding;
        }
        else
        {
            *out_p++ = sEncodingTable[0x3f & (in_p[0] << 4 | in_p[1] >> 4)];
            *out_p++ = sEncodingTable[0x3f & (in_p[1] << 2)];
        }
        *out_p++ = sEncodePadding;
    }

    return { outbuf, OUTBUF_LEN };
}
#endif
