//
//  GcmCrypto.h
//

// Generic interface to encrypt, decrypt, and hash using the Galois/Counter Mode of AES
//
// This module also allows for GCM encryption of data which provided in discontigous
// chunks of data, divided by time and/or space. The module is designed take the
// multiple chucks of data, collect it into properly page-aligned 128-bit blocks, and
// perform the proper AES opertions on those blocks. 
//
// This module virtualizes the AES encryption hardware to provide several virtual
// encryption channels. Each channel has it's own keys and state and run independently.
// Thus a multi-packet download stream can be interrupted by link or NOC stream w/o
// interference.
//
// The GcmCrypto module manages passing instructions and data to the hardware engine.
// The hardware engine requires 32-bit alignment for all data, and keys. The GcmCrypto
// module provides this alignment. It will also buffer and zero pad AAD and DATA streams
// as required.
//
// Each virtual GCM channel is identified by an `enum CrytpoStream`.
// Before data can be run thru a channel, it must have it's KEY set and specify a
// return route for notifications.
//
// After initialization, each GCM channel expects a sequence of messages in the following order:
//
// specify IV, the aad length, and the text length. Only 96-bit IVs are supported
//z9_error_t gcmCrypto_doNewMessage(GcmCrypto *gcm, const uint8_t *iv, uint32_t aadLength, uint32_t textLength);
//
// process block of aad data
//z9_error_t gcmCrypto_queueProcessAad(GcmCrypto *gcm, const uint8_t *aadPtr, uint32_t bytes);
//
// encrypt block of plain text
//z9_error_t gcmCrypto_queueEncrypt(GcmCrypto *gcm, const uint8_t *plain, uint8_t *out, uint32_t bytes);
//
// decrypt block of cipher text
//z9_error_t gcmCrypto_queueDecrypt(GcmCrypto *gcm, const uint8_t *cipher, uint8_t *out, uint32_t bytes);
//
// generate the TAG (up to 16 bytes of tag can be generated)
//z9_error_t gcmCrypto_queueGenerateTag(GcmCrypto *gcm, uint8_t *tag, uint16_t tagBytes);
//
// The plain & cipher text do not need to be multiples of the 16-byte AES block, nor to they
// have any alignment requirements. The input & output can be the same for encrypt/decrypt in
// place. The output can be omitted (NULL) for validation of tag.


#pragma once

#ifdef CONFIG_Z9_GCM_C

#include "aes-gcm/gcm.h"
#include <cstdint>

// don't use a "enumerated" key slot
// just pass references to 16-byte key for _id_t & _handle_t
using gcm_status_t     = int;
using gcm_key_id_t     = unsigned char[16];
using gcm_key_handle_t = const unsigned char[16];
//using gcm_key_id_t     = z9::z9_gcm::mbedtls_gcm_context;


#else

#include <psa/crypto.h>
#include <psa/crypto_extra.h>
#include <cstdint>

using gcm_status_t     = psa_status_t;
using gcm_key_id_t     = psa_key_id_t;
using gcm_key_handle_t = psa_key_handle_t;

#endif


using z9_error_t = const char *;

// create GSM key from raw bytes
gcm_status_t Z9Crypto_gcmSetKey(gcm_key_id_t& handle, const uint8_t *keyBytes, uint16_t numKeyBytes);

// remove key when complete
void Z9Crypto_destroyKey(gcm_key_id_t& handle);

// generate a 128 bit random number
uint8_t *Z9Crypto_random();

// encrypt / decrypt in place
gcm_status_t Z9Crypto_gcm_encrypt(gcm_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          std::size_t aad_length,
                          uint8_t *text,
                          std::size_t  text_length,
                          uint8_t *tag,
                          std::size_t  tag_length);

gcm_status_t Z9Crypto_gcm_decrypt(gcm_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          std::size_t aad_length,
                          uint8_t *text,
                          std::size_t  text_length,
                          uint8_t *tag,
                          std::size_t  tag_length);

// XXX to be removed
extern uint8_t raw_lock_public_key[33];
extern uint8_t raw_application_key[16];