#include "Z9Crypto.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>      // printk

#include <cstring>
#include <cstdint>

LOG_MODULE_REGISTER(Z9Crypto, LOG_LEVEL_DBG);

uint8_t raw_lock_public_key[33];
uint8_t raw_application_key[16];

// create GSM key from raw bytes
psa_status_t Z9Crypto_gcmSetKey(psa_key_id_t& handle, const uint8_t *keyBytes, uint16_t numKeyBytes)
{
    psa_status_t status;
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

void Z9Crypto_destroyKey(psa_key_id_t& handle)
{
    /* Destroy the key */
    psa_destroy_key(handle);

    mbedtls_psa_crypto_free();
    handle = {};
}

// generate a 128 bit random number
uint8_t *Z9Crypto_random()
{
    static uint8_t random[16];
    psa_status_t status = psa_generate_random(random, sizeof(random));
    if (!status)
        return random;
    return {};
}

// single function entrypoint: assume 12-byte nonce
// uses multi-part PSA interface
psa_status_t Z9Crypto_gcm_encrypt(psa_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          uint8_t *text,
                          size_t  text_length,
                          uint8_t *tag,
                          size_t tag_length)
{
    psa_status_t status;
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

void print_hex(const char *fn, const char *pfx, uint8_t const *data, std::size_t len)
{
    printk("%s: %s (%d bytes): ", fn, pfx, len);
    while(len--)
        printk("%02x", *data++);
    printk("\n");
}


// decrypt block of cipher text
psa_status_t Z9Crypto_gcm_decrypt(psa_key_id_t const& key,
                          const uint8_t *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          uint8_t *text,
                          size_t  text_length,
                          uint8_t *tag,
                          size_t tag_length)
{
    psa_status_t status;
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

