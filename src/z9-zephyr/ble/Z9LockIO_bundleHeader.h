// Z9LockIO_keyExchange.h

#include "z9lockio_ble.h"
#include <KernelCharacterBuffer.h>

#pragma once

// semi-global variables...
extern uint8_t  sourceType, interType, destType;
extern uint64_t sourceID  , interID  , destID;
extern bool    opaque;
extern uint8_t packetCount;

// Entrypoint for received message
void Z9LockIO_bundleHeader(KCB& kcb, uint8_t key);
