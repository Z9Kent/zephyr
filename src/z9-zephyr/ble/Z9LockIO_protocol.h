#include <cinttypes>
#include <zephyr/bluetooth/conn.h>

#include "z9lockio_ble.h"

#define NVS_PARTITION		storage_partition
#define NVS_PARTITION_DEVICE	FIXED_PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	FIXED_PARTITION_OFFSET(NVS_PARTITION)

// includes for NVS
#include <zephyr/device.h>
#include <string.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>
#include <zephyr/fs/nvs.h>

#pragma once

void set_lock_mode();
void lock_mode_reset();

/*
 * Leaf BLE messaging protocol structure.
 */

enum struct leaf_tag_t : uint8_t {
    ACK_NACK = 0x00,
    ECIES_REQ = 0x09,
    ECIES_RSP = 0x0a,
    PASSTHRU  = 0x0b,
}; 

struct _leaf_ble_msg_t
{
    uint8_t     start;      // start sequence byte 0x82 or 0xC2
    leaf_tag_t  tag;        // msg tag
    uint16_t    length;     // 2 byte msg length, network order

    // these fields are included in the length and encrypted for cipher msgs
    uint8_t     sequence;  // 1 byte rotating sequence
    uint8_t     data[400]; // msg payload
};

enum struct leaf_ble_status_t : uint8_t {
    OK   = 0x00,
    ERR  = 0x01,
    AUTH = 0x02,
};

// also serves as message length
enum struct ecies_type_: uint8_t {
    ECIES_ID = 8,           // request public ID
    ECIES_KEY = 65,         // the public key
    ECIES_NONCE = 16,       // generated value for one time use
};


/*
 * Passthrough message type structure.
 */
struct passthrough_value_t
{
    uint8_t     target;     // entity the payload is targeted for
    uint8_t     index;      // fragment index: zero basesd
    uint8_t     total;      // total number of fragments in communication
    uint8_t     length;     // big endian fragment length
    uint8_t     data[395];  // fragment data
};

// IDs 0-128 for commands, IDs 129-255 for responses
// NB: uneven number ranges in original
enum struct target_id_t : uint8_t {
    MODULE = 0,
    HOST,
    CLIENT = 129,
    SERVICE,
};

void eros_ble_recv(bt_conn *conn, const void *buf, uint16_t buf_len);

