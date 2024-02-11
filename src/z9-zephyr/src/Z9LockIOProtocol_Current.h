/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9LockIOProtocol_Current.h
 * @author Z9 Security
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

struct BasicSerializer;
struct BasicDeserializer;

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

#ifdef WITH_LOGGING
/**
 * Convert LockCredTechnology to a string.
 * @return "?" if unknown.
 */
const char *LockCredTechnology_toString(enum LockCredTechnology value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockMode to a string.
 * @return "?" if unknown.
 */
const char *LockMode_toString(enum LockMode value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockEvtCode to a string.
 * @return "?" if unknown.
 */
const char *LockEvtCode_toString(enum LockEvtCode value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockDevActionType to a string.
 * @return "?" if unknown.
 */
const char *LockDevActionType_toString(enum LockDevActionType value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockFunction to a string.
 * @return "?" if unknown.
 */
const char *LockFunction_toString(enum LockFunction value);
#endif // WITH_LOGGING


/**
 * Enum: {@link LockHostGrantFallbackMode.h}.
 */
enum LockHostGrantFallbackMode
{
	LockHostGrantFallbackMode_NONE,
	LockHostGrantFallbackMode_DENY,
	LockHostGrantFallbackMode_LOCAL_DECISION,
};

#ifdef WITH_LOGGING
/**
 * Convert LockHostGrantFallbackMode to a string.
 * @return "?" if unknown.
 */
const char *LockHostGrantFallbackMode_toString(enum LockHostGrantFallbackMode value);
#endif // WITH_LOGGING


/**
 * Enum: {@link LockHostGrantInitiationMode.h}.
 */
enum LockHostGrantInitiationMode
{
	LockHostGrantInitiationMode_NEVER,
	LockHostGrantInitiationMode_UNKNOWN_CRED,
	LockHostGrantInitiationMode_ALWAYS,
};

#ifdef WITH_LOGGING
/**
 * Convert LockHostGrantInitiationMode to a string.
 * @return "?" if unknown.
 */
const char *LockHostGrantInitiationMode_toString(enum LockHostGrantInitiationMode value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockIdentificationType to a string.
 * @return "?" if unknown.
 */
const char *LockIdentificationType_toString(enum LockIdentificationType value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockFileCategory to a string.
 * @return "?" if unknown.
 */
const char *LockFileCategory_toString(enum LockFileCategory value);
#endif // WITH_LOGGING


/**
 * Enum: {@link LockFileIdentifier.h}.
 */
enum LockFileIdentifier
{
	LockFileIdentifier_NONE,
	LockFileIdentifier_DEFAULT,
};

#ifdef WITH_LOGGING
/**
 * Convert LockFileIdentifier to a string.
 * @return "?" if unknown.
 */
const char *LockFileIdentifier_toString(enum LockFileIdentifier value);
#endif // WITH_LOGGING


/**
 * Enum: {@link LockHostGrantReqType.h}.
 */
enum LockHostGrantReqType
{
	LockHostGrantReqType_NONE,
	LockHostGrantReqType_CRED_READ,
};

#ifdef WITH_LOGGING
/**
 * Convert LockHostGrantReqType to a string.
 * @return "?" if unknown.
 */
const char *LockHostGrantReqType_toString(enum LockHostGrantReqType value);
#endif // WITH_LOGGING


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

#ifdef WITH_LOGGING
/**
 * Convert LockPolicyPriority to a string.
 * @return "?" if unknown.
 */
const char *LockPolicyPriority_toString(enum LockPolicyPriority value);
#endif // WITH_LOGGING


/** Maximum serialized length for LockDate. */
#define LockDate_MAX_SERIALIZED_LEN 4

/**
 * Main structure for module: {@link LockDate.h}.
 */
struct LockDate
{
	uint16_t year:12;
	uint8_t month:4;
	uint8_t day:5;
};

/** Maximum serialized length for LockTimeOfDay_ToMinute. */
#define LockTimeOfDay_ToMinute_MAX_SERIALIZED_LEN 2

/**
 * Main structure for module: {@link LockTimeOfDay_ToMinute.h}.
 */
struct LockTimeOfDay_ToMinute
{
	uint8_t hour:5;
	uint8_t minute:6;
};

/** Maximum serialized length for LockTimeOfDay_ToQuarterHour. */
#define LockTimeOfDay_ToQuarterHour_MAX_SERIALIZED_LEN 1

/**
 * Main structure for module: {@link LockTimeOfDay_ToQuarterHour.h}.
 */
struct LockTimeOfDay_ToQuarterHour
{
	uint8_t quarterHour;
};

/** Maximum serialized length for LockTimeOfDay_ToSecond. */
#define LockTimeOfDay_ToSecond_MAX_SERIALIZED_LEN 3

/**
 * Main structure for module: {@link LockTimeOfDay_ToSecond.h}.
 */
struct LockTimeOfDay_ToSecond
{
	uint8_t hour:5;
	uint8_t minute:6;
	uint8_t second:6;
};

/** Maximum serialized length for LockDateTime_ToMinute. */
#define LockDateTime_ToMinute_MAX_SERIALIZED_LEN 6

/**
 * Main structure for module: {@link LockDateTime_ToMinute.h}.
 */
struct LockDateTime_ToMinute
{
	uint16_t year:12;
	uint8_t month:4;
	uint8_t day:5;
	uint8_t hour:5;
	uint8_t minute:6;
};

/** Maximum serialized length for LockDateTime_ToSecond. */
#define LockDateTime_ToSecond_MAX_SERIALIZED_LEN 7

/**
 * Main structure for module: {@link LockDateTime_ToSecond.h}.
 */
struct LockDateTime_ToSecond
{
	uint16_t year:12;
	uint8_t month:4;
	uint8_t day:5;
	uint8_t hour:5;
	uint8_t minute:6;
	uint8_t second:6;
};

/**
 * Main structure for module: {@link LockEvtContent.h}.
 */
struct LockEvtContent
{
	int8_t contentType;
};

/** Maximum serialized length for LockEvtDelta. */
#define LockEvtDelta_MAX_SERIALIZED_LEN 2

/**
 * Main structure for module: {@link LockEvtDelta.h}.
 */
struct LockEvtDelta
{
	bool suppress:1;
	bool priority:1;
};

/** Maximum serialized length for LockEvtModifiers. */
#define LockEvtModifiers_MAX_SERIALIZED_LEN 7

/**
 * Main structure for module: {@link LockEvtModifiers.h}.
 */
struct LockEvtModifiers
{
	bool priority:1;
	bool hostGrant:1;
	bool mobileGrant:1;
	bool usedCard:1;
	bool usedPin:1;
	bool emergency:1;
	bool doublePresentation:1;
};

/** Maximum serialized length for LockStatus. */
#define LockStatus_MAX_SERIALIZED_LEN 12

/**
 * Main structure for module: {@link LockStatus.h}.
 */
struct LockStatus
{
	enum LockMode mode;
	bool tamper:1;
	bool batteryLow:1;
	bool batteryCritical:1;
	bool unlocked:1;
	bool open:1;
	bool forced:1;
	bool held:1;
	bool deadboltExtended:1;
	bool privacy:1;
	int16_t batteryLevel;
};

/** Maximum serialized length for LockDstTransition. */
#define LockDstTransition_MAX_SERIALIZED_LEN 4

/**
 * Main structure for module: {@link LockDstTransition.h}.
 */
struct LockDstTransition
{
	uint8_t month:4;
	uint8_t nth:3;
	uint8_t dayOfWeek:3;
	uint8_t hour:5;
};

/** Maximum serialized length for LockAccessModifiers. */
#define LockAccessModifiers_MAX_SERIALIZED_LEN 8

/**
 * Main structure for module: {@link LockAccessModifiers.h}.
 */
struct LockAccessModifiers
{
	bool extDoorTime:1;
	bool administrator:1;
	bool privacyExempt:1;
	bool staticStateLockedExempt:1;
	bool emergencyStaticStateLockedExempt:1;
	bool emergency:1;
	bool firstCredUnlock:1;
	bool pinUnique:1;
};

/** Maximum serialized length for LockCredActions. */
#define LockCredActions_MAX_SERIALIZED_LEN 9

/**
 * Main structure for module: {@link LockCredActions.h}.
 */
struct LockCredActions
{
	bool access:1;
	bool setLockMode_STATIC_STATE_UNLOCKED:1;
	bool setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED:1;
	bool setLockMode_STATIC_STATE_LOCKED:1;
	bool setLockMode_EMERGENCY_STATIC_STATE_LOCKED:1;
	bool cancelLockMode_STATIC_STATE_UNLOCKED:1;
	bool cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED:1;
	bool cancelLockMode_STATIC_STATE_LOCKED:1;
	bool cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED:1;
};

/** Maximum serialized length for LockDevActionPermissions. */
#define LockDevActionPermissions_MAX_SERIALIZED_LEN 14

/**
 * Main structure for module: {@link LockDevActionPermissions.h}.
 */
struct LockDevActionPermissions
{
	bool allow_MOMENTARY_UNLOCK:1;
	bool allow_RESET_LOCK_MODE:1;
	bool allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED:1;
	bool allow_SET_LOCK_MODE_STATIC_STATE_LOCKED:1;
	bool allow_SET_LOCK_MODE_CARD_ONLY:1;
	bool allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN:1;
	bool allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY:1;
	bool allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN:1;
	bool allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED:1;
	bool allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED:1;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY:1;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN:1;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY:1;
	bool allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN:1;
};

/** Maximum serialized length for LockCredTechnologies. */
#define LockCredTechnologies_MAX_SERIALIZED_LEN 13

/**
 * Main structure for module: {@link LockCredTechnologies.h}.
 */
struct LockCredTechnologies
{
	bool enable_PROX:1;
	bool enable_BLUETOOTH_ANY:1;
	bool enable_NFC_ANY:1;
	bool enable_DESFIRE_ANY:1;
	bool enable_ICLASS_ANY:1;
	bool enable_BLUETOOTH_WAVELYNX:1;
	bool enable_BLUETOOTH_Z9_WAVELYNX:1;
	bool enable_NFC_GOOGLE:1;
	bool enable_NFC_APPLE:1;
	bool enable_DESFIRE_LEAF:1;
	bool enable_DESFIRE_UID:1;
	bool enable_ICLASS_FULL:1;
	bool enable_ICLASS_UID:1;
};

/** Maximum serialized length for LockFunctionModifiers. */
#define LockFunctionModifiers_MAX_SERIALIZED_LEN 3

/**
 * Main structure for module: {@link LockFunctionModifiers.h}.
 */
struct LockFunctionModifiers
{
	uint8_t ipbUnlockDuration;
	uint16_t escapeAndReturnDuration;
};

/** Maximum serialized length for LockPolicyAssertion. */
#define LockPolicyAssertion_MAX_SERIALIZED_LEN 7

/**
 * Main structure for module: {@link LockPolicyAssertion.h}.
 */
struct LockPolicyAssertion
{
	enum LockMode mode;
	bool setDoorForcedMasking:1;
	bool doorForcedMasking:1;
	bool setDoorHeldMasking:1;
	bool doorHeldMasking:1;
	bool setPrivacy:1;
	bool privacy:1;
};

/** Maximum serialized length for LockHostGrantConfig. */
#define LockHostGrantConfig_MAX_SERIALIZED_LEN 3

/**
 * Main structure for module: {@link LockHostGrantConfig.h}.
 */
struct LockHostGrantConfig
{
	enum LockHostGrantInitiationMode initiationMode;
	uint8_t timeout;
	enum LockHostGrantFallbackMode fallbackMode;
};

/**
 * Main structure for module: {@link LockPacketContent.h}.
 */
struct LockPacketContent
{
	int8_t contentType;
};

/** Maximum serialized length for LockPaginationReq. */
#define LockPaginationReq_MAX_SERIALIZED_LEN 6

/**
 * Main structure for module: {@link LockPaginationReq.h}.
 */
struct LockPaginationReq
{
	int32_t aboveIndex;
	uint16_t pageSize;
};

/** Maximum serialized length for LockEvtContent_None. */
#define LockEvtContent_None_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (LockEvtContent_None) in a union. */
#define LockEvtContent_None_DISCRIMINATOR 0

/**
 * Main structure for module: {@link LockEvtContent_None.h}.
 */
struct LockEvtContent_None
{
	struct LockEvtContent base;
};

/** Maximum serialized length for LockEvtContent_BatteryLevel. */
#define LockEvtContent_BatteryLevel_MAX_SERIALIZED_LEN 3

/** Discriminator which identifies this subtype (LockEvtContent_BatteryLevel) in a union. */
#define LockEvtContent_BatteryLevel_DISCRIMINATOR 3

/**
 * Main structure for module: {@link LockEvtContent_BatteryLevel.h}.
 */
struct LockEvtContent_BatteryLevel
{
	struct LockEvtContent base;
	uint16_t batteryLevel;
};

/** Maximum serialized length for LockEvtContent_CredUnid. */
#define LockEvtContent_CredUnid_MAX_SERIALIZED_LEN 6

/** Discriminator which identifies this subtype (LockEvtContent_CredUnid) in a union. */
#define LockEvtContent_CredUnid_DISCRIMINATOR 1

/**
 * Main structure for module: {@link LockEvtContent_CredUnid.h}.
 */
struct LockEvtContent_CredUnid
{
	struct LockEvtContent base;
	enum LockCredTechnology credTechnology;
	uint32_t credUnid;
};

/** Maximum serialized length for LockEvtContent_SchedOid. */
#define LockEvtContent_SchedOid_MAX_SERIALIZED_LEN 2

/** Discriminator which identifies this subtype (LockEvtContent_SchedOid) in a union. */
#define LockEvtContent_SchedOid_DISCRIMINATOR 2

/**
 * Main structure for module: {@link LockEvtContent_SchedOid.h}.
 */
struct LockEvtContent_SchedOid
{
	struct LockEvtContent base;
	uint8_t schedOid;
};

/** Maximum serialized length for LockEvt. */
#define LockEvt_MAX_SERIALIZED_LEN 21

/**
 * Main structure for module: {@link LockEvt.h}.
 */
struct LockEvt
{
	struct LockDateTime_ToSecond dateTime;
	enum LockEvtCode evtCode;
	struct LockEvtModifiers modifiers;
	union
	{
		struct LockEvtContent_None uLockEvtContent_None;
		struct LockEvtContent_CredUnid uLockEvtContent_CredUnid;
		struct LockEvtContent_SchedOid uLockEvtContent_SchedOid;
		struct LockEvtContent_BatteryLevel uLockEvtContent_BatteryLevel;
	} content;
};

/** Maximum serialized length for LockTimeZone. */
#define LockTimeZone_MAX_SERIALIZED_LEN 12

/**
 * Main structure for module: {@link LockTimeZone.h}.
 */
struct LockTimeZone
{
	int16_t standardOffset;
	int16_t dstOffset;
	struct LockDstTransition standardTransition;
	struct LockDstTransition dstTransition;
};

/** Maximum serialized length for LockCred. */
#define LockCred_MAX_SERIALIZED_LEN 77

/**
 * Main structure for module: {@link LockCred.h}.
 */
struct LockCred
{
	uint32_t unid;
	struct LockDate effective;
	struct LockDate expires;
	enum LockCredTechnology technology;
	struct LockAccessModifiers accessModifiers;
	struct LockCredActions presentationActions;
	struct LockCredActions doublePresentationActions;
	struct LockDevActionPermissions explicitActionPermissions;
	int8_t trimBitsInLastCredByte:3;
	uint8_t numCredBytes:5;
	uint8_t credBytes[16];
	uint8_t pinDigitNybbles[4];
	uint8_t schedMaskBytes[2];
};

/** Maximum serialized length for LockEvtPolicy. */
#define LockEvtPolicy_MAX_SERIALIZED_LEN 3

/**
 * Main structure for module: {@link LockEvtPolicy.h}.
 */
struct LockEvtPolicy
{
	enum LockEvtCode evtCode;
	struct LockEvtDelta evtDelta;
};

/** Maximum serialized length for LockHol. */
#define LockHol_MAX_SERIALIZED_LEN 13

/**
 * Main structure for module: {@link LockHol.h}.
 */
struct LockHol
{
	struct LockDateTime_ToMinute start;
	struct LockDateTime_ToMinute stop;
	uint8_t holTypes;
};

/** Maximum serialized length for LockSchedElement. */
#define LockSchedElement_MAX_SERIALIZED_LEN 5

/**
 * Main structure for module: {@link LockSchedElement.h}.
 */
struct LockSchedElement
{
	struct LockTimeOfDay_ToQuarterHour start;
	struct LockTimeOfDay_ToQuarterHour stop;
	uint8_t plusDays;
	int8_t daysOfWeek;
	uint8_t holTypes;
};

/** Maximum serialized length for LockSchedElementPolicy. */
#define LockSchedElementPolicy_MAX_SERIALIZED_LEN 7

/**
 * Main structure for module: {@link LockSchedElementPolicy.h}.
 */
struct LockSchedElementPolicy
{
	struct LockPolicyAssertion assertion;
};

/** Maximum serialized length for LockSchedPolicy. */
#define LockSchedPolicy_MAX_SERIALIZED_LEN 59

/**
 * Main structure for module: {@link LockSchedPolicy.h}.
 */
struct LockSchedPolicy
{
	uint8_t schedOid;
	enum LockDevActionType action;
	int8_t numElements;
	struct LockSchedElementPolicy elements[8];
};

/** Maximum serialized length for LockSched. */
#define LockSched_MAX_SERIALIZED_LEN 57

/**
 * Main structure for module: {@link LockSched.h}.
 */
struct LockSched
{
	uint32_t unid;
	struct LockDateTime_ToMinute effective;
	struct LockDateTime_ToMinute expires;
	int8_t numElements;
	struct LockSchedElement elements[8];
};

/** Maximum serialized length for LockConfig. */
#define LockConfig_MAX_SERIALIZED_LEN 137

/**
 * Main structure for module: {@link LockConfig.h}.
 */
struct LockConfig
{
	struct LockCredTechnologies credTechnologies;
	enum LockFunction function;
	struct LockFunctionModifiers functionModifiers;
	uint8_t strikeTime;
	uint8_t extendedStrikeTime;
	uint8_t heldTime;
	uint8_t extendedHeldTime;
	bool defaultDoorForcedMasking:1;
	bool defaultDoorHeldMasking:1;
	enum LockMode defaultLockMode;
	struct LockHostGrantConfig hostGrantConfig;
	uint8_t maxPinLength:4;
	struct LockTimeZone timeZone;
	uint8_t numEvtPolicy:6;
	struct LockEvtPolicy evtPolicies[32];
};

/** Maximum serialized length for LockEvtIdentifier. */
#define LockEvtIdentifier_MAX_SERIALIZED_LEN 8

/**
 * Main structure for module: {@link LockEvtIdentifier.h}.
 */
struct LockEvtIdentifier
{
	struct LockDateTime_ToSecond dateTime;
	enum LockEvtCode evtCode;
};

/** Maximum serialized length for LockEvtIdentifierRange. */
#define LockEvtIdentifierRange_MAX_SERIALIZED_LEN 16

/**
 * Main structure for module: {@link LockEvtIdentifierRange.h}.
 */
struct LockEvtIdentifierRange
{
	struct LockEvtIdentifier start;
	struct LockEvtIdentifier stop;
};

/** Maximum serialized length for LockIdentification. */
#define LockIdentification_MAX_SERIALIZED_LEN 17

/** Discriminator which identifies this subtype (LockIdentification) in a union. */
#define LockIdentification_DISCRIMINATOR 0

/**
 * Main structure for module: {@link LockIdentification.h}.
 */
struct LockIdentification
{
	struct LockPacketContent base;
	uint8_t protocolVersionMajor;
	uint8_t protocolVersionMinor;
	enum LockIdentificationType type;
	uint64_t id;
	uint8_t model;
	uint8_t brand;
	uint8_t firmwareVersionMajor;
	uint8_t firmwareVersionMinor;
	bool licensed:1;
};

/** Maximum serialized length for LockIdentificationResult. */
#define LockIdentificationResult_MAX_SERIALIZED_LEN 3

/** Discriminator which identifies this subtype (LockIdentificationResult) in a union. */
#define LockIdentificationResult_DISCRIMINATOR 1

/**
 * Main structure for module: {@link LockIdentificationResult.h}.
 */
struct LockIdentificationResult
{
	struct LockPacketContent base;
	int16_t errorCode;
};

/** Maximum serialized length for LockDbChange_Config. */
#define LockDbChange_Config_MAX_SERIALIZED_LEN 147

/** Discriminator which identifies this subtype (LockDbChange_Config) in a union. */
#define LockDbChange_Config_DISCRIMINATOR 2

/**
 * Main structure for module: {@link LockDbChange_Config.h}.
 */
struct LockDbChange_Config
{
	struct LockPacketContent base;
	int64_t requestId;
	int8_t updateConfigPresent;
	struct LockConfig updateConfig[1];
};

/** Maximum serialized length for LockDbChangeResp. */
#define LockDbChangeResp_MAX_SERIALIZED_LEN 11

/** Discriminator which identifies this subtype (LockDbChangeResp) in a union. */
#define LockDbChangeResp_DISCRIMINATOR 3

/**
 * Main structure for module: {@link LockDbChangeResp.h}.
 */
struct LockDbChangeResp
{
	struct LockPacketContent base;
	int64_t requestId;
	int16_t errorCode;
};

/** Maximum serialized length for LockEvtControl. */
#define LockEvtControl_MAX_SERIALIZED_LEN 19

/** Discriminator which identifies this subtype (LockEvtControl) in a union. */
#define LockEvtControl_DISCRIMINATOR 4

/**
 * Main structure for module: {@link LockEvtControl.h}.
 */
struct LockEvtControl
{
	struct LockPacketContent base;
	bool priority:1;
	bool sendOneBatch:1;
	struct LockEvtIdentifierRange consume;
};

/** Maximum serialized length for LockEvtBatch. */
#define LockEvtBatch_MAX_SERIALIZED_LEN 675

/** Discriminator which identifies this subtype (LockEvtBatch) in a union. */
#define LockEvtBatch_DISCRIMINATOR 5

/**
 * Main structure for module: {@link LockEvtBatch.h}.
 */
struct LockEvtBatch
{
	struct LockPacketContent base;
	bool priority:1;
	uint8_t evtCount:6;
	struct LockEvt evt[32];
};

/** Maximum serialized length for LockDevStateRecordControl. */
#define LockDevStateRecordControl_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (LockDevStateRecordControl) in a union. */
#define LockDevStateRecordControl_DISCRIMINATOR 6

/**
 * Main structure for module: {@link LockDevStateRecordControl.h}.
 */
struct LockDevStateRecordControl
{
	struct LockPacketContent base;
};

/** Maximum serialized length for LockDevStateRecord. */
#define LockDevStateRecord_MAX_SERIALIZED_LEN 13

/** Discriminator which identifies this subtype (LockDevStateRecord) in a union. */
#define LockDevStateRecord_DISCRIMINATOR 7

/**
 * Main structure for module: {@link LockDevStateRecord.h}.
 */
struct LockDevStateRecord
{
	struct LockPacketContent base;
	struct LockStatus status;
};

/** Maximum serialized length for LockDateTimeConfig. */
#define LockDateTimeConfig_MAX_SERIALIZED_LEN 20

/**
 * Main structure for module: {@link LockDateTimeConfig.h}.
 */
struct LockDateTimeConfig
{
	struct LockDateTime_ToSecond dateTime;
	bool timeZonePresent:1;
	struct LockTimeZone timeZone;
};

/** Maximum serialized length for LockGetTimeReq. */
#define LockGetTimeReq_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (LockGetTimeReq) in a union. */
#define LockGetTimeReq_DISCRIMINATOR 8

/**
 * Main structure for module: {@link LockGetTimeReq.h}.
 */
struct LockGetTimeReq
{
	struct LockPacketContent base;
};

/** Maximum serialized length for LockGetTimeResp. */
#define LockGetTimeResp_MAX_SERIALIZED_LEN 21

/** Discriminator which identifies this subtype (LockGetTimeResp) in a union. */
#define LockGetTimeResp_DISCRIMINATOR 9

/**
 * Main structure for module: {@link LockGetTimeResp.h}.
 */
struct LockGetTimeResp
{
	struct LockPacketContent base;
	struct LockDateTimeConfig dateTimeConfig;
};

/** Maximum serialized length for LockSetTimeReq. */
#define LockSetTimeReq_MAX_SERIALIZED_LEN 21

/** Discriminator which identifies this subtype (LockSetTimeReq) in a union. */
#define LockSetTimeReq_DISCRIMINATOR 10

/**
 * Main structure for module: {@link LockSetTimeReq.h}.
 */
struct LockSetTimeReq
{
	struct LockPacketContent base;
	struct LockDateTimeConfig dateTimeConfig;
};

/** Maximum serialized length for LockSetTimeResp. */
#define LockSetTimeResp_MAX_SERIALIZED_LEN 3

/** Discriminator which identifies this subtype (LockSetTimeResp) in a union. */
#define LockSetTimeResp_DISCRIMINATOR 11

/**
 * Main structure for module: {@link LockSetTimeResp.h}.
 */
struct LockSetTimeResp
{
	struct LockPacketContent base;
	int16_t errorCode;
};

/** Maximum serialized length for LockPullFileChunkReq. */
#define LockPullFileChunkReq_MAX_SERIALIZED_LEN 15

/** Discriminator which identifies this subtype (LockPullFileChunkReq) in a union. */
#define LockPullFileChunkReq_DISCRIMINATOR 14

/**
 * Main structure for module: {@link LockPullFileChunkReq.h}.
 */
struct LockPullFileChunkReq
{
	struct LockPacketContent base;
	uint16_t requestId;
	enum LockFileCategory category;
	enum LockFileIdentifier id;
	uint64_t offset;
	uint16_t maxLength;
};

/** Maximum serialized length for LockPullFileChunkResp. */
#define LockPullFileChunkResp_MAX_SERIALIZED_LEN 808

/** Discriminator which identifies this subtype (LockPullFileChunkResp) in a union. */
#define LockPullFileChunkResp_DISCRIMINATOR 15

/**
 * Main structure for module: {@link LockPullFileChunkResp.h}.
 */
struct LockPullFileChunkResp
{
	struct LockPacketContent base;
	uint16_t requestId;
	int16_t errorCode;
	bool eof:1;
	int16_t bytesCount;
	uint8_t bytes[800];
};

/** Maximum serialized length for LockPushFileChunkReq. */
#define LockPushFileChunkReq_MAX_SERIALIZED_LEN 816

/** Discriminator which identifies this subtype (LockPushFileChunkReq) in a union. */
#define LockPushFileChunkReq_DISCRIMINATOR 12

/**
 * Main structure for module: {@link LockPushFileChunkReq.h}.
 */
struct LockPushFileChunkReq
{
	struct LockPacketContent base;
	uint16_t requestId;
	enum LockFileCategory category;
	enum LockFileIdentifier id;
	uint64_t offset;
	bool eof:1;
	int16_t bytesCount;
	uint8_t bytes[800];
};

/** Maximum serialized length for LockPushFileChunkResp. */
#define LockPushFileChunkResp_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (LockPushFileChunkResp) in a union. */
#define LockPushFileChunkResp_DISCRIMINATOR 13

/**
 * Main structure for module: {@link LockPushFileChunkResp.h}.
 */
struct LockPushFileChunkResp
{
	struct LockPacketContent base;
	uint16_t requestId;
	int16_t errorCode;
};

/** Maximum serialized length for LockUpgradeReq. */
#define LockUpgradeReq_MAX_SERIALIZED_LEN 6

/** Discriminator which identifies this subtype (LockUpgradeReq) in a union. */
#define LockUpgradeReq_DISCRIMINATOR 16

/**
 * Main structure for module: {@link LockUpgradeReq.h}.
 */
struct LockUpgradeReq
{
	struct LockPacketContent base;
	uint16_t requestId;
	enum LockFileIdentifier fileId;
	uint16_t rebootDelay;
};

/** Maximum serialized length for LockUpgradeResp. */
#define LockUpgradeResp_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (LockUpgradeResp) in a union. */
#define LockUpgradeResp_DISCRIMINATOR 17

/**
 * Main structure for module: {@link LockUpgradeResp.h}.
 */
struct LockUpgradeResp
{
	struct LockPacketContent base;
	uint16_t requestId;
	int16_t errorCode;
};

/** Maximum serialized length for LockDbQuery. */
#define LockDbQuery_MAX_SERIALIZED_LEN 14

/** Discriminator which identifies this subtype (LockDbQuery) in a union. */
#define LockDbQuery_DISCRIMINATOR 18

/**
 * Main structure for module: {@link LockDbQuery.h}.
 */
struct LockDbQuery
{
	struct LockPacketContent base;
	int16_t requestId;
	bool queryConfig:1;
	bool queryHol:1;
	bool querySched:1;
	bool querySchedPolicy:1;
	bool queryCred:1;
	struct LockPaginationReq paginationCred;
};

/** Maximum serialized length for LockDbQueryResp_Config. */
#define LockDbQueryResp_Config_MAX_SERIALIZED_LEN 143

/** Discriminator which identifies this subtype (LockDbQueryResp_Config) in a union. */
#define LockDbQueryResp_Config_DISCRIMINATOR 19

/**
 * Main structure for module: {@link LockDbQueryResp_Config.h}.
 */
struct LockDbQueryResp_Config
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	int8_t configPresent;
	struct LockConfig config[1];
};

/** Maximum serialized length for LockHostGrantReq. */
#define LockHostGrantReq_MAX_SERIALIZED_LEN 83

/** Discriminator which identifies this subtype (LockHostGrantReq) in a union. */
#define LockHostGrantReq_DISCRIMINATOR 20

/**
 * Main structure for module: {@link LockHostGrantReq.h}.
 */
struct LockHostGrantReq
{
	struct LockPacketContent base;
	int16_t requestId;
	enum LockHostGrantReqType type;
	enum LockMode lockMode;
	bool privacy:1;
	struct LockCred rawCred;
};

/** Maximum serialized length for LockHostGrantResp. */
#define LockHostGrantResp_MAX_SERIALIZED_LEN 83

/** Discriminator which identifies this subtype (LockHostGrantResp) in a union. */
#define LockHostGrantResp_DISCRIMINATOR 21

/**
 * Main structure for module: {@link LockHostGrantResp.h}.
 */
struct LockHostGrantResp
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	struct LockCred dbCred;
	enum LockEvtCode evtCode;
};

/** Maximum serialized length for LockDevActionReq. */
#define LockDevActionReq_MAX_SERIALIZED_LEN 7

/** Discriminator which identifies this subtype (LockDevActionReq) in a union. */
#define LockDevActionReq_DISCRIMINATOR 22

/**
 * Main structure for module: {@link LockDevActionReq.h}.
 */
struct LockDevActionReq
{
	struct LockPacketContent base;
	int16_t requestId;
	enum LockDevActionType actionType;
	int16_t durationSecs;
	enum LockPolicyPriority policyPriority;
};

/** Maximum serialized length for LockDevActionResp. */
#define LockDevActionResp_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (LockDevActionResp) in a union. */
#define LockDevActionResp_DISCRIMINATOR 23

/**
 * Main structure for module: {@link LockDevActionResp.h}.
 */
struct LockDevActionResp
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
};

/** Maximum serialized length for LockPolicyAssertionReq. */
#define LockPolicyAssertionReq_MAX_SERIALIZED_LEN 13

/** Discriminator which identifies this subtype (LockPolicyAssertionReq) in a union. */
#define LockPolicyAssertionReq_DISCRIMINATOR 24

/**
 * Main structure for module: {@link LockPolicyAssertionReq.h}.
 */
struct LockPolicyAssertionReq
{
	struct LockPacketContent base;
	int16_t requestId;
	enum LockPolicyPriority priority;
	bool state:1;
	bool temporary:1;
	struct LockPolicyAssertion assertion;
};

/** Maximum serialized length for LockPolicyAssertionResp. */
#define LockPolicyAssertionResp_MAX_SERIALIZED_LEN 5

/** Discriminator which identifies this subtype (LockPolicyAssertionResp) in a union. */
#define LockPolicyAssertionResp_DISCRIMINATOR 25

/**
 * Main structure for module: {@link LockPolicyAssertionResp.h}.
 */
struct LockPolicyAssertionResp
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
};

/** Maximum serialized length for LockConnectionTermination. */
#define LockConnectionTermination_MAX_SERIALIZED_LEN 1

/** Discriminator which identifies this subtype (LockConnectionTermination) in a union. */
#define LockConnectionTermination_DISCRIMINATOR 26

/**
 * Main structure for module: {@link LockConnectionTermination.h}.
 */
struct LockConnectionTermination
{
	struct LockPacketContent base;
};

/** Maximum serialized length for LockDbChange_Hol. */
#define LockDbChange_Hol_MAX_SERIALIZED_LEN 426

/** Discriminator which identifies this subtype (LockDbChange_Hol) in a union. */
#define LockDbChange_Hol_DISCRIMINATOR 27

/**
 * Main structure for module: {@link LockDbChange_Hol.h}.
 */
struct LockDbChange_Hol
{
	struct LockPacketContent base;
	int64_t requestId;
	uint8_t numHol;
	struct LockHol hol[32];
};

/** Maximum serialized length for LockDbChange_Sched. */
#define LockDbChange_Sched_MAX_SERIALIZED_LEN 865

/** Discriminator which identifies this subtype (LockDbChange_Sched) in a union. */
#define LockDbChange_Sched_DISCRIMINATOR 28

/**
 * Main structure for module: {@link LockDbChange_Sched.h}.
 */
struct LockDbChange_Sched
{
	struct LockPacketContent base;
	int64_t requestId;
	uint8_t numSched;
	struct LockSched sched[15];
};

/** Maximum serialized length for LockDbChange_SchedPolicy. */
#define LockDbChange_SchedPolicy_MAX_SERIALIZED_LEN 482

/** Discriminator which identifies this subtype (LockDbChange_SchedPolicy) in a union. */
#define LockDbChange_SchedPolicy_DISCRIMINATOR 29

/**
 * Main structure for module: {@link LockDbChange_SchedPolicy.h}.
 */
struct LockDbChange_SchedPolicy
{
	struct LockPacketContent base;
	int64_t requestId;
	uint8_t numSchedPolicy;
	struct LockSchedPolicy schedPolicy[8];
};

/** Maximum serialized length for LockDbChange_Cred. */
#define LockDbChange_Cred_MAX_SERIALIZED_LEN 1243

/** Discriminator which identifies this subtype (LockDbChange_Cred) in a union. */
#define LockDbChange_Cred_DISCRIMINATOR 30

/**
 * Main structure for module: {@link LockDbChange_Cred.h}.
 */
struct LockDbChange_Cred
{
	struct LockPacketContent base;
	int64_t requestId;
	bool deleteAllCred:1;
	uint8_t numUpsertOrDeleteCred;
	struct LockCred upsertOrDeleteCred[16];
};

/** Maximum serialized length for LockDbQueryResp_Hol. */
#define LockDbQueryResp_Hol_MAX_SERIALIZED_LEN 838

/** Discriminator which identifies this subtype (LockDbQueryResp_Hol) in a union. */
#define LockDbQueryResp_Hol_DISCRIMINATOR 31

/**
 * Main structure for module: {@link LockDbQueryResp_Hol.h}.
 */
struct LockDbQueryResp_Hol
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numHol;
	struct LockHol hol[64];
};

/** Maximum serialized length for LockDbQueryResp_Sched. */
#define LockDbQueryResp_Sched_MAX_SERIALIZED_LEN 861

/** Discriminator which identifies this subtype (LockDbQueryResp_Sched) in a union. */
#define LockDbQueryResp_Sched_DISCRIMINATOR 32

/**
 * Main structure for module: {@link LockDbQueryResp_Sched.h}.
 */
struct LockDbQueryResp_Sched
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numSched;
	struct LockSched sched[15];
};

/** Maximum serialized length for LockDbQueryResp_SchedPolicy. */
#define LockDbQueryResp_SchedPolicy_MAX_SERIALIZED_LEN 478

/** Discriminator which identifies this subtype (LockDbQueryResp_SchedPolicy) in a union. */
#define LockDbQueryResp_SchedPolicy_DISCRIMINATOR 33

/**
 * Main structure for module: {@link LockDbQueryResp_SchedPolicy.h}.
 */
struct LockDbQueryResp_SchedPolicy
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numSchedPolicy;
	struct LockSchedPolicy schedPolicy[8];
};

/** Maximum serialized length for LockDbQueryResp_Cred. */
#define LockDbQueryResp_Cred_MAX_SERIALIZED_LEN 1238

/** Discriminator which identifies this subtype (LockDbQueryResp_Cred) in a union. */
#define LockDbQueryResp_Cred_DISCRIMINATOR 34

/**
 * Main structure for module: {@link LockDbQueryResp_Cred.h}.
 */
struct LockDbQueryResp_Cred
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	uint8_t numCred;
	struct LockCred cred[16];
};

/** Maximum serialized length for LockCredAuthorization. */
#define LockCredAuthorization_MAX_SERIALIZED_LEN 172

/** Discriminator which identifies this subtype (LockCredAuthorization) in a union. */
#define LockCredAuthorization_DISCRIMINATOR 35

/**
 * Main structure for module: {@link LockCredAuthorization.h}.
 */
struct LockCredAuthorization
{
	struct LockPacketContent base;
	uint64_t mobileId;
	uint64_t lockId;
	struct LockCred cred;
	uint8_t numSchedUnids:4;
	uint32_t schedUnids[15];
	int8_t numSharedSecretBytes;
	uint8_t sharedSecretBytes[16];
};

/** Maximum serialized length for LockAccessReq. */
#define LockAccessReq_MAX_SERIALIZED_LEN 11

/** Discriminator which identifies this subtype (LockAccessReq) in a union. */
#define LockAccessReq_DISCRIMINATOR 37

/**
 * Main structure for module: {@link LockAccessReq.h}.
 */
struct LockAccessReq
{
	struct LockPacketContent base;
	int16_t requestId;
	uint64_t mobileId;
};

/** Maximum serialized length for LockAccessResp. */
#define LockAccessResp_MAX_SERIALIZED_LEN 6

/** Discriminator which identifies this subtype (LockAccessResp) in a union. */
#define LockAccessResp_DISCRIMINATOR 38

/**
 * Main structure for module: {@link LockAccessResp.h}.
 */
struct LockAccessResp
{
	struct LockPacketContent base;
	int16_t requestId;
	int16_t errorCode;
	bool granted:1;
};

/** Maximum serialized length for LockPublicKeyExchange. */
#define LockPublicKeyExchange_MAX_SERIALIZED_LEN 35

/** Discriminator which identifies this subtype (LockPublicKeyExchange) in a union. */
#define LockPublicKeyExchange_DISCRIMINATOR 41

/**
 * Main structure for module: {@link LockPublicKeyExchange.h}.
 */
struct LockPublicKeyExchange
{
	struct LockPacketContent base;
	int8_t numPublicKeyBytes;
	uint8_t publicKeyBytes[33];
};

/** Maximum serialized length for LockMobileBleChallengeNonce. */
#define LockMobileBleChallengeNonce_MAX_SERIALIZED_LEN 18

/** Discriminator which identifies this subtype (LockMobileBleChallengeNonce) in a union. */
#define LockMobileBleChallengeNonce_DISCRIMINATOR 43

/**
 * Main structure for module: {@link LockMobileBleChallengeNonce.h}.
 */
struct LockMobileBleChallengeNonce
{
	struct LockPacketContent base;
	int8_t numNonceBytes;
	uint8_t nonceBytes[16];
};

/** Maximum serialized length for LockBundleHeader. */
#define LockBundleHeader_MAX_SERIALIZED_LEN 37

/** Discriminator which identifies this subtype (LockBundleHeader) in a union. */
#define LockBundleHeader_DISCRIMINATOR 40

/**
 * Main structure for module: {@link LockBundleHeader.h}.
 */
struct LockBundleHeader
{
	struct LockPacketContent base;
	enum LockIdentificationType origin;
	enum LockIdentificationType intermediary;
	enum LockIdentificationType destination;
	uint64_t originId;
	uint64_t intermediaryId;
	uint64_t destinationId;
	struct LockDateTime_ToSecond expires;
	bool opaque:1;
	int8_t packetCount:3;
};

/** Maximum serialized length for LockOpaqueContent. */
#define LockOpaqueContent_MAX_SERIALIZED_LEN 1026

/** Discriminator which identifies this subtype (LockOpaqueContent) in a union. */
#define LockOpaqueContent_DISCRIMINATOR 42

/**
 * Main structure for module: {@link LockOpaqueContent.h}.
 */
struct LockOpaqueContent
{
	struct LockPacketContent base;
	int16_t numOpaqueBytes:10;
	uint8_t opaqueBytes[1023];
};

/** Maximum serialized length for LockPacket. */
#define LockPacket_MAX_SERIALIZED_LEN 1247

static const int16_t LockPacket_headerBytes = 31289;
/**
 * Main structure for module: {@link LockPacket.h}.
 */
struct LockPacket
{
	int16_t bytecount;
	union
	{
		struct LockIdentification uLockIdentification;
		struct LockIdentificationResult uLockIdentificationResult;
		struct LockDbChange_Config uLockDbChange_Config;
		struct LockDbChangeResp uLockDbChangeResp;
		struct LockEvtControl uLockEvtControl;
		struct LockEvtBatch uLockEvtBatch;
		struct LockDevStateRecordControl uLockDevStateRecordControl;
		struct LockDevStateRecord uLockDevStateRecord;
		struct LockGetTimeReq uLockGetTimeReq;
		struct LockGetTimeResp uLockGetTimeResp;
		struct LockSetTimeReq uLockSetTimeReq;
		struct LockSetTimeResp uLockSetTimeResp;
		struct LockPushFileChunkReq uLockPushFileChunkReq;
		struct LockPushFileChunkResp uLockPushFileChunkResp;
		struct LockPullFileChunkReq uLockPullFileChunkReq;
		struct LockPullFileChunkResp uLockPullFileChunkResp;
		struct LockUpgradeReq uLockUpgradeReq;
		struct LockUpgradeResp uLockUpgradeResp;
		struct LockDbQuery uLockDbQuery;
		struct LockDbQueryResp_Config uLockDbQueryResp_Config;
		struct LockHostGrantReq uLockHostGrantReq;
		struct LockHostGrantResp uLockHostGrantResp;
		struct LockDevActionReq uLockDevActionReq;
		struct LockDevActionResp uLockDevActionResp;
		struct LockPolicyAssertionReq uLockPolicyAssertionReq;
		struct LockPolicyAssertionResp uLockPolicyAssertionResp;
		struct LockConnectionTermination uLockConnectionTermination;
		struct LockDbChange_Hol uLockDbChange_Hol;
		struct LockDbChange_Sched uLockDbChange_Sched;
		struct LockDbChange_SchedPolicy uLockDbChange_SchedPolicy;
		struct LockDbChange_Cred uLockDbChange_Cred;
		struct LockDbQueryResp_Hol uLockDbQueryResp_Hol;
		struct LockDbQueryResp_Sched uLockDbQueryResp_Sched;
		struct LockDbQueryResp_SchedPolicy uLockDbQueryResp_SchedPolicy;
		struct LockDbQueryResp_Cred uLockDbQueryResp_Cred;
		struct LockCredAuthorization uLockCredAuthorization;
		struct LockAccessReq uLockAccessReq;
		struct LockAccessResp uLockAccessResp;
		struct LockBundleHeader uLockBundleHeader;
		struct LockPublicKeyExchange uLockPublicKeyExchange;
		struct LockOpaqueContent uLockOpaqueContent;
		struct LockMobileBleChallengeNonce uLockMobileBleChallengeNonce;
	} content;
};
