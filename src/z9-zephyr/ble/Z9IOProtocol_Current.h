/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9IOProtocol_Current.h
 * @author Z9 Security
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


struct BasicSerializer;
struct BasicDeserializer;

/**
 * Enum: {@link HostPairingState.h}.
 */
enum HostPairingState
{
	HostPairingState_CONSTRUCTION,
	HostPairingState_PAIRING,
	HostPairingState_PAIRED,
};

#ifdef WITH_LOGGING
/**
 * Convert HostPairingState to a string.
 * @return "?" if unknown.
 */
const char *HostPairingState_toString(enum HostPairingState value);
#endif // WITH_LOGGING


/**
 * Enum: {@link ProtocolPassthruId.h}.
 */
enum ProtocolPassthruId
{
	ProtocolPassthruId_NONE,
	ProtocolPassthruId_Z9LOCKIO,
	ProtocolPassthruId_SECURE_ELEMENT,
};

#ifdef WITH_LOGGING
/**
 * Convert ProtocolPassthruId to a string.
 * @return "?" if unknown.
 */
const char *ProtocolPassthruId_toString(enum ProtocolPassthruId value);
#endif // WITH_LOGGING


/**
 * Enum: {@link EncryptionKeyExchangeType.h}.
 */
enum EncryptionKeyExchangeType
{
	EncryptionKeyExchangeType_LINKING_SEED_REQ,
	EncryptionKeyExchangeType_LINKING_SEED_RESP,
	EncryptionKeyExchangeType_LINK_SESSION_SEED_REQ,
	EncryptionKeyExchangeType_LINK_SESSION_SEED_RESP,
};

#ifdef WITH_LOGGING
/**
 * Convert EncryptionKeyExchangeType to a string.
 * @return "?" if unknown.
 */
const char *EncryptionKeyExchangeType_toString(enum EncryptionKeyExchangeType value);
#endif // WITH_LOGGING


/**
 * Enum: {@link ApplicationEncryptionKeyExchangeType.h}.
 */
enum ApplicationEncryptionKeyExchangeType
{
	ApplicationEncryptionKeyExchangeType_PUBLIC_KEY_REQ,
	ApplicationEncryptionKeyExchangeType_PUBLIC_KEY_RESP,
	ApplicationEncryptionKeyExchangeType_KEY_AGREEMENT_REQ,
	ApplicationEncryptionKeyExchangeType_KEY_AGREEMENT_RESP,
	ApplicationEncryptionKeyExchangeType_BLE_CHALLENGE_NONCE_REQ,
	ApplicationEncryptionKeyExchangeType_BLE_CHALLENGE_NONCE_RESP,
};

#ifdef WITH_LOGGING
/**
 * Convert ApplicationEncryptionKeyExchangeType to a string.
 * @return "?" if unknown.
 */
const char *ApplicationEncryptionKeyExchangeType_toString(enum ApplicationEncryptionKeyExchangeType value);
#endif // WITH_LOGGING


/**
 * Main structure for module: {@link PacketContent.h}.
 */
struct PacketContent
{
	int8_t contentType;
};

/** Maximum serialized length for RawRead. */
#define RawRead_MAX_SERIALIZED_LEN 36

/** Discriminator which identifies this subtype (RawRead) in a union. */
#define RawRead_DISCRIMINATOR 1

/**
 * Main structure for module: {@link RawRead.h}.
 */
struct RawRead
{
	struct PacketContent base;
	int8_t readerIndex;
	int8_t trimBitsInLastByte;
	int8_t numBytes;
	int8_t bytes[32];
};

/** Maximum serialized length for RawKey. */
#define RawKey_MAX_SERIALIZED_LEN 3

/** Discriminator which identifies this subtype (RawKey) in a union. */
#define RawKey_DISCRIMINATOR 19

/**
 * Main structure for module: {@link RawKey.h}.
 */
struct RawKey
{
	struct PacketContent base;
	int8_t keypadIndex;
	int8_t key;
};

/** Maximum serialized length for DigitalRead. */
#define DigitalRead_MAX_SERIALIZED_LEN 4

/** Discriminator which identifies this subtype (DigitalRead) in a union. */
#define DigitalRead_DISCRIMINATOR 4

/**
 * Main structure for module: {@link DigitalRead.h}.
 */
struct DigitalRead
{
	struct PacketContent base;
	int8_t inputIndex;
	bool value:1;
	bool active:1;
};

/** Maximum serialized length for TemperatureRead. */
#define TemperatureRead_MAX_SERIALIZED_LEN 18

/** Discriminator which identifies this subtype (TemperatureRead) in a union. */
#define TemperatureRead_DISCRIMINATOR 5

/**
 * Main structure for module: {@link TemperatureRead.h}.
 */
struct TemperatureRead
{
	struct PacketContent base;
	int8_t deviceIndex;
	int8_t deviceAddress[8];
	float tempC;
	float humidity;
};

/** Maximum serialized length for BoardInfo. */
#define BoardInfo_MAX_SERIALIZED_LEN 34

/** Discriminator which identifies this subtype (BoardInfo) in a union. */
#define BoardInfo_DISCRIMINATOR 7

/**
 * Main structure for module: {@link BoardInfo.h}.
 */
struct BoardInfo
{
	struct PacketContent base;
	int8_t protocolVersionMajor;
	int8_t protocolVersionMinor;
	int16_t model;
	int8_t firmwareVersionMajor;
	int8_t firmwareVersionMinor;
	bool encryptionEnabled:1;
	int64_t serialNumber;
	int8_t spare;
	int16_t webServerPort;
	int16_t protocolServerPort;
	bool mega:1;
	bool enableSD:1;
	bool enableEthernet:1;
	bool enableSystemLED:1;
	bool enableDigitalIn:1;
	bool enableDigitalOut:1;
	bool enableAnalogIn:1;
	bool enableData01:1;
	bool enableRfid:1;
	bool enableLCD:1;
	bool enableKeypad:1;
	bool enableDallasTemperature:1;
	bool enableSHTXTemperature:1;
};

/** Maximum serialized length for AnalogRead. */
#define AnalogRead_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (AnalogRead) in a union. */
#define AnalogRead_DISCRIMINATOR 9

/**
 * Main structure for module: {@link AnalogRead.h}.
 */
struct AnalogRead
{
	struct PacketContent base;
	int8_t inputIndex;
	int16_t value;
	int8_t active;
};

/** Maximum serialized length for FileContents. */
#define FileContents_MAX_SERIALIZED_LEN 1034

/** Discriminator which identifies this subtype (FileContents) in a union. */
#define FileContents_DISCRIMINATOR 12

#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
/**
 * Main structure for module: {@link FileContents.h}.
 */
struct FileContents
{
	struct PacketContent base;
	int8_t fileId;
	int32_t offset;
	bool eof:1;
	int8_t exception;
	int16_t numBytes;
	int8_t bytes[1024];
};
#endif

/** Maximum serialized length for BoardStatus. */
#define BoardStatus_MAX_SERIALIZED_LEN 55

/** Discriminator which identifies this subtype (BoardStatus) in a union. */
#define BoardStatus_DISCRIMINATOR 14

/**
 * Main structure for module: {@link BoardStatus.h}.
 */
struct BoardStatus
{
	struct PacketContent base;
	int32_t millis;
	int16_t memoryAvailable;
	bool helloReceived:1;
	int8_t protocolConnectionType;
	int32_t numSerialProtocolPacketsRead;
	int32_t numSerialProtocolPacketsWritten;
	int32_t numNetworkProtocolPacketsRead;
	int32_t numNetworkProtocolPacketsWritten;
	int32_t numSerialProtocolInputErrors;
	int16_t lastSerialProtocolInputError;
	int32_t numSerialProtocolOutputErrors;
	int16_t lastSerialProtocolOutputError;
	int32_t numNetworkProtocolInputErrors;
	int16_t lastNetworkProtocolInputError;
	int32_t numNetworkProtocolOutputErrors;
	int16_t lastNetworkProtocolOutputError;
	int32_t numSdErrors;
	int16_t lastSdError;
};

/** Maximum serialized length for Pong. */
#define Pong_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (Pong) in a union. */
#define Pong_DISCRIMINATOR 16

/**
 * Main structure for module: {@link Pong.h}.
 */
struct Pong
{
	struct PacketContent base;
};

/** Maximum serialized length for Ack. */
#define Ack_MAX_SERIALIZED_LEN 3

/** Discriminator which identifies this subtype (Ack) in a union. */
#define Ack_DISCRIMINATOR 21

/**
 * Main structure for module: {@link Ack.h}.
 */
struct Ack
{
	struct PacketContent base;
	int8_t spare;
	int8_t responseToSeqno;
};

/** Maximum serialized length for Nak. */
#define Nak_MAX_SERIALIZED_LEN 4

/** Discriminator which identifies this subtype (Nak) in a union. */
#define Nak_DISCRIMINATOR 22

/**
 * Main structure for module: {@link Nak.h}.
 */
struct Nak
{
	struct PacketContent base;
	int8_t spare;
	int8_t responseToSeqno;
	int8_t reason;
};

/** Maximum serialized length for RawKeys. */
#define RawKeys_MAX_SERIALIZED_LEN 35

/** Discriminator which identifies this subtype (RawKeys) in a union. */
#define RawKeys_DISCRIMINATOR 24

/**
 * Main structure for module: {@link RawKeys.h}.
 */
struct RawKeys
{
	struct PacketContent base;
	int8_t keypadIndex;
	int8_t numKeys;
	int8_t keys[32];
};

/** Maximum serialized length for UserIdRead. */
#define UserIdRead_MAX_SERIALIZED_LEN 35

/** Discriminator which identifies this subtype (UserIdRead) in a union. */
#define UserIdRead_DISCRIMINATOR 25

/**
 * Main structure for module: {@link UserIdRead.h}.
 */
struct UserIdRead
{
	struct PacketContent base;
	int8_t readerIndex;
	int8_t numUserIdChars;
	int8_t userIdChars[32];
};

/** Maximum serialized length for ReaderStatus. */
#define ReaderStatus_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (ReaderStatus) in a union. */
#define ReaderStatus_DISCRIMINATOR 28

/**
 * Main structure for module: {@link ReaderStatus.h}.
 */
struct ReaderStatus
{
	struct PacketContent base;
	int8_t readerIndex;
	bool offline:1;
	bool tamper:1;
	bool power:1;
};

/** Maximum serialized length for FileAvailable. */
#define FileAvailable_MAX_SERIALIZED_LEN 6

/** Discriminator which identifies this subtype (FileAvailable) in a union. */
#define FileAvailable_DISCRIMINATOR 33

/**
 * Main structure for module: {@link FileAvailable.h}.
 */
struct FileAvailable
{
	struct PacketContent base;
	int8_t fileId;
	int32_t fileLength;
};

/** Maximum serialized length for ProcessFile. */
#define ProcessFile_MAX_SERIALIZED_LEN 2

/** Discriminator which identifies this subtype (ProcessFile) in a union. */
#define ProcessFile_DISCRIMINATOR 34

/**
 * Main structure for module: {@link ProcessFile.h}.
 */
struct ProcessFile
{
	struct PacketContent base;
	int8_t fileId;
};

/** Maximum serialized length for Ping. */
#define Ping_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (Ping) in a union. */
#define Ping_DISCRIMINATOR 15

/**
 * Main structure for module: {@link Ping.h}.
 */
struct Ping
{
	struct PacketContent base;
};

/** Maximum serialized length for BoardStatusQuery. */
#define BoardStatusQuery_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (BoardStatusQuery) in a union. */
#define BoardStatusQuery_DISCRIMINATOR 13

/**
 * Main structure for module: {@link BoardStatusQuery.h}.
 */
struct BoardStatusQuery
{
	struct PacketContent base;
};

/** Maximum serialized length for Config. */
#define Config_MAX_SERIALIZED_LEN 18

/** Discriminator which identifies this subtype (Config) in a union. */
#define Config_DISCRIMINATOR 10

/**
 * Main structure for module: {@link Config.h}.
 */
struct Config
{
	struct PacketContent base;
	int8_t enableSystemLED;
	int32_t enableDigitalIn;
	int32_t enableDigitalOut;
	int16_t enableAnalogIn;
	int8_t enableData01;
	int8_t enableRfid;
	int8_t enableLCD;
	int8_t enableDallasTemperature;
	int8_t enableSHTXTemperature;
	int8_t enableKeypad;
};

/** Maximum serialized length for FileQuery. */
#define FileQuery_MAX_SERIALIZED_LEN 6

/** Discriminator which identifies this subtype (FileQuery) in a union. */
#define FileQuery_DISCRIMINATOR 11

/**
 * Main structure for module: {@link FileQuery.h}.
 */
struct FileQuery
{
	struct PacketContent base;
	int8_t fileId;
	int32_t offset;
};

/** Maximum serialized length for Hello. */
#define Hello_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (Hello) in a union. */
#define Hello_DISCRIMINATOR 8

/**
 * Main structure for module: {@link Hello.h}.
 */
struct Hello
{
	struct PacketContent base;
	int8_t protocolVersionMajor;
	int8_t protocolVersionMinor;
	bool multidrop:1;
	bool encryptionEnabled:1;
};

/** Maximum serialized length for SerialWrite. */
#define SerialWrite_MAX_SERIALIZED_LEN 51

/** Discriminator which identifies this subtype (SerialWrite) in a union. */
#define SerialWrite_DISCRIMINATOR 6

/**
 * Main structure for module: {@link SerialWrite.h}.
 */
struct SerialWrite
{
	struct PacketContent base;
	int8_t portIndex;
	int8_t numBytes;
	int8_t bytes[48];
};

/** Maximum serialized length for DisplayWrite. */
#define DisplayWrite_MAX_SERIALIZED_LEN 51

/** Discriminator which identifies this subtype (DisplayWrite) in a union. */
#define DisplayWrite_DISCRIMINATOR 20

/**
 * Main structure for module: {@link DisplayWrite.h}.
 */
struct DisplayWrite
{
	struct PacketContent base;
	int8_t portIndex;
	int8_t numBytes;
	int8_t bytes[48];
};

/** Maximum serialized length for AnalogInConfig. */
#define AnalogInConfig_MAX_SERIALIZED_LEN 19

/** Discriminator which identifies this subtype (AnalogInConfig) in a union. */
#define AnalogInConfig_DISCRIMINATOR 17

/**
 * Main structure for module: {@link AnalogInConfig.h}.
 */
struct AnalogInConfig
{
	struct PacketContent base;
	int8_t inputIndex;
	bool enabled:1;
	bool invert:1;
	bool reportAllData:1;
	int16_t debounce;
	int16_t loStart;
	int16_t loStop;
	int16_t hiStart;
	int16_t hiStop;
	int16_t tolerance;
	int16_t pollInterval;
};

/** Maximum serialized length for DigitalInConfig. */
#define DigitalInConfig_MAX_SERIALIZED_LEN 8

/** Discriminator which identifies this subtype (DigitalInConfig) in a union. */
#define DigitalInConfig_DISCRIMINATOR 18

/**
 * Main structure for module: {@link DigitalInConfig.h}.
 */
struct DigitalInConfig
{
	struct PacketContent base;
	int8_t inputIndex;
	bool enabled:1;
	bool invert:1;
	bool reportAllData:1;
	bool enablePullup:1;
	int16_t debounce;
};

/** Maximum serialized length for DigitalWrite. */
#define DigitalWrite_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (DigitalWrite) in a union. */
#define DigitalWrite_DISCRIMINATOR 3

/**
 * Main structure for module: {@link DigitalWrite.h}.
 */
struct DigitalWrite
{
	struct PacketContent base;
	int8_t outputIndex;
	int8_t value;
	int16_t duration;
};

/** Maximum serialized length for RawWrite. */
#define RawWrite_MAX_SERIALIZED_LEN 36

/** Discriminator which identifies this subtype (RawWrite) in a union. */
#define RawWrite_DISCRIMINATOR 2

/**
 * Main structure for module: {@link RawWrite.h}.
 */
struct RawWrite
{
	struct PacketContent base;
	int8_t readerIndex;
	int8_t trimBitsInLastByte;
	int8_t numBytes;
	int8_t bytes[32];
};

/** Maximum serialized length for ReaderState. */
#define ReaderState_MAX_SERIALIZED_LEN 51

/** Discriminator which identifies this subtype (ReaderState) in a union. */
#define ReaderState_DISCRIMINATOR 26

/**
 * Main structure for module: {@link ReaderState.h}.
 */
struct ReaderState
{
	struct PacketContent base;
	int8_t readerIndex;
	int8_t doorModeType;
	int8_t stateType;
	int32_t stateTypeSeqNo;
	int8_t numUserIdChars;
	int8_t userIdChars[32];
	bool credUnidPresent:1;
	int32_t credUnid;
	bool credHolderUnidPresent:1;
	int32_t credHolderUnid;
};

/** Maximum serialized length for Poll. */
#define Poll_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (Poll) in a union. */
#define Poll_DISCRIMINATOR 29

/**
 * Main structure for module: {@link Poll.h}.
 */
struct Poll
{
	struct PacketContent base;
};

/** Maximum serialized length for HostInfo. */
#define HostInfo_MAX_SERIALIZED_LEN 13

/** Discriminator which identifies this subtype (HostInfo) in a union. */
#define HostInfo_DISCRIMINATOR 31

/**
 * Main structure for module: {@link HostInfo.h}.
 */
struct HostInfo
{
	struct PacketContent base;
	uint16_t model;
	uint8_t firmwareVersionMajor;
	uint8_t firmwareVersionMinor;
	uint64_t serialNumber;
};

/** Maximum serialized length for HostStatus. */
#define HostStatus_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (HostStatus) in a union. */
#define HostStatus_DISCRIMINATOR 32

/**
 * Main structure for module: {@link HostStatus.h}.
 */
struct HostStatus
{
	struct PacketContent base;
	enum HostPairingState pairingState;
	bool tamper:1;
	bool lowBattery:1;
	bool syncRequested:1;
};

#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
/** Maximum serialized length for ProtocolPassthru. */
#define ProtocolPassthru_MAX_SERIALIZED_LEN 1030
#else
// excluded: EncryptedContent
// excluded: ProtocolPassthru
// excluded: FileContents
// excluded: ProtocolPassthruId
/** Maximum serialized length for ProtocolPassthru. */
#define ProtocolPassthru_MAX_SERIALIZED_LEN 1029
#endif

/** Discriminator which identifies this subtype (ProtocolPassthru) in a union. */
#define ProtocolPassthru_DISCRIMINATOR 30

#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
/**
 * Main structure for module: {@link ProtocolPassthru.h}.
 */
struct ProtocolPassthru
{
	struct PacketContent base;
	enum ProtocolPassthruId protocolId;
	int8_t numFragments;
	int8_t fragmentIndex;
	int16_t numBytes;
	int8_t bytes[1024];
};
#endif

/** Maximum serialized length for EncryptedContent. */
#define EncryptedContent_MAX_SERIALIZED_LEN 1027

/** Discriminator which identifies this subtype (EncryptedContent) in a union. */
#define EncryptedContent_DISCRIMINATOR 35

#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
/**
 * Main structure for module: {@link EncryptedContent.h}.
 */
struct EncryptedContent
{
	struct PacketContent base;
	int16_t numBytes;
	int8_t bytes[1024];
};
#endif

/** Maximum serialized length for EncryptionKeyExchange. */
#define EncryptionKeyExchange_MAX_SERIALIZED_LEN 19

/** Discriminator which identifies this subtype (EncryptionKeyExchange) in a union. */
#define EncryptionKeyExchange_DISCRIMINATOR 36

/**
 * Main structure for module: {@link EncryptionKeyExchange.h}.
 */
struct EncryptionKeyExchange
{
	struct PacketContent base;
	enum EncryptionKeyExchangeType type;
	int8_t numBytes;
	int8_t bytes[16];
};

/** Maximum serialized length for ApplicationEncryptionKeyExchange. */
#define ApplicationEncryptionKeyExchange_MAX_SERIALIZED_LEN 36

/** Discriminator which identifies this subtype (ApplicationEncryptionKeyExchange) in a union. */
#define ApplicationEncryptionKeyExchange_DISCRIMINATOR 37

/**
 * Main structure for module: {@link ApplicationEncryptionKeyExchange.h}.
 */
struct ApplicationEncryptionKeyExchange
{
	struct PacketContent base;
	enum ApplicationEncryptionKeyExchangeType type;
	int8_t numBytes;
	int8_t bytes[33];
};

#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
/** Maximum serialized length for Packet. */
#define Packet_MAX_SERIALIZED_LEN 1041
#else
// excluded: EncryptedContent
// excluded: ProtocolPassthru
// excluded: FileContents
// excluded: ProtocolPassthruId
/** Maximum serialized length for Packet. */
#define Packet_MAX_SERIALIZED_LEN 62
#endif

static const int8_t Packet_headerByte = 127;
/**
 * Main structure for module: {@link Packet.h}.
 */
struct Packet
{
	int16_t bytecount;
	int8_t address;
	int8_t seqno;
	union
	{
		struct RawRead uRawRead;
		struct RawWrite uRawWrite;
		struct DigitalWrite uDigitalWrite;
		struct DigitalRead uDigitalRead;
		struct TemperatureRead uTemperatureRead;
		struct SerialWrite uSerialWrite;
		struct BoardInfo uBoardInfo;
		struct Hello uHello;
		struct AnalogRead uAnalogRead;
		struct Config uConfig;
		struct FileQuery uFileQuery;
#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
		struct FileContents uFileContents;
#endif
		struct BoardStatusQuery uBoardStatusQuery;
		struct BoardStatus uBoardStatus;
		struct Ping uPing;
		struct Pong uPong;
		struct AnalogInConfig uAnalogInConfig;
		struct DigitalInConfig uDigitalInConfig;
		struct RawKey uRawKey;
		struct DisplayWrite uDisplayWrite;
		struct Ack uAck;
		struct Nak uNak;
		struct RawKeys uRawKeys;
		struct UserIdRead uUserIdRead;
		struct ReaderState uReaderState;
		struct ReaderStatus uReaderStatus;
		struct Poll uPoll;
#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
		struct ProtocolPassthru uProtocolPassthru;
#endif
		struct HostInfo uHostInfo;
		struct HostStatus uHostStatus;
		struct FileAvailable uFileAvailable;
		struct ProcessFile uProcessFile;
#ifdef WITH_LARGE_Z9IO_PACKET_CONTENT
		struct EncryptedContent uEncryptedContent;
#endif
		struct EncryptionKeyExchange uEncryptionKeyExchange;
		struct ApplicationEncryptionKeyExchange uApplicationEncryptionKeyExchange;
	} content;
	int16_t crc16;
};

#ifdef __cplusplus
}
#endif

