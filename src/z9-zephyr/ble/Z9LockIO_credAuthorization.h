// Z9LockIO_keyExchange.h

#include "z9lockio_ble.h"
#include "Z9Crypto_gcm.h"
#include <KernelCharacterBuffer.h>
#include <stdint.h>

#pragma once

// Entrypoint for received message
extern uint64_t mobileID;
extern uint32_t unid;
extern uint8_t  schedMask;
extern gcm_key_id_t mobile_key_handle;

void Z9LockIO_credAuthorization(KCB& kcb, uint8_t key);
