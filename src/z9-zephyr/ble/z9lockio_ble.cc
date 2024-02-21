#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/gatt.h>

#include <cstring>
#include <initializer_list>
#include <iterator>

#include <zephyr/settings/settings.h>   // nvm interface
#include "z9lockio_ble.h"
#include "z9_ble_driver.h"
#include "Eros_protocol.h"
#include <zephyr/drivers/hwinfo.h>      // get serial #

#define Z9LOCK_BUFFER_SIZE      Z9LOCK_MTU
Z9lock_status z9lock_status;

static z9_ble_callbacks cb;

#define BT_UUID_SERVICE     BT_UUID_DECLARE_128(Z9LOCK_UUID_SERVICE)
#define BT_UUID_CHAR_RX     BT_UUID_DECLARE_128(Z9LOCK_UUID_CHARACTERISTIC)

#define SHORT_SERVICE       0x1101      // short service ("SerialPort")
#define SHORT_CHAR          0x1102      // short service + 1

#define USE_SHORT_SERVICE   0      // get around pc-ble-driver-py bug

static uint64_t get_hw_serialNumber()
{
    // read serial number
    uint64_t serial_number = 0;
    uint8_t  temp_buffer[sizeof(serial_number)];
    std::memset(temp_buffer, 0, sizeof(temp_buffer));
    auto sn_len = hwinfo_get_device_id(temp_buffer, sizeof(temp_buffer));
    std::memcpy(&serial_number, temp_buffer, sn_len);
    printk("DeviceID = %" PRIu64 ", len=%d, [%" PRIx64 "], [%08" PRIx32 " %08" PRIx32 "]\n"
                                            , (uint64_t)serial_number
                                            , sn_len
                                            , (uint64_t)serial_number
                                            , uint32_t(serial_number>>32)
                                            , uint32_t(serial_number));
    return serial_number;
}

std::tuple<uint8_t const *, unsigned> Z9lock_status::encode() const
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

void z9lock_ble_init()
{
    // read settings
    if (IS_ENABLED(CONFIG_SETTINGS)) {
            settings_load();
    }
        
    // init ble driver
    int err = bt_enable(NULL);
    if (err) {
            printk("Bluetooth init failed (err %d)\n", err);
            return;
    }

    // set callbacks

    // configure advertising info
    uint64_t serial_number = get_hw_serialNumber();
    z9_ble_set_SN(&serial_number);     // additional advertising data

    // get lock mode...

    auto& lock  = z9lock_status;
    lock.lockID = serial_number;
    //lock.mode   = mode;

    printk("%s; advertising lock %" PRIu64 "\n", __func__, lock.lockID);
    lock.publish();
}

// update BLE advertisement
void Z9lock_status::publish() const
{
    auto&& [encoded, encoded_len] = encode();
    printk("Encoded: %.8s, %u bytes\n", encoded, encoded_len);
    z9_ble_set_name(encoded, encoded_len);
}
