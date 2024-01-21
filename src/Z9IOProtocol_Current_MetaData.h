// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

// Z9IOProtocol_Current_MetaData.h

#include "Z9_Serialize.h"
#include "Z9LockIOProtocol_Current.h"
namespace z9{}
namespace z9::Z9LockIO
{
using meta::list;
using meta::int_;
{
// `variable` structure which can store a count + array of counted bytes

template <unsigned N, typename CNT_T = uint8_t, typename DATA_T = uint8_t>
struct variable
{
	using T = DATA_T;
	static constexpr auto MAX = N;

	auto& size () const = { return count; }
	constexpr auto& value() const = { return data;  }
	constexpr operator()() const T[]& const { return data; }

	bool set(CNT_T len, const T *value)
	{
		if (len > N)
			return false;           // TODO: error cases: should eventually throw

		auto bytes = len * sizeof(T);
		std::memcpy(data, value, bytes);
		count = len;
		return true;
	}

private:
	T     data[N];
	CNT_T count;
};

#define Z9_MEMBER(s_type, wire_size, name, m_type) \
	list<int_<wire_size>,                   \
		int_<offsetof(s_type, name)>,      \
		int_<sizeof(m_type)>,              \
		m_type,                            \
		Z9_STRING(#name)>

using Z9_TYPES = list<
	list<PacketContent, Z9_STRING("PacketContent"),
		list<
			Z9_MEMBER(PacketContent, 1, contentType, int8_t)
			// TODO: variable   |            |            | discriminator-specific content
		>
	>,

	list<RawRead, Z9_STRING("RawRead"),
		list<
			Z9_MEMBER(RawRead, 1, readerIndex, int8_t),
			Z9_MEMBER(RawRead, 1, trimBitsInLastByte, int8_t),
			Z9_MEMBER(RawRead, 33, bytes, variableArray<32, int8_t, int8_t>)
		>
	>,

	list<RawKey, Z9_STRING("RawKey"),
		list<
			Z9_MEMBER(RawKey, 1, keypadIndex, int8_t),
			Z9_MEMBER(RawKey, 1, key, int8_t)
		>
	>,

	list<DigitalRead, Z9_STRING("DigitalRead"),
		list<
			Z9_MEMBER(DigitalRead, 1, inputIndex, int8_t),
			Z9_MEMBER(DigitalRead, 1, value, bool),
			Z9_MEMBER(DigitalRead, 1, active, bool)
		>
	>,

	list<TemperatureRead, Z9_STRING("TemperatureRead"),
		list<
			Z9_MEMBER(TemperatureRead, 1, deviceIndex, int8_t)
			// TODO: 8 elements (8 bytes) | `deviceAddress` | int8_t     | ,
			Z9_MEMBER(TemperatureRead, 4, tempC, float),
			Z9_MEMBER(TemperatureRead, 4, humidity, float)
		>
	>,

	list<BoardInfo, Z9_STRING("BoardInfo"),
		list<
			Z9_MEMBER(BoardInfo, 1, protocolVersionMajor, int8_t),
			Z9_MEMBER(BoardInfo, 1, protocolVersionMinor, int8_t),
			Z9_MEMBER(BoardInfo, 2, model, int16_t),
			Z9_MEMBER(BoardInfo, 1, firmwareVersionMajor, int8_t),
			Z9_MEMBER(BoardInfo, 1, firmwareVersionMinor, int8_t),
			Z9_MEMBER(BoardInfo, 1, encryptionEnabled, bool),
			Z9_MEMBER(BoardInfo, 8, serialNumber, int64_t),
			Z9_MEMBER(BoardInfo, 1, spare, int8_t),
			Z9_MEMBER(BoardInfo, 2, webServerPort, int16_t),
			Z9_MEMBER(BoardInfo, 2, protocolServerPort, int16_t),
			Z9_MEMBER(BoardInfo, 1, mega, bool),
			Z9_MEMBER(BoardInfo, 1, enableSD, bool),
			Z9_MEMBER(BoardInfo, 1, enableEthernet, bool),
			Z9_MEMBER(BoardInfo, 1, enableSystemLED, bool),
			Z9_MEMBER(BoardInfo, 1, enableDigitalIn, bool),
			Z9_MEMBER(BoardInfo, 1, enableDigitalOut, bool),
			Z9_MEMBER(BoardInfo, 1, enableAnalogIn, bool),
			Z9_MEMBER(BoardInfo, 1, enableData01, bool),
			Z9_MEMBER(BoardInfo, 1, enableRfid, bool),
			Z9_MEMBER(BoardInfo, 1, enableLCD, bool),
			Z9_MEMBER(BoardInfo, 1, enableKeypad, bool),
			Z9_MEMBER(BoardInfo, 1, enableDallasTemperature, bool),
			Z9_MEMBER(BoardInfo, 1, enableSHTXTemperature, bool)
		>
	>,

	list<AnalogRead, Z9_STRING("AnalogRead"),
		list<
			Z9_MEMBER(AnalogRead, 1, inputIndex, int8_t),
			Z9_MEMBER(AnalogRead, 2, value, int16_t),
			Z9_MEMBER(AnalogRead, 1, active, int8_t)
		>
	>,

	list<FileContents, Z9_STRING("FileContents"),
		list<
			Z9_MEMBER(FileContents, 1, fileId, int8_t),
			Z9_MEMBER(FileContents, 4, offset, int32_t),
			Z9_MEMBER(FileContents, 1, eof, bool),
			Z9_MEMBER(FileContents, 1, exception, int8_t),
			Z9_MEMBER(FileContents, 1026, bytes, variableArray<1024, int16_t, int8_t>)
		>
	>,

	list<BoardStatus, Z9_STRING("BoardStatus"),
		list<
			Z9_MEMBER(BoardStatus, 4, millis, int32_t),
			Z9_MEMBER(BoardStatus, 2, memoryAvailable, int16_t),
			Z9_MEMBER(BoardStatus, 1, helloReceived, bool),
			Z9_MEMBER(BoardStatus, 1, protocolConnectionType, int8_t),
			Z9_MEMBER(BoardStatus, 4, numSerialProtocolPacketsRead, int32_t),
			Z9_MEMBER(BoardStatus, 4, numSerialProtocolPacketsWritten, int32_t),
			Z9_MEMBER(BoardStatus, 4, numNetworkProtocolPacketsRead, int32_t),
			Z9_MEMBER(BoardStatus, 4, numNetworkProtocolPacketsWritten, int32_t),
			Z9_MEMBER(BoardStatus, 4, numSerialProtocolInputErrors, int32_t),
			Z9_MEMBER(BoardStatus, 2, lastSerialProtocolInputError, int16_t),
			Z9_MEMBER(BoardStatus, 4, numSerialProtocolOutputErrors, int32_t),
			Z9_MEMBER(BoardStatus, 2, lastSerialProtocolOutputError, int16_t),
			Z9_MEMBER(BoardStatus, 4, numNetworkProtocolInputErrors, int32_t),
			Z9_MEMBER(BoardStatus, 2, lastNetworkProtocolInputError, int16_t),
			Z9_MEMBER(BoardStatus, 4, numNetworkProtocolOutputErrors, int32_t),
			Z9_MEMBER(BoardStatus, 2, lastNetworkProtocolOutputError, int16_t),
			Z9_MEMBER(BoardStatus, 4, numSdErrors, int32_t),
			Z9_MEMBER(BoardStatus, 2, lastSdError, int16_t)
		>
	>,

	list<Pong, Z9_STRING("Pong"),
		list<
		>
	>,

	list<Ack, Z9_STRING("Ack"),
		list<
			Z9_MEMBER(Ack, 1, spare, int8_t),
			Z9_MEMBER(Ack, 1, responseToSeqno, int8_t)
		>
	>,

	list<Nak, Z9_STRING("Nak"),
		list<
			Z9_MEMBER(Nak, 1, spare, int8_t),
			Z9_MEMBER(Nak, 1, responseToSeqno, int8_t),
			Z9_MEMBER(Nak, 1, reason, int8_t)
		>
	>,

	list<RawKeys, Z9_STRING("RawKeys"),
		list<
			Z9_MEMBER(RawKeys, 1, keypadIndex, int8_t),
			Z9_MEMBER(RawKeys, 33, keys, variableArray<32, int8_t, int8_t>)
		>
	>,

	list<UserIdRead, Z9_STRING("UserIdRead"),
		list<
			Z9_MEMBER(UserIdRead, 1, readerIndex, int8_t),
			Z9_MEMBER(UserIdRead, 33, userIdChars, variableArray<32, int8_t, int8_t>)
		>
	>,

	list<ReaderStatus, Z9_STRING("ReaderStatus"),
		list<
			Z9_MEMBER(ReaderStatus, 1, readerIndex, int8_t),
			Z9_MEMBER(ReaderStatus, 1, offline, bool),
			Z9_MEMBER(ReaderStatus, 1, tamper, bool),
			Z9_MEMBER(ReaderStatus, 1, power, bool)
		>
	>,

	list<FileAvailable, Z9_STRING("FileAvailable"),
		list<
			Z9_MEMBER(FileAvailable, 1, fileId, int8_t),
			Z9_MEMBER(FileAvailable, 4, fileLength, int32_t)
		>
	>,

	list<ProcessFile, Z9_STRING("ProcessFile"),
		list<
			Z9_MEMBER(ProcessFile, 1, fileId, int8_t)
		>
	>,

	list<Ping, Z9_STRING("Ping"),
		list<
		>
	>,

	list<BoardStatusQuery, Z9_STRING("BoardStatusQuery"),
		list<
		>
	>,

	list<Config, Z9_STRING("Config"),
		list<
			Z9_MEMBER(Config, 1, enableSystemLED, int8_t),
			Z9_MEMBER(Config, 4, enableDigitalIn, int32_t),
			Z9_MEMBER(Config, 4, enableDigitalOut, int32_t),
			Z9_MEMBER(Config, 2, enableAnalogIn, int16_t),
			Z9_MEMBER(Config, 1, enableData01, int8_t),
			Z9_MEMBER(Config, 1, enableRfid, int8_t),
			Z9_MEMBER(Config, 1, enableLCD, int8_t),
			Z9_MEMBER(Config, 1, enableDallasTemperature, int8_t),
			Z9_MEMBER(Config, 1, enableSHTXTemperature, int8_t),
			Z9_MEMBER(Config, 1, enableKeypad, int8_t)
		>
	>,

	list<FileQuery, Z9_STRING("FileQuery"),
		list<
			Z9_MEMBER(FileQuery, 1, fileId, int8_t),
			Z9_MEMBER(FileQuery, 4, offset, int32_t)
		>
	>,

	list<Hello, Z9_STRING("Hello"),
		list<
			Z9_MEMBER(Hello, 1, protocolVersionMajor, int8_t),
			Z9_MEMBER(Hello, 1, protocolVersionMinor, int8_t),
			Z9_MEMBER(Hello, 1, multidrop, bool),
			Z9_MEMBER(Hello, 1, encryptionEnabled, bool)
		>
	>,

	list<SerialWrite, Z9_STRING("SerialWrite"),
		list<
			Z9_MEMBER(SerialWrite, 1, portIndex, int8_t),
			Z9_MEMBER(SerialWrite, 49, bytes, variableArray<48, int8_t, int8_t>)
		>
	>,

	list<DisplayWrite, Z9_STRING("DisplayWrite"),
		list<
			Z9_MEMBER(DisplayWrite, 1, portIndex, int8_t),
			Z9_MEMBER(DisplayWrite, 49, bytes, variableArray<48, int8_t, int8_t>)
		>
	>,

	list<AnalogInConfig, Z9_STRING("AnalogInConfig"),
		list<
			Z9_MEMBER(AnalogInConfig, 1, inputIndex, int8_t),
			Z9_MEMBER(AnalogInConfig, 1, enabled, bool),
			Z9_MEMBER(AnalogInConfig, 1, invert, bool),
			Z9_MEMBER(AnalogInConfig, 1, reportAllData, bool),
			Z9_MEMBER(AnalogInConfig, 2, debounce, int16_t),
			Z9_MEMBER(AnalogInConfig, 2, loStart, int16_t),
			Z9_MEMBER(AnalogInConfig, 2, loStop, int16_t),
			Z9_MEMBER(AnalogInConfig, 2, hiStart, int16_t),
			Z9_MEMBER(AnalogInConfig, 2, hiStop, int16_t),
			Z9_MEMBER(AnalogInConfig, 2, tolerance, int16_t),
			Z9_MEMBER(AnalogInConfig, 2, pollInterval, int16_t)
		>
	>,

	list<DigitalInConfig, Z9_STRING("DigitalInConfig"),
		list<
			Z9_MEMBER(DigitalInConfig, 1, inputIndex, int8_t),
			Z9_MEMBER(DigitalInConfig, 1, enabled, bool),
			Z9_MEMBER(DigitalInConfig, 1, invert, bool),
			Z9_MEMBER(DigitalInConfig, 1, reportAllData, bool),
			Z9_MEMBER(DigitalInConfig, 1, enablePullup, bool),
			Z9_MEMBER(DigitalInConfig, 2, debounce, int16_t)
		>
	>,

	list<DigitalWrite, Z9_STRING("DigitalWrite"),
		list<
			Z9_MEMBER(DigitalWrite, 1, outputIndex, int8_t),
			Z9_MEMBER(DigitalWrite, 1, value, int8_t),
			Z9_MEMBER(DigitalWrite, 2, duration, int16_t)
		>
	>,

	list<RawWrite, Z9_STRING("RawWrite"),
		list<
			Z9_MEMBER(RawWrite, 1, readerIndex, int8_t),
			Z9_MEMBER(RawWrite, 1, trimBitsInLastByte, int8_t),
			Z9_MEMBER(RawWrite, 33, bytes, variableArray<32, int8_t, int8_t>)
		>
	>,

	list<ReaderState, Z9_STRING("ReaderState"),
		list<
			Z9_MEMBER(ReaderState, 1, readerIndex, int8_t),
			Z9_MEMBER(ReaderState, 1, doorModeType, int8_t),
			Z9_MEMBER(ReaderState, 1, stateType, int8_t),
			Z9_MEMBER(ReaderState, 4, stateTypeSeqNo, int32_t),
			Z9_MEMBER(ReaderState, 33, userIdChars, variableArray<32, int8_t, int8_t>),
			Z9_MEMBER(ReaderState, 1, credUnidPresent, bool),
			Z9_MEMBER(ReaderState, 4, credUnid, int32_t),
			Z9_MEMBER(ReaderState, 1, credHolderUnidPresent, bool),
			Z9_MEMBER(ReaderState, 4, credHolderUnid, int32_t)
		>
	>,

	list<Poll, Z9_STRING("Poll"),
		list<
		>
	>,

	list<HostInfo, Z9_STRING("HostInfo"),
		list<
			Z9_MEMBER(HostInfo, 2, model, uint16_t),
			Z9_MEMBER(HostInfo, 1, firmwareVersionMajor, uint8_t),
			Z9_MEMBER(HostInfo, 1, firmwareVersionMinor, uint8_t),
			Z9_MEMBER(HostInfo, 8, serialNumber, uint64_t)
		>
	>,

	list<HostStatus, Z9_STRING("HostStatus"),
		list<
			Z9_MEMBER(HostStatus, 1, pairingState, HostPairingState),
			Z9_MEMBER(HostStatus, 1, tamper, bool),
			Z9_MEMBER(HostStatus, 1, lowBattery, bool),
			Z9_MEMBER(HostStatus, 1, syncRequested, bool)
		>
	>,

	list<EncryptedContent, Z9_STRING("EncryptedContent"),
		list<
			Z9_MEMBER(EncryptedContent, 1026, bytes, variableArray<1024, int16_t, int8_t>)
		>
	>,

	list<EncryptionKeyExchange, Z9_STRING("EncryptionKeyExchange"),
		list<
			Z9_MEMBER(EncryptionKeyExchange, 1, type, EncryptionKeyExchangeType),
			Z9_MEMBER(EncryptionKeyExchange, 17, bytes, variableArray<16, int8_t, int8_t>)
		>
	>,

	list<ApplicationEncryptionKeyExchange, Z9_STRING("ApplicationEncryptionKeyExchange"),
		list<
			Z9_MEMBER(ApplicationEncryptionKeyExchange, 1, type, ApplicationEncryptionKeyExchangeType),
			Z9_MEMBER(ApplicationEncryptionKeyExchange, 66, bytes, variableArray<65, int8_t, int8_t>)
		>
	>,

	list<Packet, Z9_STRING("Packet"),
		list<
			Z9_MEMBER(Packet, 1, headerByte, int8_t),
			Z9_MEMBER(Packet, 2, bytecount, int16_t),
			Z9_MEMBER(Packet, 1, address, int8_t),
			Z9_MEMBER(Packet, 1, seqno, int8_t)
			// TODO: 1 to 1034 bytes | `content`  | PacketContent | discriminator-based structure,
			Z9_MEMBER(Packet, 2, crc16, int16_t)
		>
	>

