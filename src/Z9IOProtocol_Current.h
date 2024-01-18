// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.


#pragma once

#include <stdint.h>


/**
 * Enum: {@link HostPairingState.h}.
 */
enum HostPairingState
{
	HostPairingState_CONSTRUCTION,
	HostPairingState_PAIRING,
	HostPairingState_PAIRED,
};



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



/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.PacketContent
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class PacketContent
{
public:
	int8_t contentType;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.RawRead
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class RawRead : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 36;
	static const int8_t DISCRIMINATOR = 1;
	int8_t readerIndex;
	int8_t trimBitsInLastByte;
	int8_t numBytes;
	int8_t bytes[32];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.RawKey
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class RawKey : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	static const int8_t DISCRIMINATOR = 19;
	int8_t keypadIndex;
	int8_t key;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.DigitalRead
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class DigitalRead : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 4;
	static const int8_t DISCRIMINATOR = 4;
	int8_t inputIndex;
	bool value;
	bool active;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.TemperatureRead
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class TemperatureRead : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 18;
	static const int8_t DISCRIMINATOR = 5;
	int8_t deviceIndex;
	int8_t deviceAddress[8];
	float tempC;
	float humidity;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.BoardInfo
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class BoardInfo : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 34;
	static const int8_t DISCRIMINATOR = 7;
	int8_t protocolVersionMajor;
	int8_t protocolVersionMinor;
	int16_t model;
	int8_t firmwareVersionMajor;
	int8_t firmwareVersionMinor;
	bool encryptionEnabled;
	int64_t serialNumber;
	int8_t spare;
	int16_t webServerPort;
	int16_t protocolServerPort;
	bool mega;
	bool enableSD;
	bool enableEthernet;
	bool enableSystemLED;
	bool enableDigitalIn;
	bool enableDigitalOut;
	bool enableAnalogIn;
	bool enableData01;
	bool enableRfid;
	bool enableLCD;
	bool enableKeypad;
	bool enableDallasTemperature;
	bool enableSHTXTemperature;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.AnalogRead
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class AnalogRead : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 9;
	int8_t inputIndex;
	int16_t value;
	int8_t active;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.FileContents
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class FileContents : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1034;
	static const int8_t DISCRIMINATOR = 12;
	int8_t fileId;
	int32_t offset;
	bool eof;
	int8_t exception;
	int16_t numBytes;
	int8_t bytes[1024];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.BoardStatus
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class BoardStatus : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 55;
	static const int8_t DISCRIMINATOR = 14;
	int32_t millis;
	int16_t memoryAvailable;
	bool helloReceived;
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


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.Pong
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Pong : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 16;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.Ack
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Ack : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	static const int8_t DISCRIMINATOR = 21;
	int8_t spare;
	int8_t responseToSeqno;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.Nak
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Nak : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 4;
	static const int8_t DISCRIMINATOR = 22;
	int8_t spare;
	int8_t responseToSeqno;
	int8_t reason;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.RawKeys
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class RawKeys : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 35;
	static const int8_t DISCRIMINATOR = 24;
	int8_t keypadIndex;
	int8_t numKeys;
	int8_t keys[32];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.UserIdRead
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class UserIdRead : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 35;
	static const int8_t DISCRIMINATOR = 25;
	int8_t readerIndex;
	int8_t numUserIdChars;
	int8_t userIdChars[32];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.ReaderStatus
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class ReaderStatus : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 28;
	int8_t readerIndex;
	bool offline;
	bool tamper;
	bool power;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.FileAvailable
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class FileAvailable : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	static const int8_t DISCRIMINATOR = 33;
	int8_t fileId;
	int32_t fileLength;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.in.ProcessFile
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class ProcessFile : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 2;
	static const int8_t DISCRIMINATOR = 34;
	int8_t fileId;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.Ping
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Ping : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 15;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.BoardStatusQuery
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class BoardStatusQuery : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 13;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.Config
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Config : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 18;
	static const int8_t DISCRIMINATOR = 10;
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


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.FileQuery
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class FileQuery : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	static const int8_t DISCRIMINATOR = 11;
	int8_t fileId;
	int32_t offset;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.Hello
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Hello : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 8;
	int8_t protocolVersionMajor;
	int8_t protocolVersionMinor;
	bool multidrop;
	bool encryptionEnabled;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.SerialWrite
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class SerialWrite : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 51;
	static const int8_t DISCRIMINATOR = 6;
	int8_t portIndex;
	int8_t numBytes;
	int8_t bytes[48];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.DisplayWrite
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class DisplayWrite : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 51;
	static const int8_t DISCRIMINATOR = 20;
	int8_t portIndex;
	int8_t numBytes;
	int8_t bytes[48];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.AnalogInConfig
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class AnalogInConfig : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 19;
	static const int8_t DISCRIMINATOR = 17;
	int8_t inputIndex;
	bool enabled;
	bool invert;
	bool reportAllData;
	int16_t debounce;
	int16_t loStart;
	int16_t loStop;
	int16_t hiStart;
	int16_t hiStop;
	int16_t tolerance;
	int16_t pollInterval;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.DigitalInConfig
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class DigitalInConfig : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 8;
	static const int8_t DISCRIMINATOR = 18;
	int8_t inputIndex;
	bool enabled;
	bool invert;
	bool reportAllData;
	bool enablePullup;
	int16_t debounce;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.DigitalWrite
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class DigitalWrite : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 3;
	int8_t outputIndex;
	int8_t value;
	int16_t duration;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.RawWrite
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class RawWrite : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 36;
	static const int8_t DISCRIMINATOR = 2;
	int8_t readerIndex;
	int8_t trimBitsInLastByte;
	int8_t numBytes;
	int8_t bytes[32];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.ReaderState
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class ReaderState : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 51;
	static const int8_t DISCRIMINATOR = 26;
	int8_t readerIndex;
	int8_t doorModeType;
	int8_t stateType;
	int32_t stateTypeSeqNo;
	int8_t numUserIdChars;
	int8_t userIdChars[32];
	bool credUnidPresent;
	int32_t credUnid;
	bool credHolderUnidPresent;
	int32_t credHolderUnid;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.Poll
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Poll : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 29;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.HostInfo
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class HostInfo : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 13;
	static const int8_t DISCRIMINATOR = 31;
	uint16_t model;
	uint8_t firmwareVersionMajor;
	uint8_t firmwareVersionMinor;
	uint64_t serialNumber;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.out.HostStatus
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class HostStatus : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 32;
	HostPairingState pairingState;
	bool tamper;
	bool lowBattery;
	bool syncRequested;

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.inout.EncryptedContent
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class EncryptedContent : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1027;
	static const int8_t DISCRIMINATOR = 35;
	int16_t numBytes;
	int8_t bytes[1024];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.inout.EncryptionKeyExchange
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class EncryptionKeyExchange : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 19;
	static const int8_t DISCRIMINATOR = 36;
	EncryptionKeyExchangeType type;
	int8_t numBytes;
	int8_t bytes[16];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.inout.ApplicationEncryptionKeyExchange
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class ApplicationEncryptionKeyExchange : public PacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 68;
	static const int8_t DISCRIMINATOR = 37;
	ApplicationEncryptionKeyExchangeType type;
	int8_t numBytes;
	int8_t bytes[65];

};


/**
 * Auto-generated from Java class: z9.drivers.z9io.io.protocol.Packet
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class Packet
{
public:
	static const int MAX_SERIALIZED_LEN = 1041;
	static const int8_t headerByte = 127;
	int16_t bytecount;
	int8_t address;
	int8_t seqno;
	union
	{
		RawRead uRawRead;
		RawWrite uRawWrite;
		DigitalWrite uDigitalWrite;
		DigitalRead uDigitalRead;
		TemperatureRead uTemperatureRead;
		SerialWrite uSerialWrite;
		BoardInfo uBoardInfo;
		Hello uHello;
		AnalogRead uAnalogRead;
		Config uConfig;
		FileQuery uFileQuery;
		FileContents uFileContents;
		BoardStatusQuery uBoardStatusQuery;
		BoardStatus uBoardStatus;
		Ping uPing;
		Pong uPong;
		AnalogInConfig uAnalogInConfig;
		DigitalInConfig uDigitalInConfig;
		RawKey uRawKey;
		DisplayWrite uDisplayWrite;
		Ack uAck;
		Nak uNak;
		RawKeys uRawKeys;
		UserIdRead uUserIdRead;
		ReaderState uReaderState;
		ReaderStatus uReaderStatus;
		Poll uPoll;
		HostInfo uHostInfo;
		HostStatus uHostStatus;
		FileAvailable uFileAvailable;
		ProcessFile uProcessFile;
		EncryptedContent uEncryptedContent;
		EncryptionKeyExchange uEncryptionKeyExchange;
		ApplicationEncryptionKeyExchange uApplicationEncryptionKeyExchange;
	} content;
	int16_t crc16;

};

