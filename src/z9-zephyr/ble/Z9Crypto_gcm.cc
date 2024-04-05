#include "Z9Crypto_gcm.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>      // printk
#include <zephyr/random/random.h>

#include <cstring>
#include <string>       // std::begin
#include <cstdint>

LOG_MODULE_REGISTER(Z9Crypto, LOG_LEVEL_DBG);

uint8_t raw_lock_public_key[33];
uint8_t raw_application_key[16];

#ifdef CONFIG_Z9_GCM_C
static uint8_t z9_c_crypt_temp[512];
#endif

// generate a 128 bit random number
uint8_t *Z9Crypto_random()
{
    static uint8_t random[16];
#if 1
    auto status = sys_csrand_get(random, sizeof(random));
    if (!status)
        return random;
#else
    sys_rand_get(random, sizeof(random));
#endif
    return {};
}


//
// Key Management
// 
#ifndef CONFIG_Z9_GCM_C
// create GSM key from raw bytes
gcm_status_t Z9Crypto_gcmSetKey(gcm_key_id_t& handle, const uint8_t *keyBytes, uint16_t numKeyBytes)
{
    gcm_status_t status;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    status = psa_crypto_init();
    if (status != PSA_SUCCESS)
    {
        LOG_ERR("%s: psa_init_failed: %d", __func__, status);
        return status;
    }

   /* Set key attributes */
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_lifetime(&attributes, PSA_KEY_LIFETIME_VOLATILE);
    psa_set_key_algorithm(&attributes, PSA_ALG_GCM);
    psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&attributes, numKeyBytes * 8);

    /* Import the key */
    status = psa_import_key(&attributes, keyBytes, numKeyBytes, &handle);
    if (status != PSA_SUCCESS) {
        LOG_ERR("%s: Failed to import key: %d", __func__, status);
        return status;
    }

    /* Free the attributes */
    psa_reset_key_attributes(&attributes);
    return PSA_SUCCESS;
}

void Z9Crypto_destroyKey(gcm_key_id_t& handle)
{
    /* Destroy the key */
    psa_destroy_key(handle);

    mbedtls_psa_crypto_free();
    handle = {};
}
#else
    
static z9::z9_gcm::mbedtls_gcm_context z9_ctx;

gcm_status_t Z9Crypto_gcmSetKey(gcm_key_id_t& handle, const uint8_t *keyBytes, uint16_t numKeyBytes)
{
    z9::z9_gcm::mbedtls_gcm_init(&z9_ctx);

    auto cipher = z9::z9_gcm::Z9_CIPHER_ID_AES;
    std::memcpy(handle, keyBytes, sizeof(handle));
    return z9::z9_gcm::mbedtls_gcm_setkey(&z9_ctx, cipher, keyBytes, 128);
}
void Z9Crypto_destroyKey(gcm_key_id_t& handle)
{
    //z9::z9_gcm::mbedtls_gcm_free(ctx);
}
#endif



#ifndef CONFIG_Z9_GCM_C
// single function entrypoint: assume 12-byte nonce
// uses multi-part PSA interface
gcm_status_t Z9Crypto_gcm_encrypt(gcm_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          uint8_t *text,
                          size_t  text_length,
                          uint8_t *tag,
                          size_t tag_length)
{
    gcm_status_t status;
    size_t written;
    uint8_t temp[text_length], *output = temp;

    psa_aead_operation_t operation = PSA_AEAD_OPERATION_INIT;
    psa_aead_encrypt_setup(&operation, key, PSA_ALG_GCM);
    psa_aead_set_lengths(&operation, aad_length, text_length);
    psa_aead_set_nonce(&operation, nonce, 12);

    if (aad_length)
        psa_aead_update_ad(&operation, aad, aad_length);
    if (text_length)
    {
        psa_aead_update(&operation, text, text_length,
                                    output, text_length, &written);
        // record bytes written
        output      += written;
    }
    status = psa_aead_finish(&operation, output, text_length, &written, tag, tag_length, &tag_length);
    std::memcpy(text, temp, text_length);
    return status;
}
#else

// Z9_C
gcm_status_t Z9Crypto_gcm_encrypt(gcm_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          uint8_t *text,
                          size_t  text_length,
                          uint8_t *tag,
                          size_t tag_length)
{
    gcm_status_t status;

    z9::z9_gcm::mbedtls_cipher_id_t cipher = z9::z9_gcm::Z9_CIPHER_ID_AES;
    z9::z9_gcm::mbedtls_gcm_context ctx;
    z9::z9_gcm::mbedtls_gcm_init(&ctx);
    auto key_p = std::begin(key);
    z9::z9_gcm::mbedtls_gcm_setkey(&ctx, cipher, key_p, 128);
    status = z9::z9_gcm::mbedtls_gcm_crypt_and_tag (&ctx, Z9_GCM_ENCRYPT,
                                                    text_length,
                                                    nonce, 12,
                                                    aad, aad_length,
                                                    text, z9_c_crypt_temp,
                                                    tag_length, tag);
    std::memcpy(text, z9_c_crypt_temp, text_length);
#if 0
    z9::z9_gcm::mbedtls_gcm_init(&ctx);
    key_p = std::begin(key);
    z9::z9_gcm::mbedtls_gcm_setkey(&ctx, cipher, key_p, 128);
    auto s2 = z9::z9_gcm::mbedtls_gcm_auth_decrypt(&ctx, text_length, nonce, 12, NULL, 0, tag, tag_length, text, z9_c_crypt_temp);
    if (s2) printk("%s: s2=%d\n", __func__, s2);
#endif
    return status;
}

#endif

void print_hex(const char *fn, const char *pfx, uint8_t const *data, std::size_t len)
{
    printk("%s: %s (%d bytes): ", fn, pfx, len);
    while(len--)
        printk("%02x", *data++);
    printk("\n");
}

#ifndef CONFIG_Z9_GCM_C
// decrypt block of cipher text
gcm_status_t Z9Crypto_gcm_decrypt(gcm_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          uint8_t *text,
                          size_t  text_length,
                          uint8_t *tag,
                          size_t tag_length)
{
    gcm_status_t status;
    size_t written = {};
    uint8_t temp[text_length], *output = temp;


    psa_aead_operation_t operation = PSA_AEAD_OPERATION_INIT;
    printk("%s: key = %d (%08x)\n", __func__, key, key);
    //print_hex(__func__, "input", text, text_length);
    //print_hex(__func__, "iv ", nonce, 12);
    //print_hex(__func__, "tag", tag, 16);
    //print_hex(__func__, "in ", text, text_length);

    status = psa_aead_decrypt_setup(&operation, key, PSA_ALG_GCM);
        if (status)
        {
            printk("%s: error: psa_aead_decrypt_setup: %d\n", __func__, status);
        }
    status = psa_aead_set_lengths(&operation, aad_length, text_length);
        if (status)
        {
            printk("%s: error: psa_aead_set_lengths: %d\n", __func__, status);
        }
    status = psa_aead_set_nonce(&operation, nonce, 12);
        if (status)
        {
            printk("%s: error: psa_aead_set_nonce: %d\n", __func__, status);
        }

    if (aad_length)
    {
        psa_aead_update_ad(&operation, aad, aad_length);
    }
    if (text_length)
    {
        status = psa_aead_update(&operation, text , text_length,
                                    output, text_length, &written);
        if (status)
        {
            printk("%s: error: psa_aead_update: %d\n", __func__, status);
        }
        output += written;
    }
    //print_hex(__func__, "raw", temp, output-temp);
    status = psa_aead_verify(&operation, output, text_length, &written, tag, tag_length);
    output += written;
    print_hex(__func__, "out", temp, output-temp);
    std::memcpy(text, temp, text_length);
    return status;
}

#else
// Z9_GCM
// decrypt block of cipher text
gcm_status_t Z9Crypto_gcm_decrypt(gcm_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          uint8_t *text,
                          size_t  text_length,
                          uint8_t *tag,
                          size_t tag_length)
{
    gcm_status_t status;

    z9::z9_gcm::mbedtls_cipher_id_t cipher = z9::z9_gcm::Z9_CIPHER_ID_AES;
    z9::z9_gcm::mbedtls_gcm_context ctx;
    z9::z9_gcm::mbedtls_gcm_init(&ctx);
    auto key_p = std::begin(key);
    z9::z9_gcm::mbedtls_gcm_setkey(&ctx, cipher, key_p, 128);
    status = z9::z9_gcm::mbedtls_gcm_crypt_and_tag (&ctx, Z9_GCM_DECRYPT,
                                                    text_length,
                                                    nonce, 12,
                                                    aad, aad_length,
                                                    text, z9_c_crypt_temp,
                                                    tag_length, tag);
    std::memcpy(text, z9_c_crypt_temp, text_length);
    return status;
}
#endif 

