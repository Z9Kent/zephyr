
#include "Eros_protocol.h"
#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9Crypto_gcm.h"
#include "Settings.h"

#include <cstring>
#include <zephyr/kernel.h>

#include <psa/crypto.h>
#include <psa/crypto_extra.h>
//#include "mbedtls/sha256.h"

#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "variableArray.h"


void Z9LockIO_performECDH(void *arg, ECDH_rsp_fn fn, cosnt uint8_t *nocPublic, uint16_t keyLength)
{
    // since we only save our public key, see if NOC sent same pulic key. If so we respond with
    // our saved key
    if (memcmp(&buf[1], noc_public_key, sizeof(noc_public_key)) == 0 && lock_public_key[0])
    {
        printk("%s: NOC_didn't change: replying with saved public key", __func__);
        z9lock_gen_keyExchange_rsp(sizeof(lock_public_key), lock_public_key);
    }
    else
    {
#ifndef CONFIG_Z9_READER
        send_ecdh(arg, fn, nocPublic, keyLength);
#else
        auto [cnt, p] = Z9Lock_ECDH(buf);
        if (cnt)
        {
            printk("%s: calculated secret\n", __func__);
            z9lock_gen_keyExchange_rsp(arg, cnt, p);
            printk("%s: send response\n", __func__);
        }
    }
    break;
#endif
}
#if CONFIG_Z9_READER
static void derive_key_from_shared_secret_and_public_keys(
    const unsigned char *shared_secret, std::size_t shared_secret_len,
    const unsigned char *our_public_key, std::size_t our_public_key_len,
    const unsigned char *other_public_key, std::size_t other_public_key_len,
    unsigned char *output, std::size_t output_len)
{
    mbedtls_sha256_context sha256_ctx;
    unsigned char hash[32]; // SHA-256 outputs 32 bytes

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

    // Copy the required number of bytes to the output
    memcpy(output, hash, output_len);
}
#endif
#if 0
std::tuple<uint8_t, uint8_t const *>Z9Lock_ECDH(uint8_t const *msg)
{
    // remote public key should be 64 bytes
    if (*msg++ != 65)
        return {};

    auto& lock = z9lock_status;
    if (lock.mode != LockStatusMode::PAIRING)
    {
        printk("%s: not in pairing mode\n", __func__);
        return {};
    }

    // check if stored remote public key matches -- if so done
    if (std::memcmp(noc_public_key, msg, sizeof(noc_public_key)) == 0)
        return { sizeof(lock_public_key), lock_public_key };

    // need new public key for lock
    // 1) generate key pair
    gcm_key_handle_t key_handle;
	gcm_status_t status;
	psa_key_attributes_t key_attributes = PSA_KEY_ATTRIBUTES_INIT;

	/* Crypto settings for ECDH using the SHA256 hashing algorithm with the secp256r1 curve */

    // NB: don't need to test for errors: these methods return void
	psa_set_key_usage_flags(&key_attributes, PSA_KEY_USAGE_DERIVE);
	psa_set_key_lifetime(&key_attributes, PSA_KEY_LIFETIME_VOLATILE);
	psa_set_key_algorithm(&key_attributes, PSA_ALG_ECDH);
	psa_set_key_type(&key_attributes, PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1));
	psa_set_key_bits(&key_attributes, 256);

	/* Generate a key pair */
	status = psa_generate_key(&key_attributes, &key_handle);
    if (status)
        printk("%s: psa_generate_key: error=%d\n", __func__, status);
	psa_reset_key_attributes(&key_attributes);

    // 2) export public key
    std::size_t olen;
    status = psa_export_public_key(key_handle, lock_public_key, sizeof(lock_public_key), &olen);
    if (status)
        printk("%s: psa_export_public_key: error=%d\n", __func__, status);

    // 3) save noc public key
    std::memcpy(noc_public_key, msg, sizeof(noc_public_key));

    // 4) perform ECDH
    uint32_t ecdh_len;
    uint8_t lock_ecdh_secret[32];
    status = psa_raw_key_agreement(PSA_ALG_ECDH, key_handle,
                                   noc_public_key, sizeof(noc_public_key),
                                   lock_ecdh_secret, sizeof(lock_ecdh_secret),
                                   &ecdh_len);

    if (status)
        printk("%s: psa_raw_key_agreement: error=%d\n", __func__, status);
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
    
    derive_key_from_shared_secret_and_public_keys(
        lock_ecdh_secret, sizeof(lock_ecdh_secret),
        lock_public_key, sizeof(lock_public_key),
        noc_public_key, sizeof(noc_public_key),
        noc_derived_key, sizeof(noc_derived_key)
    );

    {
        uint8_t *p = noc_derived_key;
        auto n = sizeof(noc_derived_key);
        printk("%s: -> key = ", __func__);
        while (n--)
            printk("%02x", *p++);
        printk("\n");
    }
    
    // 5) destroy lock public key-pair
    psa_destroy_key(key_handle);

    // 6) write keys to NVM storage & update Z9Lock_status()
    nvm_settings_save_keys();

    // 8) return public key
    return { sizeof(lock_public_key), lock_public_key };
}
#endif