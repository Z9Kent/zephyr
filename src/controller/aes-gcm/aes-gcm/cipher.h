/**
 * \file cipher.h
 *
 * \brief Generic cipher wrapper.
 *
 * \author Adriaan de Jong <dejong@fox-it.com>
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

#if !defined(Z9_CONFIG_FILE)
#include "config.h"
#else
#include Z9_CONFIG_FILE
#endif

#include <stddef.h>

#if defined(Z9_GCM_C) || defined(Z9_CCM_C)
#define Z9_CIPHER_MODE_AEAD
#endif

#if defined(Z9_CIPHER_MODE_CBC)
#define Z9_CIPHER_MODE_WITH_PADDING
#endif

#if defined(Z9_ARC4_C)
#define Z9_CIPHER_MODE_STREAM
#endif

#if ( defined(__ARMCC_VERSION) || defined(_MSC_VER) ) && \
    !defined(inline) && !defined(__cplusplus)
#define inline __inline
#endif

#define Z9_ERR_CIPHER_FEATURE_UNAVAILABLE            -0x6080  /**< The selected feature is not available. */
#define Z9_ERR_CIPHER_BAD_INPUT_DATA                 -0x6100  /**< Bad input parameters to function. */
#define Z9_ERR_CIPHER_ALLOC_FAILED                   -0x6180  /**< Failed to allocate memory. */
#define Z9_ERR_CIPHER_INVALID_PADDING                -0x6200  /**< Input data contains invalid padding and is rejected. */
#define Z9_ERR_CIPHER_FULL_BLOCK_EXPECTED            -0x6280  /**< Decryption of block requires a full block. */
#define Z9_ERR_CIPHER_AUTH_FAILED                    -0x6300  /**< Authentication failed (for AEAD modes). */

#define Z9_CIPHER_VARIABLE_IV_LEN     0x01    /**< Cipher accepts IVs of variable length */
#define Z9_CIPHER_VARIABLE_KEY_LEN    0x02    /**< Cipher accepts keys of variable length */

namespace z9::z9_gcm
{

typedef enum {
    Z9_CIPHER_ID_NONE = 0,
    Z9_CIPHER_ID_NULL,
    Z9_CIPHER_ID_AES,
    Z9_CIPHER_ID_DES,
    Z9_CIPHER_ID_3DES,
    Z9_CIPHER_ID_CAMELLIA,
    Z9_CIPHER_ID_BLOWFISH,
    Z9_CIPHER_ID_ARC4,
} mbedtls_cipher_id_t;

typedef enum {
    Z9_CIPHER_NONE = 0,
    Z9_CIPHER_NULL,
    Z9_CIPHER_AES_128_ECB,
    Z9_CIPHER_AES_192_ECB,
    Z9_CIPHER_AES_256_ECB,
    Z9_CIPHER_AES_128_CBC,
    Z9_CIPHER_AES_192_CBC,
    Z9_CIPHER_AES_256_CBC,
    Z9_CIPHER_AES_128_CFB128,
    Z9_CIPHER_AES_192_CFB128,
    Z9_CIPHER_AES_256_CFB128,
    Z9_CIPHER_AES_128_CTR,
    Z9_CIPHER_AES_192_CTR,
    Z9_CIPHER_AES_256_CTR,
    Z9_CIPHER_AES_128_GCM,
    Z9_CIPHER_AES_192_GCM,
    Z9_CIPHER_AES_256_GCM,
    Z9_CIPHER_CAMELLIA_128_ECB,
    Z9_CIPHER_CAMELLIA_192_ECB,
    Z9_CIPHER_CAMELLIA_256_ECB,
    Z9_CIPHER_CAMELLIA_128_CBC,
    Z9_CIPHER_CAMELLIA_192_CBC,
    Z9_CIPHER_CAMELLIA_256_CBC,
    Z9_CIPHER_CAMELLIA_128_CFB128,
    Z9_CIPHER_CAMELLIA_192_CFB128,
    Z9_CIPHER_CAMELLIA_256_CFB128,
    Z9_CIPHER_CAMELLIA_128_CTR,
    Z9_CIPHER_CAMELLIA_192_CTR,
    Z9_CIPHER_CAMELLIA_256_CTR,
    Z9_CIPHER_CAMELLIA_128_GCM,
    Z9_CIPHER_CAMELLIA_192_GCM,
    Z9_CIPHER_CAMELLIA_256_GCM,
    Z9_CIPHER_DES_ECB,
    Z9_CIPHER_DES_CBC,
    Z9_CIPHER_DES_EDE_ECB,
    Z9_CIPHER_DES_EDE_CBC,
    Z9_CIPHER_DES_EDE3_ECB,
    Z9_CIPHER_DES_EDE3_CBC,
    Z9_CIPHER_BLOWFISH_ECB,
    Z9_CIPHER_BLOWFISH_CBC,
    Z9_CIPHER_BLOWFISH_CFB64,
    Z9_CIPHER_BLOWFISH_CTR,
    Z9_CIPHER_ARC4_128,
    Z9_CIPHER_AES_128_CCM,
    Z9_CIPHER_AES_192_CCM,
    Z9_CIPHER_AES_256_CCM,
    Z9_CIPHER_CAMELLIA_128_CCM,
    Z9_CIPHER_CAMELLIA_192_CCM,
    Z9_CIPHER_CAMELLIA_256_CCM,
} mbedtls_cipher_type_t;

typedef enum {
    Z9_MODE_NONE = 0,
    Z9_MODE_ECB,
    Z9_MODE_CBC,
    Z9_MODE_CFB,
    Z9_MODE_OFB, /* Unused! */
    Z9_MODE_CTR,
    Z9_MODE_GCM,
    Z9_MODE_STREAM,
    Z9_MODE_CCM,
} mbedtls_cipher_mode_t;

typedef enum {
    Z9_PADDING_PKCS7 = 0,     /**< PKCS7 padding (default)        */
    Z9_PADDING_ONE_AND_ZEROS, /**< ISO/IEC 7816-4 padding         */
    Z9_PADDING_ZEROS_AND_LEN, /**< ANSI X.923 padding             */
    Z9_PADDING_ZEROS,         /**< zero padding (not reversible!) */
    Z9_PADDING_NONE,          /**< never pad (full blocks only)   */
} mbedtls_cipher_padding_t;

typedef enum {
    Z9_OPERATION_NONE = -1,
    Z9_DECRYPT = 0,
    Z9_ENCRYPT,
} mbedtls_operation_t;

enum {
    /** Undefined key length */
    Z9_KEY_LENGTH_NONE = 0,
    /** Key length, in bits (including parity), for DES keys */
    Z9_KEY_LENGTH_DES  = 64,
    /** Key length, in bits (including parity), for DES in two key EDE */
    Z9_KEY_LENGTH_DES_EDE = 128,
    /** Key length, in bits (including parity), for DES in three-key EDE */
    Z9_KEY_LENGTH_DES_EDE3 = 192,
};

/** Maximum length of any IV, in bytes */
#define Z9_MAX_IV_LENGTH      16
/** Maximum block size of any cipher, in bytes */
#define Z9_MAX_BLOCK_LENGTH   16

/**
 * Base cipher information (opaque struct).
 */
typedef struct mbedtls_cipher_base_t mbedtls_cipher_base_t;

/**
 * Cipher information. Allows cipher functions to be called in a generic way.
 */
typedef struct {
    /** Full cipher identifier (e.g. Z9_CIPHER_AES_256_CBC) */
    mbedtls_cipher_type_t type;

    /** Cipher mode (e.g. Z9_MODE_CBC) */
    mbedtls_cipher_mode_t mode;

    /** Cipher key length, in bits (default length for variable sized ciphers)
     *  (Includes parity bits for ciphers like DES) */
    unsigned int key_bitlen;

    /** Name of the cipher */
    const char * name;

    /** IV/NONCE size, in bytes.
     *  For cipher that accept many sizes: recommended size */
    unsigned int iv_size;

    /** Flags for variable IV size, variable key size, etc. */
    int flags;

    /** block size, in bytes */
    unsigned int block_size;

    /** Base cipher information and functions */
    const mbedtls_cipher_base_t *base;

} mbedtls_cipher_info_t;

/**
 * Generic cipher context.
 */
typedef struct {
    /** Information about the associated cipher */
    const mbedtls_cipher_info_t *cipher_info;

    /** Key length to use */
    int key_bitlen;

    /** Operation that the context's key has been initialised for */
    mbedtls_operation_t operation;

#if defined(Z9_CIPHER_MODE_WITH_PADDING)
    /** Padding functions to use, if relevant for cipher mode */
    void (*add_padding)( unsigned char *output, size_t olen, size_t data_len );
    int (*get_padding)( unsigned char *input, size_t ilen, size_t *data_len );
#endif

    /** Buffer for data that hasn't been encrypted yet */
    unsigned char unprocessed_data[Z9_MAX_BLOCK_LENGTH];

    /** Number of bytes that still need processing */
    size_t unprocessed_len;

    /** Current IV or NONCE_COUNTER for CTR-mode */
    unsigned char iv[Z9_MAX_IV_LENGTH];

    /** IV size in bytes (for ciphers with variable-length IVs) */
    size_t iv_size;

    /** Cipher-specific context */
    void *cipher_ctx;
} mbedtls_cipher_context_t;

/**
 * \brief Returns the list of ciphers supported by the generic cipher module.
 *
 * \return              a statically allocated array of ciphers, the last entry
 *                      is 0.
 */
const int *mbedtls_cipher_list( void );

/**
 * \brief               Returns the cipher information structure associated
 *                      with the given cipher name.
 *
 * \param cipher_name   Name of the cipher to search for.
 *
 * \return              the cipher information structure associated with the
 *                      given cipher_name, or NULL if not found.
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_string( const char *cipher_name );

/**
 * \brief               Returns the cipher information structure associated
 *                      with the given cipher type.
 *
 * \param cipher_type   Type of the cipher to search for.
 *
 * \return              the cipher information structure associated with the
 *                      given cipher_type, or NULL if not found.
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_type( const mbedtls_cipher_type_t cipher_type );

/**
 * \brief               Returns the cipher information structure associated
 *                      with the given cipher id, key size and mode.
 *
 * \param cipher_id     Id of the cipher to search for
 *                      (e.g. Z9_CIPHER_ID_AES)
 * \param key_bitlen    Length of the key in bits
 * \param mode          Cipher mode (e.g. Z9_MODE_CBC)
 *
 * \return              the cipher information structure associated with the
 *                      given cipher_type, or NULL if not found.
 */
const mbedtls_cipher_info_t *mbedtls_cipher_info_from_values( const mbedtls_cipher_id_t cipher_id,
                                              int key_bitlen,
                                              const mbedtls_cipher_mode_t mode );

/**
 * \brief               Initialize a cipher_context (as NONE)
 */
void mbedtls_cipher_init( mbedtls_cipher_context_t *ctx );

/**
 * \brief               Free and clear the cipher-specific context of ctx.
 *                      Freeing ctx itself remains the responsibility of the
 *                      caller.
 */
void mbedtls_cipher_free( mbedtls_cipher_context_t *ctx );

/**
 * \brief               Initialises and fills the cipher context structure with
 *                      the appropriate values.
 *
 * \note                Currently also clears structure. In future versions you
 *                      will be required to call mbedtls_cipher_init() on the structure
 *                      first.
 *
 * \param ctx           context to initialise. May not be NULL.
 * \param cipher_info   cipher to use.
 *
 * \return              0 on success,
 *                      Z9_ERR_CIPHER_BAD_INPUT_DATA on parameter failure,
 *                      Z9_ERR_CIPHER_ALLOC_FAILED if allocation of the
 *                      cipher-specific context failed.
 */
int mbedtls_cipher_setup( mbedtls_cipher_context_t *ctx, const mbedtls_cipher_info_t *cipher_info );

/**
 * \brief               Returns the block size of the given cipher.
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              size of the cipher's blocks, or 0 if ctx has not been
 *                      initialised.
 */
static inline unsigned int mbedtls_cipher_get_block_size( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return 0;

    return ctx->cipher_info->block_size;
}

/**
 * \brief               Returns the mode of operation for the cipher.
 *                      (e.g. Z9_MODE_CBC)
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              mode of operation, or Z9_MODE_NONE if ctx
 *                      has not been initialised.
 */
static inline mbedtls_cipher_mode_t mbedtls_cipher_get_cipher_mode( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return Z9_MODE_NONE;

    return ctx->cipher_info->mode;
}

/**
 * \brief               Returns the size of the cipher's IV/NONCE in bytes.
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              If IV has not been set yet: (recommended) IV size
 *                      (0 for ciphers not using IV/NONCE).
 *                      If IV has already been set: actual size.
 */
static inline int mbedtls_cipher_get_iv_size( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return 0;

    if( ctx->iv_size != 0 )
        return (int) ctx->iv_size;

    return (int) ctx->cipher_info->iv_size;
}

/**
 * \brief               Returns the type of the given cipher.
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              type of the cipher, or Z9_CIPHER_NONE if ctx has
 *                      not been initialised.
 */
static inline mbedtls_cipher_type_t mbedtls_cipher_get_type( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return Z9_CIPHER_NONE;

    return ctx->cipher_info->type;
}

/**
 * \brief               Returns the name of the given cipher, as a string.
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              name of the cipher, or NULL if ctx was not initialised.
 */
static inline const char *mbedtls_cipher_get_name( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return 0;

    return ctx->cipher_info->name;
}

/**
 * \brief               Returns the key length of the cipher.
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              cipher's key length, in bits, or
 *                      Z9_KEY_LENGTH_NONE if ctx has not been
 *                      initialised.
 */
static inline int mbedtls_cipher_get_key_bitlen( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return Z9_KEY_LENGTH_NONE;

    return (int) ctx->cipher_info->key_bitlen;
}

/**
 * \brief               Returns the operation of the given cipher.
 *
 * \param ctx           cipher's context. Must have been initialised.
 *
 * \return              operation (Z9_ENCRYPT or Z9_DECRYPT),
 *                      or Z9_OPERATION_NONE if ctx has not been
 *                      initialised.
 */
static inline mbedtls_operation_t mbedtls_cipher_get_operation( const mbedtls_cipher_context_t *ctx )
{
    if( NULL == ctx || NULL == ctx->cipher_info )
        return Z9_OPERATION_NONE;

    return ctx->operation;
}

/**
 * \brief               Set the key to use with the given context.
 *
 * \param ctx           generic cipher context. May not be NULL. Must have been
 *                      initialised using cipher_context_from_type or
 *                      cipher_context_from_string.
 * \param key           The key to use.
 * \param key_bitlen    key length to use, in bits.
 * \param operation     Operation that the key will be used for, either
 *                      Z9_ENCRYPT or Z9_DECRYPT.
 *
 * \returns             0 on success, Z9_ERR_CIPHER_BAD_INPUT_DATA if
 *                      parameter verification fails or a cipher specific
 *                      error code.
 */
int mbedtls_cipher_setkey( mbedtls_cipher_context_t *ctx, const unsigned char *key,
                   int key_bitlen, const mbedtls_operation_t operation );

#if defined(Z9_CIPHER_MODE_WITH_PADDING)
/**
 * \brief               Set padding mode, for cipher modes that use padding.
 *                      (Default: PKCS7 padding.)
 *
 * \param ctx           generic cipher context
 * \param mode          padding mode
 *
 * \returns             0 on success, Z9_ERR_CIPHER_FEATURE_UNAVAILABLE
 *                      if selected padding mode is not supported, or
 *                      Z9_ERR_CIPHER_BAD_INPUT_DATA if the cipher mode
 *                      does not support padding.
 */
int mbedtls_cipher_set_padding_mode( mbedtls_cipher_context_t *ctx, mbedtls_cipher_padding_t mode );
#endif /* Z9_CIPHER_MODE_WITH_PADDING */

/**
 * \brief               Set the initialization vector (IV) or nonce
 *
 * \param ctx           generic cipher context
 * \param iv            IV to use (or NONCE_COUNTER for CTR-mode ciphers)
 * \param iv_len        IV length for ciphers with variable-size IV;
 *                      discarded by ciphers with fixed-size IV.
 *
 * \returns             0 on success, or Z9_ERR_CIPHER_BAD_INPUT_DATA
 *
 * \note                Some ciphers don't use IVs nor NONCE. For these
 *                      ciphers, this function has no effect.
 */
int mbedtls_cipher_set_iv( mbedtls_cipher_context_t *ctx,
                   const unsigned char *iv, size_t iv_len );

/**
 * \brief               Finish preparation of the given context
 *
 * \param ctx           generic cipher context
 *
 * \returns             0 on success, Z9_ERR_CIPHER_BAD_INPUT_DATA
 *                      if parameter verification fails.
 */
int mbedtls_cipher_reset( mbedtls_cipher_context_t *ctx );

#if defined(Z9_GCM_C)
/**
 * \brief               Add additional data (for AEAD ciphers).
 *                      Currently only supported with GCM.
 *                      Must be called exactly once, after mbedtls_cipher_reset().
 *
 * \param ctx           generic cipher context
 * \param ad            Additional data to use.
 * \param ad_len        Length of ad.
 *
 * \return              0 on success, or a specific error code.
 */
int mbedtls_cipher_update_ad( mbedtls_cipher_context_t *ctx,
                      const unsigned char *ad, size_t ad_len );
#endif /* Z9_GCM_C */

/**
 * \brief               Generic cipher update function. Encrypts/decrypts
 *                      using the given cipher context. Writes as many block
 *                      size'd blocks of data as possible to output. Any data
 *                      that cannot be written immediately will either be added
 *                      to the next block, or flushed when cipher_final is
 *                      called.
 *                      Exception: for Z9_MODE_ECB, expects single block
 *                                 in size (e.g. 16 bytes for AES)
 *
 * \param ctx           generic cipher context
 * \param input         buffer holding the input data
 * \param ilen          length of the input data
 * \param output        buffer for the output data. Should be able to hold at
 *                      least ilen + block_size. Cannot be the same buffer as
 *                      input!
 * \param olen          length of the output data, will be filled with the
 *                      actual number of bytes written.
 *
 * \returns             0 on success, Z9_ERR_CIPHER_BAD_INPUT_DATA if
 *                      parameter verification fails,
 *                      Z9_ERR_CIPHER_FEATURE_UNAVAILABLE on an
 *                      unsupported mode for a cipher or a cipher specific
 *                      error code.
 *
 * \note                If the underlying cipher is GCM, all calls to this
 *                      function, except the last one before mbedtls_cipher_finish(),
 *                      must have ilen a multiple of the block size.
 */
int mbedtls_cipher_update( mbedtls_cipher_context_t *ctx, const unsigned char *input,
                   size_t ilen, unsigned char *output, size_t *olen );

/**
 * \brief               Generic cipher finalisation function. If data still
 *                      needs to be flushed from an incomplete block, data
 *                      contained within it will be padded with the size of
 *                      the last block, and written to the output buffer.
 *
 * \param ctx           Generic cipher context
 * \param output        buffer to write data to. Needs block_size available.
 * \param olen          length of the data written to the output buffer.
 *
 * \returns             0 on success, Z9_ERR_CIPHER_BAD_INPUT_DATA if
 *                      parameter verification fails,
 *                      Z9_ERR_CIPHER_FULL_BLOCK_EXPECTED if decryption
 *                      expected a full block but was not provided one,
 *                      Z9_ERR_CIPHER_INVALID_PADDING on invalid padding
 *                      while decrypting or a cipher specific error code.
 */
int mbedtls_cipher_finish( mbedtls_cipher_context_t *ctx,
                   unsigned char *output, size_t *olen );

#if defined(Z9_GCM_C)
/**
 * \brief               Write tag for AEAD ciphers.
 *                      Currently only supported with GCM.
 *                      Must be called after mbedtls_cipher_finish().
 *
 * \param ctx           Generic cipher context
 * \param tag           buffer to write the tag
 * \param tag_len       Length of the tag to write
 *
 * \return              0 on success, or a specific error code.
 */
int mbedtls_cipher_write_tag( mbedtls_cipher_context_t *ctx,
                      unsigned char *tag, size_t tag_len );

/**
 * \brief               Check tag for AEAD ciphers.
 *                      Currently only supported with GCM.
 *                      Must be called after mbedtls_cipher_finish().
 *
 * \param ctx           Generic cipher context
 * \param tag           Buffer holding the tag
 * \param tag_len       Length of the tag to check
 *
 * \return              0 on success, or a specific error code.
 */
int mbedtls_cipher_check_tag( mbedtls_cipher_context_t *ctx,
                      const unsigned char *tag, size_t tag_len );
#endif /* Z9_GCM_C */

/**
 * \brief               Generic all-in-one encryption/decryption
 *                      (for all ciphers except AEAD constructs).
 *
 * \param ctx           generic cipher context
 * \param iv            IV to use (or NONCE_COUNTER for CTR-mode ciphers)
 * \param iv_len        IV length for ciphers with variable-size IV;
 *                      discarded by ciphers with fixed-size IV.
 * \param input         buffer holding the input data
 * \param ilen          length of the input data
 * \param output        buffer for the output data. Should be able to hold at
 *                      least ilen + block_size. Cannot be the same buffer as
 *                      input!
 * \param olen          length of the output data, will be filled with the
 *                      actual number of bytes written.
 *
 * \note                Some ciphers don't use IVs nor NONCE. For these
 *                      ciphers, use iv = NULL and iv_len = 0.
 *
 * \returns             0 on success, or
 *                      Z9_ERR_CIPHER_BAD_INPUT_DATA, or
 *                      Z9_ERR_CIPHER_FULL_BLOCK_EXPECTED if decryption
 *                      expected a full block but was not provided one, or
 *                      Z9_ERR_CIPHER_INVALID_PADDING on invalid padding
 *                      while decrypting, or
 *                      a cipher specific error code.
 */
int mbedtls_cipher_crypt( mbedtls_cipher_context_t *ctx,
                  const unsigned char *iv, size_t iv_len,
                  const unsigned char *input, size_t ilen,
                  unsigned char *output, size_t *olen );

#if defined(Z9_CIPHER_MODE_AEAD)
/**
 * \brief               Generic autenticated encryption (AEAD ciphers).
 *
 * \param ctx           generic cipher context
 * \param iv            IV to use (or NONCE_COUNTER for CTR-mode ciphers)
 * \param iv_len        IV length for ciphers with variable-size IV;
 *                      discarded by ciphers with fixed-size IV.
 * \param ad            Additional data to authenticate.
 * \param ad_len        Length of ad.
 * \param input         buffer holding the input data
 * \param ilen          length of the input data
 * \param output        buffer for the output data.
 *                      Should be able to hold at least ilen.
 * \param olen          length of the output data, will be filled with the
 *                      actual number of bytes written.
 * \param tag           buffer for the authentication tag
 * \param tag_len       desired tag length
 *
 * \returns             0 on success, or
 *                      Z9_ERR_CIPHER_BAD_INPUT_DATA, or
 *                      a cipher specific error code.
 */
int mbedtls_cipher_auth_encrypt( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         unsigned char *tag, size_t tag_len );

/**
 * \brief               Generic autenticated decryption (AEAD ciphers).
 *
 * \param ctx           generic cipher context
 * \param iv            IV to use (or NONCE_COUNTER for CTR-mode ciphers)
 * \param iv_len        IV length for ciphers with variable-size IV;
 *                      discarded by ciphers with fixed-size IV.
 * \param ad            Additional data to be authenticated.
 * \param ad_len        Length of ad.
 * \param input         buffer holding the input data
 * \param ilen          length of the input data
 * \param output        buffer for the output data.
 *                      Should be able to hold at least ilen.
 * \param olen          length of the output data, will be filled with the
 *                      actual number of bytes written.
 * \param tag           buffer holding the authentication tag
 * \param tag_len       length of the authentication tag
 *
 * \returns             0 on success, or
 *                      Z9_ERR_CIPHER_BAD_INPUT_DATA, or
 *                      Z9_ERR_CIPHER_AUTH_FAILED if data isn't authentic,
 *                      or a cipher specific error code.
 *
 * \note                If the data is not authentic, then the output buffer
 *                      is zeroed out to prevent the unauthentic plaintext to
 *                      be used by mistake, making this interface safer.
 */
int mbedtls_cipher_auth_decrypt( mbedtls_cipher_context_t *ctx,
                         const unsigned char *iv, size_t iv_len,
                         const unsigned char *ad, size_t ad_len,
                         const unsigned char *input, size_t ilen,
                         unsigned char *output, size_t *olen,
                         const unsigned char *tag, size_t tag_len );
#endif /* Z9_CIPHER_MODE_AEAD */
}
