// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file ModelInfo.h
 * @brief Information about the model of hardware that the Z9 Lock firmware is running on
 * @author Z9 Security
 */

#pragma once

#include <cstdint>

// Note that the number of inputs and outputs is the total number of inputs and outputs regardless of whether they are
// managed directly or via z9io.
// Also note: PacketQueue.h PACKET_QUEUE_MAX definition needs to be updated potentially if these are updated.
// Also keep Java and SP-Core ModelInfo up to date with any changes.  Additionally, Java DevAddr.
#define MAX_INPUTS 8
#define MAX_ANALOG_INPUTS 1
#define MAX_OUTPUTS 6

struct ModelInfo
{
	ModelInfo();
	int8_t z9ioModel; ///< the model number expected from z9io
	
	int8_t numInputs;
	int8_t numAnalogInputs;
	int8_t numOutputs;
	
	bool hasKeypad;
	
	int8_t outputIndex_STRIKE; ///< strike couples the exterior handle with the latch, allowing the door to be opened from the outside.
	int8_t outputIndex_READER_RED_LED;
	int8_t outputIndex_READER_GREEN_LED;
	int8_t outputIndex_READER_BEEPER;
	int8_t outputIndex_INTERIOR_RED_LED;
	int8_t outputIndex_INTERIOR_GREEN_LED;
	
	int8_t inputIndex_REX; // really the interior handle?
	int8_t inputIndex_DOOR_CONTACT;
	int8_t inputIndex_IPB;
	int8_t inputIndex_DOOR_LATCH; ///< the sensor that tells whether the actual latch is retracted, allowing the door to open and close.  Note that in a lock, the strike only couples the exterior handle with the latch, the strike does not retract the latch.
	int8_t inputIndex_INTERIOR_HANDLE;
	int8_t inputIndex_EXTERIOR_HANDLE;
	int8_t inputIndex_DEADBOLT;
    int8_t inputIndex_TAMPER;
    int8_t inputIndex_TAC;
	
	int8_t analogInputIndex_BATTERY;

};

extern ModelInfo modelInfo;
