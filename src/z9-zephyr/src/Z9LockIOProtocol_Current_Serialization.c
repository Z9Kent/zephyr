/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9LockIOProtocol_Current_Serialization.c
 * @author Z9 Security
 */

#include "Z9LockIOProtocol_Current_Serialization.h"
#include "BasicSerializer.h"
#include "BasicDeserializer.h"
#include "ProtocolError.h"


int LockCredTechnology_serialize(enum LockCredTechnology *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockCredTechnology_deserialize(enum LockCredTechnology *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockCredTechnology) charValue;
	return 0;
}

int LockMode_serialize(enum LockMode *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockMode_deserialize(enum LockMode *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockMode) charValue;
	return 0;
}

int LockEvtCode_serialize(enum LockEvtCode *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockEvtCode_deserialize(enum LockEvtCode *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockEvtCode) charValue;
	return 0;
}

int LockDevActionType_serialize(enum LockDevActionType *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockDevActionType_deserialize(enum LockDevActionType *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockDevActionType) charValue;
	return 0;
}

int LockFunction_serialize(enum LockFunction *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockFunction_deserialize(enum LockFunction *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockFunction) charValue;
	return 0;
}

int LockHostGrantFallbackMode_serialize(enum LockHostGrantFallbackMode *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockHostGrantFallbackMode_deserialize(enum LockHostGrantFallbackMode *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockHostGrantFallbackMode) charValue;
	return 0;
}

int LockHostGrantInitiationMode_serialize(enum LockHostGrantInitiationMode *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockHostGrantInitiationMode_deserialize(enum LockHostGrantInitiationMode *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockHostGrantInitiationMode) charValue;
	return 0;
}

int LockIdentificationType_serialize(enum LockIdentificationType *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockIdentificationType_deserialize(enum LockIdentificationType *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockIdentificationType) charValue;
	return 0;
}

int LockFileCategory_serialize(enum LockFileCategory *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockFileCategory_deserialize(enum LockFileCategory *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockFileCategory) charValue;
	return 0;
}

int LockFileIdentifier_serialize(enum LockFileIdentifier *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockFileIdentifier_deserialize(enum LockFileIdentifier *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockFileIdentifier) charValue;
	return 0;
}

int LockHostGrantReqType_serialize(enum LockHostGrantReqType *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockHostGrantReqType_deserialize(enum LockHostGrantReqType *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockHostGrantReqType) charValue;
	return 0;
}

int LockPolicyPriority_serialize(enum LockPolicyPriority *self, struct BasicSerializer *serializer)
{
	return BasicSerializer_writeChar(serializer, (int8_t) *self);
}

int LockPolicyPriority_deserialize(enum LockPolicyPriority *self, struct BasicDeserializer *deserializer)
{
	int result;
	int8_t charValue;
	if ((result = BasicDeserializer_readChar(deserializer, &charValue))) return result;
	*self = (enum LockPolicyPriority) charValue;
	return 0;
}

int LockDate_serialize(struct LockDate *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->year))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->day))) return result;

	return 0;
}

int LockDate_deserialize(struct LockDate *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	uint16_t _unpacked = self->year;
		if ((result = BasicDeserializer_readUnsignedShort(deserializer, &_unpacked))) return result;
		self->year = _unpacked;
	}
	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->day;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->day = _unpacked;
	}

	return 0;
}

int LockTimeOfDay_ToMinute_serialize(struct LockTimeOfDay_ToMinute *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->minute))) return result;

	return 0;
}

int LockTimeOfDay_ToMinute_deserialize(struct LockTimeOfDay_ToMinute *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}

	return 0;
}

int LockTimeOfDay_ToQuarterHour_serialize(struct LockTimeOfDay_ToQuarterHour *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->quarterHour))) return result;

	return 0;
}

int LockTimeOfDay_ToQuarterHour_deserialize(struct LockTimeOfDay_ToQuarterHour *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->quarterHour))) return result;

	return 0;
}

int LockTimeOfDay_ToSecond_serialize(struct LockTimeOfDay_ToSecond *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->minute))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->second))) return result;

	return 0;
}

int LockTimeOfDay_ToSecond_deserialize(struct LockTimeOfDay_ToSecond *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}
	{	uint8_t _unpacked = self->second;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->second = _unpacked;
	}

	return 0;
}

int LockDateTime_ToMinute_serialize(struct LockDateTime_ToMinute *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->year))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->day))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->minute))) return result;

	return 0;
}

int LockDateTime_ToMinute_deserialize(struct LockDateTime_ToMinute *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	uint16_t _unpacked = self->year;
		if ((result = BasicDeserializer_readUnsignedShort(deserializer, &_unpacked))) return result;
		self->year = _unpacked;
	}
	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->day;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->day = _unpacked;
	}
	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}

	return 0;
}

int LockDateTime_ToSecond_serialize(struct LockDateTime_ToSecond *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->year))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->day))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->hour))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->minute))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->second))) return result;

	return 0;
}

int LockDateTime_ToSecond_deserialize(struct LockDateTime_ToSecond *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	uint16_t _unpacked = self->year;
		if ((result = BasicDeserializer_readUnsignedShort(deserializer, &_unpacked))) return result;
		self->year = _unpacked;
	}
	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->day;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->day = _unpacked;
	}
	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}
	{	uint8_t _unpacked = self->minute;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->minute = _unpacked;
	}
	{	uint8_t _unpacked = self->second;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->second = _unpacked;
	}

	return 0;
}

int LockEvtContent_serialize(struct LockEvtContent *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeChar(serializer, self->contentType))) return result;

	return 0;
}

int LockEvtContent_deserialize(struct LockEvtContent *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readChar(deserializer, &self->contentType))) return result;

	return 0;
}

int LockEvtDelta_serialize(struct LockEvtDelta *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeBool(serializer, self->suppress))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->priority))) return result;

	return 0;
}

int LockEvtDelta_deserialize(struct LockEvtDelta *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	bool _unpacked = self->suppress;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->suppress = _unpacked;
	}
	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}

	return 0;
}

int LockEvtModifiers_serialize(struct LockEvtModifiers *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeBool(serializer, self->priority))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->hostGrant))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->mobileGrant))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->usedCard))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->usedPin))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->emergency))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->doublePresentation))) return result;

	return 0;
}

int LockEvtModifiers_deserialize(struct LockEvtModifiers *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}
	{	bool _unpacked = self->hostGrant;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->hostGrant = _unpacked;
	}
	{	bool _unpacked = self->mobileGrant;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->mobileGrant = _unpacked;
	}
	{	bool _unpacked = self->usedCard;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->usedCard = _unpacked;
	}
	{	bool _unpacked = self->usedPin;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->usedPin = _unpacked;
	}
	{	bool _unpacked = self->emergency;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->emergency = _unpacked;
	}
	{	bool _unpacked = self->doublePresentation;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->doublePresentation = _unpacked;
	}

	return 0;
}

int LockStatus_serialize(struct LockStatus *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockMode_serialize(&self->mode, serializer))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->tamper))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->batteryLow))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->batteryCritical))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->unlocked))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->open))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->forced))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->held))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->deadboltExtended))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->privacy))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->batteryLevel))) return result;

	return 0;
}

int LockStatus_deserialize(struct LockStatus *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockMode_deserialize(&self->mode, deserializer))) return result;
	{	bool _unpacked = self->tamper;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->tamper = _unpacked;
	}
	{	bool _unpacked = self->batteryLow;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->batteryLow = _unpacked;
	}
	{	bool _unpacked = self->batteryCritical;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->batteryCritical = _unpacked;
	}
	{	bool _unpacked = self->unlocked;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->unlocked = _unpacked;
	}
	{	bool _unpacked = self->open;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->open = _unpacked;
	}
	{	bool _unpacked = self->forced;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->forced = _unpacked;
	}
	{	bool _unpacked = self->held;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->held = _unpacked;
	}
	{	bool _unpacked = self->deadboltExtended;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->deadboltExtended = _unpacked;
	}
	{	bool _unpacked = self->privacy;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->privacy = _unpacked;
	}
	if ((result = BasicDeserializer_readShort(deserializer, &self->batteryLevel))) return result;

	return 0;
}

int LockDstTransition_serialize(struct LockDstTransition *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->month))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->nth))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->dayOfWeek))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->hour))) return result;

	return 0;
}

int LockDstTransition_deserialize(struct LockDstTransition *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	uint8_t _unpacked = self->month;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->month = _unpacked;
	}
	{	uint8_t _unpacked = self->nth;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->nth = _unpacked;
	}
	{	uint8_t _unpacked = self->dayOfWeek;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->dayOfWeek = _unpacked;
	}
	{	uint8_t _unpacked = self->hour;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->hour = _unpacked;
	}

	return 0;
}

int LockAccessModifiers_serialize(struct LockAccessModifiers *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeBool(serializer, self->extDoorTime))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->administrator))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->privacyExempt))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->staticStateLockedExempt))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->emergencyStaticStateLockedExempt))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->emergency))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->firstCredUnlock))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->pinUnique))) return result;

	return 0;
}

int LockAccessModifiers_deserialize(struct LockAccessModifiers *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	bool _unpacked = self->extDoorTime;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->extDoorTime = _unpacked;
	}
	{	bool _unpacked = self->administrator;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->administrator = _unpacked;
	}
	{	bool _unpacked = self->privacyExempt;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->privacyExempt = _unpacked;
	}
	{	bool _unpacked = self->staticStateLockedExempt;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->staticStateLockedExempt = _unpacked;
	}
	{	bool _unpacked = self->emergencyStaticStateLockedExempt;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->emergencyStaticStateLockedExempt = _unpacked;
	}
	{	bool _unpacked = self->emergency;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->emergency = _unpacked;
	}
	{	bool _unpacked = self->firstCredUnlock;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->firstCredUnlock = _unpacked;
	}
	{	bool _unpacked = self->pinUnique;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->pinUnique = _unpacked;
	}

	return 0;
}

int LockCredActions_serialize(struct LockCredActions *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeBool(serializer, self->access))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setLockMode_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setLockMode_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setLockMode_EMERGENCY_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->cancelLockMode_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->cancelLockMode_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED))) return result;

	return 0;
}

int LockCredActions_deserialize(struct LockCredActions *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	bool _unpacked = self->access;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->access = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->setLockMode_EMERGENCY_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setLockMode_EMERGENCY_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED = _unpacked;
	}

	return 0;
}

int LockDevActionPermissions_serialize(struct LockDevActionPermissions *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeBool(serializer, self->allow_MOMENTARY_UNLOCK))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_RESET_LOCK_MODE))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_CARD_ONLY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN))) return result;

	return 0;
}

int LockDevActionPermissions_deserialize(struct LockDevActionPermissions *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	bool _unpacked = self->allow_MOMENTARY_UNLOCK;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_MOMENTARY_UNLOCK = _unpacked;
	}
	{	bool _unpacked = self->allow_RESET_LOCK_MODE;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_RESET_LOCK_MODE = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_CARD_ONLY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_CARD_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY = _unpacked;
	}
	{	bool _unpacked = self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN = _unpacked;
	}

	return 0;
}

int LockCredTechnologies_serialize(struct LockCredTechnologies *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeBool(serializer, self->enable_PROX))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_BLUETOOTH_ANY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_NFC_ANY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_DESFIRE_ANY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_ICLASS_ANY))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_BLUETOOTH_WAVELYNX))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_BLUETOOTH_Z9_WAVELYNX))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_NFC_GOOGLE))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_NFC_APPLE))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_DESFIRE_LEAF))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_DESFIRE_UID))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_ICLASS_FULL))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->enable_ICLASS_UID))) return result;

	return 0;
}

int LockCredTechnologies_deserialize(struct LockCredTechnologies *self, struct BasicDeserializer *deserializer)
{

	int result;

	{	bool _unpacked = self->enable_PROX;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_PROX = _unpacked;
	}
	{	bool _unpacked = self->enable_BLUETOOTH_ANY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_BLUETOOTH_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_NFC_ANY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_NFC_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_DESFIRE_ANY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_DESFIRE_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_ICLASS_ANY;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_ICLASS_ANY = _unpacked;
	}
	{	bool _unpacked = self->enable_BLUETOOTH_WAVELYNX;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_BLUETOOTH_WAVELYNX = _unpacked;
	}
	{	bool _unpacked = self->enable_BLUETOOTH_Z9_WAVELYNX;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_BLUETOOTH_Z9_WAVELYNX = _unpacked;
	}
	{	bool _unpacked = self->enable_NFC_GOOGLE;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_NFC_GOOGLE = _unpacked;
	}
	{	bool _unpacked = self->enable_NFC_APPLE;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_NFC_APPLE = _unpacked;
	}
	{	bool _unpacked = self->enable_DESFIRE_LEAF;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_DESFIRE_LEAF = _unpacked;
	}
	{	bool _unpacked = self->enable_DESFIRE_UID;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_DESFIRE_UID = _unpacked;
	}
	{	bool _unpacked = self->enable_ICLASS_FULL;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_ICLASS_FULL = _unpacked;
	}
	{	bool _unpacked = self->enable_ICLASS_UID;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->enable_ICLASS_UID = _unpacked;
	}

	return 0;
}

int LockFunctionModifiers_serialize(struct LockFunctionModifiers *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->ipbUnlockDuration))) return result;
	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->escapeAndReturnDuration))) return result;

	return 0;
}

int LockFunctionModifiers_deserialize(struct LockFunctionModifiers *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->ipbUnlockDuration))) return result;
	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->escapeAndReturnDuration))) return result;

	return 0;
}

int LockPolicyAssertion_serialize(struct LockPolicyAssertion *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockMode_serialize(&self->mode, serializer))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setDoorForcedMasking))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->doorForcedMasking))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setDoorHeldMasking))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->doorHeldMasking))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->setPrivacy))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->privacy))) return result;

	return 0;
}

int LockPolicyAssertion_deserialize(struct LockPolicyAssertion *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockMode_deserialize(&self->mode, deserializer))) return result;
	{	bool _unpacked = self->setDoorForcedMasking;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setDoorForcedMasking = _unpacked;
	}
	{	bool _unpacked = self->doorForcedMasking;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->doorForcedMasking = _unpacked;
	}
	{	bool _unpacked = self->setDoorHeldMasking;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setDoorHeldMasking = _unpacked;
	}
	{	bool _unpacked = self->doorHeldMasking;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->doorHeldMasking = _unpacked;
	}
	{	bool _unpacked = self->setPrivacy;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->setPrivacy = _unpacked;
	}
	{	bool _unpacked = self->privacy;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->privacy = _unpacked;
	}

	return 0;
}

int LockHostGrantConfig_serialize(struct LockHostGrantConfig *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockHostGrantInitiationMode_serialize(&self->initiationMode, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->timeout))) return result;
	if ((result = LockHostGrantFallbackMode_serialize(&self->fallbackMode, serializer))) return result;

	return 0;
}

int LockHostGrantConfig_deserialize(struct LockHostGrantConfig *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockHostGrantInitiationMode_deserialize(&self->initiationMode, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->timeout))) return result;
	if ((result = LockHostGrantFallbackMode_deserialize(&self->fallbackMode, deserializer))) return result;

	return 0;
}

int LockPacketContent_serialize(struct LockPacketContent *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeChar(serializer, self->contentType))) return result;

	return 0;
}

int LockPacketContent_deserialize(struct LockPacketContent *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readChar(deserializer, &self->contentType))) return result;

	return 0;
}

int LockPaginationReq_serialize(struct LockPaginationReq *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeInt(serializer, self->aboveIndex))) return result;
	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->pageSize))) return result;

	return 0;
}

int LockPaginationReq_deserialize(struct LockPaginationReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readInt(deserializer, &self->aboveIndex))) return result;
	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->pageSize))) return result;

	return 0;
}

int LockEvtContent_None_serialize(struct LockEvtContent_None *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 0;
	if ((result = LockEvtContent_serialize(&self->base, serializer))) return result;


	return 0;
}

int LockEvtContent_None_deserialize(struct LockEvtContent_None *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 0) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockEvtContent_BatteryLevel_serialize(struct LockEvtContent_BatteryLevel *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 3;
	if ((result = LockEvtContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->batteryLevel))) return result;

	return 0;
}

int LockEvtContent_BatteryLevel_deserialize(struct LockEvtContent_BatteryLevel *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 3) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->batteryLevel))) return result;

	return 0;
}

int LockEvtContent_CredUnid_serialize(struct LockEvtContent_CredUnid *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 1;
	if ((result = LockEvtContent_serialize(&self->base, serializer))) return result;

	if ((result = LockCredTechnology_serialize(&self->credTechnology, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedInt(serializer, self->credUnid))) return result;

	return 0;
}

int LockEvtContent_CredUnid_deserialize(struct LockEvtContent_CredUnid *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 1) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockCredTechnology_deserialize(&self->credTechnology, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedInt(deserializer, &self->credUnid))) return result;

	return 0;
}

int LockEvtContent_SchedOid_serialize(struct LockEvtContent_SchedOid *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 2;
	if ((result = LockEvtContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->schedOid))) return result;

	return 0;
}

int LockEvtContent_SchedOid_deserialize(struct LockEvtContent_SchedOid *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockEvtContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 2) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->schedOid))) return result;

	return 0;
}

int LockEvt_serialize(struct LockEvt *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_serialize(&self->dateTime, serializer))) return result;
	if ((result = LockEvtCode_serialize(&self->evtCode, serializer))) return result;
	if ((result = LockEvtModifiers_serialize(&self->modifiers, serializer))) return result;
	// serialize union content:
	{
		switch (((struct LockEvtContent*) &self->content)->contentType)
		{
			case LockEvtContent_None_DISCRIMINATOR:
				result = LockEvtContent_None_serialize(&self->content.uLockEvtContent_None, serializer);
				if (result) return result;
				break;
			case LockEvtContent_CredUnid_DISCRIMINATOR:
				result = LockEvtContent_CredUnid_serialize(&self->content.uLockEvtContent_CredUnid, serializer);
				if (result) return result;
				break;
			case LockEvtContent_SchedOid_DISCRIMINATOR:
				result = LockEvtContent_SchedOid_serialize(&self->content.uLockEvtContent_SchedOid, serializer);
				if (result) return result;
				break;
			case LockEvtContent_BatteryLevel_DISCRIMINATOR:
				result = LockEvtContent_BatteryLevel_serialize(&self->content.uLockEvtContent_BatteryLevel, serializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}

	return 0;
}

int LockEvt_deserialize(struct LockEvt *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_deserialize(&self->dateTime, deserializer))) return result;
	if ((result = LockEvtCode_deserialize(&self->evtCode, deserializer))) return result;
	if ((result = LockEvtModifiers_deserialize(&self->modifiers, deserializer))) return result;
	// deserialize union content:
	{
		// peek ahead to read discriminator:
		const int posBeforeDiscriminator = BasicDeserializer_getCurPos(deserializer);
		int8_t discriminator;
		if ((result = BasicDeserializer_readChar(deserializer, &discriminator))) return result;
		if ((result = BasicDeserializer_seek(deserializer, posBeforeDiscriminator))) return result;

		switch (discriminator)
		{
			case LockEvtContent_None_DISCRIMINATOR:
				result = LockEvtContent_None_deserialize(&self->content.uLockEvtContent_None, deserializer);
				if (result) return result;
				break;
			case LockEvtContent_CredUnid_DISCRIMINATOR:
				result = LockEvtContent_CredUnid_deserialize(&self->content.uLockEvtContent_CredUnid, deserializer);
				if (result) return result;
				break;
			case LockEvtContent_SchedOid_DISCRIMINATOR:
				result = LockEvtContent_SchedOid_deserialize(&self->content.uLockEvtContent_SchedOid, deserializer);
				if (result) return result;
				break;
			case LockEvtContent_BatteryLevel_DISCRIMINATOR:
				result = LockEvtContent_BatteryLevel_deserialize(&self->content.uLockEvtContent_BatteryLevel, deserializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}

	return 0;
}

int LockTimeZone_serialize(struct LockTimeZone *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeShort(serializer, self->standardOffset))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->dstOffset))) return result;
	if ((result = LockDstTransition_serialize(&self->standardTransition, serializer))) return result;
	if ((result = LockDstTransition_serialize(&self->dstTransition, serializer))) return result;

	return 0;
}

int LockTimeZone_deserialize(struct LockTimeZone *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readShort(deserializer, &self->standardOffset))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->dstOffset))) return result;
	if ((result = LockDstTransition_deserialize(&self->standardTransition, deserializer))) return result;
	if ((result = LockDstTransition_deserialize(&self->dstTransition, deserializer))) return result;

	return 0;
}

int LockCred_serialize(struct LockCred *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedInt(serializer, self->unid))) return result;
	if ((result = LockDate_serialize(&self->effective, serializer))) return result;
	if ((result = LockDate_serialize(&self->expires, serializer))) return result;
	if ((result = LockCredTechnology_serialize(&self->technology, serializer))) return result;
	if ((result = LockAccessModifiers_serialize(&self->accessModifiers, serializer))) return result;
	if ((result = LockCredActions_serialize(&self->presentationActions, serializer))) return result;
	if ((result = LockCredActions_serialize(&self->doublePresentationActions, serializer))) return result;
	if ((result = LockDevActionPermissions_serialize(&self->explicitActionPermissions, serializer))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->trimBitsInLastCredByte))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numCredBytes))) return result;
	if (self->numCredBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCredBytes; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->credBytes[i]))) return result;
	for (i = 0; i < 4; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->pinDigitNybbles[i]))) return result;
	for (i = 0; i < 2; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->schedMaskBytes[i]))) return result;

	return 0;
}

int LockCred_deserialize(struct LockCred *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readUnsignedInt(deserializer, &self->unid))) return result;
	if ((result = LockDate_deserialize(&self->effective, deserializer))) return result;
	if ((result = LockDate_deserialize(&self->expires, deserializer))) return result;
	if ((result = LockCredTechnology_deserialize(&self->technology, deserializer))) return result;
	if ((result = LockAccessModifiers_deserialize(&self->accessModifiers, deserializer))) return result;
	if ((result = LockCredActions_deserialize(&self->presentationActions, deserializer))) return result;
	if ((result = LockCredActions_deserialize(&self->doublePresentationActions, deserializer))) return result;
	if ((result = LockDevActionPermissions_deserialize(&self->explicitActionPermissions, deserializer))) return result;
	{	int8_t _unpacked = self->trimBitsInLastCredByte;
		if ((result = BasicDeserializer_readChar(deserializer, &_unpacked))) return result;
		self->trimBitsInLastCredByte = _unpacked;
	}
	{	uint8_t _unpacked = self->numCredBytes;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->numCredBytes = _unpacked;
	}
	if (self->numCredBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCredBytes; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->credBytes[i]))) return result;
	for (i = self->numCredBytes; i < 16; ++i)
		self->credBytes[i] = 0;
	for (i = 0; i < 4; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->pinDigitNybbles[i]))) return result;
	for (i = 0; i < 2; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->schedMaskBytes[i]))) return result;

	return 0;
}

int LockEvtPolicy_serialize(struct LockEvtPolicy *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockEvtCode_serialize(&self->evtCode, serializer))) return result;
	if ((result = LockEvtDelta_serialize(&self->evtDelta, serializer))) return result;

	return 0;
}

int LockEvtPolicy_deserialize(struct LockEvtPolicy *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockEvtCode_deserialize(&self->evtCode, deserializer))) return result;
	if ((result = LockEvtDelta_deserialize(&self->evtDelta, deserializer))) return result;

	return 0;
}

int LockHol_serialize(struct LockHol *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockDateTime_ToMinute_serialize(&self->start, serializer))) return result;
	if ((result = LockDateTime_ToMinute_serialize(&self->stop, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->holTypes))) return result;

	return 0;
}

int LockHol_deserialize(struct LockHol *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockDateTime_ToMinute_deserialize(&self->start, deserializer))) return result;
	if ((result = LockDateTime_ToMinute_deserialize(&self->stop, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->holTypes))) return result;

	return 0;
}

int LockSchedElement_serialize(struct LockSchedElement *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockTimeOfDay_ToQuarterHour_serialize(&self->start, serializer))) return result;
	if ((result = LockTimeOfDay_ToQuarterHour_serialize(&self->stop, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->plusDays))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->daysOfWeek))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->holTypes))) return result;

	return 0;
}

int LockSchedElement_deserialize(struct LockSchedElement *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockTimeOfDay_ToQuarterHour_deserialize(&self->start, deserializer))) return result;
	if ((result = LockTimeOfDay_ToQuarterHour_deserialize(&self->stop, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->plusDays))) return result;
	if ((result = BasicDeserializer_readChar(deserializer, &self->daysOfWeek))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->holTypes))) return result;

	return 0;
}

int LockSchedElementPolicy_serialize(struct LockSchedElementPolicy *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockPolicyAssertion_serialize(&self->assertion, serializer))) return result;

	return 0;
}

int LockSchedElementPolicy_deserialize(struct LockSchedElementPolicy *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPolicyAssertion_deserialize(&self->assertion, deserializer))) return result;

	return 0;
}

int LockSchedPolicy_serialize(struct LockSchedPolicy *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->schedOid))) return result;
	if ((result = LockDevActionType_serialize(&self->action, serializer))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElementPolicy_serialize(&self->elements[i], serializer))) return result;

	return 0;
}

int LockSchedPolicy_deserialize(struct LockSchedPolicy *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->schedOid))) return result;
	if ((result = LockDevActionType_deserialize(&self->action, deserializer))) return result;
	if ((result = BasicDeserializer_readChar(deserializer, &self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElementPolicy_deserialize(&self->elements[i], deserializer))) return result;

	return 0;
}

int LockSched_serialize(struct LockSched *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = BasicSerializer_writeUnsignedInt(serializer, self->unid))) return result;
	if ((result = LockDateTime_ToMinute_serialize(&self->effective, serializer))) return result;
	if ((result = LockDateTime_ToMinute_serialize(&self->expires, serializer))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElement_serialize(&self->elements[i], serializer))) return result;

	return 0;
}

int LockSched_deserialize(struct LockSched *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = BasicDeserializer_readUnsignedInt(deserializer, &self->unid))) return result;
	if ((result = LockDateTime_ToMinute_deserialize(&self->effective, deserializer))) return result;
	if ((result = LockDateTime_ToMinute_deserialize(&self->expires, deserializer))) return result;
	if ((result = BasicDeserializer_readChar(deserializer, &self->numElements))) return result;
	if (self->numElements > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numElements; ++i)
		if ((result = LockSchedElement_deserialize(&self->elements[i], deserializer))) return result;

	return 0;
}

int LockConfig_serialize(struct LockConfig *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockCredTechnologies_serialize(&self->credTechnologies, serializer))) return result;
	if ((result = LockFunction_serialize(&self->function, serializer))) return result;
	if ((result = LockFunctionModifiers_serialize(&self->functionModifiers, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->strikeTime))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->extendedStrikeTime))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->heldTime))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->extendedHeldTime))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->defaultDoorForcedMasking))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->defaultDoorHeldMasking))) return result;
	if ((result = LockMode_serialize(&self->defaultLockMode, serializer))) return result;
	if ((result = LockHostGrantConfig_serialize(&self->hostGrantConfig, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->maxPinLength))) return result;
	if ((result = LockTimeZone_serialize(&self->timeZone, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numEvtPolicy))) return result;
	if (self->numEvtPolicy > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numEvtPolicy; ++i)
		if ((result = LockEvtPolicy_serialize(&self->evtPolicies[i], serializer))) return result;

	return 0;
}

int LockConfig_deserialize(struct LockConfig *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockCredTechnologies_deserialize(&self->credTechnologies, deserializer))) return result;
	if ((result = LockFunction_deserialize(&self->function, deserializer))) return result;
	if ((result = LockFunctionModifiers_deserialize(&self->functionModifiers, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->strikeTime))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->extendedStrikeTime))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->heldTime))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->extendedHeldTime))) return result;
	{	bool _unpacked = self->defaultDoorForcedMasking;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->defaultDoorForcedMasking = _unpacked;
	}
	{	bool _unpacked = self->defaultDoorHeldMasking;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->defaultDoorHeldMasking = _unpacked;
	}
	if ((result = LockMode_deserialize(&self->defaultLockMode, deserializer))) return result;
	if ((result = LockHostGrantConfig_deserialize(&self->hostGrantConfig, deserializer))) return result;
	{	uint8_t _unpacked = self->maxPinLength;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->maxPinLength = _unpacked;
	}
	if ((result = LockTimeZone_deserialize(&self->timeZone, deserializer))) return result;
	{	uint8_t _unpacked = self->numEvtPolicy;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->numEvtPolicy = _unpacked;
	}
	if (self->numEvtPolicy > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numEvtPolicy; ++i)
		if ((result = LockEvtPolicy_deserialize(&self->evtPolicies[i], deserializer))) return result;

	return 0;
}

int LockEvtIdentifier_serialize(struct LockEvtIdentifier *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_serialize(&self->dateTime, serializer))) return result;
	if ((result = LockEvtCode_serialize(&self->evtCode, serializer))) return result;

	return 0;
}

int LockEvtIdentifier_deserialize(struct LockEvtIdentifier *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_deserialize(&self->dateTime, deserializer))) return result;
	if ((result = LockEvtCode_deserialize(&self->evtCode, deserializer))) return result;

	return 0;
}

int LockEvtIdentifierRange_serialize(struct LockEvtIdentifierRange *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockEvtIdentifier_serialize(&self->start, serializer))) return result;
	if ((result = LockEvtIdentifier_serialize(&self->stop, serializer))) return result;

	return 0;
}

int LockEvtIdentifierRange_deserialize(struct LockEvtIdentifierRange *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockEvtIdentifier_deserialize(&self->start, deserializer))) return result;
	if ((result = LockEvtIdentifier_deserialize(&self->stop, deserializer))) return result;

	return 0;
}

int LockIdentification_serialize(struct LockIdentification *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 0;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->protocolVersionMajor))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->protocolVersionMinor))) return result;
	if ((result = LockIdentificationType_serialize(&self->type, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->id))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->model))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->brand))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->firmwareVersionMajor))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->firmwareVersionMinor))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->licensed))) return result;

	return 0;
}

int LockIdentification_deserialize(struct LockIdentification *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 0) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->protocolVersionMajor))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->protocolVersionMinor))) return result;
	if ((result = LockIdentificationType_deserialize(&self->type, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->id))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->model))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->brand))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->firmwareVersionMajor))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->firmwareVersionMinor))) return result;
	{	bool _unpacked = self->licensed;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->licensed = _unpacked;
	}

	return 0;
}

int LockIdentificationResult_serialize(struct LockIdentificationResult *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 1;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockIdentificationResult_deserialize(struct LockIdentificationResult *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 1) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockDbChange_Config_serialize(struct LockDbChange_Config *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 2;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->updateConfigPresent))) return result;
	if (self->updateConfigPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->updateConfigPresent; ++i)
		if ((result = LockConfig_serialize(&self->updateConfig[i], serializer))) return result;

	return 0;
}

int LockDbChange_Config_deserialize(struct LockDbChange_Config *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 2) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readChar(deserializer, &self->updateConfigPresent))) return result;
	if (self->updateConfigPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->updateConfigPresent; ++i)
		if ((result = LockConfig_deserialize(&self->updateConfig[i], deserializer))) return result;

	return 0;
}

int LockDbChangeResp_serialize(struct LockDbChangeResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 3;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockDbChangeResp_deserialize(struct LockDbChangeResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 3) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockEvtControl_serialize(struct LockEvtControl *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 4;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeBool(serializer, self->priority))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->sendOneBatch))) return result;
	if ((result = LockEvtIdentifierRange_serialize(&self->consume, serializer))) return result;

	return 0;
}

int LockEvtControl_deserialize(struct LockEvtControl *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 4) return ProtocolError_INCORRECT_DISCRIMINATOR;

	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}
	{	bool _unpacked = self->sendOneBatch;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->sendOneBatch = _unpacked;
	}
	if ((result = LockEvtIdentifierRange_deserialize(&self->consume, deserializer))) return result;

	return 0;
}

int LockEvtBatch_serialize(struct LockEvtBatch *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 5;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeBool(serializer, self->priority))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->evtCount))) return result;
	if (self->evtCount > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->evtCount; ++i)
		if ((result = LockEvt_serialize(&self->evt[i], serializer))) return result;

	return 0;
}

int LockEvtBatch_deserialize(struct LockEvtBatch *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 5) return ProtocolError_INCORRECT_DISCRIMINATOR;

	{	bool _unpacked = self->priority;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->priority = _unpacked;
	}
	{	uint8_t _unpacked = self->evtCount;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->evtCount = _unpacked;
	}
	if (self->evtCount > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->evtCount; ++i)
		if ((result = LockEvt_deserialize(&self->evt[i], deserializer))) return result;

	return 0;
}

int LockDevStateRecordControl_serialize(struct LockDevStateRecordControl *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 6;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;


	return 0;
}

int LockDevStateRecordControl_deserialize(struct LockDevStateRecordControl *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 6) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockDevStateRecord_serialize(struct LockDevStateRecord *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 7;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = LockStatus_serialize(&self->status, serializer))) return result;

	return 0;
}

int LockDevStateRecord_deserialize(struct LockDevStateRecord *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 7) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockStatus_deserialize(&self->status, deserializer))) return result;

	return 0;
}

int LockDateTimeConfig_serialize(struct LockDateTimeConfig *self, struct BasicSerializer *serializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_serialize(&self->dateTime, serializer))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->timeZonePresent))) return result;
	if ((result = LockTimeZone_serialize(&self->timeZone, serializer))) return result;

	return 0;
}

int LockDateTimeConfig_deserialize(struct LockDateTimeConfig *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockDateTime_ToSecond_deserialize(&self->dateTime, deserializer))) return result;
	{	bool _unpacked = self->timeZonePresent;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->timeZonePresent = _unpacked;
	}
	if ((result = LockTimeZone_deserialize(&self->timeZone, deserializer))) return result;

	return 0;
}

int LockGetTimeReq_serialize(struct LockGetTimeReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 8;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;


	return 0;
}

int LockGetTimeReq_deserialize(struct LockGetTimeReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 8) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockGetTimeResp_serialize(struct LockGetTimeResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 9;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = LockDateTimeConfig_serialize(&self->dateTimeConfig, serializer))) return result;

	return 0;
}

int LockGetTimeResp_deserialize(struct LockGetTimeResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 9) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockDateTimeConfig_deserialize(&self->dateTimeConfig, deserializer))) return result;

	return 0;
}

int LockSetTimeReq_serialize(struct LockSetTimeReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 10;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = LockDateTimeConfig_serialize(&self->dateTimeConfig, serializer))) return result;

	return 0;
}

int LockSetTimeReq_deserialize(struct LockSetTimeReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 10) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockDateTimeConfig_deserialize(&self->dateTimeConfig, deserializer))) return result;

	return 0;
}

int LockSetTimeResp_serialize(struct LockSetTimeResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 11;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockSetTimeResp_deserialize(struct LockSetTimeResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 11) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockPullFileChunkReq_serialize(struct LockPullFileChunkReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 14;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = LockFileCategory_serialize(&self->category, serializer))) return result;
	if ((result = LockFileIdentifier_serialize(&self->id, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->offset))) return result;
	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->maxLength))) return result;

	return 0;
}

int LockPullFileChunkReq_deserialize(struct LockPullFileChunkReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 14) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = LockFileCategory_deserialize(&self->category, deserializer))) return result;
	if ((result = LockFileIdentifier_deserialize(&self->id, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->offset))) return result;
	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->maxLength))) return result;

	return 0;
}

int LockPullFileChunkResp_serialize(struct LockPullFileChunkResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 15;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->eof))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->bytes[i]))) return result;

	return 0;
}

int LockPullFileChunkResp_deserialize(struct LockPullFileChunkResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 15) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	{	bool _unpacked = self->eof;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->eof = _unpacked;
	}
	if ((result = BasicDeserializer_readShort(deserializer, &self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->bytes[i]))) return result;
	for (i = self->bytesCount; i < 800; ++i)
		self->bytes[i] = 0;

	return 0;
}

int LockPushFileChunkReq_serialize(struct LockPushFileChunkReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 12;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = LockFileCategory_serialize(&self->category, serializer))) return result;
	if ((result = LockFileIdentifier_serialize(&self->id, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->offset))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->eof))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->bytes[i]))) return result;

	return 0;
}

int LockPushFileChunkReq_deserialize(struct LockPushFileChunkReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 12) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = LockFileCategory_deserialize(&self->category, deserializer))) return result;
	if ((result = LockFileIdentifier_deserialize(&self->id, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->offset))) return result;
	{	bool _unpacked = self->eof;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->eof = _unpacked;
	}
	if ((result = BasicDeserializer_readShort(deserializer, &self->bytesCount))) return result;
	if (self->bytesCount > 800) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->bytesCount; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->bytes[i]))) return result;
	for (i = self->bytesCount; i < 800; ++i)
		self->bytes[i] = 0;

	return 0;
}

int LockPushFileChunkResp_serialize(struct LockPushFileChunkResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 13;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockPushFileChunkResp_deserialize(struct LockPushFileChunkResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 13) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockUpgradeReq_serialize(struct LockUpgradeReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 16;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = LockFileIdentifier_serialize(&self->fileId, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->rebootDelay))) return result;

	return 0;
}

int LockUpgradeReq_deserialize(struct LockUpgradeReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 16) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = LockFileIdentifier_deserialize(&self->fileId, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->rebootDelay))) return result;

	return 0;
}

int LockUpgradeResp_serialize(struct LockUpgradeResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 17;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockUpgradeResp_deserialize(struct LockUpgradeResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 17) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockDbQuery_serialize(struct LockDbQuery *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 18;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->queryConfig))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->queryHol))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->querySched))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->querySchedPolicy))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->queryCred))) return result;
	if ((result = LockPaginationReq_serialize(&self->paginationCred, serializer))) return result;

	return 0;
}

int LockDbQuery_deserialize(struct LockDbQuery *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 18) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	{	bool _unpacked = self->queryConfig;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->queryConfig = _unpacked;
	}
	{	bool _unpacked = self->queryHol;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->queryHol = _unpacked;
	}
	{	bool _unpacked = self->querySched;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->querySched = _unpacked;
	}
	{	bool _unpacked = self->querySchedPolicy;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->querySchedPolicy = _unpacked;
	}
	{	bool _unpacked = self->queryCred;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->queryCred = _unpacked;
	}
	if ((result = LockPaginationReq_deserialize(&self->paginationCred, deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Config_serialize(struct LockDbQueryResp_Config *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 19;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->configPresent))) return result;
	if (self->configPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->configPresent; ++i)
		if ((result = LockConfig_serialize(&self->config[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Config_deserialize(struct LockDbQueryResp_Config *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 19) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_readChar(deserializer, &self->configPresent))) return result;
	if (self->configPresent > 1) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->configPresent; ++i)
		if ((result = LockConfig_deserialize(&self->config[i], deserializer))) return result;

	return 0;
}

int LockHostGrantReq_serialize(struct LockHostGrantReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 20;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = LockHostGrantReqType_serialize(&self->type, serializer))) return result;
	if ((result = LockMode_serialize(&self->lockMode, serializer))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->privacy))) return result;
	if ((result = LockCred_serialize(&self->rawCred, serializer))) return result;

	return 0;
}

int LockHostGrantReq_deserialize(struct LockHostGrantReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 20) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = LockHostGrantReqType_deserialize(&self->type, deserializer))) return result;
	if ((result = LockMode_deserialize(&self->lockMode, deserializer))) return result;
	{	bool _unpacked = self->privacy;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->privacy = _unpacked;
	}
	if ((result = LockCred_deserialize(&self->rawCred, deserializer))) return result;

	return 0;
}

int LockHostGrantResp_serialize(struct LockHostGrantResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 21;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = LockCred_serialize(&self->dbCred, serializer))) return result;
	if ((result = LockEvtCode_serialize(&self->evtCode, serializer))) return result;

	return 0;
}

int LockHostGrantResp_deserialize(struct LockHostGrantResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 21) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	if ((result = LockCred_deserialize(&self->dbCred, deserializer))) return result;
	if ((result = LockEvtCode_deserialize(&self->evtCode, deserializer))) return result;

	return 0;
}

int LockDevActionReq_serialize(struct LockDevActionReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 22;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = LockDevActionType_serialize(&self->actionType, serializer))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->durationSecs))) return result;
	if ((result = LockPolicyPriority_serialize(&self->policyPriority, serializer))) return result;

	return 0;
}

int LockDevActionReq_deserialize(struct LockDevActionReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 22) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = LockDevActionType_deserialize(&self->actionType, deserializer))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->durationSecs))) return result;
	if ((result = LockPolicyPriority_deserialize(&self->policyPriority, deserializer))) return result;

	return 0;
}

int LockDevActionResp_serialize(struct LockDevActionResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 23;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockDevActionResp_deserialize(struct LockDevActionResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 23) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockPolicyAssertionReq_serialize(struct LockPolicyAssertionReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 24;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = LockPolicyPriority_serialize(&self->priority, serializer))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->state))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->temporary))) return result;
	if ((result = LockPolicyAssertion_serialize(&self->assertion, serializer))) return result;

	return 0;
}

int LockPolicyAssertionReq_deserialize(struct LockPolicyAssertionReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 24) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = LockPolicyPriority_deserialize(&self->priority, deserializer))) return result;
	{	bool _unpacked = self->state;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->state = _unpacked;
	}
	{	bool _unpacked = self->temporary;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->temporary = _unpacked;
	}
	if ((result = LockPolicyAssertion_deserialize(&self->assertion, deserializer))) return result;

	return 0;
}

int LockPolicyAssertionResp_serialize(struct LockPolicyAssertionResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 25;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;

	return 0;
}

int LockPolicyAssertionResp_deserialize(struct LockPolicyAssertionResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 25) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;

	return 0;
}

int LockConnectionTermination_serialize(struct LockConnectionTermination *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 26;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;


	return 0;
}

int LockConnectionTermination_deserialize(struct LockConnectionTermination *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 26) return ProtocolError_INCORRECT_DISCRIMINATOR;


	return 0;
}

int LockDbChange_Hol_serialize(struct LockDbChange_Hol *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 27;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numHol))) return result;
	if (self->numHol > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_serialize(&self->hol[i], serializer))) return result;

	return 0;
}

int LockDbChange_Hol_deserialize(struct LockDbChange_Hol *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 27) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numHol))) return result;
	if (self->numHol > 32) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_deserialize(&self->hol[i], deserializer))) return result;

	return 0;
}

int LockDbChange_Sched_serialize(struct LockDbChange_Sched *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 28;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_serialize(&self->sched[i], serializer))) return result;

	return 0;
}

int LockDbChange_Sched_deserialize(struct LockDbChange_Sched *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 28) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_deserialize(&self->sched[i], deserializer))) return result;

	return 0;
}

int LockDbChange_SchedPolicy_serialize(struct LockDbChange_SchedPolicy *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 29;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_serialize(&self->schedPolicy[i], serializer))) return result;

	return 0;
}

int LockDbChange_SchedPolicy_deserialize(struct LockDbChange_SchedPolicy *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 29) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readLong(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_deserialize(&self->schedPolicy[i], deserializer))) return result;

	return 0;
}

int LockDbChange_Cred_serialize(struct LockDbChange_Cred *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 30;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeLong(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->deleteAllCred))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numUpsertOrDeleteCred))) return result;
	if (self->numUpsertOrDeleteCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numUpsertOrDeleteCred; ++i)
		if ((result = LockCred_serialize(&self->upsertOrDeleteCred[i], serializer))) return result;

	return 0;
}

int LockDbChange_Cred_deserialize(struct LockDbChange_Cred *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 30) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readLong(deserializer, &self->requestId))) return result;
	{	bool _unpacked = self->deleteAllCred;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->deleteAllCred = _unpacked;
	}
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numUpsertOrDeleteCred))) return result;
	if (self->numUpsertOrDeleteCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numUpsertOrDeleteCred; ++i)
		if ((result = LockCred_deserialize(&self->upsertOrDeleteCred[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Hol_serialize(struct LockDbQueryResp_Hol *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 31;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numHol))) return result;
	if (self->numHol > 64) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_serialize(&self->hol[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Hol_deserialize(struct LockDbQueryResp_Hol *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 31) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numHol))) return result;
	if (self->numHol > 64) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numHol; ++i)
		if ((result = LockHol_deserialize(&self->hol[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Sched_serialize(struct LockDbQueryResp_Sched *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 32;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_serialize(&self->sched[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Sched_deserialize(struct LockDbQueryResp_Sched *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 32) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numSched))) return result;
	if (self->numSched > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSched; ++i)
		if ((result = LockSched_deserialize(&self->sched[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_SchedPolicy_serialize(struct LockDbQueryResp_SchedPolicy *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 33;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_serialize(&self->schedPolicy[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_SchedPolicy_deserialize(struct LockDbQueryResp_SchedPolicy *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 33) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numSchedPolicy))) return result;
	if (self->numSchedPolicy > 8) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedPolicy; ++i)
		if ((result = LockSchedPolicy_deserialize(&self->schedPolicy[i], deserializer))) return result;

	return 0;
}

int LockDbQueryResp_Cred_serialize(struct LockDbQueryResp_Cred *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 34;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numCred))) return result;
	if (self->numCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCred; ++i)
		if ((result = LockCred_serialize(&self->cred[i], serializer))) return result;

	return 0;
}

int LockDbQueryResp_Cred_deserialize(struct LockDbQueryResp_Cred *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 34) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->numCred))) return result;
	if (self->numCred > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numCred; ++i)
		if ((result = LockCred_deserialize(&self->cred[i], deserializer))) return result;

	return 0;
}

int LockCredAuthorization_serialize(struct LockCredAuthorization *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 35;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->mobileId))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->lockId))) return result;
	if ((result = LockCred_serialize(&self->cred, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedChar(serializer, self->numSchedUnids))) return result;
	if (self->numSchedUnids > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedUnids; ++i)
		if ((result = BasicSerializer_writeUnsignedInt(serializer, self->schedUnids[i]))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->numSharedSecretBytes))) return result;
	if (self->numSharedSecretBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	for (i = 0; i < self->numSharedSecretBytes; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->sharedSecretBytes[i]))) return result;

	return 0;
}

int LockCredAuthorization_deserialize(struct LockCredAuthorization *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 35) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->mobileId))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->lockId))) return result;
	if ((result = LockCred_deserialize(&self->cred, deserializer))) return result;
	{	uint8_t _unpacked = self->numSchedUnids;
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &_unpacked))) return result;
		self->numSchedUnids = _unpacked;
	}
	if (self->numSchedUnids > 15) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numSchedUnids; ++i)
		if ((result = BasicDeserializer_readUnsignedInt(deserializer, &self->schedUnids[i]))) return result;
	for (i = self->numSchedUnids; i < 15; ++i)
		self->schedUnids[i] = 0;
	if ((result = BasicDeserializer_readChar(deserializer, &self->numSharedSecretBytes))) return result;
	if (self->numSharedSecretBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	for (i = 0; i < self->numSharedSecretBytes; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->sharedSecretBytes[i]))) return result;
	for (i = self->numSharedSecretBytes; i < 16; ++i)
		self->sharedSecretBytes[i] = 0;

	return 0;
}

int LockAccessReq_serialize(struct LockAccessReq *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 37;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->mobileId))) return result;

	return 0;
}

int LockAccessReq_deserialize(struct LockAccessReq *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 37) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->mobileId))) return result;

	return 0;
}

int LockAccessResp_serialize(struct LockAccessResp *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 38;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->requestId))) return result;
	if ((result = BasicSerializer_writeShort(serializer, self->errorCode))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->granted))) return result;

	return 0;
}

int LockAccessResp_deserialize(struct LockAccessResp *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 38) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readShort(deserializer, &self->requestId))) return result;
	if ((result = BasicDeserializer_readShort(deserializer, &self->errorCode))) return result;
	{	bool _unpacked = self->granted;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->granted = _unpacked;
	}

	return 0;
}

int LockPublicKeyExchange_serialize(struct LockPublicKeyExchange *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 41;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeChar(serializer, self->numPublicKeyBytes))) return result;
	if (self->numPublicKeyBytes > 33) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numPublicKeyBytes; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->publicKeyBytes[i]))) return result;

	return 0;
}

int LockPublicKeyExchange_deserialize(struct LockPublicKeyExchange *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 41) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readChar(deserializer, &self->numPublicKeyBytes))) return result;
	if (self->numPublicKeyBytes > 33) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numPublicKeyBytes; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->publicKeyBytes[i]))) return result;
	for (i = self->numPublicKeyBytes; i < 33; ++i)
		self->publicKeyBytes[i] = 0;

	return 0;
}

int LockMobileBleChallengeNonce_serialize(struct LockMobileBleChallengeNonce *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 43;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeChar(serializer, self->numNonceBytes))) return result;
	if (self->numNonceBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numNonceBytes; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->nonceBytes[i]))) return result;

	return 0;
}

int LockMobileBleChallengeNonce_deserialize(struct LockMobileBleChallengeNonce *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 43) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = BasicDeserializer_readChar(deserializer, &self->numNonceBytes))) return result;
	if (self->numNonceBytes > 16) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numNonceBytes; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->nonceBytes[i]))) return result;
	for (i = self->numNonceBytes; i < 16; ++i)
		self->nonceBytes[i] = 0;

	return 0;
}

int LockBundleHeader_serialize(struct LockBundleHeader *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 40;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = LockIdentificationType_serialize(&self->origin, serializer))) return result;
	if ((result = LockIdentificationType_serialize(&self->intermediary, serializer))) return result;
	if ((result = LockIdentificationType_serialize(&self->destination, serializer))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->originId))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->intermediaryId))) return result;
	if ((result = BasicSerializer_writeUnsignedLong(serializer, self->destinationId))) return result;
	if ((result = LockDateTime_ToSecond_serialize(&self->expires, serializer))) return result;
	if ((result = BasicSerializer_writeBool(serializer, self->opaque))) return result;
	if ((result = BasicSerializer_writeChar(serializer, self->packetCount))) return result;

	return 0;
}

int LockBundleHeader_deserialize(struct LockBundleHeader *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 40) return ProtocolError_INCORRECT_DISCRIMINATOR;

	if ((result = LockIdentificationType_deserialize(&self->origin, deserializer))) return result;
	if ((result = LockIdentificationType_deserialize(&self->intermediary, deserializer))) return result;
	if ((result = LockIdentificationType_deserialize(&self->destination, deserializer))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->originId))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->intermediaryId))) return result;
	if ((result = BasicDeserializer_readUnsignedLong(deserializer, &self->destinationId))) return result;
	if ((result = LockDateTime_ToSecond_deserialize(&self->expires, deserializer))) return result;
	{	bool _unpacked = self->opaque;
		if ((result = BasicDeserializer_readBool(deserializer, &_unpacked))) return result;
		self->opaque = _unpacked;
	}
	{	int8_t _unpacked = self->packetCount;
		if ((result = BasicDeserializer_readChar(deserializer, &_unpacked))) return result;
		self->packetCount = _unpacked;
	}

	return 0;
}

int LockOpaqueContent_serialize(struct LockOpaqueContent *self, struct BasicSerializer *serializer)
{

	int result;

	self->base.contentType = 42;
	if ((result = LockPacketContent_serialize(&self->base, serializer))) return result;

	if ((result = BasicSerializer_writeShort(serializer, self->numOpaqueBytes))) return result;
	if (self->numOpaqueBytes > 1023) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numOpaqueBytes; ++i)
		if ((result = BasicSerializer_writeUnsignedChar(serializer, self->opaqueBytes[i]))) return result;

	return 0;
}

int LockOpaqueContent_deserialize(struct LockOpaqueContent *self, struct BasicDeserializer *deserializer)
{

	int result;

	if ((result = LockPacketContent_deserialize(&self->base, deserializer))) return result;
	if (self->base.contentType != 42) return ProtocolError_INCORRECT_DISCRIMINATOR;

	{	int16_t _unpacked = self->numOpaqueBytes;
		if ((result = BasicDeserializer_readShort(deserializer, &_unpacked))) return result;
		self->numOpaqueBytes = _unpacked;
	}
	if (self->numOpaqueBytes > 1023) return ProtocolError_DYNAMIC_ARRAY_LEN_OUT_OF_BOUNDS;
	int i;
	for (i = 0; i < self->numOpaqueBytes; ++i)
		if ((result = BasicDeserializer_readUnsignedChar(deserializer, &self->opaqueBytes[i]))) return result;
	for (i = self->numOpaqueBytes; i < 1023; ++i)
		self->opaqueBytes[i] = 0;

	return 0;
}

int LockPacket_serialize(struct LockPacket *self, struct BasicSerializer *serializer)
{

	const int initialByteCount = BasicSerializer_getCurPos(serializer);

	int result;

	if ((result = BasicSerializer_writeShort(serializer, LockPacket_headerBytes))) return result;
	const int byteCountPos = BasicSerializer_getCurPos(serializer);

	if ((result = BasicSerializer_writeShort(serializer, self->bytecount))) return result;
	// serialize union content:
	{
		switch (((struct LockPacketContent*) &self->content)->contentType)
		{
			case LockIdentification_DISCRIMINATOR:
				result = LockIdentification_serialize(&self->content.uLockIdentification, serializer);
				if (result) return result;
				break;
			case LockIdentificationResult_DISCRIMINATOR:
				result = LockIdentificationResult_serialize(&self->content.uLockIdentificationResult, serializer);
				if (result) return result;
				break;
			case LockDbChange_Config_DISCRIMINATOR:
				result = LockDbChange_Config_serialize(&self->content.uLockDbChange_Config, serializer);
				if (result) return result;
				break;
			case LockDbChangeResp_DISCRIMINATOR:
				result = LockDbChangeResp_serialize(&self->content.uLockDbChangeResp, serializer);
				if (result) return result;
				break;
			case LockEvtControl_DISCRIMINATOR:
				result = LockEvtControl_serialize(&self->content.uLockEvtControl, serializer);
				if (result) return result;
				break;
			case LockEvtBatch_DISCRIMINATOR:
				result = LockEvtBatch_serialize(&self->content.uLockEvtBatch, serializer);
				if (result) return result;
				break;
			case LockDevStateRecordControl_DISCRIMINATOR:
				result = LockDevStateRecordControl_serialize(&self->content.uLockDevStateRecordControl, serializer);
				if (result) return result;
				break;
			case LockDevStateRecord_DISCRIMINATOR:
				result = LockDevStateRecord_serialize(&self->content.uLockDevStateRecord, serializer);
				if (result) return result;
				break;
			case LockGetTimeReq_DISCRIMINATOR:
				result = LockGetTimeReq_serialize(&self->content.uLockGetTimeReq, serializer);
				if (result) return result;
				break;
			case LockGetTimeResp_DISCRIMINATOR:
				result = LockGetTimeResp_serialize(&self->content.uLockGetTimeResp, serializer);
				if (result) return result;
				break;
			case LockSetTimeReq_DISCRIMINATOR:
				result = LockSetTimeReq_serialize(&self->content.uLockSetTimeReq, serializer);
				if (result) return result;
				break;
			case LockSetTimeResp_DISCRIMINATOR:
				result = LockSetTimeResp_serialize(&self->content.uLockSetTimeResp, serializer);
				if (result) return result;
				break;
			case LockPushFileChunkReq_DISCRIMINATOR:
				result = LockPushFileChunkReq_serialize(&self->content.uLockPushFileChunkReq, serializer);
				if (result) return result;
				break;
			case LockPushFileChunkResp_DISCRIMINATOR:
				result = LockPushFileChunkResp_serialize(&self->content.uLockPushFileChunkResp, serializer);
				if (result) return result;
				break;
			case LockPullFileChunkReq_DISCRIMINATOR:
				result = LockPullFileChunkReq_serialize(&self->content.uLockPullFileChunkReq, serializer);
				if (result) return result;
				break;
			case LockPullFileChunkResp_DISCRIMINATOR:
				result = LockPullFileChunkResp_serialize(&self->content.uLockPullFileChunkResp, serializer);
				if (result) return result;
				break;
			case LockUpgradeReq_DISCRIMINATOR:
				result = LockUpgradeReq_serialize(&self->content.uLockUpgradeReq, serializer);
				if (result) return result;
				break;
			case LockUpgradeResp_DISCRIMINATOR:
				result = LockUpgradeResp_serialize(&self->content.uLockUpgradeResp, serializer);
				if (result) return result;
				break;
			case LockDbQuery_DISCRIMINATOR:
				result = LockDbQuery_serialize(&self->content.uLockDbQuery, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Config_DISCRIMINATOR:
				result = LockDbQueryResp_Config_serialize(&self->content.uLockDbQueryResp_Config, serializer);
				if (result) return result;
				break;
			case LockHostGrantReq_DISCRIMINATOR:
				result = LockHostGrantReq_serialize(&self->content.uLockHostGrantReq, serializer);
				if (result) return result;
				break;
			case LockHostGrantResp_DISCRIMINATOR:
				result = LockHostGrantResp_serialize(&self->content.uLockHostGrantResp, serializer);
				if (result) return result;
				break;
			case LockDevActionReq_DISCRIMINATOR:
				result = LockDevActionReq_serialize(&self->content.uLockDevActionReq, serializer);
				if (result) return result;
				break;
			case LockDevActionResp_DISCRIMINATOR:
				result = LockDevActionResp_serialize(&self->content.uLockDevActionResp, serializer);
				if (result) return result;
				break;
			case LockPolicyAssertionReq_DISCRIMINATOR:
				result = LockPolicyAssertionReq_serialize(&self->content.uLockPolicyAssertionReq, serializer);
				if (result) return result;
				break;
			case LockPolicyAssertionResp_DISCRIMINATOR:
				result = LockPolicyAssertionResp_serialize(&self->content.uLockPolicyAssertionResp, serializer);
				if (result) return result;
				break;
			case LockConnectionTermination_DISCRIMINATOR:
				result = LockConnectionTermination_serialize(&self->content.uLockConnectionTermination, serializer);
				if (result) return result;
				break;
			case LockDbChange_Hol_DISCRIMINATOR:
				result = LockDbChange_Hol_serialize(&self->content.uLockDbChange_Hol, serializer);
				if (result) return result;
				break;
			case LockDbChange_Sched_DISCRIMINATOR:
				result = LockDbChange_Sched_serialize(&self->content.uLockDbChange_Sched, serializer);
				if (result) return result;
				break;
			case LockDbChange_SchedPolicy_DISCRIMINATOR:
				result = LockDbChange_SchedPolicy_serialize(&self->content.uLockDbChange_SchedPolicy, serializer);
				if (result) return result;
				break;
			case LockDbChange_Cred_DISCRIMINATOR:
				result = LockDbChange_Cred_serialize(&self->content.uLockDbChange_Cred, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Hol_DISCRIMINATOR:
				result = LockDbQueryResp_Hol_serialize(&self->content.uLockDbQueryResp_Hol, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Sched_DISCRIMINATOR:
				result = LockDbQueryResp_Sched_serialize(&self->content.uLockDbQueryResp_Sched, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_SchedPolicy_DISCRIMINATOR:
				result = LockDbQueryResp_SchedPolicy_serialize(&self->content.uLockDbQueryResp_SchedPolicy, serializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Cred_DISCRIMINATOR:
				result = LockDbQueryResp_Cred_serialize(&self->content.uLockDbQueryResp_Cred, serializer);
				if (result) return result;
				break;
			case LockCredAuthorization_DISCRIMINATOR:
				result = LockCredAuthorization_serialize(&self->content.uLockCredAuthorization, serializer);
				if (result) return result;
				break;
			case LockAccessReq_DISCRIMINATOR:
				result = LockAccessReq_serialize(&self->content.uLockAccessReq, serializer);
				if (result) return result;
				break;
			case LockAccessResp_DISCRIMINATOR:
				result = LockAccessResp_serialize(&self->content.uLockAccessResp, serializer);
				if (result) return result;
				break;
			case LockBundleHeader_DISCRIMINATOR:
				result = LockBundleHeader_serialize(&self->content.uLockBundleHeader, serializer);
				if (result) return result;
				break;
			case LockPublicKeyExchange_DISCRIMINATOR:
				result = LockPublicKeyExchange_serialize(&self->content.uLockPublicKeyExchange, serializer);
				if (result) return result;
				break;
			case LockOpaqueContent_DISCRIMINATOR:
				result = LockOpaqueContent_serialize(&self->content.uLockOpaqueContent, serializer);
				if (result) return result;
				break;
			case LockMobileBleChallengeNonce_DISCRIMINATOR:
				result = LockMobileBleChallengeNonce_serialize(&self->content.uLockMobileBleChallengeNonce, serializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}

	// Update and write bytecount:
	{
		const int finalByteCount = BasicSerializer_getCurPos(serializer);
		const int bytesForByteCount = finalByteCount - initialByteCount;
		if ((result = BasicSerializer_seek(serializer, byteCountPos))) return result;
		if ((result = BasicSerializer_writeShort(serializer, bytesForByteCount))) return result;
		self->bytecount = bytesForByteCount;
		if ((result = BasicSerializer_seek(serializer, finalByteCount))) return result;
	}

	return 0;
}

int LockPacket_deserialize(struct LockPacket *self, struct BasicDeserializer *deserializer)
{

	const int initialByteCount = BasicDeserializer_getCurPos(deserializer);

	int result;

	{
		int16_t val;
		if ((result = BasicDeserializer_readShort(deserializer, &val))) return result;
		if (val != LockPacket_headerBytes) return ProtocolError_INCORRECT_STATIC_VALUE;
	}
	if ((result = BasicDeserializer_readShort(deserializer, &self->bytecount))) return result;
	// deserialize union content:
	{
		// peek ahead to read discriminator:
		const int posBeforeDiscriminator = BasicDeserializer_getCurPos(deserializer);
		int8_t discriminator;
		if ((result = BasicDeserializer_readChar(deserializer, &discriminator))) return result;
		if ((result = BasicDeserializer_seek(deserializer, posBeforeDiscriminator))) return result;

		switch (discriminator)
		{
			case LockIdentification_DISCRIMINATOR:
				result = LockIdentification_deserialize(&self->content.uLockIdentification, deserializer);
				if (result) return result;
				break;
			case LockIdentificationResult_DISCRIMINATOR:
				result = LockIdentificationResult_deserialize(&self->content.uLockIdentificationResult, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Config_DISCRIMINATOR:
				result = LockDbChange_Config_deserialize(&self->content.uLockDbChange_Config, deserializer);
				if (result) return result;
				break;
			case LockDbChangeResp_DISCRIMINATOR:
				result = LockDbChangeResp_deserialize(&self->content.uLockDbChangeResp, deserializer);
				if (result) return result;
				break;
			case LockEvtControl_DISCRIMINATOR:
				result = LockEvtControl_deserialize(&self->content.uLockEvtControl, deserializer);
				if (result) return result;
				break;
			case LockEvtBatch_DISCRIMINATOR:
				result = LockEvtBatch_deserialize(&self->content.uLockEvtBatch, deserializer);
				if (result) return result;
				break;
			case LockDevStateRecordControl_DISCRIMINATOR:
				result = LockDevStateRecordControl_deserialize(&self->content.uLockDevStateRecordControl, deserializer);
				if (result) return result;
				break;
			case LockDevStateRecord_DISCRIMINATOR:
				result = LockDevStateRecord_deserialize(&self->content.uLockDevStateRecord, deserializer);
				if (result) return result;
				break;
			case LockGetTimeReq_DISCRIMINATOR:
				result = LockGetTimeReq_deserialize(&self->content.uLockGetTimeReq, deserializer);
				if (result) return result;
				break;
			case LockGetTimeResp_DISCRIMINATOR:
				result = LockGetTimeResp_deserialize(&self->content.uLockGetTimeResp, deserializer);
				if (result) return result;
				break;
			case LockSetTimeReq_DISCRIMINATOR:
				result = LockSetTimeReq_deserialize(&self->content.uLockSetTimeReq, deserializer);
				if (result) return result;
				break;
			case LockSetTimeResp_DISCRIMINATOR:
				result = LockSetTimeResp_deserialize(&self->content.uLockSetTimeResp, deserializer);
				if (result) return result;
				break;
			case LockPushFileChunkReq_DISCRIMINATOR:
				result = LockPushFileChunkReq_deserialize(&self->content.uLockPushFileChunkReq, deserializer);
				if (result) return result;
				break;
			case LockPushFileChunkResp_DISCRIMINATOR:
				result = LockPushFileChunkResp_deserialize(&self->content.uLockPushFileChunkResp, deserializer);
				if (result) return result;
				break;
			case LockPullFileChunkReq_DISCRIMINATOR:
				result = LockPullFileChunkReq_deserialize(&self->content.uLockPullFileChunkReq, deserializer);
				if (result) return result;
				break;
			case LockPullFileChunkResp_DISCRIMINATOR:
				result = LockPullFileChunkResp_deserialize(&self->content.uLockPullFileChunkResp, deserializer);
				if (result) return result;
				break;
			case LockUpgradeReq_DISCRIMINATOR:
				result = LockUpgradeReq_deserialize(&self->content.uLockUpgradeReq, deserializer);
				if (result) return result;
				break;
			case LockUpgradeResp_DISCRIMINATOR:
				result = LockUpgradeResp_deserialize(&self->content.uLockUpgradeResp, deserializer);
				if (result) return result;
				break;
			case LockDbQuery_DISCRIMINATOR:
				result = LockDbQuery_deserialize(&self->content.uLockDbQuery, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Config_DISCRIMINATOR:
				result = LockDbQueryResp_Config_deserialize(&self->content.uLockDbQueryResp_Config, deserializer);
				if (result) return result;
				break;
			case LockHostGrantReq_DISCRIMINATOR:
				result = LockHostGrantReq_deserialize(&self->content.uLockHostGrantReq, deserializer);
				if (result) return result;
				break;
			case LockHostGrantResp_DISCRIMINATOR:
				result = LockHostGrantResp_deserialize(&self->content.uLockHostGrantResp, deserializer);
				if (result) return result;
				break;
			case LockDevActionReq_DISCRIMINATOR:
				result = LockDevActionReq_deserialize(&self->content.uLockDevActionReq, deserializer);
				if (result) return result;
				break;
			case LockDevActionResp_DISCRIMINATOR:
				result = LockDevActionResp_deserialize(&self->content.uLockDevActionResp, deserializer);
				if (result) return result;
				break;
			case LockPolicyAssertionReq_DISCRIMINATOR:
				result = LockPolicyAssertionReq_deserialize(&self->content.uLockPolicyAssertionReq, deserializer);
				if (result) return result;
				break;
			case LockPolicyAssertionResp_DISCRIMINATOR:
				result = LockPolicyAssertionResp_deserialize(&self->content.uLockPolicyAssertionResp, deserializer);
				if (result) return result;
				break;
			case LockConnectionTermination_DISCRIMINATOR:
				result = LockConnectionTermination_deserialize(&self->content.uLockConnectionTermination, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Hol_DISCRIMINATOR:
				result = LockDbChange_Hol_deserialize(&self->content.uLockDbChange_Hol, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Sched_DISCRIMINATOR:
				result = LockDbChange_Sched_deserialize(&self->content.uLockDbChange_Sched, deserializer);
				if (result) return result;
				break;
			case LockDbChange_SchedPolicy_DISCRIMINATOR:
				result = LockDbChange_SchedPolicy_deserialize(&self->content.uLockDbChange_SchedPolicy, deserializer);
				if (result) return result;
				break;
			case LockDbChange_Cred_DISCRIMINATOR:
				result = LockDbChange_Cred_deserialize(&self->content.uLockDbChange_Cred, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Hol_DISCRIMINATOR:
				result = LockDbQueryResp_Hol_deserialize(&self->content.uLockDbQueryResp_Hol, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Sched_DISCRIMINATOR:
				result = LockDbQueryResp_Sched_deserialize(&self->content.uLockDbQueryResp_Sched, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_SchedPolicy_DISCRIMINATOR:
				result = LockDbQueryResp_SchedPolicy_deserialize(&self->content.uLockDbQueryResp_SchedPolicy, deserializer);
				if (result) return result;
				break;
			case LockDbQueryResp_Cred_DISCRIMINATOR:
				result = LockDbQueryResp_Cred_deserialize(&self->content.uLockDbQueryResp_Cred, deserializer);
				if (result) return result;
				break;
			case LockCredAuthorization_DISCRIMINATOR:
				result = LockCredAuthorization_deserialize(&self->content.uLockCredAuthorization, deserializer);
				if (result) return result;
				break;
			case LockAccessReq_DISCRIMINATOR:
				result = LockAccessReq_deserialize(&self->content.uLockAccessReq, deserializer);
				if (result) return result;
				break;
			case LockAccessResp_DISCRIMINATOR:
				result = LockAccessResp_deserialize(&self->content.uLockAccessResp, deserializer);
				if (result) return result;
				break;
			case LockBundleHeader_DISCRIMINATOR:
				result = LockBundleHeader_deserialize(&self->content.uLockBundleHeader, deserializer);
				if (result) return result;
				break;
			case LockPublicKeyExchange_DISCRIMINATOR:
				result = LockPublicKeyExchange_deserialize(&self->content.uLockPublicKeyExchange, deserializer);
				if (result) return result;
				break;
			case LockOpaqueContent_DISCRIMINATOR:
				result = LockOpaqueContent_deserialize(&self->content.uLockOpaqueContent, deserializer);
				if (result) return result;
				break;
			case LockMobileBleChallengeNonce_DISCRIMINATOR:
				result = LockMobileBleChallengeNonce_deserialize(&self->content.uLockMobileBleChallengeNonce, deserializer);
				if (result) return result;
				break;
			default:
				return ProtocolError_UNKNOWN_DISCRIMINATOR;
		}
	}
	// Check bytecount:
	{
		const int finalByteCount = BasicDeserializer_getCurPos(deserializer);
		const int bytesForByteCount = finalByteCount - initialByteCount;
		if (self->bytecount != bytesForByteCount) return ProtocolError_BYTECOUNT_MISMATCH;
	}


	return 0;
}
