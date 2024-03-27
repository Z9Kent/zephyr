// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @brief Uart I/O interrupt handler for Z9IO
 *
 * In Zephyr, interrupt handlers can not be written in C++, but must be coded in C.
 * This module provides interrupt services and is closely coupled with associated   
 * Z9IO_Link.cpp object.
 * 
 * 
 */


#include "Z9IO_Device.h"
#include "Crc16.h"

#include <zephyr/kernel.h>
#include <zephyr/sys_clock.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/logging/log.h>
#include <stdint.h>

LOG_MODULE_DECLARE(z9io, CONFIG_Z9IO_LOG_LEVEL);


enum XMIT_STATE { XMIT_STATE_IDLE, XMIT_STATE_BUSY, XMIT_STATE_CRC1, XMIT_STATE_CRC2, NUM_XMIT_STATE };
enum RECV_STATE { RECV_STATE_IDLE, RECV_STATE_WAIT_FLAG, RECV_STATE_WAIT_COUNT1, RECV_STATE_WAIT_COUNT2,
        RECV_STATE_DATA, RECV_STATE_CRC1, RECV_STATE_CRC2, RECV_STATE_CRC_ERR, RECV_STATE_IGNORE, NUM_RECV_STATE };

// instance data
struct z9io_device
{
	const struct device *dev;

	// z9io_link interface
	struct k_work *xmit_return, *recv_return;
	kcb_t *xmit_kcb, *recv_kcb;
	uint16_t *recv_crc_p;
	struct k_work_delayable rx_timeout;
    
	// timeout for receiver
	struct k_work_delayable timeout_work;

	// working state
	uint8_t xmit_state, recv_state;
	int16_t recv_count;
	uint16_t xmit_crc;
};

#define Z9IO_DEVICE_MAX_RECEIVE 1000
#define CONFIG_Z9IO_INSTANCES   1

// send block: exec `tx_return` when complete
void Z9IO_device_xmit(struct z9io_device *p, kcb_t *kcb, uint16_t crc, struct k_work *xmit_return)
{
	//LOG_INF("%s: KCB=%u", __func__, kcb_ident(kcb));
    // manipulate kcb_t: prepend network order length to header
    uint32_t length = kcb_size(kcb) + 5;
    kcb_push(kcb, length);
    kcb_push(kcb, length >> 8);
    kcb_top (kcb);                  	// set RW pointer
    kcb_consumeHeadroom(kcb, 2);      	// remove header w/o disturbing RW pointer

    // update state & transmit inital flag
	p->xmit_return = xmit_return;
    p->xmit_kcb   = kcb;
    p->xmit_crc   = Crc16_updateCrc(Crc16_INITIAL_VALUE, Z9IO_FLAG);
    p->xmit_state = XMIT_STATE_BUSY;
    uint8_t c = Z9IO_FLAG;
    uart_fifo_fill(p->dev, &c, sizeof(c));
    uart_irq_tx_enable(p->dev);
}

void Z9IO_device_recv(struct z9io_device *p, kcb_t *kcb, uint16_t *crc_p, struct k_work *recv_return, unsigned msec)
{
	//LOG_INF("%s: KCB=%u", __func__, kcb_ident(kcb));
 
    // TODO: neither `recv_enable` nor `recv_disable` flush fifo,
    // though data will be discarded intil Z9IO_FLAG
	p->recv_kcb    = kcb;
	p->recv_crc_p  = crc_p;
	p->recv_return = recv_return;
    
	// set timeout
	if (msec)
		k_work_schedule(&p->timeout_work, K_MSEC(msec));

	p->recv_state = kcb ? RECV_STATE_WAIT_FLAG : RECV_STATE_IGNORE;
	uart_irq_rx_enable(p->dev);
}

bool Z9IO_device_recv_disable(struct z9io_device *p)
{
    // TODO: neither `recv_enable` nor `recv_disable` flush fifo,
    uart_irq_rx_disable(p->dev); 
 	k_work_cancel_delayable(&p->timeout_work);  
	p->recv_state = RECV_STATE_IDLE;
	return false;
}

/**
 * @brief Z9IO Transmit character interrupt handler
 * 
 * @param dev 
 * @param p 
 *
 * Send characters from kcb_t while calculating the CRC.
 * At end of kcb_t, send CRC, then `notify` link controller via `tx_work`
 */
static void z9io_device_process_xmit(const struct device *dev, struct z9io_device *p)
{
	switch (p->xmit_state)
	{
		case XMIT_STATE_BUSY:
			// xmit next character
			if (!kcb_empty(p->xmit_kcb))
			{
				// NB: uart_fifo_fill data arg is `const *`
				uint8_t c;
				kcb_read(p->xmit_kcb, &c);
				uart_fifo_fill(dev, &c, sizeof(c));
				p->xmit_crc = Crc16_updateCrc(p->xmit_crc, c);
			}
			else
			{
				// at EOB: send first CRC character
				p->xmit_state = XMIT_STATE_CRC1;
				uint8_t c = p->xmit_crc >> 8;	// MSBs
				uart_fifo_fill(dev, &c, sizeof(c));
			}
			break;
		
		case XMIT_STATE_CRC1:
			// at EOB: send first CRC character
			p->xmit_state = XMIT_STATE_CRC2;
			uint8_t c = p->xmit_crc; 			// LSBs
			uart_fifo_fill(dev, &c, sizeof(c));
			break;
		
		case XMIT_STATE_CRC2:	
			// transmission complete: notify link controller
			p->xmit_state = XMIT_STATE_IDLE;
			uart_irq_tx_disable(dev);
			k_work_submit(p->xmit_return);
			break;

		case XMIT_STATE_IDLE:
		default:
			k_panic();
	}
}

/**
 * @brief Receive character interrupt handler
 * 
 * @param dev 
 * @param p 
 *
 * Monitor incoming character stream for properly formatted Z9IO packet in supplied kcb_t.
 * Look for initial framing character. Place other received characters in buffer.
 * Calculate CRC on incoming character stream. 
 *
 * At end of packet, the CRC is checked and the link handler is notified.
 *
 * The received buffer does not include the initial framing character nor the CRC.
 */
static void z9io_device_process_recv(const struct device *dev, struct z9io_device *p)
{
	// must always consume the character
	char c;
	int len = uart_fifo_read(dev, &c, sizeof(c));

	// process character based on state
	if (len > 0)
	{
		//LOG_INF("rx: %02x", c);
		switch (p->recv_state)
		{
			case RECV_STATE_WAIT_FLAG:
				if (c != Z9IO_FLAG)
				{
					LOG_INF("%s: ignoring: %02x", __func__, c);
					break;
				}
				p->recv_state = RECV_STATE_WAIT_COUNT1;
				break;

			case RECV_STATE_WAIT_COUNT1:
				p->recv_count = c << 8;				// 16-bit count: network order
				p->recv_state = RECV_STATE_WAIT_COUNT2;
				break;

			case RECV_STATE_WAIT_COUNT2:
				p->recv_count += c;					// 16-bit count: network order
				p->recv_state = RECV_STATE_DATA;

				// adjust count: FLAG, 16-bit count, & 16-bit CRC included in byte count
				p->recv_count -= 5;
				
				// disallow invalid count
				//LOG_INF("%s: count=%d", __func__, p->recv_count);
				if (p->recv_count > Z9IO_DEVICE_MAX_RECEIVE ||
					p->recv_count <= 0)
					p->recv_state = RECV_STATE_IDLE;		// just time out
				break;

			case RECV_STATE_DATA:
				// store count bytes of "data" in kcb_t
				kcb_write(p->recv_kcb, c);

				if (!--p->recv_count)
					p->recv_state = RECV_STATE_CRC1;
				break;

			case RECV_STATE_CRC1:
				// receive data complete: check first CRC byte
				//LOG_INF("crc1: %02x", c);
				*p->recv_crc_p = c << 8;	
				p->recv_state = RECV_STATE_CRC2;
				break;

			case RECV_STATE_CRC2:
				// receive data complete: check second CRC byte
				//LOG_INF("crc2: %02x", c);
				*p->recv_crc_p  += c;	
			
				// notify receive complete
				k_work_cancel_delayable(&p->timeout_work);
				k_work_submit(p->recv_return);
				
				// ignore further data
				p->recv_state = RECV_STATE_IDLE;
				break;	

			case RECV_STATE_IDLE:
			case RECV_STATE_IGNORE:
			default:
				// Receive not active: ignore character
				break;
		}
	}
}

static void recv_timeout(struct k_work *cb)
{
	//LOG_INF("%s", __func__);
    
	// get instance from callback
    struct z9io_device *p = CONTAINER_OF(cb, struct z9io_device, timeout_work.work);
	//LOG_INF("recv status: count=%d, state=%d", p->recv_count, p->recv_state);
	//LOG_INF("uart_rx_stop_reason: %d", uart_err_check(p->dev));
	p->recv_state = RECV_STATE_IDLE;

	if (p->recv_kcb)
		kcb_push(p->recv_kcb, Z9IO_FLAG);

	k_work_submit(p->recv_return);
	uart_err_check(p->dev);			// read & clear errors ???
    uart_irq_rx_disable(p->dev);
}

/**
 * @brief Zephyr interrupt handler for UART device
 * 
 * @param dev 
 * @param instance
 *
 * Actual Zephyr UART interrupt handler: dispatch to XMIT or RECV as required. 
 */
static void z9io_device_uart_isr(const struct device *dev, void *instance)
{
	struct z9io_device *p = instance;

	while (uart_irq_update(dev) && uart_irq_is_pending(dev))
	{
		if (uart_irq_rx_ready(dev))
			z9io_device_process_recv(dev, p);
		
		if (uart_irq_tx_ready(dev))
			z9io_device_process_xmit(dev, p);
	}  	
}

struct z9io_device *
	Z9IO_device_init(unsigned ordinal, const struct device *dev)
{
    static struct z9io_device z9io_devices_instances[CONFIG_Z9IO_INSTANCES];
	__ASSERT(ordinal <= CONFIG_Z9IO_INSTANCES, "%s: device instance out-of-range: %u", __func__, ordinal);
	
    // retrieve intance number from zephry device entry
	struct z9io_device *p = &z9io_devices_instances[ordinal];
    p->dev = dev;

    // get selected device
	if (!device_is_ready(dev))
	{
		LOG_ERR("Z9IO DEVICE: UART dev is not ready");
		k_panic();
	}

	/* configure uart device to 8N1 */
    // XXX isn't this done via board config
    struct uart_config config = {};

	config.baudrate  = 115200;
	config.data_bits = UART_CFG_DATA_BITS_8;
	config.parity    = UART_CFG_PARITY_NONE;
	config.stop_bits = UART_CFG_STOP_BITS_1;
	config.flow_ctrl = UART_CFG_FLOW_CTRL_NONE;
	//uart_configure(p->dev, &config);

	// for some reason, K_WORK_DELAYABLE_DEFINE doesn't compile
	// just initialize at runtime
	k_work_init_delayable(&p->timeout_work, recv_timeout);

	uart_irq_rx_disable(p->dev);
	uart_irq_tx_disable(p->dev);
	uart_irq_callback_user_data_set(p->dev, z9io_device_uart_isr, p);

	LOG_INF("Z9IO DEVICE: init okay!");
    return p;
}
