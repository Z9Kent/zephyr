// Z9lock_status.h

/* 
 * Z9LOCK BLE protocol uses device name to identify lock ID & status
 * 
 * Update BLE advertising packet via class `z9lock_status`
 */

#include <stdint.h>
#include <tuple>

#pragma once

enum class LockStatusMode : uint8_t { CONSTRUCTION = 0, PAIRING = 1, NORMAL = 2 };
struct Z9Lock_status
{
	uint64_t lockID;
	LockStatusMode mode;
	bool	 sync_req;
	bool	 battery_low;
	bool	 tamper;

	void set_mode(LockStatusMode mode);	// update "mode"
	void publish() const;				// send to "reader board"
	
	std::tuple<uint8_t const *, unsigned> encode() const;
	bool is_paired() const { return mode == LockStatusMode::NORMAL; }
};

// declare "global" object
extern Z9Lock_status z9lock_status;

extern void led_motor();		// 6 seconds
extern void led_connect(bool);
