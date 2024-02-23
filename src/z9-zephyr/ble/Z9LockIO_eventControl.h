// Z9LockIO_keyExchange.h

#include "z9lockio_ble.h"
#include "EventDb.h"
#include <KernelCharacterBuffer.h>
#include <stdint.h>

#pragma once

// Entrypoint for received message
void Z9LockIO_eventControl(KCB& kcb, uint8_t key);

