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

#include <psa/crypto.h>
#include <psa/crypto_extra.h>

#include <cstdint>

using z9_error_t = const char *;

// create GSM key from raw bytes
psa_key_id_t Z9Crypto_setKey(uint8_t *key, uint16_t key_bytes);

// remove key when complete
void Z9Crypto_destroyKey(psa_key_id_t& handle);

// generate a 128 bit random number
uint8_t *Z9Crypto_random();

extern uint8_t raw_lock_public_key[33];
extern uint8_t raw_application_key[16];
#if 0

// 16-bytes in a block. 4 "words" in a block
#define BLOCK_BITS      128
#define BLOCK_LEN       (BLOCK_BITS/8)
#define BLOCK_WORDS     (BLOCK_LEN/sizeof(uint32_t))

//#define GCM_KEYBITS_MAX 256
#define GCM_KEYBITS_MAX 128     // 256 overflows ram
// enumerate the instances of `crypto` supported.
// only 1 of each type may be active at a time
enum CryptoStream { CS_BOOT, CS_LINK, CS_NOC, NUM_CryptoStream };

// state of Crypto Channel
enum CryptoFSM { CX_IDLE, CX_AAD, CX_TEXT, CX_TAG, NUM_CrytoFSM };

// forward declare controller
struct GcmCryptoController;

// declare per-channel data
struct GcmCryptoChannel
{
   
    void *channel;              // CryptoIO channel object (based on channel)

    // decribe GCM object
    uint32_t aadLength;
    uint32_t textLength;
    
    // struct to manage blocking of aad, text
    const uint8_t *in;            // pointer to `cnt` data in gcmData
    uint8_t       *out;           // pointer to `cnt` output for gcmData
    uint8_t       *bufOutput;     // where output from `buffered` data goes
    
    // expose Key to save storage for KeyExchange
    uint32_t key[GCM_KEYBITS_MAX / 32];
    
    // data must be written to engine as 128-bit blocks
    // access data as 8-bit bytes or 32-bit words
    union
    {
        uint32_t words[BLOCK_WORDS];
        uint8_t  bytes[BLOCK_LEN];
    } buf;
    
    uint32_t    numBytes;       // length of pending write
    uint32_t    remaining;      // remaing to write in `aad` or `text`
    uint8_t     bufLen;         // valid bytes in buffer
    uint8_t     bufInitLen;     // valid bytes in first buffer chunk
    enum CryptoFSM state;       // processing state
    
    // Method pending execution (NULL indicates generateTag)
    void (*fn)(void *channel, const uint32_t *in, uint32_t *out, uint32_t numBytes);
    
    // route to exec on completion
    uint8_t    keyLengthWords;
};


typedef struct GcmCryptoChannel GcmCrypto;

// initialize the `gcm` area
GcmCrypto *gcmCrypto_init(enum CryptoStream);

// specify encryption key and length
// only needs to be executed when key changes
z9_error_t gcmCrypto_doSetKeyBytes(GcmCrypto *gcm, const uint8_t *keyPtr, uint16_t keyLengthBytes);
z9_error_t gcmCrypto_doGetKeyBytes(GcmCrypto *gcm,       uint8_t *keyPtr, uint16_t keyLengthBytes);

// specify IV, the aad length, and the text length. Only 96-bit IVs are supported
z9_error_t gcmCrypto_doNewMessage(GcmCrypto *gcm, const uint8_t *iv, uint32_t aadLength, uint32_t textLength);

// process block of aad data
z9_error_t gcmCrypto_processAad(GcmCrypto *gcm, const uint8_t *aadPtr, uint32_t bytes);

// encrypt block of plain text
z9_error_t gcmCrypto_encrypt(GcmCrypto *gcm, const uint8_t *plain, uint8_t *out, uint32_t bytes);

// decrypt block of cipher text
z9_error_t gcmCrypto_decrypt(GcmCrypto *gcm, const uint8_t *cipher, uint8_t *out, uint32_t bytes);

// gcm validate block of cipher text, but dont decrypt
z9_error_t gcmCrypto_validate(GcmCrypto *gcm, const uint8_t *cipher, uint8_t *out, uint32_t bytes);

// generate the TAG (up to 16 bytes of tag can be generated)
z9_error_t gcmCrypto_generateTag(GcmCrypto *gcm, uint8_t *tag, uint16_t tagBytes);

// GMAC is just GCM message without confidential data
#if 0
z9_error_t inline gcmCrypto_doNewGMAC(GcmCrypto *gcm, uint8_t *iv, uint32_t aadLength)
{
    return gcmCrypto_doNewMessage(gcm, iv, aadLength, 0);
}
#else
#define gcmCrypto_doNewGMAC(g,iv,aad)   gcmCrypto_doNewMessage(g, iv, aad, 0)
#endif

// generate a 128 bit random number
uint32_t *gcmCrypto_doGenerateRandom(uint8_t);

#if 0
//
// Interface to hardware or software implementation
//
// Low level implementation which virturalizes `GCM` driver as `NUM_CryptoStream` instances.
// `GcmCrypto` will serialize calls so only a single instance is processed at once.
// Thus a single AES hardware instance can mimic multiple software instances.

// NB: keys & IVs are passed as pointer to byte arrays. These vectors should be
//     cached in channels with alignment as required.
void *gcmCryptoIO_getChannel (enum CryptoStream, RouteIndex route4return);
void  gcmCryptoIO_setKey     (void *channel, const uint32_t *keyPtr, uint16_t keyBytes);
void  gcmCryptoIO_newMessage (void *channel, const uint8_t *iv, uint16_t ivBytes);
void  gcmCryptoIO_processAad (void *channel, const uint32_t *aadPtr, uint32_t *   , uint32_t bytes);
void  gcmCryptoIO_encrypt    (void *channel, const uint32_t *plain , uint32_t *out, uint32_t numBytes);
void  gcmCryptoIO_decrypt    (void *channel, const uint32_t *cipher, uint32_t *out, uint32_t numBytes);
void  gcmCryptoIO_generateTag(void *channel, uint32_t *tag, uint32_t aadLength, uint32_t textLength);
void  gcmCryptoIO_random     (uint32_t *dest, uint8_t words);
void  gcmCryptoIO_randomBytes (uint8_t *dest, uint8_t bytes);

#endif
#endif