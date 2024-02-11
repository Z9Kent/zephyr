/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9LockIOProtocol_Current.c
 * @author Z9 Security
 */

#include "Z9LockIOProtocol_Current.h"


#ifdef WITH_LOGGING
const char *LockCredTechnology_toString(enum LockCredTechnology value)
{
	switch (value)
	{
		case LockCredTechnology_ANY: return "ANY";
		case LockCredTechnology_PROX_ANY: return "PROX_ANY";
		case LockCredTechnology_BLUETOOTH_ANY: return "BLUETOOTH_ANY";
		case LockCredTechnology_NFC_ANY: return "NFC_ANY";
		case LockCredTechnology_DESFIRE_ANY: return "DESFIRE_ANY";
		case LockCredTechnology_ICLASS_ANY: return "ICLASS_ANY";
		case LockCredTechnology_BLUETOOTH_WAVELYNX: return "BLUETOOTH_WAVELYNX";
		case LockCredTechnology_BLUETOOTH_Z9_WAVELYNX: return "BLUETOOTH_Z9_WAVELYNX";
		case LockCredTechnology_NFC_GOOGLE: return "NFC_GOOGLE";
		case LockCredTechnology_NFC_APPLE: return "NFC_APPLE";
		case LockCredTechnology_NFC_WAVELYNX: return "NFC_WAVELYNX";
		case LockCredTechnology_DESFIRE_LEAF: return "DESFIRE_LEAF";
		case LockCredTechnology_DESFIRE_UID: return "DESFIRE_UID";
		case LockCredTechnology_ICLASS_FULL: return "ICLASS_FULL";
		case LockCredTechnology_ICLASS_UID: return "ICLASS_UID";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockMode_toString(enum LockMode value)
{
	switch (value)
	{
		case LockMode_NONE: return "NONE";
		case LockMode_STATIC_STATE_UNLOCKED: return "STATIC_STATE_UNLOCKED";
		case LockMode_STATIC_STATE_LOCKED: return "STATIC_STATE_LOCKED";
		case LockMode_CARD_ONLY: return "CARD_ONLY";
		case LockMode_CARD_AND_CONFIRMING_PIN: return "CARD_AND_CONFIRMING_PIN";
		case LockMode_UNIQUE_PIN_ONLY: return "UNIQUE_PIN_ONLY";
		case LockMode_CARD_ONLY_OR_UNIQUE_PIN: return "CARD_ONLY_OR_UNIQUE_PIN";
		case LockMode_EMERGENCY_STATIC_STATE_UNLOCKED: return "EMERGENCY_STATIC_STATE_UNLOCKED";
		case LockMode_EMERGENCY_STATIC_STATE_LOCKED: return "EMERGENCY_STATIC_STATE_LOCKED";
		case LockMode_FIRST_CRED_UNLOCK_CARD_ONLY: return "FIRST_CRED_UNLOCK_CARD_ONLY";
		case LockMode_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN: return "FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN";
		case LockMode_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY: return "FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY";
		case LockMode_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN: return "FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockEvtCode_toString(enum LockEvtCode value)
{
	switch (value)
	{
		case LockEvtCode_NONE: return "NONE";
		case LockEvtCode_STARTUP: return "STARTUP";
		case LockEvtCode_DOOR_ACCESS_GRANTED: return "DOOR_ACCESS_GRANTED";
		case LockEvtCode_DOOR_ACCESS_DENIED: return "DOOR_ACCESS_DENIED";
		case LockEvtCode_DOOR_ACCESS_DENIED_INACTIVE: return "DOOR_ACCESS_DENIED_INACTIVE";
		case LockEvtCode_DOOR_ACCESS_DENIED_NOT_EFFECTIVE: return "DOOR_ACCESS_DENIED_NOT_EFFECTIVE";
		case LockEvtCode_DOOR_ACCESS_DENIED_EXPIRED: return "DOOR_ACCESS_DENIED_EXPIRED";
		case LockEvtCode_DOOR_ACCESS_DENIED_OUTSIDE_SCHED: return "DOOR_ACCESS_DENIED_OUTSIDE_SCHED";
		case LockEvtCode_DOOR_ACCESS_DENIED_UNKNOWN_CRED_NUM: return "DOOR_ACCESS_DENIED_UNKNOWN_CRED_NUM";
		case LockEvtCode_DOOR_ACCESS_DENIED_UNKNOWN_CRED_UNIQUE_PIN: return "DOOR_ACCESS_DENIED_UNKNOWN_CRED_UNIQUE_PIN";
		case LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_STATIC_LOCKED: return "DOOR_ACCESS_DENIED_DOOR_MODE_STATIC_LOCKED";
		case LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_CARD: return "DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_CARD";
		case LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_UNIQUE_PIN: return "DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_UNIQUE_PIN";
		case LockEvtCode_DOOR_ACCESS_DENIED_NO_CONFIRMING_PIN_FOR_CRED: return "DOOR_ACCESS_DENIED_NO_CONFIRMING_PIN_FOR_CRED";
		case LockEvtCode_DOOR_ACCESS_DENIED_INCORRECT_CONFIRMING_PIN: return "DOOR_ACCESS_DENIED_INCORRECT_CONFIRMING_PIN";
		case LockEvtCode_DOOR_ACCESS_DENIED_DOOR_MODE_EMERGENCY_STATIC_LOCKED: return "DOOR_ACCESS_DENIED_DOOR_MODE_EMERGENCY_STATIC_LOCKED";
		case LockEvtCode_DOOR_ACCESS_DENIED_DEADBOLT: return "DOOR_ACCESS_DENIED_DEADBOLT";
		case LockEvtCode_DOOR_ACCESS_DENIED_NO_PIN_PRESENTED: return "DOOR_ACCESS_DENIED_NO_PIN_PRESENTED";
		case LockEvtCode_DOOR_ACCESS_DENIED_INCOMPLETE: return "DOOR_ACCESS_DENIED_INCOMPLETE";
		case LockEvtCode_DOOR_ACCESS_DENIED_DOOR_PRIVACY: return "DOOR_ACCESS_DENIED_DOOR_PRIVACY";
		case LockEvtCode_DOOR_FORCED: return "DOOR_FORCED";
		case LockEvtCode_DOOR_NOT_FORCED: return "DOOR_NOT_FORCED";
		case LockEvtCode_DOOR_HELD: return "DOOR_HELD";
		case LockEvtCode_DOOR_NOT_HELD: return "DOOR_NOT_HELD";
		case LockEvtCode_DOOR_OPENED: return "DOOR_OPENED";
		case LockEvtCode_DOOR_CLOSED: return "DOOR_CLOSED";
		case LockEvtCode_DOOR_LOCKED: return "DOOR_LOCKED";
		case LockEvtCode_DOOR_UNLOCKED: return "DOOR_UNLOCKED";
		case LockEvtCode_DOOR_MODE_STATIC_STATE_UNLOCKED: return "DOOR_MODE_STATIC_STATE_UNLOCKED";
		case LockEvtCode_DOOR_MODE_STATIC_STATE_LOCKED: return "DOOR_MODE_STATIC_STATE_LOCKED";
		case LockEvtCode_DOOR_MODE_CARD_ONLY: return "DOOR_MODE_CARD_ONLY";
		case LockEvtCode_DOOR_MODE_CARD_AND_CONFIRMING_PIN: return "DOOR_MODE_CARD_AND_CONFIRMING_PIN";
		case LockEvtCode_DOOR_MODE_UNIQUE_PIN_ONLY: return "DOOR_MODE_UNIQUE_PIN_ONLY";
		case LockEvtCode_DOOR_MODE_CARD_ONLY_OR_UNIQUE_PIN: return "DOOR_MODE_CARD_ONLY_OR_UNIQUE_PIN";
		case LockEvtCode_DOOR_MODE_EMERGENCY_STATIC_STATE_UNLOCKED: return "DOOR_MODE_EMERGENCY_STATIC_STATE_UNLOCKED";
		case LockEvtCode_DOOR_MODE_EMERGENCY_STATIC_STATE_LOCKED: return "DOOR_MODE_EMERGENCY_STATIC_STATE_LOCKED";
		case LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY: return "DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY";
		case LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN: return "DOOR_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN";
		case LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY: return "DOOR_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY";
		case LockEvtCode_DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN: return "DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN";
		case LockEvtCode_EXIT_REQUESTED: return "EXIT_REQUESTED";
		case LockEvtCode_MOMENTARY_UNLOCK: return "MOMENTARY_UNLOCK";
		case LockEvtCode_DOOR_FORCED_UNMASKED: return "DOOR_FORCED_UNMASKED";
		case LockEvtCode_DOOR_FORCED_MASKED: return "DOOR_FORCED_MASKED";
		case LockEvtCode_DOOR_HELD_UNMASKED: return "DOOR_HELD_UNMASKED";
		case LockEvtCode_DOOR_HELD_MASKED: return "DOOR_HELD_MASKED";
		case LockEvtCode_KEY_OVERRIDE: return "KEY_OVERRIDE";
		case LockEvtCode_DEADBOLT_ACTIVE: return "DEADBOLT_ACTIVE";
		case LockEvtCode_DEADBOLT_INACTIVE: return "DEADBOLT_INACTIVE";
		case LockEvtCode_DOOR_HELD_WARNING: return "DOOR_HELD_WARNING";
		case LockEvtCode_BATTERY_OK: return "BATTERY_OK";
		case LockEvtCode_BATTERY_LOW: return "BATTERY_LOW";
		case LockEvtCode_BATTERY_CRITICAL: return "BATTERY_CRITICAL";
		case LockEvtCode_BATTERY_FAIL: return "BATTERY_FAIL";
		case LockEvtCode_BATTERY_LEVEL: return "BATTERY_LEVEL";
		case LockEvtCode_TAMPER_NORMAL: return "TAMPER_NORMAL";
		case LockEvtCode_TAMPER: return "TAMPER";
		case LockEvtCode_SCHED_ACTIVE: return "SCHED_ACTIVE";
		case LockEvtCode_SCHED_INACTIVE: return "SCHED_INACTIVE";
		case LockEvtCode_DOOR_LOCAL_LOCKED: return "DOOR_LOCAL_LOCKED";
		case LockEvtCode_DOOR_LOCAL_UNLOCKED: return "DOOR_LOCAL_UNLOCKED";
		case LockEvtCode_DOOR_LOCAL_ACCESS_CONTROLLED: return "DOOR_LOCAL_ACCESS_CONTROLLED";
		case LockEvtCode_DOOR_LOCAL_PRIVACY: return "DOOR_LOCAL_PRIVACY";
		case LockEvtCode_DOOR_LOCAL_ESCAPE_AND_RETURN: return "DOOR_LOCAL_ESCAPE_AND_RETURN";
		case LockEvtCode_EXIT_REQUEST_DENIED: return "EXIT_REQUEST_DENIED";
		case LockEvtCode_MOMENTARY_UNLOCK_DENIED: return "MOMENTARY_UNLOCK_DENIED";
		case LockEvtCode_DOOR_LOCAL_NOT_PRIVACY: return "DOOR_LOCAL_NOT_PRIVACY";
		case LockEvtCode_IPB_PRESSED: return "IPB_PRESSED";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockDevActionType_toString(enum LockDevActionType value)
{
	switch (value)
	{
		case LockDevActionType_NONE: return "NONE";
		case LockDevActionType_MOMENTARY_UNLOCK: return "MOMENTARY_UNLOCK";
		case LockDevActionType_RESET_LOCK_MODE: return "RESET_LOCK_MODE";
		case LockDevActionType_SET_LOCK_MODE_STATIC_STATE_UNLOCKED: return "SET_LOCK_MODE_STATIC_STATE_UNLOCKED";
		case LockDevActionType_SET_LOCK_MODE_STATIC_STATE_LOCKED: return "SET_LOCK_MODE_STATIC_STATE_LOCKED";
		case LockDevActionType_SET_LOCK_MODE_CARD_ONLY: return "SET_LOCK_MODE_CARD_ONLY";
		case LockDevActionType_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN: return "SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN";
		case LockDevActionType_SET_LOCK_MODE_UNIQUE_PIN_ONLY: return "SET_LOCK_MODE_UNIQUE_PIN_ONLY";
		case LockDevActionType_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN: return "SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN";
		case LockDevActionType_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED: return "SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED";
		case LockDevActionType_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED: return "SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED";
		case LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY: return "SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY";
		case LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN: return "SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN";
		case LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY: return "SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY";
		case LockDevActionType_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN: return "SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockFunction_toString(enum LockFunction value)
{
	switch (value)
	{
		case LockFunction_NONE: return "NONE";
		case LockFunction_OFFICE: return "OFFICE";
		case LockFunction_APARTMENT: return "APARTMENT";
		case LockFunction_CLASSROOM: return "CLASSROOM";
		case LockFunction_PRIVACY: return "PRIVACY";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockHostGrantFallbackMode_toString(enum LockHostGrantFallbackMode value)
{
	switch (value)
	{
		case LockHostGrantFallbackMode_NONE: return "NONE";
		case LockHostGrantFallbackMode_DENY: return "DENY";
		case LockHostGrantFallbackMode_LOCAL_DECISION: return "LOCAL_DECISION";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockHostGrantInitiationMode_toString(enum LockHostGrantInitiationMode value)
{
	switch (value)
	{
		case LockHostGrantInitiationMode_NEVER: return "NEVER";
		case LockHostGrantInitiationMode_UNKNOWN_CRED: return "UNKNOWN_CRED";
		case LockHostGrantInitiationMode_ALWAYS: return "ALWAYS";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockIdentificationType_toString(enum LockIdentificationType value)
{
	switch (value)
	{
		case LockIdentificationType_NONE: return "NONE";
		case LockIdentificationType_LOCK: return "LOCK";
		case LockIdentificationType_HUB_CONTROLLER: return "HUB_CONTROLLER";
		case LockIdentificationType_MOBILE: return "MOBILE";
		case LockIdentificationType_AUTHORITATIVE_SOURCE: return "AUTHORITATIVE_SOURCE";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockFileCategory_toString(enum LockFileCategory value)
{
	switch (value)
	{
		case LockFileCategory_NONE: return "NONE";
		case LockFileCategory_SOFTWARE_UPDATE: return "SOFTWARE_UPDATE";
		case LockFileCategory_KEYS: return "KEYS";
		case LockFileCategory_LICENSE: return "LICENSE";
		case LockFileCategory_DIAGNOSTICS: return "DIAGNOSTICS";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockFileIdentifier_toString(enum LockFileIdentifier value)
{
	switch (value)
	{
		case LockFileIdentifier_NONE: return "NONE";
		case LockFileIdentifier_DEFAULT: return "DEFAULT";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockHostGrantReqType_toString(enum LockHostGrantReqType value)
{
	switch (value)
	{
		case LockHostGrantReqType_NONE: return "NONE";
		case LockHostGrantReqType_CRED_READ: return "CRED_READ";
		default: return "?";
	}
}
#endif // WITH_LOGGING

#ifdef WITH_LOGGING
const char *LockPolicyPriority_toString(enum LockPolicyPriority value)
{
	switch (value)
	{
		case LockPolicyPriority_DEFAULT: return "DEFAULT";
		case LockPolicyPriority_SCHEDULE: return "SCHEDULE";
		case LockPolicyPriority_POLICY_OVERRIDE: return "POLICY_OVERRIDE";
		case LockPolicyPriority_MANUAL_OVERRIDE: return "MANUAL_OVERRIDE";
		case LockPolicyPriority_EMERGENCY: return "EMERGENCY";
		default: return "?";
	}
}
#endif // WITH_LOGGING
