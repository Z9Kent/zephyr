/**
 * \file aes.h
 *
 * \brief AES block cipher
 *
 *  Copyright (C) 2006-2015, ARM Limited, All Rights Reserved
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of mbed TLS (https://tls.mbed.org)
 */

#pragma once
#define Z9_AES_C 


#include <stddef.h>
#include <stdint.h>

/* padlock.c and aesni.c rely on these values! */
#define Z9_AES_ENCRYPT     1
#define Z9_AES_DECRYPT     0

#define Z9_ERR_AES_INVALID_KEY_LENGTH                -0x0020  /**< Invalid key length. */
#define Z9_ERR_AES_INVALID_INPUT_LENGTH              -0x0022  /**< Invalid data input length. */

#if !defined(Z9_AES_ALT)
// Regular implementation
//

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          AES context structure
 *
 * \note           buf is able to hold 32 extra bytes, which can be used:
 *                 - for alignment purposes if VIA padlock is used, and/or
 *                 - to simplify key expansion in the 256-bit case by
 *                 generating an extra round key
 */
typedef struct
{
    int nr;                     /*!<  number of rounds  */
    uint32_t *rk;               /*!<  AES round keys    */
    uint32_t buf[68];           /*!<  unaligned data    */
}
z9_gcm_c_aes_context;

/**
 * \brief          Initialize AES context
 *
 * \param ctx      AES context to be initialized
 */
void z9_gcm_c_aes_init( z9_gcm_c_aes_context *ctx );

/**
 * \brief          Clear AES context
 *
 * \param ctx      AES context to be cleared
 */
void z9_gcm_c_aes_free( z9_gcm_c_aes_context *ctx );

/**
 * \brief          AES key schedule (encryption)
 *
 * \param ctx      AES context to be initialized
 * \param key      encryption key
 * \param keybits  must be 128, 192 or 256
 *
 * \return         0 if successful, or Z9_ERR_AES_INVALID_KEY_LENGTH
 */
int z9_gcm_c_aes_setkey_enc( z9_gcm_c_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );

/**
 * \brief          AES key schedule (decryption)
 *
 * \param ctx      AES context to be initialized
 * \param key      decryption key
 * \param keybits  must be 128, 192 or 256
 *
 * \return         0 if successful, or Z9_ERR_AES_INVALID_KEY_LENGTH
 */
int z9_gcm_c_aes_setkey_dec( z9_gcm_c_aes_context *ctx, const unsigned char *key,
                    unsigned int keybits );

/**
 * \brief          AES-ECB block encryption/decryption
 *
 * \param ctx      AES context
 * \param mode     Z9_AES_ENCRYPT or Z9_AES_DECRYPT
 * \param input    16-byte input block
 * \param output   16-byte output block
 *
 * \return         0 if successful
 */
int z9_gcm_c_aes_crypt_ecb( z9_gcm_c_aes_context *ctx,
                    int mode,
                    const unsigned char input[16],
                    unsigned char output[16] );

#if defined(Z9_CIPHER_MODE_CBC)
/**
 * \brief          AES-CBC buffer encryption/decryption
 *                 Length should be a multiple of the block
 *                 size (16 bytes)
 *
 * \note           Upon exit, the content of the IV is updated so that you can
 *                 call the function same function again on the following
 *                 block(s) of data and get the same result as if it was
 *                 encrypted in one call. This allows a "streaming" usage.
 *                 If on the other hand you need to retain the contents of the
 *                 IV, you should either save it manually or use the cipher
 *                 module instead.
 *
 * \param ctx      AES context
 * \param mode     Z9_AES_ENCRYPT or Z9_AES_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if successful, or Z9_ERR_AES_INVALID_INPUT_LENGTH
 */
int z9_gcm_c_aes_crypt_cbc( z9_gcm_c_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );
#endif /* Z9_CIPHER_MODE_CBC */

#if defined(Z9_CIPHER_MODE_CFB)
/**
 * \brief          AES-CFB128 buffer encryption/decryption.
 *
 * Note: Due to the nature of CFB you should use the same key schedule for
 * both encryption and decryption. So a context initialized with
 * z9_gcm_c_aes_setkey_enc() for both Z9_AES_ENCRYPT and Z9_AES_DECRYPT.
 *
 * \note           Upon exit, the content of the IV is updated so that you can
 *                 call the function same function again on the following
 *                 block(s) of data and get the same result as if it was
 *                 encrypted in one call. This allows a "streaming" usage.
 *                 If on the other hand you need to retain the contents of the
 *                 IV, you should either save it manually or use the cipher
 *                 module instead.
 *
 * \param ctx      AES context
 * \param mode     Z9_AES_ENCRYPT or Z9_AES_DECRYPT
 * \param length   length of the input data
 * \param iv_off   offset in IV (updated after use)
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if successful
 */
int z9_gcm_c_aes_crypt_cfb128( z9_gcm_c_aes_context *ctx,
                       int mode,
                       size_t length,
                       size_t *iv_off,
                       unsigned char iv[16],
                       const unsigned char *input,
                       unsigned char *output );

/**
 * \brief          AES-CFB8 buffer encryption/decryption.
 *
 * Note: Due to the nature of CFB you should use the same key schedule for
 * both encryption and decryption. So a context initialized with
 * z9_gcm_c_aes_setkey_enc() for both Z9_AES_ENCRYPT and Z9_AES_DECRYPT.
 *
 * \note           Upon exit, the content of the IV is updated so that you can
 *                 call the function same function again on the following
 *                 block(s) of data and get the same result as if it was
 *                 encrypted in one call. This allows a "streaming" usage.
 *                 If on the other hand you need to retain the contents of the
 *                 IV, you should either save it manually or use the cipher
 *                 module instead.
 *
 * \param ctx      AES context
 * \param mode     Z9_AES_ENCRYPT or Z9_AES_DECRYPT
 * \param length   length of the input data
 * \param iv       initialization vector (updated after use)
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 *
 * \return         0 if successful
 */
int z9_gcm_c_aes_crypt_cfb8( z9_gcm_c_aes_context *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output );
#endif /*Z9_CIPHER_MODE_CFB */

#if defined(Z9_CIPHER_MODE_CTR)
/**
 * \brief               AES-CTR buffer encryption/decryption
 *
 * Warning: You have to keep the maximum use of your counter in mind!
 *
 * Note: Due to the nature of CTR you should use the same key schedule for
 * both encryption and decryption. So a context initialized with
 * z9_gcm_c_aes_setkey_enc() for both Z9_AES_ENCRYPT and Z9_AES_DECRYPT.
 *
 * \param ctx           AES context
 * \param length        The length of the data
 * \param nc_off        The offset in the current stream_block (for resuming
 *                      within current cipher stream). The offset pointer to
 *                      should be 0 at the start of a stream.
 * \param nonce_counter The 128-bit nonce and counter.
 * \param stream_block  The saved stream-block for resuming. Is overwritten
 *                      by the function.
 * \param input         The input data stream
 * \param output        The output data stream
 *
 * \return         0 if successful
 */
int z9_gcm_c_aes_crypt_ctr( z9_gcm_c_aes_context *ctx,
                       size_t length,
                       size_t *nc_off,
                       unsigned char nonce_counter[16],
                       unsigned char stream_block[16],
                       const unsigned char *input,
                       unsigned char *output );
#endif /* Z9_CIPHER_MODE_CTR */

/**
 * \brief           Internal AES block encryption function
 *                  (Only exposed to allow overriding it,
 *                  see Z9_AES_ENCRYPT_ALT)
 *
 * \param ctx       AES context
 * \param input     Plaintext block
 * \param output    Output (ciphertext) block
 */
void z9_gcm_c_aes_encrypt( z9_gcm_c_aes_context *ctx,
                          const unsigned char input[16],
                          unsigned char output[16] );

/**
 * \brief           Internal AES block decryption function
 *                  (Only exposed to allow overriding it,
 *                  see Z9_AES_DECRYPT_ALT)
 *
 * \param ctx       AES context
 * \param input     Ciphertext block
 * \param output    Output (plaintext) block
 */
void z9_gcm_c_aes_decrypt( z9_gcm_c_aes_context *ctx,
                          const unsigned char input[16],
                          unsigned char output[16] );

#ifdef __cplusplus
}
#endif

#else  /* Z9_AES_ALT */
#include "aes_alt.h"
#endif /* Z9_AES_ALT */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          Checkup routine
 *
 * \return         0 if successful, or 1 if the test failed
 */
int z9_gcm_c_aes_self_test( int verbose );

#ifdef __cplusplus
}
#endif

#endif /* aes.h */
