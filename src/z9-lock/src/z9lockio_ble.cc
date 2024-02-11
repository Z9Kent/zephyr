#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <soc.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/addr.h>
#include <zephyr/bluetooth/gatt.h>

#include <cstring>
#include <initializer_list>
#include <iterator>

#include "z9lockio_ble.h"
#include "Eros_protocol.h"
#include "EventDb.h"
//#include <dk_buttons_and_leds.h>
//#define CON_STATUS_LED DK_LED2

#define Z9LOCK_BUFFER_SIZE      Z9LOCK_MTU
Z9lock_status z9lock_status;

static uint8_t data_rx[Z9LOCK_MTU];

static Z9lock_callbacks cb;

#define BT_UUID_SERVICE     BT_UUID_DECLARE_128(Z9LOCK_UUID_SERVICE)
#define BT_UUID_CHAR_RX     BT_UUID_DECLARE_128(Z9LOCK_UUID_CHARACTERISTIC)

#define SHORT_SERVICE       0x1101      // short service ("SerialPort")
#define SHORT_CHAR          0x1102      // short service + 1

#define USE_SHORT_SERVICE   0      // get around pc-ble-driver-py bug


/* 
 * Define BLE advertising service & callbacks
 */

static bt_conn *my_conn;
static struct bt_gatt_exchange_params exchange_params;
static void exchange_func(struct bt_conn *conn, uint8_t att_err,
			  struct bt_gatt_exchange_params *params);

#if defined(CONFIG_BT_USER_PHY_UPDATE)
static void update_phy(struct bt_conn *conn)
{
    int err;
    const struct bt_conn_le_phy_param preferred_phy = {
        .options = BT_CONN_LE_PHY_OPT_NONE,
        .pref_tx_phy = BT_GAP_LE_PHY_2M,
        .pref_rx_phy = BT_GAP_LE_PHY_2M,
    };

    err = bt_conn_le_phy_update(conn, &preferred_phy);
    if (err) {
        printk("bt_conn_le_phy_update() returned %d\n", err);
    }
}
#endif

static void update_data_length(struct bt_conn *conn)
{
	int err;
	struct bt_conn_le_data_len_param my_data_len = {
		.tx_max_len = BT_GAP_DATA_LEN_MAX,
		.tx_max_time = BT_GAP_DATA_TIME_MAX,
	};
	err = bt_conn_le_data_len_update(my_conn, &my_data_len);
	if (err) {
		printk("%s: data_len_update failed (err %d)", __func__, err);
	}
}


static void update_mtu(struct bt_conn *conn)
{
	int err;
	exchange_params.func = exchange_func;

	err = bt_gatt_exchange_mtu(conn, &exchange_params);
	if (err) {
		printk("%s: bt_gatt_exchange_mtu failed (err %d)", __func__, err);
	}
}

void on_connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printk("Connection error %d\n", err);
        return;
    }
    printk("MOBILE Connected\n");
    my_conn = bt_conn_ref(conn);
#if defined(CONFIG_BT_USER_PHY_UPDATE)
    update_phy(my_conn);
#endif
    update_data_length(my_conn);
    update_mtu(my_conn);
    //dk_set_led_on(CON_STATUS_LED);
}
void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
    printk("MOBILE Disconnected. Reason %d\n", reason);
    bt_conn_unref(my_conn);
    //dk_set_led_off(CON_STATUS_LED);
}

void on_le_phy_updated(struct bt_conn *conn, struct bt_conn_le_phy_info *param)
{
    // PHY Updated
    if (param->tx_phy == BT_CONN_LE_TX_POWER_PHY_1M) {
        printk("PHY updated. New PHY: 1M\n");
    }
    else if (param->tx_phy == BT_CONN_LE_TX_POWER_PHY_2M) {
        printk("PHY updated. New PHY: 2M\n");
    }
    else if (param->tx_phy == BT_CONN_LE_TX_POWER_PHY_CODED_S8) {
        printk("PHY updated. New PHY: Long Range\n");
    }
}

static void exchange_func(struct bt_conn *conn, uint8_t att_err,
			  struct bt_gatt_exchange_params *params)
{
	printk("%s: MTU exchange %s", __func__, att_err == 0 ? "successful" : "failed");
	if (!att_err) {
		uint16_t payload_mtu =
			bt_gatt_get_mtu(conn) - 3; // 3 bytes used for Attribute headers.
		printk("%s: New MTU: %d bytes\n", __func__, payload_mtu);
	}
}

struct bt_conn_cb connection_callbacks = {
    .connected              = on_connected,
    .disconnected           = on_disconnected,
#if defined(CONFIG_BT_USER_PHY_UPDATE)
    .le_phy_updated         = on_le_phy_updated,
#endif
};

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

#define DEVICE_NAME "Z9Lock"
#define DEVICE_NAME_LEN     (sizeof(DEVICE_NAME) - 1)

// because of c++ UUID macro, this needs to be at global scope
// leave last adverting message empty. Calculate name & update.
static struct bt_data ad[3] = {
        BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
        BT_DATA_BYTES(BT_DATA_UUID128_ALL, Z9LOCK_UUID_SERVICE), 
};

static struct bt_data sd[1];

data_send_t z9lock_ble_init(Z9lock_callbacks const& cb)
{
    LockEventDb::instance().save(EVT(LockEvtCode_STARTUP));
    bt_conn_cb_register(&connection_callbacks);
    auto& lock = z9lock_status;

    // if lockID not set, can't advertise
    if (!lock.lockID)
        return {};
    printk("%s; advertising lock %" PRIu64"\n", __func__, lock.lockID);
    lock.publish();
    return {};
}

void Z9lock_status::publish() const
{
    auto&& [encoded, encoded_len] = encode();
    printk("Encoded: %.8s, %u bytes\n", encoded, encoded_len);

    // update "NAME" as last advertising tuple
    constexpr auto ad_size = ARRAY_SIZE(ad);
    ad[ad_size-1].type = BT_DATA_NAME_COMPLETE;
    ad[ad_size-1].data = encoded;
    ad[ad_size-1].data_len = encoded_len;

    // don't know about static...
    static uint8_t sd_data[sizeof(uint64_t)];
    sd[0].type = BT_DATA_MANUFACTURER_DATA;
    sd[0].data = sd_data;
    sd[0].data_len = sizeof(sd_data);


    // save 64-bit `lockID`, in network order, into `sd_data` byte array 
    for (auto [n, p, v] = std::tuple{sizeof(sd_data), std::end(sd_data), lockID}; --n; v >>= 8)
        *--p = v;

    // C++ compiler error workaround
    auto const&& conn = BT_LE_ADV_CONN;
    int err = 0;
    static bool started;

    if (!started)
    {
        started = true;
        err = bt_le_adv_start(conn, ad, ad_size, sd, 1);
    } else 
    {
        printk("UPDATING NAME: %.8s\n", encoded);
        err = bt_le_adv_update_data(ad, ad_size, sd, 1);
    }
    
    if (err) {
            printk("Advertising failed to start (err %d)\n", err);
    }
}

/* 
 * Define BLE data callbacks
 */



/* This function is called whenever the RX Characteristic has been written to by a Client */
static ssize_t on_receive(struct bt_conn *conn,
			  const struct bt_gatt_attr *attr,
			  const void *buf,
			  uint16_t len,
			  uint16_t offset,
			  uint8_t flags)
{
    auto buffer = static_cast<uint8_t const *>(buf);
    
	printk("Received data: handle %d, conn %p, len: %u, data: 0x", attr->handle, conn, len);
    for(uint8_t i = 0; i < len; i++){
        printk("%02X", buffer[i]);
    }
    printk("\n");
    printk("Received data: offset=%d (0x%04x), flags=0x%02x\n", offset, offset, flags);

    eros_ble_recv(conn, buf, len);
    //my_service_send(conn, reply, sizeof(reply)-1);
	return len;
}

/* This function is called whenever a Notification has been sent by the TX Characteristic */
static void on_sent(struct bt_conn *conn, void *user_data)
{
	ARG_UNUSED(user_data);

    const bt_addr_le_t * addr = bt_conn_get_dst(conn);
        
	printk("Data sent to Address 0x %02X %02X %02X %02X %02X %02X \n", addr->a.val[0]
                                                                    , addr->a.val[1]
                                                                    , addr->a.val[2]
                                                                    , addr->a.val[3]
                                                                    , addr->a.val[4]
                                                                    , addr->a.val[5]);
}

/* This function is called whenever the CCCD register has been changed by the client*/
void on_cccd_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
    ARG_UNUSED(attr);
    switch(value)
    {
        case BT_GATT_CCC_NOTIFY: 
            printk("CCCD has been set to NOTIFY\n");     
            // Start sending stuff!
            break;

        case BT_GATT_CCC_INDICATE: 
            // Start sending stuff via indications
            printk("CCCD has been set to INDICATE\n");     
            break;

        case 0: 
            // Stop sending stuff
            printk("CCCD has been set to OFF\n");     
            break;
        
        default: 
            printk("Error, CCCD has been set to an invalid value\n");     
    }
}
                        

/* Z9Lock Service Declaration and Registration */
#if defined(USE_SHORT_SERVICE) && USE_SHORT_SERVICE
BT_GATT_SERVICE_DEFINE(z9lock_service,
BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_16(SHORT_SERVICE)),
BT_GATT_CHARACTERISTIC(BT_UUID_DECLARE_16(SHORT_CHAR),
			       BT_GATT_CHRC_WRITE_WITHOUT_RESP | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_WRITE, 
                   NULL, on_receive, data_rx),
BT_GATT_CCC(on_cccd_changed,
                    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);
#else
BT_GATT_SERVICE_DEFINE(z9lock_service,
BT_GATT_PRIMARY_SERVICE(BT_UUID_SERVICE),
BT_GATT_CHARACTERISTIC(BT_UUID_CHAR_RX,
			       BT_GATT_CHRC_WRITE_WITHOUT_RESP | BT_GATT_CHRC_NOTIFY,
			       BT_GATT_PERM_WRITE, 
                   NULL, on_receive, data_rx),
BT_GATT_CCC(on_cccd_changed,
                    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);
#endif

struct notify_data {
	const struct bt_gatt_attr *attr;
	uint16_t handle;
	int err;
	uint16_t type;
	union {
		struct bt_gatt_notify_params *nfy_params;
		struct bt_gatt_indicate_params *ind_params;
	};
};
static uint8_t match_uuid(const struct bt_gatt_attr *attr, uint16_t handle,
			  void *user_data)
{
	struct notify_data *data = static_cast<notify_data *>(user_data);

	data->attr = attr;
	data->handle = handle;

	return BT_GATT_ITER_STOP;
}


static bool gatt_find_by_uuid(struct notify_data *found,
			      const struct bt_uuid *uuid)
{
	found->attr = NULL;

	bt_gatt_foreach_attr_type(found->handle, 0xffff, uuid, NULL, 1,
				  match_uuid, found);

	return found->attr ? true : false;
}


/* This function sends a notification to a Client with the provided data,
given that the Client Characteristic Control Descripter has been set to Notify (0x1).
It also calls the on_sent() callback if successful*/
void my_service_send(struct bt_conn *conn, const uint8_t *data, uint16_t len)
{
	printk("Sending data: conn %p, len: %u, data: 0x", conn, len);
    for(uint8_t i = 0; i < len; i++){
        printk("%02X", data[i]);
    }
    printk("\n");
 
    /* 
    The attribute for the TX characteristic is used with bt_gatt_is_subscribed 
    to check whether notification has been enabled by the peer or not.
    Attribute table: 0 = Service, 1 = Primary service, 2 = RX, 3 = TX, 4 = CCC.
    XXX We don't have TX: Attribute table: 0 = Service, 1 = Primary service, 2 = RX, 3 = CCC.
    */
    const struct bt_gatt_attr *attr = &z9lock_service.attrs[3]; 

    // work around C++ address of temporary issue...
    
#if defined(USE_SHORT_SERVICE) && USE_SHORT_SERVICE
     const bt_uuid_16 uuid = { .uuid = BT_UUID_TYPE_16, .val = { SHORT_CHAR } };
#else
    const bt_uuid_128 uuid = { .uuid = BT_UUID_TYPE_128, .val = { Z9LOCK_UUID_CHARACTERISTIC } };
#endif
    
    struct bt_gatt_notify_params params = 
    {
        //.uuid   = BT_UUID_CHAR_RX,
        .uuid   = (const bt_uuid *)&uuid,
        .attr   = attr,
        .data   = data,
        .len    = len,
        .func   = on_sent
    };

    // Check whether notifications are enabled or not
    if(bt_gatt_is_subscribed(conn, attr, BT_GATT_CCC_NOTIFY)) 
    {
        struct notify_data data;
        auto Xparams = &params;
        __ASSERT(Xparams, "invalid parameters\n");
        __ASSERT(Xparams->attr || Xparams->uuid, "invalid parameters\n");
        
        data.attr = Xparams->attr;
        data.handle = bt_gatt_attr_get_handle(data.attr);

        /* Lookup UUID if it was given */
        if (Xparams->uuid)
        {
            if (!gatt_find_by_uuid(&data, Xparams->uuid)) {
                printk("%s: Error: can't find uuid\n", __func__);
            }
            Xparams->attr = data.attr;
        }
        else
        {
            if (!data.handle) {
                printk("%s: Error: no data handle\n", __func__);
            }
        } 
        
        // Send the notification
        if(auto err = bt_gatt_notify_cb(conn, &params))
        {
            printk("Error, unable to send notification: %d\n", err);
        }
    }
    else
    {
        printk("Warning, notification not enabled on the selected attribute\n");
    }
}