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

#include "Z9Lock_status.h"

#pragma once

// Z9Lock BLE protocol parameters
#define Z9LOCK_UUID_SERVICE			BT_UUID_128_ENCODE(0x7599914c, 0xa984, 0x11ed, 0xafa1, 0x0242ac120002)
#define Z9LOCK_UUID_CHARACTERISTIC 	BT_UUID_128_ENCODE(0xee8732b3, 0x2d52, 0x409b, 0x9084, 0x70ad31f6c790)
#define Z9LOCK_MTU					CONFIG_BT_L2CAP_TX_MTU	
#define Z9LOCK_PREFER_2M			1



// Declare interface
void z9lock_ble_init();
void z9lock_ble_update_advertising(const Z9Lock_status &lock);

void lock_service_send(struct bt_conn *conn, const uint8_t *data, uint16_t len);

