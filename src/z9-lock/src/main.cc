
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/drivers/gpio.h>
#include <soc.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/gap.h>

#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>


#include <zephyr/settings/settings.h>
#include "dk_buttons_and_leds.h"
#include "z9lockio_ble.h"
#include "Eros_protocol.h"
#include <hal/nrf_ficr.h>
#include <nrf.h>
#include <zephyr/drivers/hwinfo.h>
#include <cstring>

LOG_MODULE_REGISTER(z9_ble, LOG_LEVEL_INF);

#define PRIV_STATUS_LED DK_LED2
#define RUN_STATUS_LED DK_LED2
#define RUN_LED_BLINK_INTERVAL 1000

#define SYNC_LED        DK_LED3
#define NO_ACCESS_LED   DK_LED4

#define RED_BUTTON      DK_BTN1_MSK
#define ID64_BUTTON     DK_BTN2_MSK
#define SYNC_BUTTON     DK_BTN3_MSK
#define ACCESS_BUTTON   DK_BTN4_MSK

bool privacy_state;
bool id64_button_state;
bool sync_button_state;
bool access_button_state;
        
static void pairing_expired(struct k_work *work)
{
        printk("%s: expired\n", __func__);
        set_lock_mode();
}

static void perform_reset(struct k_work *work)
{
        printk("%s: expired\n", __func__);
        lock_mode_reset();              // clear flash
        __NVIC_SystemReset();
}

K_WORK_DELAYABLE_DEFINE(pairing_timer, pairing_expired);
K_WORK_DELAYABLE_DEFINE(reset_timer, perform_reset);

static void button_changed(uint32_t button_state, uint32_t has_changed)
{
        auto& lock = z9lock_status;
        if (has_changed & RED_BUTTON)
        {
                bool is_pressed = button_state & RED_BUTTON;
                printk("red: is_pressed: %d\n", is_pressed);

                if (is_pressed)
                        k_work_schedule(&reset_timer, K_SECONDS(10));
                else 
                {
                        k_work_cancel_delayable(&reset_timer);

                        // if in paired, then it's the priv button
                        if (lock.mode == LockStatusMode::NORMAL)
                        {
                                privacy_state ^= 1; //bool(button_state & RED_BUTTON);
                                dk_set_led(PRIV_STATUS_LED, privacy_state);
                        }
                        else
                        {
                                k_work_schedule(&pairing_timer, K_SECONDS(30));
                                lock.mode = LockStatusMode::PAIRING;
                                lock.publish();
                        }
                }

                #if 0
                red_button_state ^= (button_state & RED_BUTTON);
                if (button_state & RED_BUTTON)
                        ++lock_mode;
                if (lock_mode >= 3)
                        lock_mode = 0;

                if (lock_mode == 1)
                        k_work_schedule(&end_pend, K_SECONDS(30));


                lock.mode   = static_cast<LockStatusMode>(lock_mode);
                lock.publish();
                #endif
        }
        if (has_changed & ID64_BUTTON)
        {
                id64_button_state ^= (button_state & ID64_BUTTON);
               
                // clear MSBs
                z9lock_status.lockID &= 0xffff'ffff'ffff'ffff;
                // set according to flag
                z9lock_status.lockID |= static_cast<uint64_t>(id64_button_state)<< 32;
                z9lock_status.publish();
        }
        if (has_changed & SYNC_BUTTON)
        {
                sync_button_state ^= bool(button_state & SYNC_BUTTON);
                dk_set_led(SYNC_LED, sync_button_state);
                
                z9lock_status.sync_req = sync_button_state;
                z9lock_status.publish();

        }
        if (has_changed & ACCESS_BUTTON)
        {
                access_button_state ^= bool(button_state & ACCESS_BUTTON);
                dk_set_led(NO_ACCESS_LED, access_button_state);
        }

        auto lock_mode = static_cast<uint8_t>(lock.mode);
        printk("%s: MODE=%d, PRIV=%d, ID=%d, SYNC=%d, ACCESS=%d\n", __func__, lock_mode, privacy_state, id64_button_state, sync_button_state, access_button_state);

}

static int init_button(void)
{
        int err;

        err = dk_buttons_init(button_changed);
        if (err) {
                printk("Cannot init buttons (err: %d)\n", err);
        }

        return err;
}

#include <psa/crypto.h>
#include <psa/crypto_extra.h>


int main()
{
        int err;

        printk("Starting Z9Lock BLE Test Fixture\n");
        psa_crypto_init();
#ifdef TEST_KEYGEN
            // need new public key for lock
        // 1) generate key pair
        psa_key_handle_t key_handle;
	psa_status_t status;
	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;

	/* Crypto settings for ECDH using the SHA256 hashing algorithm,
	 * the secp256r1 curve
	 */
	psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_DERIVE);
	psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_ECDH);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
	psa_set_key_bits(&key_attributes, 256);

	/* Generate a key pair */
	status = psa_generate_key(&key_attributes, &key_handle);
        if (status)
        {
                printk("%s: psa_generate_key: %d", __func__, status);
                return {};
        }
	psa_reset_key_attributes(&key_attributes);

    // 2) export public key
    size_t olen;
    status = psa_export_public_key(key_handle, lock_public_key, sizeof(lock_public_key), &olen);
        if (status || olen != sizeof(lock_public_key))
        {
                printk("%s: psa_export_public_key: %d, %u bytes generated", __func__, status, olen);
                return {};
        }
#endif

        // print serial number
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

         err = dk_leds_init();
        if (err) {
                printk("LEDs init failed (err %d)\n", err);
                return err;
        }

        err = init_button();
        if (err) {
                printk("Button init failed (err %d)\n", err);
                return err;
        }
        
        err = bt_enable(NULL);
        if (err) {
                printk("Bluetooth init failed (err %d)\n", err);
                return err;
        }

        printk("Bluetooth initialized\n");

        if (IS_ENABLED(CONFIG_SETTINGS)) {
                settings_load();
        }
        
        // update advertising
        auto& lock = z9lock_status;
        lock.lockID = serial_number;
        //lock.lockID = 12345;
        //lock.lockID = 0x11223344;
        set_lock_mode();                // examine nvm
        //lock.mode   = LockStatusMode::PAIRING;
        //lock.mode   = get_lock_mode();
        //lock.mode   = LockStatusMode::NORMAL;
        //lock.battery_low = true;
        //lock.publish();

        // start the Z9 BLE stack
        z9lock_ble_init({});

        printk("Advertising successfully started\n");

        uint8_t blink_status = 0;

        for (;;) {
                auto led = false;
                ++blink_status;
                switch (lock.mode)
                {
                        case LockStatusMode::PAIRING:
                                blink_status %= 5;
                                // FALLSTHRU
                        case LockStatusMode::CONSTRUCTION:
                                led = blink_status & 1;
                                dk_set_led(RUN_STATUS_LED, led);
                                break;
                        default:
                                dk_set_led(RUN_STATUS_LED, 0);
                                return 0;
                                led = blink_status & 2;
                                break;
                }


                k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL/2));
        }
        
        return 0;       
}
