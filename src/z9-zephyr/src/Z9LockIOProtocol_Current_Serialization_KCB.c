/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9LockIOProtocol_Current_Serialization_KCB.c
 * @author Z9 Security
 */

#include "Z9LockIOProtocol_Current_Serialization_KCB.h"
#include "BasicSerializer_KCB.h"
#include "BasicDeserializer_KCB.h"
#include "ProtocolError.h"


int LockCredTechnology_serialize_KCB(enum LockCredTechnology *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockCredTechnology_deserialize_KCB(enum LockCredTechnology *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockCredTechnology) charValue;
	return 0;
}

int LockMode_serialize_KCB(enum LockMode *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockMode_deserialize_KCB(enum LockMode *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockMode) charValue;
	return 0;
}

int LockEvtCode_serialize_KCB(enum LockEvtCode *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockEvtCode_deserialize_KCB(enum LockEvtCode *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockEvtCode) charValue;
	return 0;
}

int LockDevActionType_serialize_KCB(enum LockDevActionType *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockDevActionType_deserialize_KCB(enum LockDevActionType *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockDevActionType) charValue;
	return 0;
}

int LockFunction_serialize_KCB(enum LockFunction *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockFunction_deserialize_KCB(enum LockFunction *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockFunction) charValue;
	return 0;
}

int LockHostGrantFallbackMode_serialize_KCB(enum LockHostGrantFallbackMode *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockHostGrantFallbackMode_deserialize_KCB(enum LockHostGrantFallbackMode *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockHostGrantFallbackMode) charValue;
	return 0;
}

int LockHostGrantInitiationMode_serialize_KCB(enum LockHostGrantInitiationMode *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockHostGrantInitiationMode_deserialize_KCB(enum LockHostGrantInitiationMode *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockHostGrantInitiationMode) charValue;
	return 0;
}

int LockIdentificationType_serialize_KCB(enum LockIdentificationType *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockIdentificationType_deserialize_KCB(enum LockIdentificationType *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockIdentificationType) charValue;
	return 0;
}

int LockFileCategory_serialize_KCB(enum LockFileCategory *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockFileCategory_deserialize_KCB(enum LockFileCategory *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockFileCategory) charValue;
	return 0;
}

int LockFileIdentifier_serialize_KCB(enum LockFileIdentifier *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockFileIdentifier_deserialize_KCB(enum LockFileIdentifier *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockFileIdentifier) charValue;
	return 0;
}

int LockHostGrantReqType_serialize_KCB(enum LockHostGrantReqType *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockHostGrantReqType_deserialize_KCB(enum LockHostGrantReqType *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockHostGrantReqType) charValue;
	return 0;
}

int LockPolicyPriority_serialize_KCB(enum LockPolicyPriority *self, struct BasicSerializer_KCB *serializer)
{
	return BasicSerializer_KCB_writeChar(serializer, (int8_t) *self);
}

int LockPolicyPriority_deserialize_KCB(enum LockPolicyPriority *self, struct BasicDeserializer_KCB *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &charValue))) return result;
	*self = (enum LockPolicyPriority) charValue;
	return 0;
}

int LockDate_serialize_KCB(struct LockDate *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->year))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->day))) return result;

	return 0;
}

int LockDate_deserialize_KCB(struct LockDate *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	uint16_t _unpacked = self->year;
		if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &_unpacked))) return result;
		self->year = _unpacked;
	}
	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->day;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->day = _unpacked;
	}

	return 0;
}

int LockTimeOfDay_ToMinute_serialize_KCB(struct LockTimeOfDay_ToMinute *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->minute))) return result;

	return 0;
}

int LockTimeOfDay_ToMinute_deserialize_KCB(struct LockTimeOfDay_ToMinute *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}

	return 0;
}

int LockTimeOfDay_ToQuarterHour_serialize_KCB(struct LockTimeOfDay_ToQuarterHour *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->quarterHour))) return result;

	return 0;
}

int LockTimeOfDay_ToQuarterHour_deserialize_KCB(struct LockTimeOfDay_ToQuarterHour *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->quarterHour))) return result;

	return 0;
}

int LockTimeOfDay_ToSecond_serialize_KCB(struct LockTimeOfDay_ToSecond *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->minute))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->second))) return result;

	return 0;
}

int LockTimeOfDay_ToSecond_deserialize_KCB(struct LockTimeOfDay_ToSecond *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}
	{	uint8_t _unpacked = self->second;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->second = _unpacked;
	}

	return 0;
}

int LockDateTime_ToMinute_serialize_KCB(struct LockDateTime_ToMinute *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->year))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->day))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->minute))) return result;

	return 0;
}

int LockDateTime_ToMinute_deserialize_KCB(struct LockDateTime_ToMinute *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	uint16_t _unpacked = self->year;
		if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &_unpacked))) return result;
		self->year = _unpacked;
	}
	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->day;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->day = _unpacked;
	}
	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}

	return 0;
}

int LockDateTime_ToSecond_serialize_KCB(struct LockDateTime_ToSecond *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->year))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->day))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->minute))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->second))) return result;

	return 0;
}

int LockDateTime_ToSecond_deserialize_KCB(struct LockDateTime_ToSecond *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	uint16_t _unpacked = self->year;
		if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &_unpacked))) return result;
		self->year = _unpacked;
	}
	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->day;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->day = _unpacked;
	}
	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}
	{	uint8_t _unpacked = self->second;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->second = _unpacked;
	}

	return 0;
}

int LockEvtContent_serialize_KCB(struct LockEvtContent *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeChar(serializer, self->contentType))) return result;

	return 0;
}

int LockEvtContent_deserialize_KCB(struct LockEvtContent *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->contentType))) return result;

	return 0;
}

int LockEvtDelta_serialize_KCB(struct LockEvtDelta *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->suppress))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->priority))) return result;

	return 0;
}

int LockEvtDelta_deserialize_KCB(struct LockEvtDelta *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	bool _unpacked = self->suppress;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->suppress = _unpacked;
	}
	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}

	return 0;
}

int LockEvtModifiers_serialize_KCB(struct LockEvtModifiers *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->priority))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->hostGrant))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->mobileGrant))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->usedCard))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->usedPin))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->emergency))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->doublePresentation))) return result;

	return 0;
}

int LockEvtModifiers_deserialize_KCB(struct LockEvtModifiers *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}
	{	bool _unpacked = self->hostGrant;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->hostGrant = _unpacked;
	}
	{	bool _unpacked = self->mobileGrant;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->mobileGrant = _unpacked;
	}
	{	bool _unpacked = self->usedCard;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->usedCard = _unpacked;
	}
	{	bool _unpacked = self->usedPin;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->usedPin = _unpacked;
	}
	{	bool _unpacked = self->emergency;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->emergency = _unpacked;
	}
	{	bool _unpacked = self->doublePresentation;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->doublePresentation = _unpacked;
	}

	return 0;
}

int LockStatus_serialize_KCB(struct LockStatus *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockMode_serialize_KCB(&self->mode, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->tamper))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->batteryLow))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->batteryCritical))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->unlocked))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->open))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->forced))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->held))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->deadboltExtended))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->privacy))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->batteryLevel))) return result;

	return 0;
}

int LockStatus_deserialize_KCB(struct LockStatus *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockMode_deserialize_KCB(&self->mode, deserializer))) return result;
	{	bool _unpacked = self->tamper;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->tamper = _unpacked;
	}
	{	bool _unpacked = self->batteryLow;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->batteryLow = _unpacked;
	}
	{	bool _unpacked = self->batteryCritical;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->batteryCritical = _unpacked;
	}
	{	bool _unpacked = self->unlocked;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->unlocked = _unpacked;
	}
	{	bool _unpacked = self->open;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->open = _unpacked;
	}
	{	bool _unpacked = self->forced;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->forced = _unpacked;
	}
	{	bool _unpacked = self->held;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->held = _unpacked;
	}
	{	bool _unpacked = self->deadboltExtended;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->deadboltExtended = _unpacked;
	}
	{	bool _unpacked = self->privacy;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->privacy = _unpacked;
	}
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->batteryLevel))) return result;

	return 0;
}

int LockDstTransition_serialize_KCB(struct LockDstTransition *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->nth))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->dayOfWeek))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->hour))) return result;

	return 0;
}

int LockDstTransition_deserialize_KCB(struct LockDstTransition *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->nth;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->nth = _unpacked;
	}
	{	uint8_t _unpacked = self->dayOfWeek;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->dayOfWeek = _unpacked;
	}
	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}

	return 0;
}

int LockAccessModifiers_serialize_KCB(struct LockAccessModifiers *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->extDoorTime))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->administrator))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->privacyExempt))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->staticStateLockedExempt))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->emergencyStaticStateLockedExempt))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->emergency))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->firstCredUnlock))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->pinUnique))) return result;

	return 0;
}

int LockAccessModifiers_deserialize_KCB(struct LockAccessModifiers *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	bool _unpacked = self->extDoorTime;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->extDoorTime = _unpacked;
	}
	{	bool _unpacked = self->administrator;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->administrator = _unpacked;
	}
	{	bool _unpacked = self->privacyExempt;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->privacyExempt = _unpacked;
	}
	{	bool _unpacked = self->staticStateLockedExempt;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->staticStateLockedExempt = _unpacked;
	}
	{	bool _unpacked = self->emergencyStaticStateLockedExempt;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->emergencyStaticStateLockedExempt = _unpacked;
	}
	{	bool _unpacked = self->emergency;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->emergency = _unpacked;
	}
	{	bool _unpacked = self->firstCredUnlock;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->firstCredUnlock = _unpacked;
	}
	{	bool _unpacked = self->pinUnique;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->pinUnique = _unpacked;
	}

	return 0;
}

int LockCredActions_serialize_KCB(struct LockCredActions *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->access))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setLockMode_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setLockMode_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setLockMode_EMERGENCY_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->cancelLockMode_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->cancelLockMode_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED))) return result;

	return 0;
}

int LockCredActions_deserialize_KCB(struct LockCredActions *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	bool _unpacked = self->access;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->access = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_EMERGENCY_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_EMERGENCY_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED = _unpacked;
	}

	return 0;
}

int LockDevActionPermissions_serialize_KCB(struct LockDevActionPermissions *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_MOMENTARY_UNLOCK))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_RESET_LOCK_MODE))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_CARD_ONLY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN))) return result;

	return 0;
}

int LockDevActionPermissions_deserialize_KCB(struct LockDevActionPermissions *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	bool _unpacked = self->allow_MOMENTARY_UNLOCK;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_MOMENTARY_UNLOCK = _unpacked;
	}
	{	bool _unpacked = self->allow_RESET_LOCK_MODE;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_RESET_LOCK_MODE = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_CARD_ONLY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_CARD_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN = _unpacked;
	}

	return 0;
}

int LockCredTechnologies_serialize_KCB(struct LockCredTechnologies *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_PROX))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_BLUETOOTH_ANY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_NFC_ANY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_DESFIRE_ANY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_ICLASS_ANY))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_BLUETOOTH_WAVELYNX))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_BLUETOOTH_Z9_WAVELYNX))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_NFC_GOOGLE))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_NFC_APPLE))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_DESFIRE_LEAF))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_DESFIRE_UID))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_ICLASS_FULL))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->enable_ICLASS_UID))) return result;

	return 0;
}

int LockCredTechnologies_deserialize_KCB(struct LockCredTechnologies *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	{	bool _unpacked = self->enable_PROX;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_PROX = _unpacked;
	}
	{	bool _unpacked = self->enable_BLUETOOTH_ANY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_BLUETOOTH_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_NFC_ANY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_NFC_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_DESFIRE_ANY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_DESFIRE_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_ICLASS_ANY;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_ICLASS_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_BLUETOOTH_WAVELYNX;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_BLUETOOTH_WAVELYNX = _unpacked;
	}
	{	bool _unpacked = self->enable_BLUETOOTH_Z9_WAVELYNX;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_BLUETOOTH_Z9_WAVELYNX = _unpacked;
	}
	{	bool _unpacked = self->enable_NFC_GOOGLE;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_NFC_GOOGLE = _unpacked;
	}
	{	bool _unpacked = self->enable_NFC_APPLE;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_NFC_APPLE = _unpacked;
	}
	{	bool _unpacked = self->enable_DESFIRE_LEAF;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_DESFIRE_LEAF = _unpacked;
	}
	{	bool _unpacked = self->enable_DESFIRE_UID;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_DESFIRE_UID = _unpacked;
	}
	{	bool _unpacked = self->enable_ICLASS_FULL;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_ICLASS_FULL = _unpacked;
	}
	{	bool _unpacked = self->enable_ICLASS_UID;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->enable_ICLASS_UID = _unpacked;
	}

	return 0;
}

int LockFunctionModifiers_serialize_KCB(struct LockFunctionModifiers *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->ipbUnlockDuration))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->escapeAndReturnDuration))) return result;

	return 0;
}

int LockFunctionModifiers_deserialize_KCB(struct LockFunctionModifiers *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->ipbUnlockDuration))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->escapeAndReturnDuration))) return result;

	return 0;
}

int LockPolicyAssertion_serialize_KCB(struct LockPolicyAssertion *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockMode_serialize_KCB(&self->mode, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setDoorForcedMasking))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->doorForcedMasking))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setDoorHeldMasking))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->doorHeldMasking))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->setPrivacy))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->privacy))) return result;

	return 0;
}

int LockPolicyAssertion_deserialize_KCB(struct LockPolicyAssertion *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockMode_deserialize_KCB(&self->mode, deserializer))) return result;
	{	bool _unpacked = self->setDoorForcedMasking;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setDoorForcedMasking = _unpacked;
	}
	{	bool _unpacked = self->doorForcedMasking;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->doorForcedMasking = _unpacked;
	}
	{	bool _unpacked = self->setDoorHeldMasking;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setDoorHeldMasking = _unpacked;
	}
	{	bool _unpacked = self->doorHeldMasking;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->doorHeldMasking = _unpacked;
	}
	{	bool _unpacked = self->setPrivacy;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->setPrivacy = _unpacked;
	}
	{	bool _unpacked = self->privacy;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->privacy = _unpacked;
	}

	return 0;
}

int LockHostGrantConfig_serialize_KCB(struct LockHostGrantConfig *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockHostGrantInitiationMode_serialize_KCB(&self->initiationMode, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->timeout))) return result;
	if ((result = LockHostGrantFallbackMode_serialize_KCB(&self->fallbackMode, serializer))) return result;

	return 0;
}

int LockHostGrantConfig_deserialize_KCB(struct LockHostGrantConfig *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockHostGrantInitiationMode_deserialize_KCB(&self->initiationMode, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->timeout))) return result;
	if ((result = LockHostGrantFallbackMode_deserialize_KCB(&self->fallbackMode, deserializer))) return result;

	return 0;
}

int LockPacketContent_serialize_KCB(struct LockPacketContent *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeChar(serializer, self->contentType))) return result;

	return 0;
}

int LockPacketContent_deserialize_KCB(struct LockPacketContent *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->contentType))) return result;

	return 0;
}

int LockPaginationReq_serialize_KCB(struct LockPaginationReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeInt(serializer, self->aboveIndex))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->pageSize))) return result;

	return 0;
}

int LockPaginationReq_deserialize_KCB(struct LockPaginationReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readInt(deserializer, &self->aboveIndex))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->pageSize))) return result;

	return 0;
}

int LockEvtContent_None_serialize_KCB(struct LockEvtContent_None *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 0;
	if ((result = LockEvtContent_serialize_KCB(&self->base, serializer))) return result;


	return 0;
}

int LockEvtContent_None_deserialize_KCB(struct LockEvtContent_None *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 0) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockEvtContent_BatteryLevel_serialize_KCB(struct LockEvtContent_BatteryLevel *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 3;
	if ((result = LockEvtContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->batteryLevel))) return result;

	return 0;
}

int LockEvtContent_BatteryLevel_deserialize_KCB(struct LockEvtContent_BatteryLevel *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 3) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->batteryLevel))) return result;

	return 0;
}

int LockEvtContent_CredUnid_serialize_KCB(struct LockEvtContent_CredUnid *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 1;
	if ((result = LockEvtContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = LockCredTechnology_serialize_KCB(&self->credTechnology, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedInt(serializer, self->credUnid))) return result;

	return 0;
}

int LockEvtContent_CredUnid_deserialize_KCB(struct LockEvtContent_CredUnid *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 1) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockCredTechnology_deserialize_KCB(&self->credTechnology, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedInt(deserializer, &self->credUnid))) return result;

	return 0;
}

int LockEvtContent_SchedOid_serialize_KCB(struct LockEvtContent_SchedOid *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 2;
	if ((result = LockEvtContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->schedOid))) return result;

	return 0;
}

int LockEvtContent_SchedOid_deserialize_KCB(struct LockEvtContent_SchedOid *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 2) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->schedOid))) return result;

	return 0;
}

int LockEvt_serialize_KCB(struct LockEvt *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_serialize_KCB(&self->dateTime, serializer))) return result;
	if ((result = LockEvtCode_serialize_KCB(&self->evtCode, serializer))) return result;
	if ((result = LockEvtModifiers_serialize_KCB(&self->modifiers, serializer))) return result;
	// serialize union content:
	{
		switch (((struct LockEvtContent*) &self->content)->contentType)
		{
			case LockEvtContent_None_DISCRIMINATOR:
				result = LockEvtContent_None_serialize_KCB(&self->content.uLockEvtContent_None, serializer);
				if (result) return result;
				break;
			case LockEvtContent_CredUnid_DISCRIMINATOR:
				result = LockEvtContent_CredUnid_serialize_KCB(&self->content.uLockEvtContent_CredUnid, serializer);
				if (result) return result;
				break;
			case LockEvtContent_SchedOid_DISCRIMINATOR:
				result = LockEvtContent_SchedOid_serialize_KCB(&self->content.uLockEvtContent_SchedOid, serializer);
				if (result) return result;
				break;
			case LockEvtContent_BatteryLevel_DISCRIMINATOR:
				result = LockEvtContent_BatteryLevel_serialize_KCB(&self->content.uLockEvtContent_BatteryLevel, serializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}

	return 0;
}

int LockEvt_deserialize_KCB(struct LockEvt *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_deserialize_KCB(&self->dateTime, deserializer))) return result;
	if ((result = LockEvtCode_deserialize_KCB(&self->evtCode, deserializer))) return result;
	if ((result = LockEvtModifiers_deserialize_KCB(&self->modifiers, deserializer))) return result;
	// deserialize union content:
	{
		// peek ahead to read discriminator:
		const int posBeforeDiscriminator = BasicDeserializer_KCB_getCurPos(deserializer);
		int8_t discriminator;
		if ((result = BasicDeserializer_KCB_readChar(deserializer, &discriminator))) return result;
		if ((result = BasicDeserializer_KCB_seek(deserializer, posBeforeDiscriminator))) return result;

		switch (discriminator)
		{
			case LockEvtContent_None_DISCRIMINATOR:
				result = LockEvtContent_None_deserialize_KCB(&self->content.uLockEvtContent_None, deserializer);
				if (result) return result;
				break;
			case LockEvtContent_CredUnid_DISCRIMINATOR:
				result = LockEvtContent_CredUnid_deserialize_KCB(&self->content.uLockEvtContent_CredUnid, deserializer);
				if (result) return result;
				break;
			case LockEvtContent_SchedOid_DISCRIMINATOR:
				result = LockEvtContent_SchedOid_deserialize_KCB(&self->content.uLockEvtContent_SchedOid, deserializer);
				if (result) return result;
				break;
			case LockEvtContent_BatteryLevel_DISCRIMINATOR:
				result = LockEvtContent_BatteryLevel_deserialize_KCB(&self->content.uLockEvtContent_BatteryLevel, deserializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}

	return 0;
}

int LockTimeZone_serialize_KCB(struct LockTimeZone *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->standardOffset))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->dstOffset))) return result;
	if ((result = LockDstTransition_serialize_KCB(&self->standardTransition, serializer))) return result;
	if ((result = LockDstTransition_serialize_KCB(&self->dstTransition, serializer))) return result;

	return 0;
}

int LockTimeZone_deserialize_KCB(struct LockTimeZone *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->standardOffset))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->dstOffset))) return result;
	if ((result = LockDstTransition_deserialize_KCB(&self->standardTransition, deserializer))) return result;
	if ((result = LockDstTransition_deserialize_KCB(&self->dstTransition, deserializer))) return result;

	return 0;
}

int LockCred_serialize_KCB(struct LockCred *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedInt(serializer, self->unid))) return result;
	if ((result = LockDate_serialize_KCB(&self->effective, serializer))) return result;
	if ((result = LockDate_serialize_KCB(&self->expires, serializer))) return result;
	if ((result = LockCredTechnology_serialize_KCB(&self->technology, serializer))) return result;
	if ((result = LockAccessModifiers_serialize_KCB(&self->accessModifiers, serializer))) return result;
	if ((result = LockCredActions_serialize_KCB(&self->presentationActions, serializer))) return result;
	if ((result = LockCredActions_serialize_KCB(&self->doublePresentationActions, serializer))) return result;
	if ((result = LockDevActionPermissions_serialize_KCB(&self->explicitActionPermissions, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->trimBitsInLastCredByte))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numCredBytes))) return result;
	if (self->numCredBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCredBytes; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->credBytes[i]))) return result;
	for (i = 0; i < 4; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->pinDigitNybbles[i]))) return result;
	for (i = 0; i < 2; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->schedMaskBytes[i]))) return result;

	return 0;
}

int LockCred_deserialize_KCB(struct LockCred *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readUnsignedInt(deserializer, &self->unid))) return result;
	if ((result = LockDate_deserialize_KCB(&self->effective, deserializer))) return result;
	if ((result = LockDate_deserialize_KCB(&self->expires, deserializer))) return result;
	if ((result = LockCredTechnology_deserialize_KCB(&self->technology, deserializer))) return result;
	if ((result = LockAccessModifiers_deserialize_KCB(&self->accessModifiers, deserializer))) return result;
	if ((result = LockCredActions_deserialize_KCB(&self->presentationActions, deserializer))) return result;
	if ((result = LockCredActions_deserialize_KCB(&self->doublePresentationActions, deserializer))) return result;
	if ((result = LockDevActionPermissions_deserialize_KCB(&self->explicitActionPermissions, deserializer))) return result;
	{	int8_t _unpacked = self->trimBitsInLastCredByte;
		if ((result = BasicDeserializer_KCB_readChar(deserializer, &_unpacked))) return result;
		self->trimBitsInLastCredByte = _unpacked;
	}
	{	uint8_t _unpacked = self->numCredBytes;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->numCredBytes = _unpacked;
	}
	if (self->numCredBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCredBytes; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->credBytes[i]))) return result;
	for (i = self->numCredBytes; i < 16; ++i)
		self->credBytes[i] = 0;
	for (i = 0; i < 4; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->pinDigitNybbles[i]))) return result;
	for (i = 0; i < 2; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->schedMaskBytes[i]))) return result;

	return 0;
}

int LockEvtPolicy_serialize_KCB(struct LockEvtPolicy *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockEvtCode_serialize_KCB(&self->evtCode, serializer))) return result;
	if ((result = LockEvtDelta_serialize_KCB(&self->evtDelta, serializer))) return result;

	return 0;
}

int LockEvtPolicy_deserialize_KCB(struct LockEvtPolicy *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockEvtCode_deserialize_KCB(&self->evtCode, deserializer))) return result;
	if ((result = LockEvtDelta_deserialize_KCB(&self->evtDelta, deserializer))) return result;

	return 0;
}

int LockHol_serialize_KCB(struct LockHol *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockDateTime_ToMinute_serialize_KCB(&self->start, serializer))) return result;
	if ((result = LockDateTime_ToMinute_serialize_KCB(&self->stop, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->holTypes))) return result;

	return 0;
}

int LockHol_deserialize_KCB(struct LockHol *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockDateTime_ToMinute_deserialize_KCB(&self->start, deserializer))) return result;
	if ((result = LockDateTime_ToMinute_deserialize_KCB(&self->stop, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->holTypes))) return result;

	return 0;
}

int LockSchedElement_serialize_KCB(struct LockSchedElement *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockTimeOfDay_ToQuarterHour_serialize_KCB(&self->start, serializer))) return result;
	if ((result = LockTimeOfDay_ToQuarterHour_serialize_KCB(&self->stop, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->plusDays))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->daysOfWeek))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->holTypes))) return result;

	return 0;
}

int LockSchedElement_deserialize_KCB(struct LockSchedElement *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockTimeOfDay_ToQuarterHour_deserialize_KCB(&self->start, deserializer))) return result;
	if ((result = LockTimeOfDay_ToQuarterHour_deserialize_KCB(&self->stop, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->plusDays))) return result;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->daysOfWeek))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->holTypes))) return result;

	return 0;
}

int LockSchedElementPolicy_serialize_KCB(struct LockSchedElementPolicy *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockPolicyAssertion_serialize_KCB(&self->assertion, serializer))) return result;

	return 0;
}

int LockSchedElementPolicy_deserialize_KCB(struct LockSchedElementPolicy *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPolicyAssertion_deserialize_KCB(&self->assertion, deserializer))) return result;

	return 0;
}

int LockSchedPolicy_serialize_KCB(struct LockSchedPolicy *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->schedOid))) return result;
	if ((result = LockDevActionType_serialize_KCB(&self->action, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElementPolicy_serialize_KCB(&self->elements[i], serializer))) return result;

	return 0;
}

int LockSchedPolicy_deserialize_KCB(struct LockSchedPolicy *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->schedOid))) return result;
	if ((result = LockDevActionType_deserialize_KCB(&self->action, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElementPolicy_deserialize_KCB(&self->elements[i], deserializer))) return result;

	return 0;
}

int LockSched_serialize_KCB(struct LockSched *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = BasicSerializer_KCB_writeUnsignedInt(serializer, self->unid))) return result;
	if ((result = LockDateTime_ToMinute_serialize_KCB(&self->effective, serializer))) return result;
	if ((result = LockDateTime_ToMinute_serialize_KCB(&self->expires, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElement_serialize_KCB(&self->elements[i], serializer))) return result;

	return 0;
}

int LockSched_deserialize_KCB(struct LockSched *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = BasicDeserializer_KCB_readUnsignedInt(deserializer, &self->unid))) return result;
	if ((result = LockDateTime_ToMinute_deserialize_KCB(&self->effective, deserializer))) return result;
	if ((result = LockDateTime_ToMinute_deserialize_KCB(&self->expires, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElement_deserialize_KCB(&self->elements[i], deserializer))) return result;

	return 0;
}

int LockConfig_serialize_KCB(struct LockConfig *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockCredTechnologies_serialize_KCB(&self->credTechnologies, serializer))) return result;
	if ((result = LockFunction_serialize_KCB(&self->function, serializer))) return result;
	if ((result = LockFunctionModifiers_serialize_KCB(&self->functionModifiers, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->strikeTime))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->extendedStrikeTime))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->heldTime))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->extendedHeldTime))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->defaultDoorForcedMasking))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->defaultDoorHeldMasking))) return result;
	if ((result = LockMode_serialize_KCB(&self->defaultLockMode, serializer))) return result;
	if ((result = LockHostGrantConfig_serialize_KCB(&self->hostGrantConfig, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->maxPinLength))) return result;
	if ((result = LockTimeZone_serialize_KCB(&self->timeZone, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numEvtPolicy))) return result;
	if (self->numEvtPolicy > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numEvtPolicy; ++i)
		if ((result = LockEvtPolicy_serialize_KCB(&self->evtPolicies[i], serializer))) return result;

	return 0;
}

int LockConfig_deserialize_KCB(struct LockConfig *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockCredTechnologies_deserialize_KCB(&self->credTechnologies, deserializer))) return result;
	if ((result = LockFunction_deserialize_KCB(&self->function, deserializer))) return result;
	if ((result = LockFunctionModifiers_deserialize_KCB(&self->functionModifiers, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->strikeTime))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->extendedStrikeTime))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->heldTime))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->extendedHeldTime))) return result;
	{	bool _unpacked = self->defaultDoorForcedMasking;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->defaultDoorForcedMasking = _unpacked;
	}
	{	bool _unpacked = self->defaultDoorHeldMasking;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->defaultDoorHeldMasking = _unpacked;
	}
	if ((result = LockMode_deserialize_KCB(&self->defaultLockMode, deserializer))) return result;
	if ((result = LockHostGrantConfig_deserialize_KCB(&self->hostGrantConfig, deserializer))) return result;
	{	uint8_t _unpacked = self->maxPinLength;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->maxPinLength = _unpacked;
	}
	if ((result = LockTimeZone_deserialize_KCB(&self->timeZone, deserializer))) return result;
	{	uint8_t _unpacked = self->numEvtPolicy;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->numEvtPolicy = _unpacked;
	}
	if (self->numEvtPolicy > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numEvtPolicy; ++i)
		if ((result = LockEvtPolicy_deserialize_KCB(&self->evtPolicies[i], deserializer))) return result;

	return 0;
}

int LockEvtIdentifier_serialize_KCB(struct LockEvtIdentifier *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_serialize_KCB(&self->dateTime, serializer))) return result;
	if ((result = LockEvtCode_serialize_KCB(&self->evtCode, serializer))) return result;

	return 0;
}

int LockEvtIdentifier_deserialize_KCB(struct LockEvtIdentifier *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_deserialize_KCB(&self->dateTime, deserializer))) return result;
	if ((result = LockEvtCode_deserialize_KCB(&self->evtCode, deserializer))) return result;

	return 0;
}

int LockEvtIdentifierRange_serialize_KCB(struct LockEvtIdentifierRange *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockEvtIdentifier_serialize_KCB(&self->start, serializer))) return result;
	if ((result = LockEvtIdentifier_serialize_KCB(&self->stop, serializer))) return result;

	return 0;
}

int LockEvtIdentifierRange_deserialize_KCB(struct LockEvtIdentifierRange *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockEvtIdentifier_deserialize_KCB(&self->start, deserializer))) return result;
	if ((result = LockEvtIdentifier_deserialize_KCB(&self->stop, deserializer))) return result;

	return 0;
}

int LockIdentification_serialize_KCB(struct LockIdentification *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 0;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->protocolVersionMajor))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->protocolVersionMinor))) return result;
	if ((result = LockIdentificationType_serialize_KCB(&self->type, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->id))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->model))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->brand))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->firmwareVersionMajor))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->firmwareVersionMinor))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->licensed))) return result;

	return 0;
}

int LockIdentification_deserialize_KCB(struct LockIdentification *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 0) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->protocolVersionMajor))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->protocolVersionMinor))) return result;
	if ((result = LockIdentificationType_deserialize_KCB(&self->type, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->id))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->model))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->brand))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->firmwareVersionMajor))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->firmwareVersionMinor))) return result;
	{	bool _unpacked = self->licensed;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->licensed = _unpacked;
	}

	return 0;
}

int LockIdentificationResult_serialize_KCB(struct LockIdentificationResult *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 1;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockIdentificationResult_deserialize_KCB(struct LockIdentificationResult *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 1) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockDbChange_Config_serialize_KCB(struct LockDbChange_Config *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 2;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->updateConfigPresent))) return result;
	if (self->updateConfigPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->updateConfigPresent; ++i)
		if ((result = LockConfig_serialize_KCB(&self->updateConfig[i], serializer))) return result;

	return 0;
}

int LockDbChange_Config_deserialize_KCB(struct LockDbChange_Config *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 2) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->updateConfigPresent))) return result;
	if (self->updateConfigPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->updateConfigPresent; ++i)
		if ((result = LockConfig_deserialize_KCB(&self->updateConfig[i], deserializer))) return result;

	return 0;
}

int LockDbChangeResp_serialize_KCB(struct LockDbChangeResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 3;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockDbChangeResp_deserialize_KCB(struct LockDbChangeResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 3) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockEvtControl_serialize_KCB(struct LockEvtControl *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 4;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->priority))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->sendOneBatch))) return result;
	if ((result = LockEvtIdentifierRange_serialize_KCB(&self->consume, serializer))) return result;

	return 0;
}

int LockEvtControl_deserialize_KCB(struct LockEvtControl *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 4) return ProtocolError_INCORRECT_DISCRIMINATOR;

	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}
	{	bool _unpacked = self->sendOneBatch;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->sendOneBatch = _unpacked;
	}
	if ((result = LockEvtIdentifierRange_deserialize_KCB(&self->consume, deserializer))) return result;

	return 0;
}

int LockEvtBatch_serialize_KCB(struct LockEvtBatch *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 5;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeBool(serializer, self->priority))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->evtCount))) return result;
	if (self->evtCount > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->evtCount; ++i)
		if ((result = LockEvt_serialize_KCB(&self->evt[i], serializer))) return result;

	return 0;
}

int LockEvtBatch_deserialize_KCB(struct LockEvtBatch *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 5) return ProtocolError_INCORRECT_DISCRIMINATOR;

	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}
	{	uint8_t _unpacked = self->evtCount;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->evtCount = _unpacked;
	}
	if (self->evtCount > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->evtCount; ++i)
		if ((result = LockEvt_deserialize_KCB(&self->evt[i], deserializer))) return result;

	return 0;
}

int LockDevStateRecordControl_serialize_KCB(struct LockDevStateRecordControl *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 6;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;


	return 0;
}

int LockDevStateRecordControl_deserialize_KCB(struct LockDevStateRecordControl *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 6) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockDevStateRecord_serialize_KCB(struct LockDevStateRecord *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 7;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = LockStatus_serialize_KCB(&self->status, serializer))) return result;

	return 0;
}

int LockDevStateRecord_deserialize_KCB(struct LockDevStateRecord *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 7) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockStatus_deserialize_KCB(&self->status, deserializer))) return result;

	return 0;
}

int LockDateTimeConfig_serialize_KCB(struct LockDateTimeConfig *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_serialize_KCB(&self->dateTime, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->timeZonePresent))) return result;
	if ((result = LockTimeZone_serialize_KCB(&self->timeZone, serializer))) return result;

	return 0;
}

int LockDateTimeConfig_deserialize_KCB(struct LockDateTimeConfig *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_deserialize_KCB(&self->dateTime, deserializer))) return result;
	{	bool _unpacked = self->timeZonePresent;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->timeZonePresent = _unpacked;
	}
	if ((result = LockTimeZone_deserialize_KCB(&self->timeZone, deserializer))) return result;

	return 0;
}

int LockGetTimeReq_serialize_KCB(struct LockGetTimeReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 8;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;


	return 0;
}

int LockGetTimeReq_deserialize_KCB(struct LockGetTimeReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 8) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockGetTimeResp_serialize_KCB(struct LockGetTimeResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 9;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = LockDateTimeConfig_serialize_KCB(&self->dateTimeConfig, serializer))) return result;

	return 0;
}

int LockGetTimeResp_deserialize_KCB(struct LockGetTimeResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 9) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockDateTimeConfig_deserialize_KCB(&self->dateTimeConfig, deserializer))) return result;

	return 0;
}

int LockSetTimeReq_serialize_KCB(struct LockSetTimeReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 10;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = LockDateTimeConfig_serialize_KCB(&self->dateTimeConfig, serializer))) return result;

	return 0;
}

int LockSetTimeReq_deserialize_KCB(struct LockSetTimeReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 10) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockDateTimeConfig_deserialize_KCB(&self->dateTimeConfig, deserializer))) return result;

	return 0;
}

int LockSetTimeResp_serialize_KCB(struct LockSetTimeResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 11;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockSetTimeResp_deserialize_KCB(struct LockSetTimeResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 11) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockPullFileChunkReq_serialize_KCB(struct LockPullFileChunkReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 14;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = LockFileCategory_serialize_KCB(&self->category, serializer))) return result;
	if ((result = LockFileIdentifier_serialize_KCB(&self->id, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->offset))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->maxLength))) return result;

	return 0;
}

int LockPullFileChunkReq_deserialize_KCB(struct LockPullFileChunkReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 14) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = LockFileCategory_deserialize_KCB(&self->category, deserializer))) return result;
	if ((result = LockFileIdentifier_deserialize_KCB(&self->id, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->offset))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->maxLength))) return result;

	return 0;
}

int LockPullFileChunkResp_serialize_KCB(struct LockPullFileChunkResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 15;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->eof))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->bytes[i]))) return result;

	return 0;
}

int LockPullFileChunkResp_deserialize_KCB(struct LockPullFileChunkResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 15) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	{	bool _unpacked = self->eof;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->eof = _unpacked;
	}
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->bytes[i]))) return result;
	for (i = self->bytesCount; i < 800; ++i)
		self->bytes[i] = 0;

	return 0;
}

int LockPushFileChunkReq_serialize_KCB(struct LockPushFileChunkReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 12;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = LockFileCategory_serialize_KCB(&self->category, serializer))) return result;
	if ((result = LockFileIdentifier_serialize_KCB(&self->id, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->offset))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->eof))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->bytes[i]))) return result;

	return 0;
}

int LockPushFileChunkReq_deserialize_KCB(struct LockPushFileChunkReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 12) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = LockFileCategory_deserialize_KCB(&self->category, deserializer))) return result;
	if ((result = LockFileIdentifier_deserialize_KCB(&self->id, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->offset))) return result;
	{	bool _unpacked = self->eof;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->eof = _unpacked;
	}
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->bytes[i]))) return result;
	for (i = self->bytesCount; i < 800; ++i)
		self->bytes[i] = 0;

	return 0;
}

int LockPushFileChunkResp_serialize_KCB(struct LockPushFileChunkResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 13;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockPushFileChunkResp_deserialize_KCB(struct LockPushFileChunkResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 13) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockUpgradeReq_serialize_KCB(struct LockUpgradeReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 16;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = LockFileIdentifier_serialize_KCB(&self->fileId, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->rebootDelay))) return result;

	return 0;
}

int LockUpgradeReq_deserialize_KCB(struct LockUpgradeReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 16) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = LockFileIdentifier_deserialize_KCB(&self->fileId, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->rebootDelay))) return result;

	return 0;
}

int LockUpgradeResp_serialize_KCB(struct LockUpgradeResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 17;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockUpgradeResp_deserialize_KCB(struct LockUpgradeResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 17) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockDbQuery_serialize_KCB(struct LockDbQuery *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 18;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->queryConfig))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->queryHol))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->querySched))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->querySchedPolicy))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->queryCred))) return result;
	if ((result = LockPaginationReq_serialize_KCB(&self->paginationCred, serializer))) return result;

	return 0;
}

int LockDbQuery_deserialize_KCB(struct LockDbQuery *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 18) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	{	bool _unpacked = self->queryConfig;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->queryConfig = _unpacked;
	}
	{	bool _unpacked = self->queryHol;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->queryHol = _unpacked;
	}
	{	bool _unpacked = self->querySched;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->querySched = _unpacked;
	}
	{	bool _unpacked = self->querySchedPolicy;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->querySchedPolicy = _unpacked;
	}
	{	bool _unpacked = self->queryCred;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->queryCred = _unpacked;
	}
	if ((result = LockPaginationReq_deserialize_KCB(&self->paginationCred, deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Config_serialize_KCB(struct LockDbQueryResp_Config *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 19;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->configPresent))) return result;
	if (self->configPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->configPresent; ++i)
		if ((result = LockConfig_serialize_KCB(&self->config[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Config_deserialize_KCB(struct LockDbQueryResp_Config *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 19) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->configPresent))) return result;
	if (self->configPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->configPresent; ++i)
		if ((result = LockConfig_deserialize_KCB(&self->config[i], deserializer))) return result;

	return 0;
}

int LockHostGrantReq_serialize_KCB(struct LockHostGrantReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 20;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = LockHostGrantReqType_serialize_KCB(&self->type, serializer))) return result;
	if ((result = LockMode_serialize_KCB(&self->lockMode, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->privacy))) return result;
	if ((result = LockCred_serialize_KCB(&self->rawCred, serializer))) return result;

	return 0;
}

int LockHostGrantReq_deserialize_KCB(struct LockHostGrantReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 20) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = LockHostGrantReqType_deserialize_KCB(&self->type, deserializer))) return result;
	if ((result = LockMode_deserialize_KCB(&self->lockMode, deserializer))) return result;
	{	bool _unpacked = self->privacy;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->privacy = _unpacked;
	}
	if ((result = LockCred_deserialize_KCB(&self->rawCred, deserializer))) return result;

	return 0;
}

int LockHostGrantResp_serialize_KCB(struct LockHostGrantResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 21;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = LockCred_serialize_KCB(&self->dbCred, serializer))) return result;
	if ((result = LockEvtCode_serialize_KCB(&self->evtCode, serializer))) return result;

	return 0;
}

int LockHostGrantResp_deserialize_KCB(struct LockHostGrantResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 21) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	if ((result = LockCred_deserialize_KCB(&self->dbCred, deserializer))) return result;
	if ((result = LockEvtCode_deserialize_KCB(&self->evtCode, deserializer))) return result;

	return 0;
}

int LockDevActionReq_serialize_KCB(struct LockDevActionReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 22;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = LockDevActionType_serialize_KCB(&self->actionType, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->durationSecs))) return result;
	if ((result = LockPolicyPriority_serialize_KCB(&self->policyPriority, serializer))) return result;

	return 0;
}

int LockDevActionReq_deserialize_KCB(struct LockDevActionReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 22) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = LockDevActionType_deserialize_KCB(&self->actionType, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->durationSecs))) return result;
	if ((result = LockPolicyPriority_deserialize_KCB(&self->policyPriority, deserializer))) return result;

	return 0;
}

int LockDevActionResp_serialize_KCB(struct LockDevActionResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 23;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockDevActionResp_deserialize_KCB(struct LockDevActionResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 23) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockPolicyAssertionReq_serialize_KCB(struct LockPolicyAssertionReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 24;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = LockPolicyPriority_serialize_KCB(&self->priority, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->state))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->temporary))) return result;
	if ((result = LockPolicyAssertion_serialize_KCB(&self->assertion, serializer))) return result;

	return 0;
}

int LockPolicyAssertionReq_deserialize_KCB(struct LockPolicyAssertionReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 24) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = LockPolicyPriority_deserialize_KCB(&self->priority, deserializer))) return result;
	{	bool _unpacked = self->state;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->state = _unpacked;
	}
	{	bool _unpacked = self->temporary;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->temporary = _unpacked;
	}
	if ((result = LockPolicyAssertion_deserialize_KCB(&self->assertion, deserializer))) return result;

	return 0;
}

int LockPolicyAssertionResp_serialize_KCB(struct LockPolicyAssertionResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 25;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockPolicyAssertionResp_deserialize_KCB(struct LockPolicyAssertionResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 25) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockConnectionTermination_serialize_KCB(struct LockConnectionTermination *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 26;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;


	return 0;
}

int LockConnectionTermination_deserialize_KCB(struct LockConnectionTermination *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 26) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockDbChange_Hol_serialize_KCB(struct LockDbChange_Hol *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 27;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numHol))) return result;
	if (self->numHol > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_serialize_KCB(&self->hol[i], serializer))) return result;

	return 0;
}

int LockDbChange_Hol_deserialize_KCB(struct LockDbChange_Hol *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 27) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numHol))) return result;
	if (self->numHol > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_deserialize_KCB(&self->hol[i], deserializer))) return result;

	return 0;
}

int LockDbChange_Sched_serialize_KCB(struct LockDbChange_Sched *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 28;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_serialize_KCB(&self->sched[i], serializer))) return result;

	return 0;
}

int LockDbChange_Sched_deserialize_KCB(struct LockDbChange_Sched *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 28) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_deserialize_KCB(&self->sched[i], deserializer))) return result;

	return 0;
}

int LockDbChange_SchedPolicy_serialize_KCB(struct LockDbChange_SchedPolicy *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 29;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_serialize_KCB(&self->schedPolicy[i], serializer))) return result;

	return 0;
}

int LockDbChange_SchedPolicy_deserialize_KCB(struct LockDbChange_SchedPolicy *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 29) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_deserialize_KCB(&self->schedPolicy[i], deserializer))) return result;

	return 0;
}

int LockDbChange_Cred_serialize_KCB(struct LockDbChange_Cred *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 30;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->deleteAllCred))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numUpsertOrDeleteCred))) return result;
	if (self->numUpsertOrDeleteCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numUpsertOrDeleteCred; ++i)
		if ((result = LockCred_serialize_KCB(&self->upsertOrDeleteCred[i], serializer))) return result;

	return 0;
}

int LockDbChange_Cred_deserialize_KCB(struct LockDbChange_Cred *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 30) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readLong(deserializer, &self->requestId))) return result;
	{	bool _unpacked = self->deleteAllCred;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->deleteAllCred = _unpacked;
	}
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numUpsertOrDeleteCred))) return result;
	if (self->numUpsertOrDeleteCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numUpsertOrDeleteCred; ++i)
		if ((result = LockCred_deserialize_KCB(&self->upsertOrDeleteCred[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Hol_serialize_KCB(struct LockDbQueryResp_Hol *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 31;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numHol))) return result;
	if (self->numHol > 64) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_serialize_KCB(&self->hol[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Hol_deserialize_KCB(struct LockDbQueryResp_Hol *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 31) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numHol))) return result;
	if (self->numHol > 64) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_deserialize_KCB(&self->hol[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Sched_serialize_KCB(struct LockDbQueryResp_Sched *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 32;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_serialize_KCB(&self->sched[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Sched_deserialize_KCB(struct LockDbQueryResp_Sched *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 32) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_deserialize_KCB(&self->sched[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_SchedPolicy_serialize_KCB(struct LockDbQueryResp_SchedPolicy *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 33;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_serialize_KCB(&self->schedPolicy[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_SchedPolicy_deserialize_KCB(struct LockDbQueryResp_SchedPolicy *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 33) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_deserialize_KCB(&self->schedPolicy[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Cred_serialize_KCB(struct LockDbQueryResp_Cred *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 34;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numCred))) return result;
	if (self->numCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCred; ++i)
		if ((result = LockCred_serialize_KCB(&self->cred[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Cred_deserialize_KCB(struct LockDbQueryResp_Cred *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 34) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->numCred))) return result;
	if (self->numCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCred; ++i)
		if ((result = LockCred_deserialize_KCB(&self->cred[i], deserializer))) return result;

	return 0;
}

int LockCredAuthorization_serialize_KCB(struct LockCredAuthorization *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 35;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->mobileId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->lockId))) return result;
	if ((result = LockCred_serialize_KCB(&self->cred, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->numSchedUnids))) return result;
	if (self->numSchedUnids > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedUnids; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedInt(serializer, self->schedUnids[i]))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->numSharedSecretBytes))) return result;
	if (self->numSharedSecretBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	for (i = 0; i < self->numSharedSecretBytes; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->sharedSecretBytes[i]))) return result;

	return 0;
}

int LockCredAuthorization_deserialize_KCB(struct LockCredAuthorization *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 35) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->mobileId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->lockId))) return result;
	if ((result = LockCred_deserialize_KCB(&self->cred, deserializer))) return result;
	{	uint8_t _unpacked = self->numSchedUnids;
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->numSchedUnids = _unpacked;
	}
	if (self->numSchedUnids > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedUnids; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedInt(deserializer, &self->schedUnids[i]))) return result;
	for (i = self->numSchedUnids; i < 15; ++i)
		self->schedUnids[i] = 0;
	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->numSharedSecretBytes))) return result;
	if (self->numSharedSecretBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	for (i = 0; i < self->numSharedSecretBytes; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->sharedSecretBytes[i]))) return result;
	for (i = self->numSharedSecretBytes; i < 16; ++i)
		self->sharedSecretBytes[i] = 0;

	return 0;
}

int LockAccessReq_serialize_KCB(struct LockAccessReq *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 37;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->mobileId))) return result;

	return 0;
}

int LockAccessReq_deserialize_KCB(struct LockAccessReq *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 37) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->mobileId))) return result;

	return 0;
}

int LockAccessResp_serialize_KCB(struct LockAccessResp *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 38;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_KCB_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->granted))) return result;

	return 0;
}

int LockAccessResp_deserialize_KCB(struct LockAccessResp *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 38) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->errorCode))) return result;
	{	bool _unpacked = self->granted;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->granted = _unpacked;
	}

	return 0;
}

int LockPublicKeyExchange_serialize_KCB(struct LockPublicKeyExchange *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 41;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeChar(serializer, self->numPublicKeyBytes))) return result;
	if (self->numPublicKeyBytes > 33) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numPublicKeyBytes; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->publicKeyBytes[i]))) return result;

	return 0;
}

int LockPublicKeyExchange_deserialize_KCB(struct LockPublicKeyExchange *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 41) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->numPublicKeyBytes))) return result;
	if (self->numPublicKeyBytes > 33) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numPublicKeyBytes; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->publicKeyBytes[i]))) return result;
	for (i = self->numPublicKeyBytes; i < 33; ++i)
		self->publicKeyBytes[i] = 0;

	return 0;
}

int LockMobileBleChallengeNonce_serialize_KCB(struct LockMobileBleChallengeNonce *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 43;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeChar(serializer, self->numNonceBytes))) return result;
	if (self->numNonceBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numNonceBytes; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->nonceBytes[i]))) return result;

	return 0;
}

int LockMobileBleChallengeNonce_deserialize_KCB(struct LockMobileBleChallengeNonce *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 43) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_KCB_readChar(deserializer, &self->numNonceBytes))) return result;
	if (self->numNonceBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numNonceBytes; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->nonceBytes[i]))) return result;
	for (i = self->numNonceBytes; i < 16; ++i)
		self->nonceBytes[i] = 0;

	return 0;
}

int LockBundleHeader_serialize_KCB(struct LockBundleHeader *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 40;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = LockIdentificationType_serialize_KCB(&self->origin, serializer))) return result;
	if ((result = LockIdentificationType_serialize_KCB(&self->intermediary, serializer))) return result;
	if ((result = LockIdentificationType_serialize_KCB(&self->destination, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->originId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->intermediaryId))) return result;
	if ((result = BasicSerializer_KCB_writeUnsignedLong(serializer, self->destinationId))) return result;
	if ((result = LockDateTime_ToSecond_serialize_KCB(&self->expires, serializer))) return result;
	if ((result = BasicSerializer_KCB_writeBool(serializer, self->opaque))) return result;
	if ((result = BasicSerializer_KCB_writeChar(serializer, self->packetCount))) return result;

	return 0;
}

int LockBundleHeader_deserialize_KCB(struct LockBundleHeader *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 40) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockIdentificationType_deserialize_KCB(&self->origin, deserializer))) return result;
	if ((result = LockIdentificationType_deserialize_KCB(&self->intermediary, deserializer))) return result;
	if ((result = LockIdentificationType_deserialize_KCB(&self->destination, deserializer))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->originId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->intermediaryId))) return result;
	if ((result = BasicDeserializer_KCB_readUnsignedLong(deserializer, &self->destinationId))) return result;
	if ((result = LockDateTime_ToSecond_deserialize_KCB(&self->expires, deserializer))) return result;
	{	bool _unpacked = self->opaque;
		if ((result = BasicDeserializer_KCB_readBool(deserializer, &_unpacked))) return result;
		self->opaque = _unpacked;
	}
	{	int8_t _unpacked = self->packetCount;
		if ((result = BasicDeserializer_KCB_readChar(deserializer, &_unpacked))) return result;
		self->packetCount = _unpacked;
	}

	return 0;
}

int LockOpaqueContent_serialize_KCB(struct LockOpaqueContent *self, struct BasicSerializer_KCB *serializer)
{

	int result;

	self->base.contentType = 42;
	if ((result = LockPacketContent_serialize_KCB(&self->base, serializer))) return result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->numOpaqueBytes))) return result;
	if (self->numOpaqueBytes > 1023) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numOpaqueBytes; ++i)
		if ((result = BasicSerializer_KCB_writeUnsignedChar(serializer, self->opaqueBytes[i]))) return result;

	return 0;
}

int LockOpaqueContent_deserialize_KCB(struct LockOpaqueContent *self, struct BasicDeserializer_KCB *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize_KCB(&self->base, deserializer))) return result;
	if (self->base.contentType != 42) return ProtocolError_INCORRECT_DISCRIMINATOR;

	{	int16_t _unpacked = self->numOpaqueBytes;
		if ((result = BasicDeserializer_KCB_readShort(deserializer, &_unpacked))) return result;
		self->numOpaqueBytes = _unpacked;
	}
	if (self->numOpaqueBytes > 1023) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numOpaqueBytes; ++i)
		if ((result = BasicDeserializer_KCB_readUnsignedChar(deserializer, &self->opaqueBytes[i]))) return result;
	for (i = self->numOpaqueBytes; i < 1023; ++i)
		self->opaqueBytes[i] = 0;

	return 0;
}

int LockPacket_serialize_KCB(struct LockPacket *self, struct BasicSerializer_KCB *serializer)
{

	const int initialByteCount = BasicSerializer_KCB_getCurPos(serializer);

	int result;

	if ((result = BasicSerializer_KCB_writeShort(serializer, LockPacket_headerBytes))) return result;
	const int byteCountPos = BasicSerializer_KCB_getCurPos(serializer);

	if ((result = BasicSerializer_KCB_writeShort(serializer, self->bytecount))) return result;
	// serialize union content:
	{
		switch (((struct LockPacketContent*) &self->content)->contentType)
		{
			case LockIdentification_DISCRIMINATOR:
				result = LockIdentification_serialize_KCB(&self->content.uLockIdentification, serializer);
				if (result) return result;
				break;
			case LockIdentificationResult_DISCRIMINATOR:
				result = LockIdentificationResult_serialize_KCB(&self->content.uLockIdentificationResult, serializer);
				if (result) return result;
				break;
			case LockDbChange_Config_DISCRIMINATOR:
				result = LockDbChange_Config_serialize_KCB(&self->content.uLockDbChange_Config, serializer);
				if (result) return result;
				break;
			case LockDbChangeResp_DISCRIMINATOR:
				result = LockDbChangeResp_serialize_KCB(&self->content.uLockDbChangeResp, serializer);
				if (result) return result;
				break;
			case LockEvtControl_DISCRIMINATOR:
				result = LockEvtControl_serialize_KCB(&self->content.uLockEvtControl, serializer);
				if (result) return result;
				break;
			case LockEvtBatch_DISCRIMINATOR:
				result = LockEvtBatch_serialize_KCB(&self->content.uLockEvtBatch, serializer);
				if (result) return result;
				break;
			case LockDevStateRecordControl_DISCRIMINATOR:
				result = LockDevStateRecordControl_serialize_KCB(&self->content.uLockDevStateRecordControl, serializer);
				if (result) return result;
				break;
			case LockDevStateRecord_DISCRIMINATOR:
				result = LockDevStateRecord_serialize_KCB(&self->content.uLockDevStateRecord, serializer);
				if (result) return result;
				break;
			case LockGetTimeReq_DISCRIMINATOR:
				result = LockGetTimeReq_serialize_KCB(&self->content.uLockGetTimeReq, serializer);
				if (result) return result;
				break;
			case LockGetTimeResp_DISCRIMINATOR:
				result = LockGetTimeResp_serialize_KCB(&self->content.uLockGetTimeResp, serializer);
				if (result) return result;
				break;
			case LockSetTimeReq_DISCRIMINATOR:
				result = LockSetTimeReq_serialize_KCB(&self->content.uLockSetTimeReq, serializer);
				if (result) return result;
				break;
			case LockSetTimeResp_DISCRIMINATOR:
				result = LockSetTimeResp_serialize_KCB(&self->content.uLockSetTimeResp, serializer);
				if (result) return result;
				break;
			case LockPushFileChunkReq_DISCRIMINATOR:
				result = LockPushFileChunkReq_serialize_KCB(&self->content.uLockPushFileChunkReq, serializer);
				if (result) return result;
				break;
			case LockPushFileChunkResp_DISCRIMINATOR:
				result = LockPushFileChunkResp_serialize_KCB(&self->content.uLockPushFileChunkResp, serializer);
				if (result) return result;
				break;
			case LockPullFileChunkReq_DISCRIMINATOR:
				result = LockPullFileChunkReq_serialize_KCB(&self->content.uLockPullFileChunkReq, serializer);
				if (result) return result;
				break;
			case LockPullFileChunkResp_DISCRIMINATOR:
				result = LockPullFileChunkResp_serialize_KCB(&self->content.uLockPullFileChunkResp, serializer);
				if (result) return result;
				break;
			case LockUpgradeReq_DISCRIMINATOR:
				result = LockUpgradeReq_serialize_KCB(&self->content.uLockUpgradeReq, serializer);
				if (result) return result;
				break;
			case LockUpgradeResp_DISCRIMINATOR:
				result = LockUpgradeResp_serialize_KCB(&self->content.uLockUpgradeResp, serializer);
				if (result) return result;
				break;
			case LockDbQuery_DISCRIMINATOR:
				result = LockDbQuery_serialize_KCB(&self->content.uLockDbQuery, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Config_DISCRIMINATOR:
				result = LockDbQueryResp_Config_serialize_KCB(&self->content.uLockDbQueryResp_Config, serializer);
				if (result) return result;
				break;
			case LockHostGrantReq_DISCRIMINATOR:
				result = LockHostGrantReq_serialize_KCB(&self->content.uLockHostGrantReq, serializer);
				if (result) return result;
				break;
			case LockHostGrantResp_DISCRIMINATOR:
				result = LockHostGrantResp_serialize_KCB(&self->content.uLockHostGrantResp, serializer);
				if (result) return result;
				break;
			case LockDevActionReq_DISCRIMINATOR:
				result = LockDevActionReq_serialize_KCB(&self->content.uLockDevActionReq, serializer);
				if (result) return result;
				break;
			case LockDevActionResp_DISCRIMINATOR:
				result = LockDevActionResp_serialize_KCB(&self->content.uLockDevActionResp, serializer);
				if (result) return result;
				break;
			case LockPolicyAssertionReq_DISCRIMINATOR:
				result = LockPolicyAssertionReq_serialize_KCB(&self->content.uLockPolicyAssertionReq, serializer);
				if (result) return result;
				break;
			case LockPolicyAssertionResp_DISCRIMINATOR:
				result = LockPolicyAssertionResp_serialize_KCB(&self->content.uLockPolicyAssertionResp, serializer);
				if (result) return result;
				break;
			case LockConnectionTermination_DISCRIMINATOR:
				result = LockConnectionTermination_serialize_KCB(&self->content.uLockConnectionTermination, serializer);
				if (result) return result;
				break;
			case LockDbChange_Hol_DISCRIMINATOR:
				result = LockDbChange_Hol_serialize_KCB(&self->content.uLockDbChange_Hol, serializer);
				if (result) return result;
				break;
			case LockDbChange_Sched_DISCRIMINATOR:
				result = LockDbChange_Sched_serialize_KCB(&self->content.uLockDbChange_Sched, serializer);
				if (result) return result;
				break;
			case LockDbChange_SchedPolicy_DISCRIMINATOR:
				result = LockDbChange_SchedPolicy_serialize_KCB(&self->content.uLockDbChange_SchedPolicy, serializer);
				if (result) return result;
				break;
			case LockDbChange_Cred_DISCRIMINATOR:
				result = LockDbChange_Cred_serialize_KCB(&self->content.uLockDbChange_Cred, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Hol_DISCRIMINATOR:
				result = LockDbQueryResp_Hol_serialize_KCB(&self->content.uLockDbQueryResp_Hol, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Sched_DISCRIMINATOR:
				result = LockDbQueryResp_Sched_serialize_KCB(&self->content.uLockDbQueryResp_Sched, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_SchedPolicy_DISCRIMINATOR:
				result = LockDbQueryResp_SchedPolicy_serialize_KCB(&self->content.uLockDbQueryResp_SchedPolicy, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Cred_DISCRIMINATOR:
				result = LockDbQueryResp_Cred_serialize_KCB(&self->content.uLockDbQueryResp_Cred, serializer);
				if (result) return result;
				break;
			case LockCredAuthorization_DISCRIMINATOR:
				result = LockCredAuthorization_serialize_KCB(&self->content.uLockCredAuthorization, serializer);
				if (result) return result;
				break;
			case LockAccessReq_DISCRIMINATOR:
				result = LockAccessReq_serialize_KCB(&self->content.uLockAccessReq, serializer);
				if (result) return result;
				break;
			case LockAccessResp_DISCRIMINATOR:
				result = LockAccessResp_serialize_KCB(&self->content.uLockAccessResp, serializer);
				if (result) return result;
				break;
			case LockBundleHeader_DISCRIMINATOR:
				result = LockBundleHeader_serialize_KCB(&self->content.uLockBundleHeader, serializer);
				if (result) return result;
				break;
			case LockPublicKeyExchange_DISCRIMINATOR:
				result = LockPublicKeyExchange_serialize_KCB(&self->content.uLockPublicKeyExchange, serializer);
				if (result) return result;
				break;
			case LockOpaqueContent_DISCRIMINATOR:
				result = LockOpaqueContent_serialize_KCB(&self->content.uLockOpaqueContent, serializer);
				if (result) return result;
				break;
			case LockMobileBleChallengeNonce_DISCRIMINATOR:
				result = LockMobileBleChallengeNonce_serialize_KCB(&self->content.uLockMobileBleChallengeNonce, serializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}

	// Update and write bytecount:
	{
		const int finalByteCount = BasicSerializer_KCB_getCurPos(serializer);
		const int bytesForByteCount = finalByteCount - initialByteCount;
		if ((result = BasicSerializer_KCB_seek(serializer, byteCountPos))) return result;
		if ((result = BasicSerializer_KCB_writeShort(serializer, bytesForByteCount))) return result;
		self->bytecount = bytesForByteCount;
		if ((result = BasicSerializer_KCB_seek(serializer, finalByteCount))) return result;
	}

	return 0;
}

int LockPacket_deserialize_KCB(struct LockPacket *self, struct BasicDeserializer_KCB *deserializer)
{

	const int initialByteCount = BasicDeserializer_KCB_getCurPos(deserializer);

	int result;

	{
		int16_t val;
		if ((result = BasicDeserializer_KCB_readShort(deserializer, &val))) return result;
		if (val != LockPacket_headerBytes) return ProtocolError_INCORRECT_STATIC_VALUE;
	}
	if ((result = BasicDeserializer_KCB_readShort(deserializer, &self->bytecount))) return result;
	// deserialize union content:
	{
		// peek ahead to read discriminator:
		const int posBeforeDiscriminator = BasicDeserializer_KCB_getCurPos(deserializer);
		int8_t discriminator;
		if ((result = BasicDeserializer_KCB_readChar(deserializer, &discriminator))) return result;
		if ((result = BasicDeserializer_KCB_seek(deserializer, posBeforeDiscriminator))) return result;

		switch (discriminator)
		{
			case LockIdentification_DISCRIMINATOR:
				result = LockIdentification_deserialize_KCB(&self->content.uLockIdentification, deserializer);
				if (result) return result;
				break;
			case LockIdentificationResult_DISCRIMINATOR:
				result = LockIdentificationResult_deserialize_KCB(&self->content.uLockIdentificationResult, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Config_DISCRIMINATOR:
				result = LockDbChange_Config_deserialize_KCB(&self->content.uLockDbChange_Config, deserializer);
				if (result) return result;
				break;
			case LockDbChangeResp_DISCRIMINATOR:
				result = LockDbChangeResp_deserialize_KCB(&self->content.uLockDbChangeResp, deserializer);
				if (result) return result;
				break;
			case LockEvtControl_DISCRIMINATOR:
				result = LockEvtControl_deserialize_KCB(&self->content.uLockEvtControl, deserializer);
				if (result) return result;
				break;
			case LockEvtBatch_DISCRIMINATOR:
				result = LockEvtBatch_deserialize_KCB(&self->content.uLockEvtBatch, deserializer);
				if (result) return result;
				break;
			case LockDevStateRecordControl_DISCRIMINATOR:
				result = LockDevStateRecordControl_deserialize_KCB(&self->content.uLockDevStateRecordControl, deserializer);
				if (result) return result;
				break;
			case LockDevStateRecord_DISCRIMINATOR:
				result = LockDevStateRecord_deserialize_KCB(&self->content.uLockDevStateRecord, deserializer);
				if (result) return result;
				break;
			case LockGetTimeReq_DISCRIMINATOR:
				result = LockGetTimeReq_deserialize_KCB(&self->content.uLockGetTimeReq, deserializer);
				if (result) return result;
				break;
			case LockGetTimeResp_DISCRIMINATOR:
				result = LockGetTimeResp_deserialize_KCB(&self->content.uLockGetTimeResp, deserializer);
				if (result) return result;
				break;
			case LockSetTimeReq_DISCRIMINATOR:
				result = LockSetTimeReq_deserialize_KCB(&self->content.uLockSetTimeReq, deserializer);
				if (result) return result;
				break;
			case LockSetTimeResp_DISCRIMINATOR:
				result = LockSetTimeResp_deserialize_KCB(&self->content.uLockSetTimeResp, deserializer);
				if (result) return result;
				break;
			case LockPushFileChunkReq_DISCRIMINATOR:
				result = LockPushFileChunkReq_deserialize_KCB(&self->content.uLockPushFileChunkReq, deserializer);
				if (result) return result;
				break;
			case LockPushFileChunkResp_DISCRIMINATOR:
				result = LockPushFileChunkResp_deserialize_KCB(&self->content.uLockPushFileChunkResp, deserializer);
				if (result) return result;
				break;
			case LockPullFileChunkReq_DISCRIMINATOR:
				result = LockPullFileChunkReq_deserialize_KCB(&self->content.uLockPullFileChunkReq, deserializer);
				if (result) return result;
				break;
			case LockPullFileChunkResp_DISCRIMINATOR:
				result = LockPullFileChunkResp_deserialize_KCB(&self->content.uLockPullFileChunkResp, deserializer);
				if (result) return result;
				break;
			case LockUpgradeReq_DISCRIMINATOR:
				result = LockUpgradeReq_deserialize_KCB(&self->content.uLockUpgradeReq, deserializer);
				if (result) return result;
				break;
			case LockUpgradeResp_DISCRIMINATOR:
				result = LockUpgradeResp_deserialize_KCB(&self->content.uLockUpgradeResp, deserializer);
				if (result) return result;
				break;
			case LockDbQuery_DISCRIMINATOR:
				result = LockDbQuery_deserialize_KCB(&self->content.uLockDbQuery, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Config_DISCRIMINATOR:
				result = LockDbQueryResp_Config_deserialize_KCB(&self->content.uLockDbQueryResp_Config, deserializer);
				if (result) return result;
				break;
			case LockHostGrantReq_DISCRIMINATOR:
				result = LockHostGrantReq_deserialize_KCB(&self->content.uLockHostGrantReq, deserializer);
				if (result) return result;
				break;
			case LockHostGrantResp_DISCRIMINATOR:
				result = LockHostGrantResp_deserialize_KCB(&self->content.uLockHostGrantResp, deserializer);
				if (result) return result;
				break;
			case LockDevActionReq_DISCRIMINATOR:
				result = LockDevActionReq_deserialize_KCB(&self->content.uLockDevActionReq, deserializer);
				if (result) return result;
				break;
			case LockDevActionResp_DISCRIMINATOR:
				result = LockDevActionResp_deserialize_KCB(&self->content.uLockDevActionResp, deserializer);
				if (result) return result;
				break;
			case LockPolicyAssertionReq_DISCRIMINATOR:
				result = LockPolicyAssertionReq_deserialize_KCB(&self->content.uLockPolicyAssertionReq, deserializer);
				if (result) return result;
				break;
			case LockPolicyAssertionResp_DISCRIMINATOR:
				result = LockPolicyAssertionResp_deserialize_KCB(&self->content.uLockPolicyAssertionResp, deserializer);
				if (result) return result;
				break;
			case LockConnectionTermination_DISCRIMINATOR:
				result = LockConnectionTermination_deserialize_KCB(&self->content.uLockConnectionTermination, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Hol_DISCRIMINATOR:
				result = LockDbChange_Hol_deserialize_KCB(&self->content.uLockDbChange_Hol, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Sched_DISCRIMINATOR:
				result = LockDbChange_Sched_deserialize_KCB(&self->content.uLockDbChange_Sched, deserializer);
				if (result) return result;
				break;
			case LockDbChange_SchedPolicy_DISCRIMINATOR:
				result = LockDbChange_SchedPolicy_deserialize_KCB(&self->content.uLockDbChange_SchedPolicy, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Cred_DISCRIMINATOR:
				result = LockDbChange_Cred_deserialize_KCB(&self->content.uLockDbChange_Cred, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Hol_DISCRIMINATOR:
				result = LockDbQueryResp_Hol_deserialize_KCB(&self->content.uLockDbQueryResp_Hol, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Sched_DISCRIMINATOR:
				result = LockDbQueryResp_Sched_deserialize_KCB(&self->content.uLockDbQueryResp_Sched, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_SchedPolicy_DISCRIMINATOR:
				result = LockDbQueryResp_SchedPolicy_deserialize_KCB(&self->content.uLockDbQueryResp_SchedPolicy, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Cred_DISCRIMINATOR:
				result = LockDbQueryResp_Cred_deserialize_KCB(&self->content.uLockDbQueryResp_Cred, deserializer);
				if (result) return result;
				break;
			case LockCredAuthorization_DISCRIMINATOR:
				result = LockCredAuthorization_deserialize_KCB(&self->content.uLockCredAuthorization, deserializer);
				if (result) return result;
				break;
			case LockAccessReq_DISCRIMINATOR:
				result = LockAccessReq_deserialize_KCB(&self->content.uLockAccessReq, deserializer);
				if (result) return result;
				break;
			case LockAccessResp_DISCRIMINATOR:
				result = LockAccessResp_deserialize_KCB(&self->content.uLockAccessResp, deserializer);
				if (result) return result;
				break;
			case LockBundleHeader_DISCRIMINATOR:
				result = LockBundleHeader_deserialize_KCB(&self->content.uLockBundleHeader, deserializer);
				if (result) return result;
				break;
			case LockPublicKeyExchange_DISCRIMINATOR:
				result = LockPublicKeyExchange_deserialize_KCB(&self->content.uLockPublicKeyExchange, deserializer);
				if (result) return result;
				break;
			case LockOpaqueContent_DISCRIMINATOR:
				result = LockOpaqueContent_deserialize_KCB(&self->content.uLockOpaqueContent, deserializer);
				if (result) return result;
				break;
			case LockMobileBleChallengeNonce_DISCRIMINATOR:
				result = LockMobileBleChallengeNonce_deserialize_KCB(&self->content.uLockMobileBleChallengeNonce, deserializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}
	// Check bytecount:
	{
		const int finalByteCount = BasicDeserializer_KCB_getCurPos(deserializer);
		const int bytesForByteCount = finalByteCount - initialByteCount;
		if (self->bytecount != bytesForByteCount) return ProtocolError_BYTECOUNT_MISMATCH;
	}


	return 0;
}
