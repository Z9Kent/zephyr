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
#include "Z9Lock_status.h"
#include "z9_ble_driver.h"
#include "Eros_protocol.h"
#include <zephyr/drivers/hwinfo.h>      // get serial #

#define Z9LOCK_BUFFER_SIZE      Z9LOCK_MTU

static void ble_recv_trampoline(k_work *work);
struct ble_recv_message
{
    K_WORK_DEFINE(recv_work, ble_recv_trampoline);
    bt_conn  *conn;
    uint16_t buf_len;
    uint8_t buf[420];
};

static constexpr auto BLE_RECV_QUEUE_SIZE = 20;
static ble_recv_message ble_recv_queue[BLE_RECV_QUEUE_SIZE], *ble_queue_ptr = ble_recv_queue;

static void *conn_conn;
static send_cb_t send_fn;

static void ble_recv(void *cb_arg, bt_conn *conn, const uint8_t *buf, uint16_t buf_len)
{
    // get next circular queue location
    auto p = ble_queue_ptr++;
    if (ble_queue_ptr - ble_recv_queue == BLE_RECV_QUEUE_SIZE)
        ble_queue_ptr = ble_recv_queue;

    // just overwrite if busy
    // print message if overwriting
    if (p->recv_work.flags & K_WORK_MASK)
        printk("%s: overwriting previous message", __func__);

    p->conn    = conn;
    p->buf_len = buf_len;
    std::memcpy(p->buf, buf, buf_len);
    k_work_submit(&p->recv_work);
}

static void ble_recv_trampoline(k_work *work)
{
    auto self = CONTAINER_OF(work, ble_recv_message, recv_work);
    
    printk("%s: received %u bytes of data\n", __func__, self->buf_len);

    

    auto p = self->buf;
    auto n = self->buf_len;
    printk("%s: data: ", __func__);
    while(n--) printk("%02x", *p++);
    printk("\n");
    eros_ble_recv(self->conn, self->buf, self->buf_len);
}

static bool ble_accept(void *cb_arg, void *peer)
{
    // connection attempt from peer
    printk("%s: connection request from peer\n", __func__);
    return true;
}

static void ble_connected(void *cb_arg, send_cb_t fn, void *conn)
{
    printk("%s: connected. send fn = %p\n", __func__, fn);
    send_fn = fn;
    conn_conn = conn;
}

static z9_ble_callbacks cb
{
    .accept    = ble_accept,
    .connected = ble_connected,
    .recv_cb   = ble_recv,
};

void z9lock_ble_init()
{
    static bool inited;
    // init ble driver
    if (!inited)
        z9_ble_init(&cb, NULL);
    inited = true;
}

void z9lock_ble_set_sn(uint64_t const& sn)
{
    z9lock_ble_init();
    z9lock_status.lockID = sn;
}
void z9lock_ble_update_advertising(uint8_t pairing
                                , bool tamper
                                , bool lowBattery
                                , bool syncRequested)
{
    auto& lock = z9lock_status;

    z9lock_status.mode = static_cast<LockStatusMode>(pairing);
    z9lock_status.sync_req = syncRequested;
    z9lock_status.battery_low = lowBattery;
    z9lock_status.tamper = tamper;
   
    z9_ble_set_SN(&lock.lockID);
    auto [name, len] = lock.encode();
    z9_ble_set_name(name, len);
    const char *modeName;
    switch (lock.mode)
    {   
        case LockStatusMode::CONSTRUCTION:
            modeName = "Construction";
            break;
        case LockStatusMode::PAIRING:
            modeName = "Pairing";
            break;
        case LockStatusMode::NORMAL:
            modeName = "Normal";
            break;
        default:
            modeName = "Unknown";
            break;

    }
    printk("%s; advertising lock %" PRIu32 ", MODE=%s\n", __func__, uint32_t(lock.lockID), modeName);
}