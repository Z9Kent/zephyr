// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
//
//  GcmCrypto_KCB.h
//

/**
 * @file GcmCrypto_KCB.h
 *
 * The `GcmCrypto_*_KCB` encrypt & decrypt the content of a properly formatted KCB in place.
 *
 * A properly formatted KCB will have the following format:
 *
 * Headroom: encryption operations modify the initial block of a KCB. The initial block must
 * be formatted as follows:
 *
 * [ empty space allowed ]
 * [ accounting area for GcmCrypto_KCB routines: 8 bytes]
 * [optional prefix prepended to output KCB: prefixLen bytes]
 * [initialization vector: 12 bytes]
 * [tag: 16 bytes]
 *
 * For a packet passed for encryption, a minimum of 36 bytes of header must be present. Additional
 * space is required for any prefix header.
 *
 * For a packet passed for decryption, a minimum of 8 bytes of header must be present. Additional
 * space is required for any prefix header. Before a decrypted packet is returned, the memory occupied
 * by the IV + TAG will be relcaimed and the specified prefix-header will be placed in that memory.
 *
 * NB: generally the KCB will be  encrypted / decrypted in it's entirety. The "length" argument is provided
 * to support packets that have a trailer (such as CRC) which is not part if the data to be processed.
 */

#pragma once

#include "Z9Crypto.h"
#include "KernelCharacterBuffer.h"
#include <cstdint>


// IV arg is for unit test
z9_error_t Z9Crypto_gcm_encrypt_KCB(psa_key_id_t key, KCB& kcb, uint8_t *prefix = {}, uint8_t prefix_len = 0, uint8_t *iv = {});
z9_error_t Z9Crypto_gcm_decrypt_KCB(psa_key_id_t key, KCB& kcb, uint8_t *prefix = {}, uint8_t prefix_len = 0);

#if 0
// the IV argument is for unitTests
error_t GcmCrypto_encrypt_KCB(enum CryptoStream stream,
                              uint8_t *prefix, uint16_t prefixLen,
                              KCB*, uint32_t length, const uint32_t *iv = nullptr);
error_t GcmCrypto_decrypt_KCB(enum CryptoStream stream,
                              uint8_t *prefix, uint16_t prefixLen,
                              KCB&, uint32_t length);
#endif
