// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file Z9LockIOProtocolTest_KCB.c
 * @author Z9 Security
 */

#ifndef NO_UNIT_TESTS

#include "util/Logging.h"
#include "util/bzero.h"
#include "util/Assert.h"
#include "util/Bytes.h"
#include "util/Bytes_KCB.h"
#include "util/strncmp.h"
#include "util/ErrorStr.h"
#include "BasicSerializer_KCB.h"
#include "BasicDeserializer_KCB.h"
#include "Z9LockIOProtocol_Current.h"
#include "Z9LockIOProtocol_Current_Serialization_KCB.h"
#include "LockPacketUtil.h"
#include "z9io/ProtocolPassthru_Optimized.h"
#include "z9io/PacketUtil.h"
#include "Crc16_KCB.h"
#ifndef WITH_UNIT_TEST_LOCAL_STORAGE
#include "Task_HostIO.h" // for a LockPacket we can use
#endif
#include "Z9LockIOProtocolTest_KCB.h"

#define LOG_NAME "Z9LockIOProtocolTest_KCB"

static error_t Z9LockIOProtocolTest_KCB_testSerializeDeserialize_01(void);
static error_t Z9LockIOProtocolTest_KCB_testSerializeDeserialize_03(void);
static error_t Z9LockIOProtocolTest_KCB_testProtocolPassthru_LockIdentification(void);
static error_t Z9LockIOProtocolTest_KCB_testProtocolPassthru_LockPublicKeyExchange(void);

error_t Z9LockIOProtocolTest_KCB_testAll(void)
{
	error_t error = E_OK;

	KernelConfigurationData configurationData;
	bzero(&configurationData, sizeof (configurationData));
	
	CHECK_THROW( KernelBuffer_init(configurationData) );
	CHECK_THROW( Z9LockIOProtocolTest_KCB_testSerializeDeserialize_01() );
	CHECK_THROW( Z9LockIOProtocolTest_KCB_testSerializeDeserialize_03() );
	CHECK_THROW( Z9LockIOProtocolTest_KCB_testProtocolPassthru_LockIdentification() );
	CHECK_THROW( Z9LockIOProtocolTest_KCB_testProtocolPassthru_LockPublicKeyExchange() );

	return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", "testAll", errorStr(error), error);
	return error;
}

error_t Z9LockIOProtocolTest_KCB_testSerializeDeserialize_Single(struct LockPacket *p, const char *targetHex);

#ifndef WITH_UNIT_TEST_LOCAL_STORAGE
#ifdef NO_HOSTIO
struct LockPacket Task_HostIO_incomingPacket_Full_Static; // if NO_HOSTIO is defined, then this doesn't exist externally and we need one defined here.
#else
extern struct LockPacket Task_HostIO_incomingPacket_Full_Static;
#endif
#endif


error_t Z9LockIOProtocolTest_KCB_testSerializeDeserialize_01(void)
{
	error_t error = E_OK;

#ifdef WITH_UNIT_TEST_LOCAL_STORAGE
	struct LockPacket packet;
	struct LockPacket *p = &packet;
#else
	struct LockPacket *p = &Task_HostIO_incomingPacket_Full_Static;
#endif
	
	bzero(p, sizeof(struct LockPacket));
	struct LockDbChange_Config *dbChange = &p->content.uLockDbChange_Config;
	dbChange->base.contentType = LockDbChange_Config_DISCRIMINATOR;
	dbChange->updateConfigPresent = true;
	struct LockConfig *lockConfig = &dbChange->updateConfig[0];
	lockConfig->hostGrantConfig.initiationMode = LockHostGrantInitiationMode_ALWAYS;

	CHECK_THROW ( Z9LockIOProtocolTest_KCB_testSerializeDeserialize_Single(p, "7a390037020000000000000000010000000000000000000000000000000000000000000000000100000000000000000000000000000000") );
	
	return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", "testSerializeDeserialize_01", errorStr(error), error);
	return error;
}

error_t Z9LockIOProtocolTest_KCB_testSerializeDeserialize_03(void)
{
	error_t error = E_OK;

#ifdef WITH_UNIT_TEST_LOCAL_STORAGE
	struct LockPacket packet;
	struct LockPacket *p = &packet;
#else
	struct LockPacket *p = &Task_HostIO_incomingPacket_Full_Static;
#endif
	
	bzero(p, sizeof(struct LockPacket));
	struct LockEvtBatch *b = &p->content.uLockEvtBatch;
	b->base.contentType = LockEvtBatch_DISCRIMINATOR;

	b->evtCount = 1;
	struct LockEvt *e = &b->evt[0];
	e->evtCode = LockEvtCode_DOOR_ACCESS_DENIED_UNKNOWN_CRED_NUM;
	// 2022-06-27 10:52:06
	e->dateTime.year = 2022;
	e->dateTime.month = 6;
	e->dateTime.day = 27;
	e->dateTime.hour = 10;
	e->dateTime.minute = 52;
	e->dateTime.second = 6;
	
	CHECK_THROW ( Z9LockIOProtocolTest_KCB_testSerializeDeserialize_Single(p, "7a39001705000107e6061b0a3406080000000000000000") );
	
	return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", "testSerializeDeserialize_03", errorStr(error), error);
	return error;
}

// Z9LOCKIO_MESSAGE_MAX_BODY_LEN is overkill for this test, and consumes too much memory for an embedded test run.
#define Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST 100

error_t Z9LockIOProtocolTest_KCB_testSerializeDeserialize_Single(struct LockPacket *p, const char *targetHex)
{
	error_t error = E_OK;

	KCB_Hdr *kcb = KCB_alloc(0);
	if (!kcb)
		THROW( E_OUT_OF_MEMORY );
	
	struct BasicSerializer_KCB serializer;
	BasicSerializer_KCB_init(&serializer, kcb, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST, true);

	int result;
	if ((result = LockPacket_serialize_KCB(p, &serializer)) != 0)
	{
		LOG_ERROR("%s: Packet.serialize failed: result=%d contentType=%d", "testSerializeDeserialize_Single", result, (int) LockPacket_getContentType(p));
		THROW( E_SERIALIZE );
	}
	
	const uint8_t contentType = LockPacket_getContentType(p);

	const int serializedByteCount = BasicSerializer_KCB_getCurPos(&serializer);

	KCB_top(kcb);
	CHECK_THROW( KCB_status(kcb) );
	
	char serializedHex[Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST * 2 + 1];
	CHECK_THROW( Bytes_toHexString_KCB(kcb, serializedByteCount, serializedHex, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST * 2 + 1) );
	
	result = strncmp(targetHex, serializedHex, serializedByteCount * 2);
	if (result)
	{
		LOG_WARN("%s: expected hex: %s", "testSerializeDeserialize", targetHex);
		LOG_WARN("%s: actual hex:   %s", "testSerializeDeserialize", serializedHex);
	}
	CHECK_THROW( result == 0 ? 0 : 1000);

	LOG_OFF("%s: actual hex:   %s", "testSerializeDeserialize", serializedHex);

	// save some stuff to check against later, so we can re-use the LockPacket p
	struct LockHostGrantConfig hostGrantConfig;
	memcpy(&hostGrantConfig, &p->content.uLockDbChange_Config.updateConfig[0].hostGrantConfig, sizeof(struct LockHostGrantConfig));
	
	bzero(p, sizeof(struct LockPacket));

	KCB_top(kcb);
	CHECK_THROW( KCB_status(kcb) );

	struct BasicDeserializer_KCB deserializer;
	BasicDeserializer_KCB_init(&deserializer, kcb, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST, true);
	if ((result = LockPacket_deserialize_KCB(p, &deserializer)) != 0)
	{
		LOG_WARN("%s: LockPacket_deserialize failed: result=%d", "testSerializeDeserialize", result);
		THROW( E_SERIALIZE );
	}

	const uint8_t contentType2 = LockPacket_getContentType(p);

	// just assert a bunch of stuff we might test
	CHECK_THROW(hostGrantConfig.initiationMode == p->content.uLockDbChange_Config.updateConfig[0].hostGrantConfig.initiationMode ? 0 : 1001);

	CHECK_THROW(contentType == contentType2 ? 0 : 1002);
	
	CHECK_THROW( KCB_free(kcb) );
	
	return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", "testSerializeDeserialize_Single", errorStr(error), error);
	return error;
}


// this test is intended to reflect what we do in HostIO when we want to send a z9lockio message via z9io ProtocolPassthru.
#undef Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST
#define Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST 1037

error_t Z9LockIOProtocolTest_KCB_testProtocolPassthru_LockIdentification()
{
	error_t error = E_OK;

	KCB_Hdr *kcb = KCB_alloc(0);
	if (!kcb)
		THROW( E_OUT_OF_MEMORY );
	
	struct BasicSerializer_KCB serializer;
	BasicSerializer_KCB_init(&serializer, kcb, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST, true);
	
	const enum LockIdentificationType destination = LockIdentificationType_LOCK;
	
	struct Packet packet_headerTrailerOnly;
	struct ProtocolPassthru_Optimized protocolPassthru_Optimized;
	int posBeforePassthruContent;
	{
		int result;
		
		bzero(&packet_headerTrailerOnly, sizeof(packet_headerTrailerOnly));
		
		if ((result = Packet_HeaderOnly_serialize_KCB(&packet_headerTrailerOnly, &serializer)) != 0)
		{
			LOG_ERROR("%s: Packet_HeaderOnly_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
		
		bzero(&protocolPassthru_Optimized, sizeof(protocolPassthru_Optimized));
		
		protocolPassthru_Optimized.base.contentType = ProtocolPassthru_DISCRIMINATOR;
		protocolPassthru_Optimized.protocolId = PROTOCOL_PASSTHRU_ID_Z9LOCKIO;
		protocolPassthru_Optimized.numFragments = 1;
		protocolPassthru_Optimized.fragmentIndex = 0;
		protocolPassthru_Optimized.numBytes = 0; // we will have to set this later, below, after we know the total length.
		
		posBeforePassthruContent = BasicSerializer_KCB_getCurPos(&serializer);
		const size_t curPos = KCB_curPos(kcb);
		if (curPos != posBeforePassthruContent)
		{
			LOG_ERROR("%s: BasicSerializer_KCB_getCurPos returned=%d, but KCB_curPos returned %d", __FUNCTION__, (int) posBeforePassthruContent, (int) curPos);
			THROW( E_GENERIC );
		}

		if ((result = ProtocolPassthru_Optimized_serialize_KCB(&protocolPassthru_Optimized, &serializer)) != 0)
		{
			LOG_ERROR("%s: ProtocolPassthru_Optimized_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
		
	}
	
	const int posBeforePassthruBytes = BasicSerializer_KCB_getCurPos(&serializer);
	
	// now LockPacket
	
	{
#ifdef WITH_UNIT_TEST_LOCAL_STORAGE
		struct LockPacket packet;
		struct LockPacket *p = &packet;
#else
		struct LockPacket *p = &Task_HostIO_incomingPacket_Full_Static;
#endif
		
		p->content.uLockIdentification.base.contentType = LockBundleHeader_DISCRIMINATOR;
		
		int result;
		
		if ((result = LockPacket_serialize_KCB(p, &serializer)) != 0)
		{
			LOG_ERROR("%s: LockPacket_serialize_KCB failed: result=%d contentType=%d, destination=%s", __FUNCTION__, result, (int) LockPacket_getContentType(p), LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
	}
	
	{
#ifdef WITH_UNIT_TEST_LOCAL_STORAGE
		struct LockPacket packet;
		struct LockPacket *p = &packet;
#else
		struct LockPacket *p = &Task_HostIO_incomingPacket_Full_Static;
#endif
		
		p->content.uLockIdentification.base.contentType = LockIdentification_DISCRIMINATOR;
		
		int result;
		
		if ((result = LockPacket_serialize_KCB(p, &serializer)) != 0)
		{
			LOG_ERROR("%s: LockPacket_serialize_KCB failed: result=%d contentType=%d, destination=%s", __FUNCTION__, result, (int) LockPacket_getContentType(p), LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
	}
	
	{
		int result;
		
		const int posAfterPassthruBytes = BasicSerializer_KCB_getCurPos(&serializer);
		{
			const size_t curPos = KCB_curPos(kcb);
			if (curPos != posAfterPassthruBytes)
			{
				LOG_ERROR("%s: BasicSerializer_KCB_getCurPos returned=%d, but KCB_curPos returned %d", __FUNCTION__, (int) posAfterPassthruBytes, (int) curPos);
				THROW( E_GENERIC );
			}
		}
		
		const int passthruBytesCount = posAfterPassthruBytes - posBeforePassthruBytes;

		// go back and write the proper bytecount for the passthru bytes:
		
		protocolPassthru_Optimized.numBytes = passthruBytesCount; // we will have to set this later, below, after we know the total length.
		
		CHECK_THROW( BasicSerializer_KCB_seek(&serializer, posBeforePassthruContent) );
		if ((result = ProtocolPassthru_Optimized_serialize_KCB(&protocolPassthru_Optimized, &serializer)) != 0)
		{
			LOG_ERROR("%s: ProtocolPassthru_Optimized_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}

		// go to top and rewrite z9io header with bytecount
		CHECK_THROW( BasicSerializer_KCB_seek(&serializer, 0) );
		packet_headerTrailerOnly.bytecount = posAfterPassthruBytes + 2; // add 2 for trailer bytes
		if ((result = Packet_HeaderOnly_serialize_KCB(&packet_headerTrailerOnly, &serializer)) != 0)
		{
			LOG_ERROR("%s: Packet_HeaderOnly_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
		
		// Calculate CRC16
		{
			const unsigned short crc16 = Crc16_calculateCRC_KCB(BasicSerializer_KCB_getKCB(&serializer), 0, packet_headerTrailerOnly.bytecount - 2); // -2 for the CRC16.
			packet_headerTrailerOnly.crc16 = crc16;
		}
		
		// add bytes for the z9io trailer:
		CHECK_THROW( BasicSerializer_KCB_seek(&serializer, posAfterPassthruBytes) );
		if ((result = Packet_TrailerOnly_serialize_KCB(&packet_headerTrailerOnly, &serializer)) != 0)
		{
			LOG_ERROR("%s: Packet_TrailerOnly_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
	}
	
	const int posAfterAllWrites = BasicSerializer_KCB_getCurPos(&serializer);
	{
		const size_t curPos = KCB_curPos(kcb);
		if (curPos != posAfterAllWrites)
		{
			LOG_ERROR("%s: BasicSerializer_KCB_getCurPos returned=%d, but KCB_curPos returned %d", __FUNCTION__, (int) posAfterAllWrites, (int) curPos);
			THROW( E_GENERIC );
		}
	}
	
	KCB_top(kcb);
	CHECK_THROW( KCB_status(kcb) );

	// now read all bytes:
	for (int i = 0; i < posAfterAllWrites; ++i)
	{
		/* const uint8_t c = */ KCB_read(kcb);
		CHECK_THROW( KCB_status(kcb) );
	}
	
#if 0
#ifdef WITH_LOGGING
	{
		KCB_top(kcb);
		char serializedHex[Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST * 2 + 1];
		CHECK_THROW( Bytes_toHexString_KCB(kcb, posAfterAllWrites, serializedHex, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST * 2 + 1) );
		LOG_INFO("%s: generated %d bytes: %s, destination=%s", __FUNCTION__, (int) posAfterAllWrites, serializedHex, LockIdentificationType_toString(destination));
	}
#endif
#endif
	
	// now do what SerialAsync does in async_tx_queue:
	KCB_top(kcb);
	CHECK_THROW( KCB_status(kcb) );
	for (unsigned n = 0; n < 5; n++)
		KCB_pop(kcb);
	CHECK_THROW( KCB_status(kcb) );
	
	CHECK_THROW( KCB_free(kcb) );
	
	return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", __FUNCTION__, errorStr(error), error);
	return error;
}

error_t Z9LockIOProtocolTest_KCB_testProtocolPassthru_LockPublicKeyExchange()
{
	error_t error = E_OK;

	KCB_Hdr *kcb = KCB_alloc(0);
	if (!kcb)
		THROW( E_OUT_OF_MEMORY );
	
	struct BasicSerializer_KCB serializer;
	BasicSerializer_KCB_init(&serializer, kcb, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST, true);
	
	const enum LockIdentificationType destination = LockIdentificationType_LOCK;
	
	struct Packet packet_headerTrailerOnly;
	struct ProtocolPassthru_Optimized protocolPassthru_Optimized;
	int posBeforePassthruContent;
	{
		int result;
		
		bzero(&packet_headerTrailerOnly, sizeof(packet_headerTrailerOnly));
		
		if ((result = Packet_HeaderOnly_serialize_KCB(&packet_headerTrailerOnly, &serializer)) != 0)
		{
			LOG_ERROR("%s: Packet_HeaderOnly_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
		
		bzero(&protocolPassthru_Optimized, sizeof(protocolPassthru_Optimized));
		
		protocolPassthru_Optimized.base.contentType = ProtocolPassthru_DISCRIMINATOR;
		protocolPassthru_Optimized.protocolId = PROTOCOL_PASSTHRU_ID_Z9LOCKIO;
		protocolPassthru_Optimized.numFragments = 1;
		protocolPassthru_Optimized.fragmentIndex = 0;
		protocolPassthru_Optimized.numBytes = 0; // we will have to set this later, below, after we know the total length.
		
		posBeforePassthruContent = BasicSerializer_KCB_getCurPos(&serializer);
		const size_t curPos = KCB_curPos(kcb);
		if (curPos != posBeforePassthruContent)
		{
			LOG_ERROR("%s: BasicSerializer_KCB_getCurPos returned=%d, but KCB_curPos returned %d", __FUNCTION__, (int) posBeforePassthruContent, (int) curPos);
			THROW( E_GENERIC );
		}

		if ((result = ProtocolPassthru_Optimized_serialize_KCB(&protocolPassthru_Optimized, &serializer)) != 0)
		{
			LOG_ERROR("%s: ProtocolPassthru_Optimized_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
		
	}
	
	const int posBeforePassthruBytes = BasicSerializer_KCB_getCurPos(&serializer);
	
	// now LockPacket
	
	{
#ifdef WITH_UNIT_TEST_LOCAL_STORAGE
		struct LockPacket packet;
		struct LockPacket *p = &packet;
#else
		struct LockPacket *p = &Task_HostIO_incomingPacket_Full_Static;
#endif
		
		p->content.uLockIdentification.base.contentType = LockBundleHeader_DISCRIMINATOR;
		
		int result;
		
		if ((result = LockPacket_serialize_KCB(p, &serializer)) != 0)
		{
			LOG_ERROR("%s: LockPacket_serialize_KCB failed: result=%d contentType=%d, destination=%s", __FUNCTION__, result, (int) LockPacket_getContentType(p), LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
	}
	
	{
#ifdef WITH_UNIT_TEST_LOCAL_STORAGE
		struct LockPacket packet;
		struct LockPacket *p = &packet;
#else
		struct LockPacket *p = &Task_HostIO_incomingPacket_Full_Static;
#endif
		
		p->content.uLockPublicKeyExchange.base.contentType = LockPublicKeyExchange_DISCRIMINATOR;
		p->content.uLockPublicKeyExchange.numPublicKeyBytes = 33;
		for (int i = 0; i < p->content.uLockPublicKeyExchange.numPublicKeyBytes; ++i)
			p->content.uLockPublicKeyExchange.publicKeyBytes[i] = i;

		
		int result;
		
		if ((result = LockPacket_serialize_KCB(p, &serializer)) != 0)
		{
			LOG_ERROR("%s: LockPacket_serialize_KCB failed: result=%d contentType=%d, destination=%s", __FUNCTION__, result, (int) LockPacket_getContentType(p), LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
	}
	
	{
		int result;
		
		const int posAfterPassthruBytes = BasicSerializer_KCB_getCurPos(&serializer);
		{
			const size_t curPos = KCB_curPos(kcb);
			if (curPos != posAfterPassthruBytes)
			{
				LOG_ERROR("%s: BasicSerializer_KCB_getCurPos returned=%d, but KCB_curPos returned %d", __FUNCTION__, (int) posAfterPassthruBytes, (int) curPos);
				THROW( E_GENERIC );
			}
		}
		
		const int passthruBytesCount = posAfterPassthruBytes - posBeforePassthruBytes;

		// go back and write the proper bytecount for the passthru bytes:
		
		protocolPassthru_Optimized.numBytes = passthruBytesCount; // we will have to set this later, below, after we know the total length.
		
		CHECK_THROW( BasicSerializer_KCB_seek(&serializer, posBeforePassthruContent) );
		if ((result = ProtocolPassthru_Optimized_serialize_KCB(&protocolPassthru_Optimized, &serializer)) != 0)
		{
			LOG_ERROR("%s: ProtocolPassthru_Optimized_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}

		// go to top and rewrite z9io header with bytecount
		CHECK_THROW( BasicSerializer_KCB_seek(&serializer, 0) );
		packet_headerTrailerOnly.bytecount = posAfterPassthruBytes + 2; // add 2 for trailer bytes
		if ((result = Packet_HeaderOnly_serialize_KCB(&packet_headerTrailerOnly, &serializer)) != 0)
		{
			LOG_ERROR("%s: Packet_HeaderOnly_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
		
		// Calculate CRC16
		{
			const unsigned short crc16 = Crc16_calculateCRC_KCB(BasicSerializer_KCB_getKCB(&serializer), 0, packet_headerTrailerOnly.bytecount - 2); // -2 for the CRC16.
			packet_headerTrailerOnly.crc16 = crc16;
		}
		
		// add bytes for the z9io trailer:
		CHECK_THROW( BasicSerializer_KCB_seek(&serializer, posAfterPassthruBytes) );
		if ((result = Packet_TrailerOnly_serialize_KCB(&packet_headerTrailerOnly, &serializer)) != 0)
		{
			LOG_ERROR("%s: Packet_TrailerOnly_serialize_KCB failed: result=%d destination=%s", __FUNCTION__, result, LockIdentificationType_toString(destination));
			THROW( E_SERIALIZE );
		}
	}
	
	const int posAfterAllWrites = BasicSerializer_KCB_getCurPos(&serializer);
	{
		const size_t curPos = KCB_curPos(kcb);
		if (curPos != posAfterAllWrites)
		{
			LOG_ERROR("%s: BasicSerializer_KCB_getCurPos returned=%d, but KCB_curPos returned %d", __FUNCTION__, (int) posAfterAllWrites, (int) curPos);
			THROW( E_GENERIC );
		}
	}
	
	KCB_top(kcb);
	CHECK_THROW( KCB_status(kcb) );

	// now read all bytes:
	for (int i = 0; i < posAfterAllWrites; ++i)
	{
		/* const uint8_t c = */ KCB_read(kcb);
		CHECK_THROW( KCB_status(kcb) );
	}
	
#if 0
#ifdef WITH_LOGGING
	{
		KCB_top(kcb);
		char serializedHex[Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST * 2 + 1];
		CHECK_THROW( Bytes_toHexString_KCB(kcb, posAfterAllWrites, serializedHex, Z9LOCKIO_MESSAGE_MAX_BODY_LEN__THIS_TEST * 2 + 1) );
		LOG_INFO("%s: generated %d bytes: %s, destination=%s", __FUNCTION__, (int) posAfterAllWrites, serializedHex, LockIdentificationType_toString(destination));
	}
#endif
#endif
	
	// now do what SerialAsync does in async_tx_queue:
	KCB_top(kcb);
	CHECK_THROW( KCB_status(kcb) );
	for (unsigned n = 0; n < 5; n++)
		KCB_pop(kcb);
	CHECK_THROW( KCB_status(kcb) );

	CHECK_THROW( KCB_free(kcb) );
	
	return E_OK;
	
exception:
	LOG_ERROR("%s: Error: %s (%d)", __FUNCTION__, errorStr(error), error);
	return error;
}


#endif

