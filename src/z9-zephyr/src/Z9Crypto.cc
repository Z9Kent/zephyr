

#include "Z9Crypto.h"
#include "Z9IO_Link.h"      // key
#include <zephyr/logging/log.h>

#include <cstring>
#include <cstdint>

LOG_MODULE_REGISTER(Z9Crypto, LOG_LEVEL_DBG);

uint8_t raw_lock_public_key[33];
uint8_t raw_application_key[16];

// create GSM key from raw bytes
gcm_key_id_t Z9Crypto_setKey(uint8_t *key, uint16_t key_bytes)
{
    gcm_status_t status;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    gcm_key_id_t handle;

    status = psa_crypto_init();
    if (status != PSA_SUCCESS)
    {
        LOG_ERR("%s: psa_init_failed", __func__);
        return 0;
    }

   /* Set key attributes */
    psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT);
    psa_set_key_algorithm(&attributes, PSA_ALG_GCM);
    psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
    psa_set_key_bits(&attributes, key_bytes * 8);

    /* Import the key */
    status = psa_import_key(&attributes, key, key_bytes, &handle);
    if (status != PSA_SUCCESS) {
        LOG_ERR("%s: Failed to import key", __func__);
        return 0;
    }

    /* Free the attributes */
    psa_reset_key_attributes(&attributes);
    return handle;
}

void Z9Crypto_destroyKey(gcm_key_id_t& handle)
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
    gcm_status_t status = psa_generate_random(random, sizeof(random));
    if (!status)
        return random;
    return {};
}

#if 0
//using z9_error_t = const char *;

// single function entrypoint: assume 12-byte nonce
// uses multi-part PSA interface
void Z9Crypto_gcm_encrypt(gcm_key_id_t key,
                          const char *nonce,
                          const uint8_t *aad,
                          size_t aad_length,
                          const uint8_t *plain_text,
                          size_t plain_text_length,
                          uint8_t *cipher_tex,
                          uint8_t *tag,
                          size_t tag_length)
{
    gcm_status_t status;
    psa_aead_operation_t operation = PSA_AEAD_OPERATION_INIT;
    
    status = psa_aead_encrypt_setup(&operation, key, PSA_ALG_GCM);
    if (!status)
        status = psa_aead_set_lengths(&operation, aad_length, text_length);
    if (!status)
        status = psa_cipher_set_iv(&operation, iv, 12);
    if (!status)
        status = psa_aead_update_ad(&operation, aad, aad_length);
    if (!status)
        status = psa_aead_update(&operation, plain_text, plain_text_length,
                                            cipher_text, plain_text_length);
    if (!status)
        status = psa_aead_finish(&operation,)




}

static ocrypto_aes_gcm_ctx *gcmCrypto_init(enum CryptoStream stream)
{
    static ocrypto_aes_gcm_ctx ctx;
    ocrypto_aes_gcm_init(&ctx, gcm_key, 16, nullptr);
    return &ctx;
}

// initialize the `gcm` area
GcmCrypto *gcmCrypto_init(enum CryptoStream stream)
{
    static GcmCrypto gcm_instance[NUM_CryptoStream];
    if (stream >= NUM_CryptoStream)
        return NULL;
    
    GcmCrypto *gcm = &gcm_instance[stream];
    return gcm;
}
                    
// specify encryption key and length
// only needs to be executed when key changes
z9_error_t gcmCrypto_doSetKeyBytes(GcmCrypto *gcm, const uint8_t *keyPtr, uint16_t keyLengthBytes)
{
    // validate keyLength
    switch (keyLengthBytes * 8)
    {
        case 128:
        case 192:
        case 256:
            if (keyLengthBytes <= (GCM_KEYBITS_MAX/8))
                break;
            // FALLSTHRU
        default:
            return "GCM: Invalid Key Length";
    }
    
    memcpy(gcm->key, keyPtr, keyLengthBytes);
    gcmCryptoIO_setKey(gcm->channel, gcm->key, keyLengthBytes);
    return {};
}

z9_error_t gcmCrypto_doGetKeyBytes(GcmCrypto *gcm, uint8_t *keyPtr, uint16_t keyLengthBytes)
{
    memcpy(keyPtr, gcm->key, keyLengthBytes);
    return {};
}

// specify IV, the aad length, and the text length. Only 96-bit IVs are supported
z9_error_t gcmCrypto_doNewMessage(GcmCrypto *gcm, const uint8_t *iv, uint32_t aadLength, uint32_t textLength)
{
    gcm->aadLength  = aadLength;
    gcm->textLength = textLength;
   
    // clear buffer
    gcm->bufLen = 0;
    
    // pass IV to implementation
    ocrypto_aes_gcm_init_iv(ctx, iv, 96/8);
    return {};
}

// process block of aad data
z9_error_t gcmCrypto_processAad(GcmCrypto *gcm, const uint8_t *aadPtr, uint32_t numBytes)
{
    ocrypto_aes_gcm_update_aad(gcm, aadPtr, numBytes);
    return {};
}

// encrypt block of plain text
z9_error_t gcmCrypto_encrypt(GcmCrypto *gcm, const uint8_t *plain, uint8_t *out, uint32_t numBytes)
{
    ocrypto_aes_gcm_update_enc(gcm, out, plain, numBytes);
    return {};

}

// decrypt block of cipher text
z9_error_t gcmCrypto_decrypt(GcmCrypto *gcm, const uint8_t *cipher, uint8_t *out, uint32_t numBytes)
{
    ocrypto_aes_gcm_update_dec(gcm, out, cipher, numBytes);
    return {};
}

// gcm validate block of cipher text, but don't decrypt
// really just a hint to DFU engine to write before decrypting
z9_error_t gcmCrypto_queueValidate(GcmCrypto *gcm, const uint8_t *cipher, uint8_t *out, uint32_t numBytes)
{
    ocrypto_aes_gcm_update_dec(gcm, nullptr, cipher, numBytes);
    return {};
}

// generate the TAG (up to 16 bytes of tag can be generated)
z9_error_t gcmCrypto_generateTag(GcmCrypto *gcm, uint8_t *tag, uint16_t tagBytes)
{
    ocrypto_aes_gcm_final_enc(ctx, tag, tagBytes);
    return {};
}


#endif