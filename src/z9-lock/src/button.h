// zephyr example: https://www.zephyrproject.org/how-to-debounce-button-inputs-in-a-rtos/
// retreived from https://github.com/ubieda/zephyr_button_debouncing.git
#ifndef _BUTTON_H_
#define _BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

enum button_evt {
    BUTTON_EVT_PRESSED,
    BUTTON_EVT_RELEASED
};

typedef void (*button_event_handler_t)(enum button_evt evt);

int button_init(button_event_handler_t handler);

#ifdef __cplusplus
}
#endif

#endif /* _BUTTON_H_ */
