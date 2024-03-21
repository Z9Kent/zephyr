// Z9LockIO_ECDH.h

#include "z9lockio_ble.h"
#include <KernelCharacterBuffer.h>
#include <stdint.h>

#pragma once

// Entrypoint for received message
typedef void (*ECDH_rsp_fn)(void *arg, const uint8_t *localPublic, uint16_t keyLength);
void Z9LockIO_performECDH(void *arg, ECDH_rsp_fn, const uint8_t *nocPublic, uint16_t keyLength);




