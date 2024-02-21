// Eros_protocol.h, language C++
//
// Implement the WaveLynx: "Eros Protocol" as described in undated markdown document
// This module is designed to interface with the `z9lockio_ble` module & `z9_ble_driver` modules
// Passthru messages are accepted / forwarded via the zero-config `Z9Message` protocol

#pragma once

#include <cinttypes>
#include <zephyr/bluetooth/conn.h>

#include "z9lockio_ble.h"

/*
 * Leaf BLE messaging protocol structure.
 */

enum struct leaf_tag_t : uint8_t
{
    ACK_NACK = 0x00,
    ECIES_REQ = 0x09,
    ECIES_RSP = 0x0a,
    PASSTHRU  = 0x0b,
}; 

struct _leaf_ble_msg_t
{
    static constexpr std::size_t max_data_length = 400;
    uint8_t     start;      // start sequence byte 0x82 or 0xC2
    leaf_tag_t  tag;        // msg tag
    uint16_t    length;     // 2 byte msg length, network order

    // these fields are included in the length and encrypted for cipher msgs
    uint8_t     sequence;  // 1 byte rotating sequence
};

enum struct leaf_ble_status_t : uint8_t
{
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
    uint16_t    length;     // big endian fragment length
};

static constexpr auto max_passthru_size = _leaf_ble_msg_t::max_data_length - sizeof(passthrough_value_t);

// IDs 0-128 for commands, IDs 129-255 for responses
// NB: uneven number ranges in original
enum struct target_id_t : uint8_t
{
    MODULE = 0,
    HOST,
    CLIENT = 129,
    SERVICE,
};

// Declare PASSTHRU IDs for Z9LockProtocol
static constexpr auto EROS_PASSTHRU_Z9LOCKIO = 1;
static constexpr auto EROS_PASSTHRU_ECHO     = 2;

void eros_ble_recv(bt_conn *conn, const void *buf, uint16_t buf_len);
void eros_passthru_send(uint8_t passthru_id, uint8_t *buf, uint8_t len);
