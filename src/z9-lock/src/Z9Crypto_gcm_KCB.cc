// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
//
//  GcmCrypto_KCB.c
//

#include "Z9Crypto_gcm_KCB.h"
#include <zephyr/logging/log.h>
#include <cstring>

LOG_MODULE_REGISTER(Crypto, LOG_LEVEL_DBG);

//z9_error_t Z9Crypto_gcm_encrypt_KCB(KCB& kcb, uint8_t *iv = {});

z9_error_t Z9Crypto_gcm_decrypt_KCB(psa_key_id_t key, KCB& kcb, uint8_t *prefix, uint8_t prefix_len)
{
    // psa doesn't allow same input & output.
    // until I can fix it, decrypt into 1K buffer, then copy decrypted data back to KCB
    // use static buffer: don't have stack space
    static uint8_t buffer[1024];

    LOG_INF("%s: kcb=%d, len=%d", __func__, kcb.id(), kcb.size());
    auto iv  = kcb.consumeHeadroom(12);     // IV is first
    auto tag = kcb.consumeHeadroom(16);     // TAG is next
    auto len = kcb.top().length();          // bytes to decrypt

    // psa altorithm
    psa_aead_operation_t operation = PSA_AEAD_OPERATION_INIT;
    psa_aead_decrypt_setup(&operation, key, PSA_ALG_GCM);
    psa_aead_set_lengths(&operation, 0, len);
    psa_aead_set_nonce(&operation, iv, 12);

    auto output = buffer;
    kcb_headroom_t available;
    size_t decrypted;

    // loop thru buffer, decrypting
    while (auto p = kcb.currentBlock(available))
    {
        psa_aead_update(&operation, p, available, output, sizeof(buffer), &decrypted);
        output += decrypted;
    }

    // validate tag & get final decrypted bytes
    auto result = psa_aead_verify(&operation, output, sizeof(buffer), &decrypted, tag, 16);
    output += decrypted;

    LOG_INF("%s: result=%d, input=%d bytes, output=%d", __func__, result, len, output-buffer);
    LOG_HEXDUMP_INF(buffer, 16, "decrypted");
    if (result)
        return "GCM AUTH FAIL";

    // now put decrypted data back in KCB
    kcb.flush(10);
    // add prefix
    while(prefix_len--) kcb.write(*prefix++);
    
    output = buffer;
    while(len--)
        kcb.write(*output++);
    kcb.top();
    return {};
}

z9_error_t Z9Crypto_gcm_encrypt_KCB(psa_key_id_t key, KCB& kcb, uint8_t *prefix, uint8_t prefix_len, uint8_t *iv_data)
{
    // psa doesn't allow same input & output.
    // until I can fix it, decrypt into 1K buffer, then copy decrypted data back to KCB
    // use static buffer: don't have stack space
    static uint8_t buffer[1024];

    LOG_INF("%s: kcb=%d, len=%d", __func__, kcb.id(), kcb.size());
    auto len = kcb.top().length();          // bytes to encrypt
    #if 0
    auto tag = kcb.allocHeadroom(16);       // TAG prepends data
    auto iv  = kcb.allocHeadroom(12);       // IV prepends TAG
    #else
    uint8_t tag[16];
    uint8_t iv [12];
    #endif

    if (!iv_data)
        iv_data = Z9Crypto_random();

    // save IV
    std::memcpy(iv, iv_data, sizeof(iv));

    // psa altorithm
    psa_aead_operation_t operation = PSA_AEAD_OPERATION_INIT;
    psa_aead_encrypt_setup(&operation, key, PSA_ALG_GCM);
    psa_aead_set_lengths(&operation, 0, len);
    psa_aead_set_nonce(&operation, iv, 12);

    auto output = buffer;
    kcb_headroom_t available;
    size_t encrypted;

    // loop thru buffer, decrypting
    while (auto p = kcb.currentBlock(available))
    {
        psa_aead_update(&operation, p, available, output, sizeof(buffer), &encrypted);
        output += encrypted;
    }

    // validate tag & get final decrypted bytes
    size_t tag_length;
    auto result = psa_aead_finish(&operation, output, sizeof(buffer), &encrypted, tag, 16, &tag_length);
    output += encrypted;

    LOG_INF("%s: result=%d, input=%d bytes, output=%d", __func__, result, len, output-buffer);
    LOG_HEXDUMP_INF(buffer, 16, "encrypted");
    if (result)
        return "GCM AUTH FAIL";

    // now put encrypted data back in KCB
    kcb.flush(10);

    // add prefix
    while(prefix_len--) kcb.write(*prefix++);
    
    output = iv;
    int n = 12;
    while(n--) kcb.write(*output++);

    output = tag;
    n = 16;
    while(n--) kcb.write(*output++);

    output = buffer;
    while(len--)
        kcb.write(*output++);
    kcb.top();
    return {};
}

#if 0
enum GCM_OP { OP_PASSTHRU, OP_ENCRYPT, OP_DECRYPT, NUM_GCM_OP };

typedef struct
{
    GcmCrypto  *gcm;
    uint32_t    length;
    uint8_t     tag[16];
    enum GCM_OP operation;
    uint16_t    prefixLen;
} crypto_KCB;

// define size of transaction header
// [operation: 1] [returnRoute: 1] [gcmStream: 1] [length: 3] [prefixLength: 2]
// for PASSTHRU, only operation & returnRoute are present

#define TRANSACTION_HDR_SIZE 8

// unaligned encryption is slower
#define ALLOW_UNALIGNED_KCB_ENCRYPTION

// forward Declarations
static error_t GcmCrypto_return(void *instance, Signal err);
static error_t GcmCrypto_queue(enum CryptoStream stream,
                               uint8_t *prefix, uint16_t prefixLen,
                               KCB_Hdr *buf, enum GCM_OP operation, uint32_t length, RouteIndex returnRoute);

static void    GcmCrypto_selectNext(crypto_KCB *self);
static void    GcmCrypto_processNext(crypto_KCB *self);

static bool isNonZero(void *v_key, size_t n)
{
    uint8_t *key = v_key;
    while (n--)
        if (*key++)
            return true;
    return false;
}

static crypto_KCB *getCrypto_KCB(void)
{
    static crypto_KCB crypto_KCB_instance;
    crypto_KCB *self = &crypto_KCB_instance;
    
    // initialize first time thru
    if (!self->route2here)
    {
        KernelExecutor_registerRoute(&self->route2here, GcmCrypto_return, self, "GcmCrypto_KCB: Return", NULL);
    }
    
    return self;
}


error_t GcmCrypto_encrypt_KCB(enum CryptoStream stream,
                              uint8_t *prefix, uint16_t prefixLen,
                              KCB& kcb, const uint32_t *iv = {})
{
    // Validate crypto stream
    GcmCrypto *gcm = gcmCrypto_init(stream, 0);
    if (!gcm)
        return "GCM: Invalid stream";
    
    // Validate key is non-zero
    uint8_t key[16];
    if (auto error = gcmCrypto_doGetKeyBytes(gcm, key, sizeof(key))
        return error;
    
    if (!isNonZero(key, sizeof(key)))
        return "GCM: Key not set";
    
    // Access the buffer & headroom
    uint16_t curHeadroom = kcb.getHeadroom(buf);
    uint16_t maxHeadroom = kcb.maxHeadroom();
    uint16_t allocatedHeadroom = maxHeadroom - curHeadroom;
    
    //LOG_INFO("%s: headroom: cur=%d, max=%d, allocated=%d", __FUNCTION__, curHeadroom, maxHeadroom, allocatedHeadroom);
    //LOG_INFO("%s: buf=%p, prefixLen=%d", __FUNCTION__, buf, prefixLen);
    
    
    // Validate HEADROOM in buffer: IV, TAG, accounting
    int minHeadroom = 12 + 16 + prefixLen + TRANSACTION_HDR_SIZE;
  
    if (curHeadroom < minHeadroom)
        return "GCM: not enough KCB headroom";
    
    // Allocate 12-byte IV & store in buffer
    auto tag_p = kcb.allocHeadroom(16);
    auto iv_p  = kcb.allocHeadroom(12);
    // generate IV if needed
    if (!iv)
        iv = gcmCrypto_doGenerateRandom(12);
    memcpy(iv_p, iv, 12);
  
    int len = kcb.top().length();
    gcm_init();
    gcm_set_iv();
    kcb_headroom_t n;
    while (auto p = kcb.currentBlock(n))
        gcm_encrypt(gcm, p, p, n);
    gcm_finish(gcm);
    //save tag   

    auto prefix_p = kcb.allocHeadroom(prefixLen);
    memcpy(prefix_p, prefix, prefixLen);
    kcb.top();
    return {};
}

error_t GcmCrypto_decrypt_KCB(enum CryptoStream stream,
                              uint8_t *prefix, uint16_t prefixLen,
                              KCB& kcb)
{
    // Validate crypto stream
    GcmCrypto *gcm = gcmCrypto_init(stream, 0);
    if (!gcm)
        return "GCM: Invalid stream";
    
    // Validate key is non-zero
    uint8_t key[16];
    if (auto error = gcmCrypto_doGetKeyBytes(gcm, key, sizeof(key))
        return error;
    
    if (!isNonZero(key, sizeof(key)))
        return "GCM: Key not set";
    
    // Access the buffer & headroom
    uint16_t curHeadroom = KCB_getHeadroom(buf);
    uint16_t maxHeadroom = KCB_maxHeadroom();
    uint16_t allocatedHeadroom = maxHeadroom - curHeadroom;
    
    // HEADROOM should contain IV + TAG (so it can be removed)
    if (allocatedHeadroom <= (12 + 16))
        return "GCM: insufficient headroom for IV + TAG";
    
    // HEADROOM must have room for prefix & accounting
    if (curHeadroom < (prefixLen + TRANSACTION_HDR_SIZE))
        return "GCM: insufficient headroom for prefix";
  
    // enqueue operation
    return GcmCrypto_queue(stream, prefix, prefixLen, buf, OP_DECRYPT, length - 12 - 16, returnRoute);
}


// buffer and args are validated before this routine
static error_t GcmCrypto_queue(enum CryptoStream stream,
                               uint8_t *prefix, uint16_t prefixLen,
                               KCB_Hdr *buf, enum GCM_OP operation, uint32_t length, RouteIndex returnRoute)
{
    crypto_KCB *self = getCrypto_KCB();
   
    // add transaction to queue
    if (!self->head)
        self->tail_p = &self->head;
    
    *self->tail_p = buf;
    self->tail_p = &buf->queue[0];
    *self->tail_p = NULL;       // mark end-of-list
  
    // prepend actual encryption header if not PASSTHRU
    if (operation != OP_PASSTHRU)
    {
        // push prefix onto buffer
        prefix += prefixLen;
        for (uint16_t n = prefixLen; n; --n)
            KCB_push(buf, *--prefix);
        
        // push Transaction header onto buffer
        KCB_push(buf, prefixLen);
        KCB_push(buf, prefixLen >> 8);
        for (int i = 0; i < 3; ++i)
        {
            KCB_push(buf, length);
            length >>= 8;
        }
        KCB_push(buf, stream);
    }
   
    // prepend "common" (ie passthru) header
    KCB_push(buf, returnRoute);
    KCB_push(buf, operation);
   
    // if not running, start
    if (!self->gcm)
        GcmCrypto_selectNext(self);
    
    return E_OK;
}

// process next queued operation
static void GcmCrypto_selectNext(crypto_KCB *self)
{
    // mark previous operation complete
    self->gcm = NULL;
    
    // if queue is empty, go idle
    if (!self->head) return;
    
    // pop values off header
    self->operation   = KCB_pop(self->head);
    self->returnRoute = KCB_pop(self->head);
   
    // if PASSTHRU, just send buffer on it's way
    if (self->operation == OP_PASSTHRU)
    {
        // PASSTHRU: send buffer on route
        KernelBufferHandle h = 0;
        KCB_getHandle(self->head, &h);
        KernelExecutor_queue(self->returnRoute, h);
        
        // process next operation
        self->head = self->head->queue[0];      // remove current from queue
        return GcmCrypto_selectNext(self);
    }
    
    
    // start GCM engine & flag that TAG needs to be generated
    memset(self->tag, 0, sizeof(self->tag));
    self->gcm = gcmCrypto_init(KCB_pop(self->head), self->route2here);
   
    // read rest of TRANSACTION_HDR
    self->length = 0;
    for (int i = 0; i < 3; ++i)
    {
        self->length <<= 8;
        self->length += KCB_pop(self->head);
    }
    self->prefixLen   = KCB_pop(self->head) << 8;
    self->prefixLen  += KCB_pop(self->head);
    
    //LOG_INFO("%s: buf=%p, prefixLen=%d, op=%d", __FUNCTION__, self->head, self->prefixLen, self->operation);
    
    // start up encryption: set IV after prefix
    uint8_t *iv = KCB_consumeHeadroom(self->head, 0) + self->prefixLen;
    gcmCrypto_doNewMessage(self->gcm, iv, 0, self->length);
    
    // seek to beginning of data. Then perform cipher in place
    KCB_seek(self->head, 12 + 16 + self->prefixLen);          // after TAG
    GcmCrypto_processNext(self);
}


// process next KernelBuffer_Block in KCB
static void GcmCrypto_processNext(crypto_KCB *self)
{
    uint16_t charsRemaining;
    uint8_t *p = KCB_getCurrentBlockData(self->head, &charsRemaining);
   
    //LOG_INFO("%s: buf=%p, chars=%d", __FUNCTION__, self->head, charsRemaining);
    
    
    // don't process trailing characters (eg CRC)
    if (charsRemaining > self->length)
        charsRemaining = self->length;
    
    // if all data is processed, extract or check TAG
    if (!charsRemaining)
    {
        // if tag is zero, then generate TAG
        if (!isNonZero(self->tag, sizeof(self->tag)))
            return (void)gcmCrypto_queueGenerateTag(self->gcm, self->tag, 16);
       
        // GCM complete: remove buffer from QUEUE
        KCB_Hdr *buf = self->head;
        self->head   = buf->queue[0];
        
        // If Encrypt, save the TAG in the KCB
        if (self->operation == OP_ENCRYPT)
        {
            // if encrypting, store TAG after IV
            uint8_t *iv  = KCB_consumeHeadroom(buf, 0) + self->prefixLen;
            uint8_t *tag = iv + 12;
            memcpy(tag, self->tag, sizeof(self->tag));
        }
        // if Decrypt, validate TAG
        else
        {
            uint8_t *tag = KCB_consumeHeadroom(buf, 0) + self->prefixLen + 12;     // skip past IV
            int result = memcmp(self->tag, tag, sizeof(self->tag));
            //LOG_OFF("%s: decrypt result = %d", __FUNCTION__, result);
            if (result)
            {
                // decrypt error: queue a zero
                KCB_free(buf);
                buf = NULL;
            }
            else
            {
                // move prefix to just before decrypted data
                uint8_t *prefixEnd = KCB_consumeHeadroom(buf, 0) + self->prefixLen;
                uint8_t *data      = prefixEnd + 12 + 16;
                while(self->prefixLen--)
                    *--data = *--prefixEnd;
                KCB_consumeHeadroom(buf, 12 + 16);
            }
        }
        
        // forward processed buffer on: queue zero on decrypt error
        KernelBufferHandle h = 0;
        if (buf)
        {
            KCB_getHandle(buf, &h);
            KCB_top(buf);
        }
        KernelExecutor_queue(self->returnRoute, h);
        //LOG_INFO("%s: forwarding buf=%p, route=%d", __FUNCTION__, buf, self->returnRoute);
       
        // process next operation
        return GcmCrypto_selectNext(self);
    }
    
    // send next chunk to crypto engine: process in place
    if (self->operation == OP_ENCRYPT)
        gcmCrypto_queueEncrypt(self->gcm, p, p, charsRemaining);
    else
        gcmCrypto_queueDecrypt(self->gcm, p, p, charsRemaining);
    
    // move to next block. update accounting
    self->length -= charsRemaining;
    KCB_skip(self->head, charsRemaining);
}
#endif
