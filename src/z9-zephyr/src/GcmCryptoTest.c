// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file GcmCryptoTest.c
 * @author Z9 Security
 */

#ifndef NO_UNIT_TESTS

#include "util/Logging.h"
#include "util/bzero.h"
#include "util/Assert.h"
#include "util/ErrorStr.h"
#include "util/Dates.h"
#include "util/memcmp.h"
#include "kernel/KernelBuffer.h"
#include "kernel/KernelTimer.h"
#include "kernel/KernelSchedule.h"
#include "GcmCrypto_KCB.h"
#include "GcmCryptoTest.h"
#include "GcmCryptoTest.h"
#include <stdio.h>

#define LOG_NAME "GcmCryptoTest"

// configure test
//#define DEBUG_GCM                   // generate logging messages
//#define DISABLE_TIMEOUT             // prevent timeouts from failing tests
//#define DUMP_CIPHER                 // dump hex to faciliate generating tests
//#define GCM_INITIAL_VECTOR_INDEX 1  // start with specified test

// declare test vectors
static const char LoremIpsum[] = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt "
    "ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
    "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
    "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
    "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
};

static const struct GcmVector
{
    const char *keyHexString;
    const char *plainString;
    const char *cryptoHexString;
} Vectors[] =
{
    {
        // 16-byte message (1 block of 16 bytes)
        .keyHexString    = "d6fdfe5ea396d9fdcd3748390ddba8d8",
        .plainString     = "plain text here!",
        .cryptoHexString = "76fb6d7d50c601a4176855ae"           // IV
                           "e042ab0854f68cba20f0273a5b8f3ca6"   // TAG
                           "812da90d4accc6f0f28ce72ce3c7d363",  // cipher
    },
    {
        // 24-byte message (1 + 1/2 blocks)
        .keyHexString    = "d6fdfe5ea396d9fdcd3748390ddba8d8",
        .plainString     = "plain text here! extra++",
        .cryptoHexString = "76fb6d7d50c601a4176855ae"           // IV
                           "a7a8158757d0c7c7ad24556fc8759c31"   // TAG
                           "812da90d4accc6f0f28ce72ce3c7d363"   // cipher
                           "bbde0f8171393618",
    },
    {
        // 72-byte message (KCB spans 2 KerenelBlocks)
        .keyHexString    = "d6fdfe5ea396d9fdcd3748390ddba8d8",
        .plainString     = "plain text here! extra++"
                           "plain text here! extra++"
                           "plain text here! extra++",
        .cryptoHexString = "76fb6d7d50c601a4176855ae"           // IV
                "c53281717c48b0041f0bae2059074f57"
                "812da90d4accc6f0f28ce72ce3c7d363"
                "bbde0f81713936189812db2a080fdbc2"
                "6cbe4a676efb492a1331ac1eba4735ca"
                "4f3737057e65b0a2a0f9b1d19109262b"
                "2e5793e6ca69c637",
    },
    {
        // long message (long message: 445 bytes)
        .keyHexString    = "a7a8158757d0c7c7ad24556fc8759c31",
        .plainString     = LoremIpsum,
        .cryptoHexString = "a7a8158757d0c7c7ad24556f"       // IV
                "df1784433bc27c9711c10998bc089b46"          // TAG
                "24ff74acde8283b7649bab35edb1f2ea"
                "b4690ecb39fc5368ecc5f865a7bc1307"
                "2eb469b96c2ecfd3aeed0e2b3a235600"
                "4c97a9935d813578df267aee35fe99fe"
                "ce558bc45317e36ec17fc178248be1f6"
                "5feff3b3a94b28da9b5f5e4ee321169c"
                "01cbeaf5f3e1a964298e172a4c2d579a"
                "d9162d236b1b84302772ad8090cea862"
                "60aae2530bb6066c1662d13aca36974f"
                "7f30bc4304b8b1c2fe8695a3458581a1"
                "464c0e7bccbab5386a7a79886ddc2796"
                "2905c25be0790ae8d9c3f9008e6a88a5"
                "3ac2a85fb031d560966376c762b6349c"
                "cff40c7d64b04f3e9462b7455a9b622f"
                "7d9ca35838c626d69f33b63d6ec3e221"
                "2eae3292812a301536c74261a0dc868d"
                "e4c1512741f9de1f5b2ca1b783aa349d"
                "6be547ca68c51c7b49fcaccf4f8febd8"
                "ecb793bf31823da42f9b0d65d1029f3e"
                "bdeed3c6f9c06507b760b51907a2e5ed"
                "0862244b84940bd108c8929086f3f7e9"
                "375ef48229e1ef1e9690de23952603dd"
                "9fef34bf7177894838030784d5662b6e"
                "18393423bf9269ecbdded832645eb3bd"
                "573150e7388194948ad5b86e1fb5e443"
                "49cdb980083a1f6da6127ee4ee60da02"
                "abc0e2c1be790f51b1405a3eccca8771"
                "11ae4313688faf932f0d5ce05f"
    },
};

#define NUM_VECTORS (sizeof(Vectors)/sizeof(struct GcmVector))
#define MAX_PLAIN   1000

// allow test to start with specific vector
#ifndef GCM_INITIAL_VECTOR_INDEX
#define GCM_INITIAL_VECTOR_INDEX 0
#endif

// manipulate LOG_* verbosity
#ifdef DEBUG_GCM
#define LOG_INFO_GCM    LOG_INFO
#else
#define LOG_INFO_GCM    LOG_OFF
#endif

// forward declare internal functions
static void readHex(uint32_t *bin, const char *hex, size_t bytes);
static KCB_Hdr *create_kcb(uint8_t headroom, const void *crypto, size_t length);
static void dumpHex(const char *title, const void *data, unsigned length);

static error_t GcmCryptoTest_testEncrypt(GcmCrypto *,
                                         const uint32_t *key,
                                         const uint32_t *iv,
                                         const uint32_t *tag,
                                         const uint32_t *plain,
                                         const uint32_t *cipher,
                                         const uint32_t length);

static error_t GcmCryptoTest_testDecrypt(GcmCrypto *,
                                         const uint32_t *key,
                                         const uint32_t *iv,
                                         const uint32_t *tag,
                                         const uint32_t *plain,
                                         const uint32_t *cipher,
                                         const uint32_t length);

static error_t GcmCryptoTest_testEncrypt_KCB(GcmCrypto *,
                                             const uint32_t *key,
                                             uint32_t        headroom,
                                             const char     *prefix,
                                             uint32_t        prefixLen,
                                             const uint32_t *plain,
                                             const uint32_t *crypto,
                                             const uint32_t length);

static error_t GcmCryptoTest_testDecrypt_KCB(GcmCrypto *,
                                             const uint32_t *key,
                                             uint32_t        headroom,
                                             const char     *prefix,
                                             uint32_t        prefixLen,
                                             const uint32_t *plain,
                                             const uint32_t *crypto,
                                             const uint32_t length);

error_t GcmCryptoTest_testAll(void)
{
	error_t error = E_OK;

	KernelConfigurationData configurationData;
	bzero(&configurationData, sizeof (configurationData));
	
	CHECK_THROW( KernelBuffer_init(configurationData) );
	CHECK_THROW( KernelExecutor_init(configurationData) );
    CHECK_THROW( KernelTimer_init(configurationData) );
    CHECK_THROW( KernelSchedule_init(configurationData) );

    GcmCrypto *gcm = gcmCrypto_init(CS_LINK, 0);
  
    int i = GCM_INITIAL_VECTOR_INDEX;          // first test to run
    const struct GcmVector *vector_p = &Vectors[i];
    while(i++ < NUM_VECTORS)
    {
        // convert hex values to binary
        const uint32_t plainLength  = (unsigned)strlen(vector_p->plainString);
        const uint32_t cryptoLength = (unsigned)strlen(vector_p->cryptoHexString)/2;
#ifdef DUMP_CIPHER
        LOG_INFO_GCM("%s: vector %d: plainLen = %d, cryptoLen = %d", __FUNCTION__, i, plainLength, cryptoLength);
#endif
        
        CHECK_THROW( plainLength >= MAX_PLAIN );
        
        uint32_t buffer[MAX_PLAIN/4 + 7], plain[MAX_PLAIN/4], key[4];
        const uint32_t *iv, *tag, *cipher;
        readHex(key   , vector_p->keyHexString   , sizeof(key));
        readHex(buffer, vector_p->cryptoHexString, cryptoLength);
        iv     = &buffer[0];
        tag    = &buffer[3];
        cipher = &buffer[3 + 4];
       
        // copy `plainString` into 32-bit aligned memory
        memcpy (plain, vector_p->plainString, plainLength);
        
        // validate test vector
        CHECK_THROW( plainLength != (cryptoLength - 12 - 16) );

        // validate page aligned data
        CHECK_THROW( GcmCryptoTest_testEncrypt(gcm, key, iv, tag, plain, cipher, plainLength) );
        CHECK_THROW( GcmCryptoTest_testDecrypt(gcm, key, iv, tag, plain, cipher, plainLength) );
        
        // KCB validate page aligned data
        CHECK_THROW( GcmCryptoTest_testEncrypt_KCB(gcm, key, 0, LoremIpsum, 0, plain, buffer, plainLength) );
        CHECK_THROW( GcmCryptoTest_testDecrypt_KCB(gcm, key, 0, LoremIpsum, 0, plain, buffer, plainLength) );
        
        // KCB validate unaligned data, no prefix specified
        CHECK_THROW( GcmCryptoTest_testEncrypt_KCB(gcm, key, 1, LoremIpsum, 0, plain, buffer, plainLength) );
        CHECK_THROW( GcmCryptoTest_testDecrypt_KCB(gcm, key, 1, LoremIpsum, 0, plain, buffer, plainLength) );

        // KCB validate unaligned data, with prefix specified
        CHECK_THROW( GcmCryptoTest_testEncrypt_KCB(gcm, key, 3, LoremIpsum, 6, plain, buffer, plainLength) );
        CHECK_THROW( GcmCryptoTest_testDecrypt_KCB(gcm, key, 3, LoremIpsum, 6, plain, buffer, plainLength) );
        
        // next vector
        ++vector_p;
    }
    return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", "testAll", errorStr(error), error);
	return error;
		
}

// testEncrypt

static volatile Signal routeHandler_testEncrypt_signal;
static volatile MonotonicMillis routeHandler_testEncrypt_millis;

static error_t routeHandler_testEncrypt(void *instance, Signal signal)
{
    // Signal is error code
    routeHandler_testEncrypt_millis = Dates_monotonicMillis();
    routeHandler_testEncrypt_signal = signal;
    return E_OK;
}


static error_t GcmCryptoTest_testEncrypt(GcmCrypto *gcm,
                                         const uint32_t *key,
                                         const uint32_t *iv,
                                         const uint32_t *tag,
                                         const uint32_t *plain,
                                         const uint32_t *cipher,
                                         const uint32_t length)
{
    error_t error = E_OK;

    routeHandler_testEncrypt_signal = 0;
    routeHandler_testEncrypt_millis = 0;
    
    RouteIndex returnRoute;
    KernelExecutor_registerRoute(&returnRoute , routeHandler_testEncrypt, NULL, "testEncrypt" , NULL);

    // set up gcm engine
    const uint32_t output[MAX_PLAIN], tag_output[4];
    gcmCrypto_init(CS_LINK, returnRoute);
    gcmCrypto_doSetKeyBytes(gcm, (void *)key, 16);
    gcmCrypto_doNewMessage (gcm, (void *)iv, 0, length);
    gcmCrypto_queueEncrypt (gcm, (void *)plain, (void *)output, length);
    
    LOG_INFO_GCM("%s: awaiting scheduled callback: encrypting", __FUNCTION__);

    MonotonicMillis startMillis = Dates_monotonicMillis();
    const int timeoutAfterMillis = 500;
   
    while (!routeHandler_testEncrypt_millis)
    {
        bool idle = false;
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );

#ifndef DISABLE_TIMEOUT
        MonotonicMillis nowMillis = Dates_monotonicMillis();
        if (nowMillis > startMillis + timeoutAfterMillis)
        {
            LOG_ERROR("%s: did not receive encrypt callback within %d millis", __FUNCTION__, timeoutAfterMillis);
            THROW (E_TIMEOUT);
        }
#endif
    }
    CHECK_THROW( routeHandler_testEncrypt_signal != E_OK);
    
    // print out calculated cipher
    dumpHex("CIPHER", output, length);
    
    CHECK_THROW( memcmp(output, cipher, length) != 0 );

    routeHandler_testEncrypt_signal = 0;
    routeHandler_testEncrypt_millis = 0;
    gcmCrypto_queueGenerateTag(gcm, (void *)tag_output, sizeof(tag_output));
    
    LOG_INFO_GCM("%s: awaiting scheduled callback: generating tag", __FUNCTION__);

    while (!routeHandler_testEncrypt_millis)
    {
        bool idle = false;
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
#ifndef DISABLE_TIMEOUT
        MonotonicMillis nowMillis = Dates_monotonicMillis();
        if (nowMillis > startMillis + timeoutAfterMillis)
        {
            LOG_ERROR("%s: did not receive encrypt callback within %d millis", __FUNCTION__, timeoutAfterMillis);
            THROW (E_TIMEOUT);
        }
#endif
        
    }
    CHECK_THROW ( routeHandler_testEncrypt_signal != E_OK);

    // print out calculated
    dumpHex("TAG", tag_output, sizeof(tag_output));
    
    CHECK_THROW( memcmp(tag_output, tag, sizeof(tag_output)) != 0 );
    
    KernelExecutor_deregisterRoute(returnRoute);
    return E_OK;
    
exception:
    LOG_ERROR("%s: Error: %s (%d)", __FUNCTION__, errorStr(error), error);
    return error;
        
}

// testDecrypt

static volatile Signal routeHandler_testDecrypt_signal;
static volatile MonotonicMillis routeHandler_testDecrypt_millis;

static error_t routeHandler_testDecrypt(void *instance, Signal signal)
{
    // Signal is error code
    routeHandler_testDecrypt_millis = Dates_monotonicMillis();
    routeHandler_testDecrypt_signal = signal;
    return E_OK;
}


static error_t GcmCryptoTest_testDecrypt(GcmCrypto *gcm,
                                         const uint32_t *key,
                                         const uint32_t *iv,
                                         const uint32_t *tag,
                                         const uint32_t *plain,
                                         const uint32_t *cipher,
                                         const uint32_t length)
{
    error_t error = E_OK;

    routeHandler_testDecrypt_signal = 0;
    routeHandler_testDecrypt_millis = 0;
    
    RouteIndex returnRoute;
    KernelExecutor_registerRoute(&returnRoute , routeHandler_testDecrypt, NULL, "testDecrypt" , NULL);

    // set up gcm engine
    const uint32_t output[MAX_PLAIN], tag_output[4];
    gcmCrypto_init(CS_LINK, returnRoute);
    gcmCrypto_doSetKeyBytes(gcm, (void *)key, 16);
    gcmCrypto_doNewMessage (gcm, (void *)iv, 0, length);
    gcmCrypto_queueDecrypt (gcm, (void *)cipher, (void *)output, length);
    
    
    LOG_INFO_GCM("%s: awaiting scheduled callback: decrypting", __FUNCTION__);

    MonotonicMillis startMillis = Dates_monotonicMillis();
    const int timeoutAfterMillis = 500;
   
    while (!routeHandler_testDecrypt_millis)
    {
        bool idle = false;
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );

#ifndef DISABLE_TIMEOUT
        MonotonicMillis nowMillis = Dates_monotonicMillis();
        if (nowMillis > startMillis + timeoutAfterMillis)
        {
            LOG_ERROR("%s: did not receive encrypt callback within %d millis", __FUNCTION__, timeoutAfterMillis);
            THROW (E_TIMEOUT);
        }
#endif

    }
    CHECK_THROW( routeHandler_testDecrypt_signal != E_OK);
    CHECK_THROW( memcmp(output, plain, length) != 0 );

    routeHandler_testDecrypt_signal = 0;
    routeHandler_testDecrypt_millis = 0;
    gcmCrypto_queueGenerateTag(gcm, (void *)tag_output, sizeof(tag_output));
    
    LOG_INFO_GCM("%s: awaiting scheduled callback: generating tag", __FUNCTION__);

    while (!routeHandler_testDecrypt_millis)
    {
        bool idle = false;
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );

#ifndef DISABLE_TIMEOUT
        MonotonicMillis nowMillis = Dates_monotonicMillis();
        if (nowMillis > startMillis + timeoutAfterMillis)
        {
            LOG_ERROR("%s: did not receive callback within %d millis", __FUNCTION__, timeoutAfterMillis);
            THROW (E_TIMEOUT);
        }
#endif

    }
    CHECK_THROW ( routeHandler_testDecrypt_signal != E_OK);

    CHECK_THROW( memcmp(tag_output, tag, sizeof(tag_output)) != 0 );
    
    KernelExecutor_deregisterRoute(returnRoute);
    return E_OK;
    
exception:
    LOG_ERROR("%s: Error: %s (%d)", __FUNCTION__, errorStr(error), error);
    return error;
        
}

// testEecrypt_KCB


static error_t GcmCryptoTest_testEncrypt_KCB(GcmCrypto *gcm,
                                             const uint32_t *key,
                                             uint32_t        headroom,
                                             const char     *prefix,
                                             uint32_t        prefixLen,
                                             const uint32_t *plain,
                                             const uint32_t *crypto,
                                                   uint32_t length)
{
    error_t error = E_OK;

    routeHandler_testEncrypt_signal = 0;
    routeHandler_testEncrypt_millis = 0;
    
    RouteIndex returnRoute;
    KernelExecutor_registerRoute(&returnRoute , routeHandler_testEncrypt, NULL, "testDecrypt" , NULL);

    // create KCB
    KCB_Hdr *buf = create_kcb(8 + 12 + 16 + headroom + prefixLen, plain, length);
    
    // set up gcm engine
    gcmCrypto_doSetKeyBytes(gcm, (void *)key, 16);
    
    // run engine
    const uint32_t *iv = crypto;      // IV is first
    CHECK_THROW( GcmCrypto_encrypt_KCB(CS_LINK, (void *)prefix, prefixLen, buf, length, returnRoute, iv) );
    
    LOG_INFO_GCM("%s: awaiting scheduled callback: encrypting", __FUNCTION__);

    MonotonicMillis startMillis = Dates_monotonicMillis();
    const int timeoutAfterMillis = 500;
   
    while (!routeHandler_testEncrypt_millis)
    {
        bool idle = false;
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
#ifndef DISABLE_TIMEOUT
        MonotonicMillis nowMillis = Dates_monotonicMillis();
        if (nowMillis > startMillis + timeoutAfterMillis)
        {
            LOG_ERROR("%s: did not receive encrypt callback within %d millis", __FUNCTION__, timeoutAfterMillis);
            THROW (E_TIMEOUT);
        }
#endif
    }
   
    // zero means tag failed
    CHECK_THROW( routeHandler_testEncrypt_signal == 0 );
    
    // test properly decoded
    length += 12 + 16;      // length is new size of buffer
    CHECK_THROW( KCB_size(buf) != (length + prefixLen) );
    
    KCB_top(buf);
   
    // check prefix
    while (prefixLen--)
        CHECK_THROW( *prefix++ != KCB_read(buf))
    
    // check IV + TAG + CIPHER
    const uint8_t *p = (void *)crypto;
    while (length--)
        CHECK_THROW( *p++ != KCB_read(buf) );
    
    KCB_free(buf);
    KernelExecutor_deregisterRoute(returnRoute);
    return E_OK;
    
exception:
    LOG_ERROR("%s: Error: %s (%d)", __FUNCTION__, errorStr(error), error);
    return error;
        
}
// testDecrypt_KCB


static error_t GcmCryptoTest_testDecrypt_KCB(GcmCrypto *gcm,
                                             const uint32_t *key,
                                             uint32_t        headroom,
                                             const char     *prefix,
                                             uint32_t        prefixLen,
                                             const uint32_t *plain,
                                             const uint32_t *crypto,
                                             uint32_t length)
{
    error_t error = E_OK;

    routeHandler_testDecrypt_signal = 0;
    routeHandler_testDecrypt_millis = 0;
    
    RouteIndex returnRoute;
    KernelExecutor_registerRoute(&returnRoute , routeHandler_testDecrypt, NULL, "testDecrypt" , NULL);

    // create KCB
    KCB_Hdr *buf = create_kcb(8 + headroom + prefixLen, crypto, length + 12 + 16);
    
    // set up gcm engine
    gcmCrypto_doSetKeyBytes(gcm, (void *)key, 16);
    
    // run engine
    CHECK_THROW( GcmCrypto_decrypt_KCB(CS_LINK, prefix, prefixLen, buf, length + 12 + 16, returnRoute) );
    
    LOG_INFO_GCM("%s: awaiting scheduled callback: decrypting", __FUNCTION__);

    MonotonicMillis startMillis = Dates_monotonicMillis();
    const int timeoutAfterMillis = 500;
   
    while (!routeHandler_testDecrypt_millis)
    {
        bool idle = false;
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
        CHECK_THROW( KernelExecutor_iteration(&idle) );
#ifndef DISABLE_TIMEOUT
        MonotonicMillis nowMillis = Dates_monotonicMillis();
        if (nowMillis > startMillis + timeoutAfterMillis)
        {
            LOG_ERROR("%s: did not receive encrypt callback within %d millis", __FUNCTION__, timeoutAfterMillis);
            THROW (E_TIMEOUT);
        }
#endif
    }
   
    // zero means tag failed
    CHECK_THROW( routeHandler_testDecrypt_signal == 0 );
    
    // test properly decoded
    CHECK_THROW( KCB_size(buf) != length + prefixLen );
    
    // check prefix
    while (prefixLen--)
        CHECK_THROW( *prefix++ != KCB_read(buf))
    
    uint8_t *p = (void *)plain;
    while (length--)
        CHECK_THROW( *p++ != KCB_read(buf) );
    
    KCB_free(buf);
    KernelExecutor_deregisterRoute(returnRoute);
    return E_OK;
    
exception:
    LOG_ERROR("%s: Error: %s (%d)", __FUNCTION__, errorStr(error), error);
    return error;
        
}

static KCB_Hdr *create_kcb(uint8_t headroom, const void *crypto, size_t length)
{
    const uint8_t *p = crypto;
    KCB_Hdr *hdr = KCB_alloc(headroom);
    while (length--)
        KCB_write(hdr, *p++);
    return hdr;
}

static void readHex(uint32_t *bin, const char *hex, size_t bytes)
{
    // read in big-endian order
    uint8_t *p = (void *)bin;
    while (bytes--)
    {
        char c = *hex++;
        int  n = 0;
        n += c > '9' ? (c &~ 0x20) - 'A' + 10 : c - '0';
        n <<= 4;
        c = *hex++;
        n += c > '9' ? (c &~ 0x20) - 'A' + 10 : c - '0';
        *p++ = n;
    }
}

static void dumpHex(const char *title, const void *data, unsigned length)
{
#ifdef DUMP_CIPHER
    uint8_t *p = data;
    
    printf("%s\n", title);
    
    while (length)
    {
        int n = length;
        if (n > 16)
            n = 16;
        length -= n;
        printf("\"");
        while (n--)
            printf("%02x", *p++);
        printf("\"\n");
    }
#endif
}

#endif // NO_UNIT_TESTS

