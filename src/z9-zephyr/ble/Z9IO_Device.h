
/**
 * @file
 * @brief API for Z9IO Physical Layer 
 *
 */


#pragma once

#include "KernelCharacterBuffer.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// XXX move to KConfig
#define CONFIG_Z9IO_INSTANCES   1
#define CONFIG_Z9IO_LOG_LEVEL   3

// forward declare implementation data
struct z9io_device;

/**
 * @brief Set Z9IO Link Controller callback pointers
 *
 * 
 */
struct z9io_device *
	Z9IO_device_init(unsigned ordinal, const struct device *dev);

/**
 * @brief Function to begin KCB transmission
 *
 * KCB does not include the initial FLAG nor trailing 16-bit CRC.
 * The calculated CRC is passed separately.
 * 
 * The Driver exec `tx_return` when transmission is complete
 */
void Z9IO_device_xmit(struct z9io_device *, kcb_t *, uint16_t crc, struct k_work *tx_return);

/**
 * @brief Function to enable Z9IO receiver
 *
 * The receiver performs the following:
 * 1) It starts timer for completion
 * 2) It scans for Z9IO_FLAG, absorbing characters until received
 * 3) It scans for 16-bit length (network order) and places in KCB
 * 4) It receives `length` additional characters, less FLAG, length and CRC (5 characters)
 * 5) It receives two CRC characters at `crc *`
 * 6) It stops timer and execs `rx_return`
 * 
 * If the timer expires, a `Z9IO_FLAG` is prepended to the buffer indicating error
 * If a receive error occurs (eg framing error), two `Z9IO_FLAG`s are prepended
 */
void Z9IO_device_recv(struct z9io_device *, kcb_t *, uint16_t *crc, struct k_work *rx_return, unsigned msec);

/**
 * @brief Function to disable receiver
 * 
 * Returns true if receiver was active
 * 
 */
bool Z9IO_device_recv_disable(struct z9io_device *);

// link level flag
#define Z9IO_FLAG   0x7f

#ifdef __cplusplus
}
#endif