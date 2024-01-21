// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

// Z9LockIOProtocol_Current_MetaData.h

#include "ProtocolMetadata.h"
#include "Z9LockIOProtocol_Current.h"

namespace z9::drivers::z9lockio::protocol
{

using meta::list;

using Z9_TYPES = list<
	list<LockDate, Z9_STRING("LockDate"),
		list<
			Z9_MEMBER(LockDate, 2, year, uint16_t),
			Z9_MEMBER(LockDate, 1, month, uint8_t),
			Z9_MEMBER(LockDate, 1, day, uint8_t)
		>
	>,

	list<LockTimeOfDay_ToMinute, Z9_STRING("LockTimeOfDay_ToMinute"),
		list<
			Z9_MEMBER(LockTimeOfDay_ToMinute, 1, hour, uint8_t),
			Z9_MEMBER(LockTimeOfDay_ToMinute, 1, minute, uint8_t)
		>
	>,

	list<LockTimeOfDay_ToQuarterHour, Z9_STRING("LockTimeOfDay_ToQuarterHour"),
		list<
			Z9_MEMBER(LockTimeOfDay_ToQuarterHour, 1, quarterHour, uint8_t)
		>
	>,

	list<LockTimeOfDay_ToSecond, Z9_STRING("LockTimeOfDay_ToSecond"),
		list<
			Z9_MEMBER(LockTimeOfDay_ToSecond, 1, hour, uint8_t),
			Z9_MEMBER(LockTimeOfDay_ToSecond, 1, minute, uint8_t),
			Z9_MEMBER(LockTimeOfDay_ToSecond, 1, second, uint8_t)
		>
	>,

	list<LockDateTime_ToMinute, Z9_STRING("LockDateTime_ToMinute"),
		list<
			Z9_MEMBER(LockDateTime_ToMinute, 2, year, uint16_t),
			Z9_MEMBER(LockDateTime_ToMinute, 1, month, uint8_t),
			Z9_MEMBER(LockDateTime_ToMinute, 1, day, uint8_t),
			Z9_MEMBER(LockDateTime_ToMinute, 1, hour, uint8_t),
			Z9_MEMBER(LockDateTime_ToMinute, 1, minute, uint8_t)
		>
	>,

	list<LockDateTime_ToSecond, Z9_STRING("LockDateTime_ToSecond"),
		list<
			Z9_MEMBER(LockDateTime_ToSecond, 2, year, uint16_t),
			Z9_MEMBER(LockDateTime_ToSecond, 1, month, uint8_t),
			Z9_MEMBER(LockDateTime_ToSecond, 1, day, uint8_t),
			Z9_MEMBER(LockDateTime_ToSecond, 1, hour, uint8_t),
			Z9_MEMBER(LockDateTime_ToSecond, 1, minute, uint8_t),
			Z9_MEMBER(LockDateTime_ToSecond, 1, second, uint8_t)
		>
	>,

	list<LockEvtContent, Z9_STRING("LockEvtContent"),
		list<
			Z9_MEMBER(LockEvtContent, 1, contentType, int8_t)
			// TODO: variable   |            |            | discriminator-specific content
		>
	>,

	list<LockEvtDelta, Z9_STRING("LockEvtDelta"),
		list<
			Z9_MEMBER(LockEvtDelta, 1, suppress, bool),
			Z9_MEMBER(LockEvtDelta, 1, priority, bool)
		>
	>,

	list<LockEvtModifiers, Z9_STRING("LockEvtModifiers"),
		list<
			Z9_MEMBER(LockEvtModifiers, 1, priority, bool),
			Z9_MEMBER(LockEvtModifiers, 1, hostGrant, bool),
			Z9_MEMBER(LockEvtModifiers, 1, mobileGrant, bool),
			Z9_MEMBER(LockEvtModifiers, 1, usedCard, bool),
			Z9_MEMBER(LockEvtModifiers, 1, usedPin, bool),
			Z9_MEMBER(LockEvtModifiers, 1, emergency, bool),
			Z9_MEMBER(LockEvtModifiers, 1, doublePresentation, bool)
		>
	>,

	list<LockDstTransition, Z9_STRING("LockDstTransition"),
		list<
			Z9_MEMBER(LockDstTransition, 1, month, uint8_t),
			Z9_MEMBER(LockDstTransition, 1, nth, uint8_t),
			Z9_MEMBER(LockDstTransition, 1, dayOfWeek, uint8_t),
			Z9_MEMBER(LockDstTransition, 1, hour, uint8_t)
		>
	>,

	list<LockAccessModifiers, Z9_STRING("LockAccessModifiers"),
		list<
			Z9_MEMBER(LockAccessModifiers, 1, extDoorTime, bool),
			Z9_MEMBER(LockAccessModifiers, 1, administrator, bool),
			Z9_MEMBER(LockAccessModifiers, 1, privacyExempt, bool),
			Z9_MEMBER(LockAccessModifiers, 1, staticStateLockedExempt, bool),
			Z9_MEMBER(LockAccessModifiers, 1, emergencyStaticStateLockedExempt, bool),
			Z9_MEMBER(LockAccessModifiers, 1, emergency, bool),
			Z9_MEMBER(LockAccessModifiers, 1, firstCredUnlock, bool),
			Z9_MEMBER(LockAccessModifiers, 1, pinUnique, bool)
		>
	>,

	list<LockCredActions, Z9_STRING("LockCredActions"),
		list<
			Z9_MEMBER(LockCredActions, 1, access, bool),
			Z9_MEMBER(LockCredActions, 1, setLockMode_STATIC_STATE_UNLOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, setLockMode_STATIC_STATE_LOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, setLockMode_EMERGENCY_STATIC_STATE_LOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, cancelLockMode_STATIC_STATE_UNLOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, cancelLockMode_STATIC_STATE_LOCKED, bool),
			Z9_MEMBER(LockCredActions, 1, cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED, bool)
		>
	>,

	list<LockDevActionPermissions, Z9_STRING("LockDevActionPermissions"),
		list<
			Z9_MEMBER(LockDevActionPermissions, 1, allow_MOMENTARY_UNLOCK, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_RESET_LOCK_MODE, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_STATIC_STATE_LOCKED, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_CARD_ONLY, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY, bool),
			Z9_MEMBER(LockDevActionPermissions, 1, allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN, bool)
		>
	>,

	list<LockCredTechnologies, Z9_STRING("LockCredTechnologies"),
		list<
			Z9_MEMBER(LockCredTechnologies, 1, enable_PROX, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_BLUETOOTH_ANY, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_NFC_ANY, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_DESFIRE_ANY, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_ICLASS_ANY, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_BLUETOOTH_WAVELYNX, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_BLUETOOTH_Z9_WAVELYNX, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_NFC_GOOGLE, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_NFC_APPLE, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_DESFIRE_LEAF, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_DESFIRE_UID, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_ICLASS_FULL, bool),
			Z9_MEMBER(LockCredTechnologies, 1, enable_ICLASS_UID, bool)
		>
	>,

	list<LockFunctionModifiers, Z9_STRING("LockFunctionModifiers"),
		list<
			Z9_MEMBER(LockFunctionModifiers, 1, ipbUnlockDuration, uint8_t),
			Z9_MEMBER(LockFunctionModifiers, 2, escapeAndReturnDuration, uint16_t)
		>
	>,

	list<LockPacketContent, Z9_STRING("LockPacketContent"),
		list<
			Z9_MEMBER(LockPacketContent, 1, contentType, int8_t)
			// TODO: variable   |            |            | discriminator-specific content
		>
	>,

	list<LockPaginationReq, Z9_STRING("LockPaginationReq"),
		list<
			Z9_MEMBER(LockPaginationReq, 4, aboveIndex, int32_t),
			Z9_MEMBER(LockPaginationReq, 2, pageSize, uint16_t)
		>
	>,

	list<LockEvtContent_None, Z9_STRING("LockEvtContent_None"),
		list<
		>
	>,

	list<LockEvtContent_BatteryLevel, Z9_STRING("LockEvtContent_BatteryLevel"),
		list<
			Z9_MEMBER(LockEvtContent_BatteryLevel, 2, batteryLevel, uint16_t)
		>
	>,

	list<LockEvtContent_CredUnid, Z9_STRING("LockEvtContent_CredUnid"),
		list<
			Z9_MEMBER(LockEvtContent_CredUnid, 1, credTechnology, LockCredTechnology),
			Z9_MEMBER(LockEvtContent_CredUnid, 4, credUnid, uint32_t)
		>
	>,

	list<LockEvtContent_SchedOid, Z9_STRING("LockEvtContent_SchedOid"),
		list<
			Z9_MEMBER(LockEvtContent_SchedOid, 1, schedOid, uint8_t)
		>
	>,

	list<LockEvt, Z9_STRING("LockEvt"),
		list<
			Z9_MEMBER(LockEvt, 7, dateTime, LockDateTime_ToSecond),
			Z9_MEMBER(LockEvt, 1, evtCode, LockEvtCode),
			Z9_MEMBER(LockEvt, 7, modifiers, LockEvtModifiers)
			// TODO: 1 to 6 bytes | `content`  | LockEvtContent | discriminator-based structure
		>
	>,

	list<LockStatus, Z9_STRING("LockStatus"),
		list<
			Z9_MEMBER(LockStatus, 1, mode, LockMode),
			Z9_MEMBER(LockStatus, 1, tamper, bool),
			Z9_MEMBER(LockStatus, 1, batteryLow, bool),
			Z9_MEMBER(LockStatus, 1, batteryCritical, bool),
			Z9_MEMBER(LockStatus, 1, unlocked, bool),
			Z9_MEMBER(LockStatus, 1, open, bool),
			Z9_MEMBER(LockStatus, 1, forced, bool),
			Z9_MEMBER(LockStatus, 1, held, bool),
			Z9_MEMBER(LockStatus, 1, deadboltExtended, bool),
			Z9_MEMBER(LockStatus, 1, privacy, bool),
			Z9_MEMBER(LockStatus, 2, batteryLevel, int16_t)
		>
	>,

	list<LockTimeZone, Z9_STRING("LockTimeZone"),
		list<
			Z9_MEMBER(LockTimeZone, 2, standardOffset, int16_t),
			Z9_MEMBER(LockTimeZone, 2, dstOffset, int16_t),
			Z9_MEMBER(LockTimeZone, 4, standardTransition, LockDstTransition),
			Z9_MEMBER(LockTimeZone, 4, dstTransition, LockDstTransition)
		>
	>,

	list<LockCred, Z9_STRING("LockCred"),
		list<
			Z9_MEMBER(LockCred, 4, unid, uint32_t),
			Z9_MEMBER(LockCred, 4, effective, LockDate),
			Z9_MEMBER(LockCred, 4, expires, LockDate),
			Z9_MEMBER(LockCred, 1, technology, LockCredTechnology),
			Z9_MEMBER(LockCred, 8, accessModifiers, LockAccessModifiers),
			Z9_MEMBER(LockCred, 9, presentationActions, LockCredActions),
			Z9_MEMBER(LockCred, 9, doublePresentationActions, LockCredActions),
			Z9_MEMBER(LockCred, 14, explicitActionPermissions, LockDevActionPermissions),
			Z9_MEMBER(LockCred, 1, trimBitsInLastCredByte, int8_t),
			Z9_MEMBER(LockCred, 17, credBytes, variableArray<16, uint8_t, uint8_t>)
			// TODO: 4 elements (4 bytes) | `pinDigitNybbles` | uint8_t    | 
			// TODO: 2 elements (2 bytes) | `schedMaskBytes` | uint8_t    | 
		>
	>,

	list<LockEvtPolicy, Z9_STRING("LockEvtPolicy"),
		list<
			Z9_MEMBER(LockEvtPolicy, 1, evtCode, LockEvtCode),
			Z9_MEMBER(LockEvtPolicy, 2, evtDelta, LockEvtDelta)
		>
	>,

	list<LockHol, Z9_STRING("LockHol"),
		list<
			Z9_MEMBER(LockHol, 6, start, LockDateTime_ToMinute),
			Z9_MEMBER(LockHol, 6, stop, LockDateTime_ToMinute),
			Z9_MEMBER(LockHol, 1, holTypes, uint8_t)
		>
	>,

	list<LockSchedElement, Z9_STRING("LockSchedElement"),
		list<
			Z9_MEMBER(LockSchedElement, 1, start, LockTimeOfDay_ToQuarterHour),
			Z9_MEMBER(LockSchedElement, 1, stop, LockTimeOfDay_ToQuarterHour),
			Z9_MEMBER(LockSchedElement, 1, plusDays, uint8_t),
			Z9_MEMBER(LockSchedElement, 1, daysOfWeek, int8_t),
			Z9_MEMBER(LockSchedElement, 1, holTypes, uint8_t)
		>
	>,

	list<LockPolicyAssertion, Z9_STRING("LockPolicyAssertion"),
		list<
			Z9_MEMBER(LockPolicyAssertion, 1, mode, LockMode),
			Z9_MEMBER(LockPolicyAssertion, 1, setDoorForcedMasking, bool),
			Z9_MEMBER(LockPolicyAssertion, 1, doorForcedMasking, bool),
			Z9_MEMBER(LockPolicyAssertion, 1, setDoorHeldMasking, bool),
			Z9_MEMBER(LockPolicyAssertion, 1, doorHeldMasking, bool),
			Z9_MEMBER(LockPolicyAssertion, 1, setPrivacy, bool),
			Z9_MEMBER(LockPolicyAssertion, 1, privacy, bool)
		>
	>,

	list<LockSchedElementPolicy, Z9_STRING("LockSchedElementPolicy"),
		list<
			Z9_MEMBER(LockSchedElementPolicy, 7, assertion, LockPolicyAssertion)
		>
	>,

	list<LockSchedPolicy, Z9_STRING("LockSchedPolicy"),
		list<
			Z9_MEMBER(LockSchedPolicy, 1, schedOid, uint8_t),
			Z9_MEMBER(LockSchedPolicy, 1, action, LockDevActionType),
			Z9_MEMBER(LockSchedPolicy, 57, elements, variableArray<8, int8_t, LockSchedElementPolicy>)
		>
	>,

	list<LockSched, Z9_STRING("LockSched"),
		list<
			Z9_MEMBER(LockSched, 4, unid, uint32_t),
			Z9_MEMBER(LockSched, 6, effective, LockDateTime_ToMinute),
			Z9_MEMBER(LockSched, 6, expires, LockDateTime_ToMinute),
			Z9_MEMBER(LockSched, 41, elements, variableArray<8, int8_t, LockSchedElement>)
		>
	>,

	list<LockHostGrantConfig, Z9_STRING("LockHostGrantConfig"),
		list<
			Z9_MEMBER(LockHostGrantConfig, 1, initiationMode, LockHostGrantInitiationMode),
			Z9_MEMBER(LockHostGrantConfig, 1, timeout, uint8_t),
			Z9_MEMBER(LockHostGrantConfig, 1, fallbackMode, LockHostGrantFallbackMode)
		>
	>,

	list<LockConfig, Z9_STRING("LockConfig"),
		list<
			Z9_MEMBER(LockConfig, 13, credTechnologies, LockCredTechnologies),
			Z9_MEMBER(LockConfig, 1, function, LockFunction),
			Z9_MEMBER(LockConfig, 3, functionModifiers, LockFunctionModifiers),
			Z9_MEMBER(LockConfig, 1, strikeTime, uint8_t),
			Z9_MEMBER(LockConfig, 1, extendedStrikeTime, uint8_t),
			Z9_MEMBER(LockConfig, 1, heldTime, uint8_t),
			Z9_MEMBER(LockConfig, 1, extendedHeldTime, uint8_t),
			Z9_MEMBER(LockConfig, 1, defaultDoorForcedMasking, bool),
			Z9_MEMBER(LockConfig, 1, defaultDoorHeldMasking, bool),
			Z9_MEMBER(LockConfig, 1, defaultLockMode, LockMode),
			Z9_MEMBER(LockConfig, 3, hostGrantConfig, LockHostGrantConfig),
			Z9_MEMBER(LockConfig, 1, maxPinLength, uint8_t),
			Z9_MEMBER(LockConfig, 12, timeZone, LockTimeZone),
			Z9_MEMBER(LockConfig, 97, evtPolicies, variableArray<32, uint8_t, LockEvtPolicy>)
		>
	>,

	list<LockEvtIdentifier, Z9_STRING("LockEvtIdentifier"),
		list<
			Z9_MEMBER(LockEvtIdentifier, 7, dateTime, LockDateTime_ToSecond),
			Z9_MEMBER(LockEvtIdentifier, 1, evtCode, LockEvtCode)
		>
	>,

	list<LockEvtIdentifierRange, Z9_STRING("LockEvtIdentifierRange"),
		list<
			Z9_MEMBER(LockEvtIdentifierRange, 8, start, LockEvtIdentifier),
			Z9_MEMBER(LockEvtIdentifierRange, 8, stop, LockEvtIdentifier)
		>
	>,

	list<LockIdentification, Z9_STRING("LockIdentification"),
		list<
			Z9_MEMBER(LockIdentification, 1, protocolVersionMajor, uint8_t),
			Z9_MEMBER(LockIdentification, 1, protocolVersionMinor, uint8_t),
			Z9_MEMBER(LockIdentification, 1, type, LockIdentificationType),
			Z9_MEMBER(LockIdentification, 8, id, uint64_t),
			Z9_MEMBER(LockIdentification, 1, model, uint8_t),
			Z9_MEMBER(LockIdentification, 1, brand, uint8_t),
			Z9_MEMBER(LockIdentification, 1, firmwareVersionMajor, uint8_t),
			Z9_MEMBER(LockIdentification, 1, firmwareVersionMinor, uint8_t),
			Z9_MEMBER(LockIdentification, 1, licensed, bool)
		>
	>,

	list<LockIdentificationResult, Z9_STRING("LockIdentificationResult"),
		list<
			Z9_MEMBER(LockIdentificationResult, 2, errorCode, int16_t)
		>
	>,

	list<LockDbChange_Config, Z9_STRING("LockDbChange_Config"),
		list<
			Z9_MEMBER(LockDbChange_Config, 8, requestId, int64_t),
			Z9_MEMBER(LockDbChange_Config, 138, updateConfig, variableArray<1, int8_t, LockConfig>)
		>
	>,

	list<LockDbChangeResp, Z9_STRING("LockDbChangeResp"),
		list<
			Z9_MEMBER(LockDbChangeResp, 8, requestId, int64_t),
			Z9_MEMBER(LockDbChangeResp, 2, errorCode, int16_t)
		>
	>,

	list<LockEvtControl, Z9_STRING("LockEvtControl"),
		list<
			Z9_MEMBER(LockEvtControl, 1, priority, bool),
			Z9_MEMBER(LockEvtControl, 1, sendOneBatch, bool),
			Z9_MEMBER(LockEvtControl, 16, consume, LockEvtIdentifierRange)
		>
	>,

	list<LockEvtBatch, Z9_STRING("LockEvtBatch"),
		list<
			Z9_MEMBER(LockEvtBatch, 1, priority, bool),
			Z9_MEMBER(LockEvtBatch, 673, evt, variableArray<32, uint8_t, LockEvt>)
		>
	>,

	list<LockDevStateRecordControl, Z9_STRING("LockDevStateRecordControl"),
		list<
		>
	>,

	list<LockDevStateRecord, Z9_STRING("LockDevStateRecord"),
		list<
			Z9_MEMBER(LockDevStateRecord, 12, status, LockStatus)
		>
	>,

	list<LockDateTimeConfig, Z9_STRING("LockDateTimeConfig"),
		list<
			Z9_MEMBER(LockDateTimeConfig, 7, dateTime, LockDateTime_ToSecond),
			Z9_MEMBER(LockDateTimeConfig, 1, timeZonePresent, bool),
			Z9_MEMBER(LockDateTimeConfig, 12, timeZone, LockTimeZone)
		>
	>,

	list<LockGetTimeReq, Z9_STRING("LockGetTimeReq"),
		list<
		>
	>,

	list<LockGetTimeResp, Z9_STRING("LockGetTimeResp"),
		list<
			Z9_MEMBER(LockGetTimeResp, 20, dateTimeConfig, LockDateTimeConfig)
		>
	>,

	list<LockSetTimeReq, Z9_STRING("LockSetTimeReq"),
		list<
			Z9_MEMBER(LockSetTimeReq, 20, dateTimeConfig, LockDateTimeConfig)
		>
	>,

	list<LockSetTimeResp, Z9_STRING("LockSetTimeResp"),
		list<
			Z9_MEMBER(LockSetTimeResp, 2, errorCode, int16_t)
		>
	>,

	list<LockPullFileChunkReq, Z9_STRING("LockPullFileChunkReq"),
		list<
			Z9_MEMBER(LockPullFileChunkReq, 2, requestId, uint16_t),
			Z9_MEMBER(LockPullFileChunkReq, 1, category, LockFileCategory),
			Z9_MEMBER(LockPullFileChunkReq, 1, id, LockFileIdentifier),
			Z9_MEMBER(LockPullFileChunkReq, 8, offset, uint64_t),
			Z9_MEMBER(LockPullFileChunkReq, 2, maxLength, uint16_t)
		>
	>,

	list<LockPullFileChunkResp, Z9_STRING("LockPullFileChunkResp"),
		list<
			Z9_MEMBER(LockPullFileChunkResp, 2, requestId, uint16_t),
			Z9_MEMBER(LockPullFileChunkResp, 2, errorCode, int16_t),
			Z9_MEMBER(LockPullFileChunkResp, 1, eof, bool),
			Z9_MEMBER(LockPullFileChunkResp, 802, bytes, variableArray<800, int16_t, uint8_t>)
		>
	>,

	list<LockPushFileChunkReq, Z9_STRING("LockPushFileChunkReq"),
		list<
			Z9_MEMBER(LockPushFileChunkReq, 2, requestId, uint16_t),
			Z9_MEMBER(LockPushFileChunkReq, 1, category, LockFileCategory),
			Z9_MEMBER(LockPushFileChunkReq, 1, id, LockFileIdentifier),
			Z9_MEMBER(LockPushFileChunkReq, 8, offset, uint64_t),
			Z9_MEMBER(LockPushFileChunkReq, 1, eof, bool),
			Z9_MEMBER(LockPushFileChunkReq, 802, bytes, variableArray<800, int16_t, uint8_t>)
		>
	>,

	list<LockPushFileChunkResp, Z9_STRING("LockPushFileChunkResp"),
		list<
			Z9_MEMBER(LockPushFileChunkResp, 2, requestId, uint16_t),
			Z9_MEMBER(LockPushFileChunkResp, 2, errorCode, int16_t)
		>
	>,

	list<LockUpgradeReq, Z9_STRING("LockUpgradeReq"),
		list<
			Z9_MEMBER(LockUpgradeReq, 2, requestId, uint16_t),
			Z9_MEMBER(LockUpgradeReq, 1, fileId, LockFileIdentifier),
			Z9_MEMBER(LockUpgradeReq, 2, rebootDelay, uint16_t)
		>
	>,

	list<LockUpgradeResp, Z9_STRING("LockUpgradeResp"),
		list<
			Z9_MEMBER(LockUpgradeResp, 2, requestId, uint16_t),
			Z9_MEMBER(LockUpgradeResp, 2, errorCode, int16_t)
		>
	>,

	list<LockDbQuery, Z9_STRING("LockDbQuery"),
		list<
			Z9_MEMBER(LockDbQuery, 2, requestId, int16_t),
			Z9_MEMBER(LockDbQuery, 1, queryConfig, bool),
			Z9_MEMBER(LockDbQuery, 1, queryHol, bool),
			Z9_MEMBER(LockDbQuery, 1, querySched, bool),
			Z9_MEMBER(LockDbQuery, 1, querySchedPolicy, bool),
			Z9_MEMBER(LockDbQuery, 1, queryCred, bool),
			Z9_MEMBER(LockDbQuery, 6, paginationCred, LockPaginationReq)
		>
	>,

	list<LockDbQueryResp_Config, Z9_STRING("LockDbQueryResp_Config"),
		list<
			Z9_MEMBER(LockDbQueryResp_Config, 2, requestId, int16_t),
			Z9_MEMBER(LockDbQueryResp_Config, 2, errorCode, int16_t),
			Z9_MEMBER(LockDbQueryResp_Config, 138, config, variableArray<1, int8_t, LockConfig>)
		>
	>,

	list<LockHostGrantReq, Z9_STRING("LockHostGrantReq"),
		list<
			Z9_MEMBER(LockHostGrantReq, 2, requestId, int16_t),
			Z9_MEMBER(LockHostGrantReq, 1, type, LockHostGrantReqType),
			Z9_MEMBER(LockHostGrantReq, 1, lockMode, LockMode),
			Z9_MEMBER(LockHostGrantReq, 1, privacy, bool),
			Z9_MEMBER(LockHostGrantReq, 77, rawCred, LockCred)
		>
	>,

	list<LockHostGrantResp, Z9_STRING("LockHostGrantResp"),
		list<
			Z9_MEMBER(LockHostGrantResp, 2, requestId, int16_t),
			Z9_MEMBER(LockHostGrantResp, 2, errorCode, int16_t),
			Z9_MEMBER(LockHostGrantResp, 77, dbCred, LockCred),
			Z9_MEMBER(LockHostGrantResp, 1, evtCode, LockEvtCode)
		>
	>,

	list<LockDevActionReq, Z9_STRING("LockDevActionReq"),
		list<
			Z9_MEMBER(LockDevActionReq, 2, requestId, int16_t),
			Z9_MEMBER(LockDevActionReq, 1, actionType, LockDevActionType),
			Z9_MEMBER(LockDevActionReq, 2, durationSecs, int16_t),
			Z9_MEMBER(LockDevActionReq, 1, policyPriority, LockPolicyPriority)
		>
	>,

	list<LockDevActionResp, Z9_STRING("LockDevActionResp"),
		list<
			Z9_MEMBER(LockDevActionResp, 2, requestId, int16_t),
			Z9_MEMBER(LockDevActionResp, 2, errorCode, int16_t)
		>
	>,

	list<LockPolicyAssertionReq, Z9_STRING("LockPolicyAssertionReq"),
		list<
			Z9_MEMBER(LockPolicyAssertionReq, 2, requestId, int16_t),
			Z9_MEMBER(LockPolicyAssertionReq, 1, priority, LockPolicyPriority),
			Z9_MEMBER(LockPolicyAssertionReq, 1, state, bool),
			Z9_MEMBER(LockPolicyAssertionReq, 1, temporary, bool),
			Z9_MEMBER(LockPolicyAssertionReq, 7, assertion, LockPolicyAssertion)
		>
	>,

	list<LockPolicyAssertionResp, Z9_STRING("LockPolicyAssertionResp"),
		list<
			Z9_MEMBER(LockPolicyAssertionResp, 2, requestId, int16_t),
			Z9_MEMBER(LockPolicyAssertionResp, 2, errorCode, int16_t)
		>
	>,

	list<LockConnectionTermination, Z9_STRING("LockConnectionTermination"),
		list<
		>
	>,

	list<LockDbChange_Hol, Z9_STRING("LockDbChange_Hol"),
		list<
			Z9_MEMBER(LockDbChange_Hol, 8, requestId, int64_t),
			Z9_MEMBER(LockDbChange_Hol, 417, hol, variableArray<32, uint8_t, LockHol>)
		>
	>,

	list<LockDbChange_Sched, Z9_STRING("LockDbChange_Sched"),
		list<
			Z9_MEMBER(LockDbChange_Sched, 8, requestId, int64_t),
			Z9_MEMBER(LockDbChange_Sched, 856, sched, variableArray<15, uint8_t, LockSched>)
		>
	>,

	list<LockDbChange_SchedPolicy, Z9_STRING("LockDbChange_SchedPolicy"),
		list<
			Z9_MEMBER(LockDbChange_SchedPolicy, 8, requestId, int64_t),
			Z9_MEMBER(LockDbChange_SchedPolicy, 473, schedPolicy, variableArray<8, uint8_t, LockSchedPolicy>)
		>
	>,

	list<LockDbChange_Cred, Z9_STRING("LockDbChange_Cred"),
		list<
			Z9_MEMBER(LockDbChange_Cred, 8, requestId, int64_t),
			Z9_MEMBER(LockDbChange_Cred, 1, deleteAllCred, bool),
			Z9_MEMBER(LockDbChange_Cred, 1233, upsertOrDeleteCred, variableArray<16, uint8_t, LockCred>)
		>
	>,

	list<LockDbQueryResp_Hol, Z9_STRING("LockDbQueryResp_Hol"),
		list<
			Z9_MEMBER(LockDbQueryResp_Hol, 2, requestId, int16_t),
			Z9_MEMBER(LockDbQueryResp_Hol, 2, errorCode, int16_t),
			Z9_MEMBER(LockDbQueryResp_Hol, 833, hol, variableArray<64, uint8_t, LockHol>)
		>
	>,

	list<LockDbQueryResp_Sched, Z9_STRING("LockDbQueryResp_Sched"),
		list<
			Z9_MEMBER(LockDbQueryResp_Sched, 2, requestId, int16_t),
			Z9_MEMBER(LockDbQueryResp_Sched, 2, errorCode, int16_t),
			Z9_MEMBER(LockDbQueryResp_Sched, 856, sched, variableArray<15, uint8_t, LockSched>)
		>
	>,

	list<LockDbQueryResp_SchedPolicy, Z9_STRING("LockDbQueryResp_SchedPolicy"),
		list<
			Z9_MEMBER(LockDbQueryResp_SchedPolicy, 2, requestId, int16_t),
			Z9_MEMBER(LockDbQueryResp_SchedPolicy, 2, errorCode, int16_t),
			Z9_MEMBER(LockDbQueryResp_SchedPolicy, 473, schedPolicy, variableArray<8, uint8_t, LockSchedPolicy>)
		>
	>,

	list<LockDbQueryResp_Cred, Z9_STRING("LockDbQueryResp_Cred"),
		list<
			Z9_MEMBER(LockDbQueryResp_Cred, 2, requestId, int16_t),
			Z9_MEMBER(LockDbQueryResp_Cred, 2, errorCode, int16_t),
			Z9_MEMBER(LockDbQueryResp_Cred, 1233, cred, variableArray<16, uint8_t, LockCred>)
		>
	>,

	list<LockCredAuthorization, Z9_STRING("LockCredAuthorization"),
		list<
			Z9_MEMBER(LockCredAuthorization, 8, mobileId, uint64_t),
			Z9_MEMBER(LockCredAuthorization, 8, lockId, uint64_t),
			Z9_MEMBER(LockCredAuthorization, 77, cred, LockCred),
			Z9_MEMBER(LockCredAuthorization, 61, schedUnids, variableArray<15, uint8_t, uint32_t>),
			Z9_MEMBER(LockCredAuthorization, 17, sharedSecretBytes, variableArray<16, int8_t, uint8_t>)
		>
	>,

	list<LockAccessReq, Z9_STRING("LockAccessReq"),
		list<
			Z9_MEMBER(LockAccessReq, 2, requestId, int16_t),
			Z9_MEMBER(LockAccessReq, 8, mobileId, uint64_t)
		>
	>,

	list<LockAccessResp, Z9_STRING("LockAccessResp"),
		list<
			Z9_MEMBER(LockAccessResp, 2, requestId, int16_t),
			Z9_MEMBER(LockAccessResp, 2, errorCode, int16_t),
			Z9_MEMBER(LockAccessResp, 1, granted, bool)
		>
	>,

	list<LockPublicKeyExchange, Z9_STRING("LockPublicKeyExchange"),
		list<
			Z9_MEMBER(LockPublicKeyExchange, 66, publicKeyBytes, variableArray<65, int8_t, uint8_t>)
		>
	>,

	list<LockMobileBleChallengeNonce, Z9_STRING("LockMobileBleChallengeNonce"),
		list<
			Z9_MEMBER(LockMobileBleChallengeNonce, 17, nonceBytes, variableArray<16, int8_t, uint8_t>)
		>
	>,

	list<LockBundleHeader, Z9_STRING("LockBundleHeader"),
		list<
			Z9_MEMBER(LockBundleHeader, 1, origin, LockIdentificationType),
			Z9_MEMBER(LockBundleHeader, 1, intermediary, LockIdentificationType),
			Z9_MEMBER(LockBundleHeader, 1, destination, LockIdentificationType),
			Z9_MEMBER(LockBundleHeader, 8, originId, uint64_t),
			Z9_MEMBER(LockBundleHeader, 8, intermediaryId, uint64_t),
			Z9_MEMBER(LockBundleHeader, 8, destinationId, uint64_t),
			Z9_MEMBER(LockBundleHeader, 7, expires, LockDateTime_ToSecond),
			Z9_MEMBER(LockBundleHeader, 1, opaque, bool),
			Z9_MEMBER(LockBundleHeader, 1, packetCount, int8_t)
		>
	>,

	list<LockOpaqueContent, Z9_STRING("LockOpaqueContent"),
		list<
			Z9_MEMBER(LockOpaqueContent, 1025, opaqueBytes, variableArray<1023, int16_t, uint8_t>)
		>
	>,

	list<LockPacket, Z9_STRING("LockPacket"),
		list<
			Z9_MEMBER(LockPacket, 2, headerBytes, int16_t),
			Z9_MEMBER(LockPacket, 2, bytecount, int16_t)
			// TODO: 1 to 1243 bytes | `content`  | LockPacketContent | discriminator-based structure
		>
	>
>;

}

