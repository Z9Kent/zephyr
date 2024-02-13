
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
#include "button.h"
#include "z9lockio_ble.h"
#include "Eros_protocol.h"
#include <zephyr/drivers/hwinfo.h>
#include <cstring>

LOG_MODULE_REGISTER(z9_ble, LOG_LEVEL_INF);
#define RUN_LED_BLINK_INTERVAL 1000

#define GREEN_LED_NODE  DT_ALIAS(led0)
#define RED_LED_NODE    DT_ALIAS(led1)
static const gpio_dt_spec green_led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
static const gpio_dt_spec red_led   = GPIO_DT_SPEC_GET(RED_LED_NODE  , gpios);

static void set_green_led(bool led)
{
        gpio_pin_set_dt(&green_led, led);
}
static void set_red_led(bool led)
{
        gpio_pin_set_dt(&red_led, led);
}
static int init_leds()
{
        int err;
        err = gpio_is_ready_dt(&green_led);
        if (err < 0) return err;
     	err = gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_ACTIVE);
        if (err < 0) return err;
        err = gpio_is_ready_dt(&red_led);
        if (err < 0) return err;
     	err = gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_ACTIVE);
        if (err < 0) return err;
        set_green_led(0);
        set_red_led(0);
        return 0;
}

bool privacy_state;
        
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

static void button_changed(button_evt evt)
{
        static bool was_pressed = false;
        auto& lock = z9lock_status;
                
        bool is_pressed = evt == BUTTON_EVT_PRESSED;
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
                        //dk_set_led(PRIV_STATUS_LED, privacy_state);
                        set_red_led(privacy_state);
                }
                else
                {
                        k_work_schedule(&pairing_timer, K_SECONDS(30));
                        lock.mode = LockStatusMode::PAIRING;
                        lock.publish();
                }
        }

        
        auto lock_mode = static_cast<uint8_t>(lock.mode);
        printk("%s: MODE=%d, PRIV=%d\n", __func__, lock_mode, privacy_state);

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

        err = init_leds();
        if (err) {
                printk("LEDs init failed (err %d)\n", err);
                return err;
        }

        err = button_init(button_changed);
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
        set_lock_mode();                // examine nvm

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
                                set_green_led(led);
                                break;
                        default:
                                set_green_led(0);
                                return 0;
                                led = blink_status & 2;
                                break;
                }

                k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL/2));
        }
        
        return 0;       
}
