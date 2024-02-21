// Settings.h

enum NVS_KEY { KEY_mode = 1, KEY_lock_public, KEY_noc_public, KEY_noc_derived_key};
static uint8_t lock_public_key[65];
static uint8_t noc_public_key[65];
static uint8_t noc_derived_key[16];

// key handles for PSA
extern psa_key_id_t noc_key_handle;
extern psa_key_id_t mobile_key_handle;
