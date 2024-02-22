// z9_ble_driver.h (C-language)

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

// Z9 Lock BLE protocol parameters

// TODO: These UUID definitions should probably be moved out of driver, but
// because of the Zephyr BT macros it's difficult. 
#define Z9LOCK_UUID_SERVICE			BT_UUID_128_ENCODE(0x7599914c, 0xa984, 0x11ed, 0xafa1, 0x0242ac120002)
#define Z9LOCK_UUID_CHARACTERISTIC 	BT_UUID_128_ENCODE(0xee8732b3, 0x2d52, 0x409b, 0x9084, 0x70ad31f6c790)
#define Z9LOCK_MTU					CONFIG_BT_L2CAP_TX_MTU	
#define Z9LOCK_PREFER_2M			1


/* 
 * Z9 BLE DRIVER callbacks for connections and data transfer
 */
struct bt_conn;
typedef void (*send_cb_t)  (void *conn  , uint8_t *data, uint16_t length);
typedef void (*recv_cb_t)  (void *cb_arg, struct bt_conn *conn, uint8_t const *data, uint16_t length);
typedef void (*conn_cb_t)  (void *cb_arg, send_cb_t fn, void *conn);
typedef bool (*accept_cb_t)(void *cb_arg, void *peer);

struct z9_ble_callbacks
{
	/** Received connection request: return true to accept */
	accept_cb_t  accept;

	/** Connection established */
	conn_cb_t connected;

	/** Data received callback. */
	recv_cb_t recv_cb;
};

// Declare interface
void z9_ble_init(struct z9_ble_callbacks const *callbacks, void *cb_arg);
void z9_ble_set_SN(const uint64_t *sn);
void z9_ble_set_name(const uint8_t *name, uint16_t nameLen);



#ifdef __cplusplus
}
#endif
