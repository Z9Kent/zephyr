#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/kernel.h>
#include <soc.h>
#include <tuple>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#pragma once

// Z9Lock BLE protocol parameters
#define Z9LOCK_UUID_SERVICE			BT_UUID_128_ENCODE(0x7599914c, 0xa984, 0x11ed, 0xafa1, 0x0242ac120002)
#define Z9LOCK_UUID_CHARACTERISTIC 	BT_UUID_128_ENCODE(0xee8732b3, 0x2d52, 0x409b, 0x9084, 0x70ad31f6c790)
#define Z9LOCK_MTU					CONFIG_BT_L2CAP_TX_MTU	
#define Z9LOCK_PREFER_2M			1

/* 
 * Z9LOCK BLE protocol uses device name to identify lock ID & status
 * 
 * Update BLE advertising packet via class `z9lock_status`
 */

enum class LockStatusMode : uint8_t { CONSTRUCTION = 0, PAIRING = 1, NORMAL = 2 };
struct Z9lock_status
{
	void publish() const;
	
	uint64_t lockID;
	LockStatusMode mode;
	bool	 sync_req;
	bool	 battery_low;
	bool	 tamper;

	std::tuple<uint8_t const *, unsigned> encode() const;
};

/* 
 * Z9LOCK BLE callbacks for connections and data transfer
 * 
 */
#if 0
struct Z9lock_callbacks
{
	/** Received connection request: return true to accept */
	accept_cb_t  accept;

	/** Connection established */
	connect_cb_t connected;

	/** Data received callback. */
	data_rx_cb_t data_rx_cb;
};
#endif

// z9_lock interface
void lock_mode_reset();
void set_lock_mode();

// Declare interface
void z9lock_ble_init();
extern Z9lock_status z9lock_status;
void lock_service_send(struct bt_conn *conn, const uint8_t *data, uint16_t len);

