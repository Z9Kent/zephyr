// Settings.h

#include <stdint.h>

#include "Z9Crypto_gcm.h"

#pragma once

enum NVS_KEY { KEY_mode = 1, KEY_lock_public, KEY_noc_public, KEY_noc_derived_key};
extern uint8_t lock_public_key[65];
extern uint8_t noc_public_key[65];
extern uint8_t noc_derived_key[16];

// key handles for PSA
extern gcm_key_id_t noc_key_handle;

#ifdef CONFIG_Z9_CONTROLLER

void nvm_settings_reset();
void nvm_settings_init();
void nvm_settings_save_keys();

#endif
