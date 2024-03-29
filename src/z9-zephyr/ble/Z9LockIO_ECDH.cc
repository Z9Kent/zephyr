
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9Crypto_gcm.h"
#include "Settings.h"

#include <cstring>
#include <zephyr/kernel.h>

#ifdef CONFIG_MBEDTLS_PSA_CRYPTO_C
#include <psa/crypto.h>
#include <psa/crypto_extra.h>
//#include "mbedtls/sha256.h"
#endif

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"
#include "Z9LockIO_ECDH.h"
#include "Z9IO_Logic.h"

void Z9LockIO_performECDH(ECDH_rsp_fn fn, const uint8_t *nocPublic, uint16_t keyLength)
{
    // since we only save our public key, see if NOC sent same pulic key. If so we respond with
    // our saved key
    if (memcmp(nocPublic, noc_public_key, sizeof(noc_public_key)) == 0 &&
        lock_public_key[0] && noc_derived_key[0])
    {
            printk("%s: NOC_didn't change: replying with saved public key", __func__);
            fn(lock_public_key, sizeof(lock_public_key));
    }
    else
    {
#ifdef CONFIG_Z9_CONTROLLER
        // save the public key
        std::memcpy(noc_public_key, nocPublic, sizeof(noc_public_key));
        send_req_ecdh(fn, nocPublic, keyLength);
#endif
    }
}
#if CONFIG_Z9_READER
static void derive_key_from_shared_secret_and_public_keys(
    const unsigned char *shared_secret, std::size_t shared_secret_len,
    const unsigned char *our_public_key, std::size_t our_public_key_len,
    const unsigned char *other_public_key, std::size_t other_public_key_len,
    unsigned char *output, std::size_t output_len)
{

    unsigned char hash[32]; // SHA-256 outputs 32 bytes
#ifdef CONFIG_MBEDTLS_PSA_CRYPTO_C
    psa_status_t status;
    psa_hash_operation_t hash_operation = {0};
    uint32_t olen {};

    psa_crypto_init();
    psa_hash_setup(&hash_operation, PSA_ALG_SHA_256);
    psa_hash_update(&hash_operation, shared_secret, shared_secret_len);
    psa_hash_update(&hash_operation, our_public_key, our_public_key_len);
    psa_hash_update(&hash_operation, other_public_key, other_public_key_len);
    status = psa_hash_finish(&hash_operation, hash, sizeof(hash), &olen);
    if (status)
        printk("%s: error = %d\n", __func__, status);

#else
  mbedtls_sha256_context sha256_ctx;

    // Initialize SHA-256 context
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, 0); // 0 for SHA-256, not 224

    // Hash the shared secret
    mbedtls_sha256_update(&sha256_ctx, shared_secret, shared_secret_len);

    // Hash our public key
    mbedtls_sha256_update(&sha256_ctx, our_public_key, our_public_key_len);

    // Hash other public key
    mbedtls_sha256_update(&sha256_ctx, other_public_key, other_public_key_len);

    // Finalize and get the hash
    mbedtls_sha256_finish(&sha256_ctx, hash);

    // Clean up
    mbedtls_sha256_free(&sha256_ctx);
#endif

    // Copy the required number of bytes to the output
    memcpy(output, hash, output_len);
}

std::tuple<uint8_t, uint8_t const *>
Z9Lock_ECDH(uint8_t const *msg)
{
    // remote public key should be 64 bytes
    if (*msg++ != 65)
        return {};

    // need new public key for lock
    // 1) generate key pair
    gcm_key_handle_t key_handle;
	gcm_status_t status;
	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;

	/* Crypto settings for ECDH using the SHA256 hashing algorithm with the secp256r1 curve */

    // NB: don't need to test for errors: these methods return void
    psa_crypto_init();
	psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_DERIVE);
	psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_ECDH);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
	psa_set_key_bits(&key_attributes, 256);
	/* Generate a key pair */
#if 1
	status = psa_generate_key(&key_attributes, &key_handle);
    if (status)
        printk("%s: psa_generate_key: error=%d\n", __func__, status);
#endif
#if 1
    // 2) export public key
    std::size_t olen;
    status = psa_export_public_key(key_handle, lock_public_key, sizeof(lock_public_key), &olen);
    if (status)
        printk("%s: psa_export_public_key: error=%d\n", __func__, status);
    if (olen != sizeof(lock_public_key))
        printk("%s: psa_export_public_key: exported %u bytes, expected %u\n",
            __func__, olen, sizeof(lock_public_key));
#endif
    // 3) save noc public key
    std::memcpy(noc_public_key, msg, sizeof(noc_public_key));

    // 4) perform ECDH
    uint32_t ecdh_len;
    uint8_t lock_ecdh_secret[32] = {};
#if 1
    status = psa_raw_key_agreement(PSA_ALG_ECDH, key_handle,
                                   noc_public_key, sizeof(noc_public_key),
                                   lock_ecdh_secret, sizeof(lock_ecdh_secret),
                                   &ecdh_len);
    if (status)
        printk("%s: psa_raw_key_agreement: error=%d\n", __func__, status);
	psa_reset_key_attributes(&key_attributes);
#endif
#if 1
    {
        uint8_t *p = lock_public_key;
        auto n = sizeof(lock_public_key);
        printk("%s: lock_public = ", __func__);
        while (n--)
            printk("%02x ", *p++);
        printk("\n");
    }
    {
        uint8_t *p = noc_public_key;
        auto n = sizeof(noc_public_key);
        printk("%s: noc_public = ", __func__);
        while (n--)
            printk("%02x ", *p++);
        printk("\n");
    }
    {
        uint8_t *p = lock_ecdh_secret;
        auto n = sizeof(lock_ecdh_secret);
        printk("%s: secret = ", __func__);
        while (n--)
            printk("%02x ", *p++);
        printk("\n");
    }
#endif
#if 1
    derive_key_from_shared_secret_and_public_keys(
        lock_ecdh_secret, sizeof(lock_ecdh_secret),
        lock_public_key, sizeof(lock_public_key),
        noc_public_key, sizeof(noc_public_key),
        noc_derived_key, sizeof(noc_derived_key)
    );
#endif
#if 1
    {
        uint8_t *p = noc_derived_key;
        auto n = sizeof(noc_derived_key);
        printk("%s: -> key = ", __func__);
        while (n--)
            printk("%02x", *p++);
        printk("\n");
    }
#endif
    // 5) destroy lock public key-pair
    psa_destroy_key(key_handle);
    
    // 8) return public key
    return { sizeof(lock_public_key), lock_public_key };
}
#endif