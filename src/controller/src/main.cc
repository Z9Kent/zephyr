
#include "button.h"
#include "Z9Lock_status.h"
#include "EventDb.h"
#include "Settings.h"

#ifdef CONFIG_Z9_READER
#include "z9lockio_ble.h"
#endif

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>


LOG_MODULE_REGISTER(z9_ble, LOG_LEVEL_INF);
#define RUN_LED_BLINK_INTERVAL 1000

#define GREEN_LED_NODE  DT_ALIAS(led0)
#define RED_LED_NODE    DT_ALIAS(led1)
//#define RED_LED_NODE    DT_ALIAS(led0)
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

static void pairing_expired(struct k_work *work)
{
        printk("%s: expired\n", __func__);
        nvm_settings_set_mode();
}

static void perform_reset(struct k_work *work)
{
        printk("%s: expired\n", __func__);
        nvm_settings_reset();           // clear flash
        //__NVIC_SystemReset();
        abort();
}

static void led_motor_off(struct k_work *work)
{
        set_red_led(0);
}

K_WORK_DELAYABLE_DEFINE(pairing_timer, pairing_expired);
K_WORK_DELAYABLE_DEFINE(reset_timer  , perform_reset);
K_WORK_DELAYABLE_DEFINE(motor_timer  , led_motor_off);

void led_motor()
{
        set_red_led(1);
        k_work_schedule(&motor_timer, K_SECONDS(6));
}

bool privacy_state;
static void button_changed(button_evt evt)
{
        auto&& lock = z9lock_status;
                
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
                        set_red_led(privacy_state);
                }
                else
                {
                        k_work_schedule(&pairing_timer, K_SECONDS(30));
                        lock.set_mode(LockStatusMode::PAIRING);
                }
        }

        auto lock_mode = static_cast<uint8_t>(lock.mode);
        printk("%s: MODE=%d, PRIV=%d\n", __func__, lock_mode, privacy_state);
}



int main()
{
        int err;

        printk("Starting Z9Lock BLE Test Fixture\n");
        //psa_crypto_init();              // XXX
 

#ifdef CONFIG_Z9_READER 
        // start the Z9 BLE stack
        printk("Initializing Bluetooth\n");
        z9lock_ble_init();
#endif

#ifdef CONFIG_Z9_CONTROLLER
        // LEDs & buttons on READER
        err = init_leds();
        if (err) {
                printk("LEDs init failed (err %d)\n", err);
                return err;
        }

        err = button_init(button_changed);
        if (err) {
                printk("Button init failed (err %d)\n", err);
                //return err;
        }
        
        nvm_settings_init();           // read settings: retrive keys & set mode

        // startup complete -- generate an event
        LockEventDb::instance().save(EVT(LockEvtCode_STARTUP));

        // if in construction or pairing mode, blink LED 
        uint8_t blink_status = 0;
        for (;;)
        {
                auto&& lock = z9lock_status;

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
                }

                k_sleep(K_MSEC(RUN_LED_BLINK_INTERVAL/2));
        }
 #endif       
        // NOTREACHED
}
