// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.


#pragma once

#ifndef NO_Z9LOCKIO

#include <stdint.h>

namespace z9 { namespace drivers { namespace z9lockio { namespace protocol {

/**
 * Enum: {@link LockCredTechnology.h}.
 */
enum LockCredTechnology
{
	LockCredTechnology_ANY,
	LockCredTechnology_PROX_ANY,
	LockCredTechnology_BLUETOOTH_ANY,
	LockCredTechnology_NFC_ANY,
	LockCredTechnology_DESFIRE_ANY,
	LockCredTechnology_ICLASS_ANY,
	LockCredTechnology_BLUETOOTH_WAVELYNX,
	LockCredTechnology_BLUETOOTH_Z9_WAVELYNX,
	LockCredTechnology_NFC_GOOGLE,
	LockCredTechnology_NFC_APPLE,
	LockCredTechnology_NFC_WAVELYNX,
	LockCredTechnology_DESFIRE_LEAF,
	LockCredTechnology_DESFIRE_UID,
	LockCredTechnology_ICLASS_FULL,
	LockCredTechnology_ICLASS_UID,
};



/**
 * Enum: {@link LockMode.h}.
 */
enum LockMode
{
	LockMode_NONE,
	LockMode_STATIC_STATE_UNLOCKED,
	LockMode_STATIC_STATE_LOCKED,
	LockMode_CARD_ONLY,
	LockMode_CARD_AND_CONFIRMING_PIN,
	LockMode_UNIQUE_PIN_ONLY,
	LockMode_CARD_ONLY_OR_UNIQUE_PIN,
	LockMode_EMERGENCY_STATIC_STATE_UNLOCKED,
	LockMode_EMERGENCY_STATIC_STATE_LOCKED,
	LockMode_FIRST_CRED_UNLOCK_CARD_ONLY,
	LockMode_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN,
	LockMode_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY,
	LockMode_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN,
};



/**
 * Enum: {@link LockEvtCode.h}.
 */
enum LockEvtCode
{
	LockEvtCode_NONE,
	LockEvtCode_STARTUP,
	LockEvtCode_DOOR_ACCESS_GRANTED,
	LockEvtCode_DOOR_ACCESS_DENIED,
	LockEvtCode_DOOR_ACCESS_DENIED_INACTIVE,
	LockEvtCode_DOOR_ACCESS_DENIED_NOT_EFFECTIVE,
	LockEvtCode_DOOR_ACCESS_DENIED_EXPIRED,
	LockEvtCode_DOOR_ACCESS_DENIED_OUTSIDE_SCHED,
	LockEvtCode_DOOR_ACCESS_DENIED_UNKNOWN_CRED_NUM,
	LockEvtCode_DOOR_ACCESS_DENIED_UNKNOWN_CRED_UNIQUE_PIN,
	LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_STATIC_LOCKED,
	LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_CARD,
	LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_UNIQUE_PIN,
	LockEvtCode_DOOR_ACCESS_DENIED_NO_CONFIRMING_PIN_FOR_CRED,
	LockEvtCode_DOOR_ACCESS_DENIED_INCORRECT_CONFIRMING_PIN,
	LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_EMERGENCY_STATIC_LOCKED,
	LockEvtCode_DOOR_ACCESS_DENIED_DEADBOLT,
	LockEvtCode_DOOR_ACCESS_DENIED_NO_PIN_PRESENTED,
	LockEvtCode_DOOR_ACCESS_DENIED_INCOMPLETE,
	LockEvtCode_DOOR_ACCESS_DENIED_DOOR_PRIVACY,
	LockEvtCode_DOOR_FORCED,
	LockEvtCode_DOOR_NOT_FORCED,
	LockEvtCode_DOOR_HELD,
	LockEvtCode_DOOR_NOT_HELD,
	LockEvtCode_DOOR_OPENED,
	LockEvtCode_DOOR_CLOSED,
	LockEvtCode_DOOR_LOCKED,
	LockEvtCode_DOOR_UNLOCKED,
	LockEvtCode_DOOR_MODE_STATIC_STATE_UNLOCKED,
	LockEvtCode_DOOR_MODE_STATIC_STATE_LOCKED,
	LockEvtCode_DOOR_MODE_CARD_ONLY,
	LockEvtCode_DOOR_MODE_CARD_AND_CONFIRMING_PIN,
	LockEvtCode_DOOR_MODE_UNIQUE_PIN_ONLY,
	LockEvtCode_DOOR_MODE_CARD_ONLY_OR_UNIQUE_PIN,
	LockEvtCode_DOOR_MODE_EMERGENCY_STATIC_STATE_UNLOCKED,
	LockEvtCode_DOOR_MODE_EMERGENCY_STATIC_STATE_LOCKED,
	LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY,
	LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN,
	LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY,
	LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN,
	LockEvtCode_EXIT_REQUESTED,
	LockEvtCode_MOMENTARY_UNLOCK,
	LockEvtCode_DOOR_FORCED_UNMASKED,
	LockEvtCode_DOOR_FORCED_MASKED,
	LockEvtCode_DOOR_HELD_UNMASKED,
	LockEvtCode_DOOR_HELD_MASKED,
	LockEvtCode_KEY_OVERRIDE,
	LockEvtCode_DEADBOLT_ACTIVE,
	LockEvtCode_DEADBOLT_INACTIVE,
	LockEvtCode_DOOR_HELD_WARNING,
	LockEvtCode_BATTERY_OK,
	LockEvtCode_BATTERY_LOW,
	LockEvtCode_BATTERY_CRITICAL,
	LockEvtCode_BATTERY_FAIL,
	LockEvtCode_BATTERY_LEVEL,
	LockEvtCode_TAMPER_NORMAL,
	LockEvtCode_TAMPER,
	LockEvtCode_SCHED_ACTIVE,
	LockEvtCode_SCHED_INACTIVE,
	LockEvtCode_DOOR_LOCAL_LOCKED,
	LockEvtCode_DOOR_LOCAL_UNLOCKED,
	LockEvtCode_DOOR_LOCAL_ACCESS_CONTROLLED,
	LockEvtCode_DOOR_LOCAL_PRIVACY,
	LockEvtCode_DOOR_LOCAL_ESCAPE_AND_RETURN,
	LockEvtCode_EXIT_REQUEST_DENIED,
	LockEvtCode_MOMENTARY_UNLOCK_DENIED,
	LockEvtCode_DOOR_LOCAL_NOT_PRIVACY,
	LockEvtCode_IPB_PRESSED,
};



/**
 * Enum: {@link LockDevActionType.h}.
 */
enum LockDevActionType
{
	LockDevActionType_NONE,
	LockDevActionType_MOMENTARY_UNLOCK,
	LockDevActionType_RESET_LOCK_MODE,
	LockDevActionType_SET_LOCK_MODE_STATIC_STATE_UNLOCKED,
	LockDevActionType_SET_LOCK_MODE_STATIC_STATE_LOCKED,
	LockDevActionType_SET_LOCK_MODE_CARD_ONLY,
	LockDevActionType_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN,
	LockDevActionType_SET_LOCK_MODE_UNIQUE_PIN_ONLY,
	LockDevActionType_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN,
	LockDevActionType_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED,
	LockDevActionType_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED,
	LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY,
	LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN,
	LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY,
	LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN,
};



/**
 * Enum: {@link LockFunction.h}.
 */
enum LockFunction
{
	LockFunction_NONE,
	LockFunction_OFFICE,
	LockFunction_APARTMENT,
	LockFunction_CLASSROOM,
	LockFunction_PRIVACY,
};



/**
 * Enum: {@link LockHostGrantFallbackMode.h}.
 */
enum LockHostGrantFallbackMode
{
	LockHostGrantFallbackMode_NONE,
	LockHostGrantFallbackMode_DENY,
	LockHostGrantFallbackMode_LOCAL_DECISION,
};



/**
 * Enum: {@link LockHostGrantInitiationMode.h}.
 */
enum LockHostGrantInitiationMode
{
	LockHostGrantInitiationMode_NEVER,
	LockHostGrantInitiationMode_UNKNOWN_CRED,
	LockHostGrantInitiationMode_ALWAYS,
};



/**
 * Enum: {@link LockIdentificationType.h}.
 */
enum LockIdentificationType
{
	LockIdentificationType_NONE,
	LockIdentificationType_LOCK,
	LockIdentificationType_HUB_CONTROLLER,
	LockIdentificationType_MOBILE,
	LockIdentificationType_AUTHORITATIVE_SOURCE,
};



/**
 * Enum: {@link LockFileCategory.h}.
 */
enum LockFileCategory
{
	LockFileCategory_NONE,
	LockFileCategory_SOFTWARE_UPDATE,
	LockFileCategory_KEYS,
	LockFileCategory_LICENSE,
	LockFileCategory_DIAGNOSTICS,
};



/**
 * Enum: {@link LockFileIdentifier.h}.
 */
enum LockFileIdentifier
{
	LockFileIdentifier_NONE,
	LockFileIdentifier_DEFAULT,
};



/**
 * Enum: {@link LockHostGrantReqType.h}.
 */
enum LockHostGrantReqType
{
	LockHostGrantReqType_NONE,
	LockHostGrantReqType_CRED_READ,
};



/**
 * Enum: {@link LockPolicyPriority.h}.
 */
enum LockPolicyPriority
{
	LockPolicyPriority_DEFAULT,
	LockPolicyPriority_SCHEDULE,
	LockPolicyPriority_POLICY_OVERRIDE,
	LockPolicyPriority_MANUAL_OVERRIDE,
	LockPolicyPriority_EMERGENCY,
};



/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockDate
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDate
{
public:
	static const int MAX_SERIALIZED_LEN = 4;
	uint16_t year;
	uint8_t month;
	uint8_t day;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockTimeOfDay_ToMinute
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockTimeOfDay_ToMinute
{
public:
	static const int MAX_SERIALIZED_LEN = 2;
	uint8_t hour;
	uint8_t minute;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockTimeOfDay_ToQuarterHour
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockTimeOfDay_ToQuarterHour
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	uint8_t quarterHour;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockTimeOfDay_ToSecond
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockTimeOfDay_ToSecond
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockDateTime_ToMinute
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDateTime_ToMinute
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockDateTime_ToSecond
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDateTime_ToSecond
{
public:
	static const int MAX_SERIALIZED_LEN = 7;
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtContent
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtContent
{
public:
	int8_t contentType;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtDelta
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtDelta
{
public:
	static const int MAX_SERIALIZED_LEN = 2;
	bool suppress;
	bool priority;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtModifiers
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtModifiers
{
public:
	static const int MAX_SERIALIZED_LEN = 7;
	bool priority;
	bool hostGrant;
	bool mobileGrant;
	bool usedCard;
	bool usedPin;
	bool emergency;
	bool doublePresentation;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockDstTransition
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDstTransition
{
public:
	static const int MAX_SERIALIZED_LEN = 4;
	uint8_t month;
	uint8_t nth;
	uint8_t dayOfWeek;
	uint8_t hour;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.cred.LockAccessModifiers
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockAccessModifiers
{
public:
	static const int MAX_SERIALIZED_LEN = 8;
	bool extDoorTime;
	bool administrator;
	bool privacyExempt;
	bool staticStateLockedExempt;
	bool emergencyStaticStateLockedExempt;
	bool emergency;
	bool firstCredUnlock;
	bool pinUnique;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.cred.LockCredActions
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockCredActions
{
public:
	static const int MAX_SERIALIZED_LEN = 9;
	bool access;
	bool setLockMode_STATIC_STATE_UNLOCKED;
	bool setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED;
	bool setLockMode_STATIC_STATE_LOCKED;
	bool setLockMode_EMERGENCY_STATIC_STATE_LOCKED;
	bool cancelLockMode_STATIC_STATE_UNLOCKED;
	bool cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED;
	bool cancelLockMode_STATIC_STATE_LOCKED;
	bool cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.LockDevActionPermissions
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDevActionPermissions
{
public:
	static const int MAX_SERIALIZED_LEN = 14;
	bool allow_MOMENTARY_UNLOCK;
	bool allow_RESET_LOCK_MODE;
	bool allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED;
	bool allow_SET_LOCK_MODE_STATIC_STATE_LOCKED;
	bool allow_SET_LOCK_MODE_CARD_ONLY;
	bool allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN;
	bool allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY;
	bool allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN;
	bool allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED;
	bool allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.cred.LockCredTechnologies
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockCredTechnologies
{
public:
	static const int MAX_SERIALIZED_LEN = 13;
	bool enable_PROX;
	bool enable_BLUETOOTH_ANY;
	bool enable_NFC_ANY;
	bool enable_DESFIRE_ANY;
	bool enable_ICLASS_ANY;
	bool enable_BLUETOOTH_WAVELYNX;
	bool enable_BLUETOOTH_Z9_WAVELYNX;
	bool enable_NFC_GOOGLE;
	bool enable_NFC_APPLE;
	bool enable_DESFIRE_LEAF;
	bool enable_DESFIRE_UID;
	bool enable_ICLASS_FULL;
	bool enable_ICLASS_UID;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockFunctionModifiers
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockFunctionModifiers
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	uint8_t ipbUnlockDuration;
	uint16_t escapeAndReturnDuration;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPacketContent
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPacketContent
{
public:
	int8_t contentType;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.LockPaginationReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPaginationReq
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	int32_t aboveIndex;
	uint16_t pageSize;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtContent_None
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtContent_None : public LockEvtContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 0;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtContent_BatteryLevel
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtContent_BatteryLevel : public LockEvtContent
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	static const int8_t DISCRIMINATOR = 3;
	uint16_t batteryLevel;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtContent_CredUnid
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtContent_CredUnid : public LockEvtContent
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	static const int8_t DISCRIMINATOR = 1;
	LockCredTechnology credTechnology;
	uint32_t credUnid;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtContent_SchedOid
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtContent_SchedOid : public LockEvtContent
{
public:
	static const int MAX_SERIALIZED_LEN = 2;
	static const int8_t DISCRIMINATOR = 2;
	uint8_t schedOid;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvt
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvt
{
public:
	static const int MAX_SERIALIZED_LEN = 21;
	LockDateTime_ToSecond dateTime;
	LockEvtCode evtCode;
	LockEvtModifiers modifiers;
	union
	{
		LockEvtContent_None uLockEvtContent_None;
		LockEvtContent_CredUnid uLockEvtContent_CredUnid;
		LockEvtContent_SchedOid uLockEvtContent_SchedOid;
		LockEvtContent_BatteryLevel uLockEvtContent_BatteryLevel;
	} content;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.LockStatus
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockStatus
{
public:
	static const int MAX_SERIALIZED_LEN = 12;
	LockMode mode;
	bool tamper;
	bool batteryLow;
	bool batteryCritical;
	bool unlocked;
	bool open;
	bool forced;
	bool held;
	bool deadboltExtended;
	bool privacy;
	int16_t batteryLevel;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockTimeZone
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockTimeZone
{
public:
	static const int MAX_SERIALIZED_LEN = 12;
	int16_t standardOffset;
	int16_t dstOffset;
	LockDstTransition standardTransition;
	LockDstTransition dstTransition;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.cred.LockCred
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockCred
{
public:
	static const int MAX_SERIALIZED_LEN = 77;
	uint32_t unid;
	LockDate effective;
	LockDate expires;
	LockCredTechnology technology;
	LockAccessModifiers accessModifiers;
	LockCredActions presentationActions;
	LockCredActions doublePresentationActions;
	LockDevActionPermissions explicitActionPermissions;
	int8_t trimBitsInLastCredByte;
	uint8_t numCredBytes;
	uint8_t credBytes[16];
	uint8_t pinDigitNybbles[4];
	uint8_t schedMaskBytes[2];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtPolicy
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtPolicy
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	LockEvtCode evtCode;
	LockEvtDelta evtDelta;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockHol
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockHol
{
public:
	static const int MAX_SERIALIZED_LEN = 13;
	LockDateTime_ToMinute start;
	LockDateTime_ToMinute stop;
	uint8_t holTypes;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockSchedElement
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockSchedElement
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	LockTimeOfDay_ToQuarterHour start;
	LockTimeOfDay_ToQuarterHour stop;
	uint8_t plusDays;
	int8_t daysOfWeek;
	uint8_t holTypes;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockPolicyAssertion
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPolicyAssertion
{
public:
	static const int MAX_SERIALIZED_LEN = 7;
	LockMode mode;
	bool setDoorForcedMasking;
	bool doorForcedMasking;
	bool setDoorHeldMasking;
	bool doorHeldMasking;
	bool setPrivacy;
	bool privacy;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockSchedElementPolicy
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockSchedElementPolicy
{
public:
	static const int MAX_SERIALIZED_LEN = 7;
	LockPolicyAssertion assertion;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockSchedPolicy
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockSchedPolicy
{
public:
	static const int MAX_SERIALIZED_LEN = 59;
	uint8_t schedOid;
	LockDevActionType action;
	int8_t numElements;
	LockSchedElementPolicy elements[8];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockSched
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockSched
{
public:
	static const int MAX_SERIALIZED_LEN = 57;
	uint32_t unid;
	LockDateTime_ToMinute effective;
	LockDateTime_ToMinute expires;
	int8_t numElements;
	LockSchedElement elements[8];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockHostGrantConfig
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockHostGrantConfig
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	LockHostGrantInitiationMode initiationMode;
	uint8_t timeout;
	LockHostGrantFallbackMode fallbackMode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.config.LockConfig
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockConfig
{
public:
	static const int MAX_SERIALIZED_LEN = 137;
	LockCredTechnologies credTechnologies;
	LockFunction function;
	LockFunctionModifiers functionModifiers;
	uint8_t strikeTime;
	uint8_t extendedStrikeTime;
	uint8_t heldTime;
	uint8_t extendedHeldTime;
	bool defaultDoorForcedMasking;
	bool defaultDoorHeldMasking;
	LockMode defaultLockMode;
	LockHostGrantConfig hostGrantConfig;
	uint8_t maxPinLength;
	LockTimeZone timeZone;
	uint8_t numEvtPolicy;
	LockEvtPolicy evtPolicies[32];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtIdentifier
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtIdentifier
{
public:
	static const int MAX_SERIALIZED_LEN = 8;
	LockDateTime_ToSecond dateTime;
	LockEvtCode evtCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.evt.LockEvtIdentifierRange
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtIdentifierRange
{
public:
	static const int MAX_SERIALIZED_LEN = 16;
	LockEvtIdentifier start;
	LockEvtIdentifier stop;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockIdentification
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockIdentification : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 17;
	static const int8_t DISCRIMINATOR = 0;
	uint8_t protocolVersionMajor;
	uint8_t protocolVersionMinor;
	LockIdentificationType type;
	uint64_t id;
	uint8_t model;
	uint8_t brand;
	uint8_t firmwareVersionMajor;
	uint8_t firmwareVersionMinor;
	bool licensed;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockIdentificationResult
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockIdentificationResult : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	static const int8_t DISCRIMINATOR = 1;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbChange_Config
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbChange_Config : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 147;
	static const int8_t DISCRIMINATOR = 2;
	int64_t requestId;
	int8_t updateConfigPresent;
	LockConfig updateConfig[1];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbChangeResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbChangeResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 11;
	static const int8_t DISCRIMINATOR = 3;
	int64_t requestId;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockEvtControl
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtControl : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 19;
	static const int8_t DISCRIMINATOR = 4;
	bool priority;
	bool sendOneBatch;
	LockEvtIdentifierRange consume;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockEvtBatch
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockEvtBatch : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 675;
	static const int8_t DISCRIMINATOR = 5;
	bool priority;
	uint8_t evtCount;
	LockEvt evt[32];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDevStateRecordControl
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDevStateRecordControl : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 6;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDevStateRecord
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDevStateRecord : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 13;
	static const int8_t DISCRIMINATOR = 7;
	LockStatus status;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.datetime.LockDateTimeConfig
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDateTimeConfig
{
public:
	static const int MAX_SERIALIZED_LEN = 20;
	LockDateTime_ToSecond dateTime;
	bool timeZonePresent;
	LockTimeZone timeZone;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockGetTimeReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockGetTimeReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 8;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockGetTimeResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockGetTimeResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 21;
	static const int8_t DISCRIMINATOR = 9;
	LockDateTimeConfig dateTimeConfig;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockSetTimeReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockSetTimeReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 21;
	static const int8_t DISCRIMINATOR = 10;
	LockDateTimeConfig dateTimeConfig;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockSetTimeResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockSetTimeResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 3;
	static const int8_t DISCRIMINATOR = 11;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPullFileChunkReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPullFileChunkReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 15;
	static const int8_t DISCRIMINATOR = 14;
	uint16_t requestId;
	LockFileCategory category;
	LockFileIdentifier id;
	uint64_t offset;
	uint16_t maxLength;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPullFileChunkResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPullFileChunkResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 808;
	static const int8_t DISCRIMINATOR = 15;
	uint16_t requestId;
	int16_t errorCode;
	bool eof;
	int16_t bytesCount;
	uint8_t bytes[800];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPushFileChunkReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPushFileChunkReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 816;
	static const int8_t DISCRIMINATOR = 12;
	uint16_t requestId;
	LockFileCategory category;
	LockFileIdentifier id;
	uint64_t offset;
	bool eof;
	int16_t bytesCount;
	uint8_t bytes[800];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPushFileChunkResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPushFileChunkResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 13;
	uint16_t requestId;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockUpgradeReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockUpgradeReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	static const int8_t DISCRIMINATOR = 16;
	uint16_t requestId;
	LockFileIdentifier fileId;
	uint16_t rebootDelay;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockUpgradeResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockUpgradeResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 17;
	uint16_t requestId;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbQuery
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbQuery : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 14;
	static const int8_t DISCRIMINATOR = 18;
	int16_t requestId;
	bool queryConfig;
	bool queryHol;
	bool querySched;
	bool querySchedPolicy;
	bool queryCred;
	LockPaginationReq paginationCred;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbQueryResp_Config
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbQueryResp_Config : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 143;
	static const int8_t DISCRIMINATOR = 19;
	int16_t requestId;
	int16_t errorCode;
	int8_t configPresent;
	LockConfig config[1];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockHostGrantReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockHostGrantReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 83;
	static const int8_t DISCRIMINATOR = 20;
	int16_t requestId;
	LockHostGrantReqType type;
	LockMode lockMode;
	bool privacy;
	LockCred rawCred;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockHostGrantResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockHostGrantResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 83;
	static const int8_t DISCRIMINATOR = 21;
	int16_t requestId;
	int16_t errorCode;
	LockCred dbCred;
	LockEvtCode evtCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDevActionReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDevActionReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 7;
	static const int8_t DISCRIMINATOR = 22;
	int16_t requestId;
	LockDevActionType actionType;
	int16_t durationSecs;
	LockPolicyPriority policyPriority;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDevActionResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDevActionResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 23;
	int16_t requestId;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPolicyAssertionReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPolicyAssertionReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 13;
	static const int8_t DISCRIMINATOR = 24;
	int16_t requestId;
	LockPolicyPriority priority;
	bool state;
	bool temporary;
	LockPolicyAssertion assertion;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPolicyAssertionResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPolicyAssertionResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 5;
	static const int8_t DISCRIMINATOR = 25;
	int16_t requestId;
	int16_t errorCode;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockConnectionTermination
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockConnectionTermination : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1;
	static const int8_t DISCRIMINATOR = 26;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbChange_Hol
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbChange_Hol : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 426;
	static const int8_t DISCRIMINATOR = 27;
	int64_t requestId;
	uint8_t numHol;
	LockHol hol[32];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbChange_Sched
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbChange_Sched : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 865;
	static const int8_t DISCRIMINATOR = 28;
	int64_t requestId;
	uint8_t numSched;
	LockSched sched[15];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbChange_SchedPolicy
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbChange_SchedPolicy : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 482;
	static const int8_t DISCRIMINATOR = 29;
	int64_t requestId;
	uint8_t numSchedPolicy;
	LockSchedPolicy schedPolicy[8];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbChange_Cred
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbChange_Cred : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1243;
	static const int8_t DISCRIMINATOR = 30;
	int64_t requestId;
	bool deleteAllCred;
	uint8_t numUpsertOrDeleteCred;
	LockCred upsertOrDeleteCred[16];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbQueryResp_Hol
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbQueryResp_Hol : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 838;
	static const int8_t DISCRIMINATOR = 31;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numHol;
	LockHol hol[64];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbQueryResp_Sched
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbQueryResp_Sched : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 861;
	static const int8_t DISCRIMINATOR = 32;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numSched;
	LockSched sched[15];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbQueryResp_SchedPolicy
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbQueryResp_SchedPolicy : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 478;
	static const int8_t DISCRIMINATOR = 33;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numSchedPolicy;
	LockSchedPolicy schedPolicy[8];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockDbQueryResp_Cred
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockDbQueryResp_Cred : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1238;
	static const int8_t DISCRIMINATOR = 34;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numCred;
	LockCred cred[16];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockCredAuthorization
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockCredAuthorization : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 172;
	static const int8_t DISCRIMINATOR = 35;
	uint64_t mobileId;
	uint64_t lockId;
	LockCred cred;
	uint8_t numSchedUnids;
	uint32_t schedUnids[15];
	int8_t numSharedSecretBytes;
	uint8_t sharedSecretBytes[16];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockAccessReq
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockAccessReq : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 11;
	static const int8_t DISCRIMINATOR = 37;
	int16_t requestId;
	uint64_t mobileId;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockAccessResp
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockAccessResp : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 6;
	static const int8_t DISCRIMINATOR = 38;
	int16_t requestId;
	int16_t errorCode;
	bool granted;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPublicKeyExchange
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPublicKeyExchange : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 67;
	static const int8_t DISCRIMINATOR = 41;
	int8_t numPublicKeyBytes;
	uint8_t publicKeyBytes[65];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockMobileBleChallengeNonce
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockMobileBleChallengeNonce : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 18;
	static const int8_t DISCRIMINATOR = 43;
	int8_t numNonceBytes;
	uint8_t nonceBytes[16];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.bundle.LockBundleHeader
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockBundleHeader : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 37;
	static const int8_t DISCRIMINATOR = 40;
	LockIdentificationType origin;
	LockIdentificationType intermediary;
	LockIdentificationType destination;
	uint64_t originId;
	uint64_t intermediaryId;
	uint64_t destinationId;
	LockDateTime_ToSecond expires;
	bool opaque;
	int8_t packetCount;

};


/**
 * Auto-generated from Java class: z9.lock.protocol.bundle.LockOpaqueContent
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockOpaqueContent : public LockPacketContent
{
public:
	static const int MAX_SERIALIZED_LEN = 1026;
	static const int8_t DISCRIMINATOR = 42;
	int16_t numOpaqueBytes;
	uint8_t opaqueBytes[1023];

};


/**
 * Auto-generated from Java class: z9.lock.protocol.packet.LockPacket
 *
 * See the Javadoc for more information.
 *
 * @author Z9 Security (code generator) 
 */
class LockPacket
{
public:
	static const int MAX_SERIALIZED_LEN = 1247;
	static const int16_t headerBytes = 31289;
	int16_t bytecount;
	union
	{
		LockIdentification uLockIdentification;
		LockIdentificationResult uLockIdentificationResult;
		LockDbChange_Config uLockDbChange_Config;
		LockDbChangeResp uLockDbChangeResp;
		LockEvtControl uLockEvtControl;
		LockEvtBatch uLockEvtBatch;
		LockDevStateRecordControl uLockDevStateRecordControl;
		LockDevStateRecord uLockDevStateRecord;
		LockGetTimeReq uLockGetTimeReq;
		LockGetTimeResp uLockGetTimeResp;
		LockSetTimeReq uLockSetTimeReq;
		LockSetTimeResp uLockSetTimeResp;
		LockPushFileChunkReq uLockPushFileChunkReq;
		LockPushFileChunkResp uLockPushFileChunkResp;
		LockPullFileChunkReq uLockPullFileChunkReq;
		LockPullFileChunkResp uLockPullFileChunkResp;
		LockUpgradeReq uLockUpgradeReq;
		LockUpgradeResp uLockUpgradeResp;
		LockDbQuery uLockDbQuery;
		LockDbQueryResp_Config uLockDbQueryResp_Config;
		LockHostGrantReq uLockHostGrantReq;
		LockHostGrantResp uLockHostGrantResp;
		LockDevActionReq uLockDevActionReq;
		LockDevActionResp uLockDevActionResp;
		LockPolicyAssertionReq uLockPolicyAssertionReq;
		LockPolicyAssertionResp uLockPolicyAssertionResp;
		LockConnectionTermination uLockConnectionTermination;
		LockDbChange_Hol uLockDbChange_Hol;
		LockDbChange_Sched uLockDbChange_Sched;
		LockDbChange_SchedPolicy uLockDbChange_SchedPolicy;
		LockDbChange_Cred uLockDbChange_Cred;
		LockDbQueryResp_Hol uLockDbQueryResp_Hol;
		LockDbQueryResp_Sched uLockDbQueryResp_Sched;
		LockDbQueryResp_SchedPolicy uLockDbQueryResp_SchedPolicy;
		LockDbQueryResp_Cred uLockDbQueryResp_Cred;
		LockCredAuthorization uLockCredAuthorization;
		LockAccessReq uLockAccessReq;
		LockAccessResp uLockAccessResp;
		LockBundleHeader uLockBundleHeader;
		LockPublicKeyExchange uLockPublicKeyExchange;
		LockOpaqueContent uLockOpaqueContent;
		LockMobileBleChallengeNonce uLockMobileBleChallengeNonce;
	} content;

};

}}}}
#endif // #ifndef NO_Z9LOCKIO
