// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file ModelInfo.c
 * @author Z9 Security
 */

#include "ModelInfo.h"

ModelInfo modelInfo;

ModelInfo::ModelInfo()
{
	z9ioModel = 20; // should match up with what is in ModelInfo.java for DevMod.DOOR_Z9_LOCK
	
	numInputs = MAX_INPUTS;
	numAnalogInputs = MAX_ANALOG_INPUTS;
	numOutputs = MAX_OUTPUTS;
	
	// these addresses don't actually have to correspond to any particular physical addresses, they
	// can be "mapped" by the platform-specific implementation to the right values if needed.
	
	outputIndex_STRIKE = 0;
	outputIndex_READER_RED_LED = 1;
	outputIndex_READER_GREEN_LED = 2;
	outputIndex_READER_BEEPER = 3;
	outputIndex_INTERIOR_RED_LED = 4;
	outputIndex_INTERIOR_GREEN_LED = 5;

	inputIndex_REX = 0;
	inputIndex_DOOR_CONTACT = 1;
	inputIndex_IPB = 2;
	inputIndex_DOOR_LATCH = 3;
	inputIndex_INTERIOR_HANDLE = 4;
	inputIndex_EXTERIOR_HANDLE = 5;
	inputIndex_DEADBOLT = 6;
	inputIndex_TAMPER = 7;
 	inputIndex_TAC = 8;
	
	analogInputIndex_BATTERY = 0;
}

