// Z9LockIO_keyExchange.h

#include "z9lockio_ble.h"
#include <KernelCharacterBuffer.h>
#include <stdtypes.h>

#pragma once

// Entrypoint for received message
void Z9LockIO_keyExchange(void *arg, KCB& kcb);
