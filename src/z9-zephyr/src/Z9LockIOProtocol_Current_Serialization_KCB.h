/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9LockIOProtocol_Current_Serialization_KCB.h
 * @author Z9 Security
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Z9LockIOProtocol_Current.h"

struct BasicSerializer_KCB;
struct BasicDeserializer_KCB;

/**
 * Serialize LockCredTechnology.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnology_serialize_KCB(enum LockCredTechnology *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockCredTechnology.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnology_deserialize_KCB(enum LockCredTechnology *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockMode.
 * @return 0 if successful, nonzero on error.
 */
int LockMode_serialize_KCB(enum LockMode *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockMode.
 * @return 0 if successful, nonzero on error.
 */
int LockMode_deserialize_KCB(enum LockMode *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockEvtCode.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtCode_serialize_KCB(enum LockEvtCode *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtCode.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtCode_deserialize_KCB(enum LockEvtCode *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockDevActionType.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionType_serialize_KCB(enum LockDevActionType *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDevActionType.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionType_deserialize_KCB(enum LockDevActionType *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockFunction.
 * @return 0 if successful, nonzero on error.
 */
int LockFunction_serialize_KCB(enum LockFunction *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockFunction.
 * @return 0 if successful, nonzero on error.
 */
int LockFunction_deserialize_KCB(enum LockFunction *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockHostGrantFallbackMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantFallbackMode_serialize_KCB(enum LockHostGrantFallbackMode *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHostGrantFallbackMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantFallbackMode_deserialize_KCB(enum LockHostGrantFallbackMode *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockHostGrantInitiationMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantInitiationMode_serialize_KCB(enum LockHostGrantInitiationMode *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHostGrantInitiationMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantInitiationMode_deserialize_KCB(enum LockHostGrantInitiationMode *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockIdentificationType.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationType_serialize_KCB(enum LockIdentificationType *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockIdentificationType.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationType_deserialize_KCB(enum LockIdentificationType *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockFileCategory.
 * @return 0 if successful, nonzero on error.
 */
int LockFileCategory_serialize_KCB(enum LockFileCategory *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockFileCategory.
 * @return 0 if successful, nonzero on error.
 */
int LockFileCategory_deserialize_KCB(enum LockFileCategory *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockFileIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockFileIdentifier_serialize_KCB(enum LockFileIdentifier *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockFileIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockFileIdentifier_deserialize_KCB(enum LockFileIdentifier *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockHostGrantReqType.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReqType_serialize_KCB(enum LockHostGrantReqType *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHostGrantReqType.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReqType_deserialize_KCB(enum LockHostGrantReqType *self, struct BasicDeserializer_KCB *deserializer);


/**
 * Serialize LockPolicyPriority.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyPriority_serialize_KCB(enum LockPolicyPriority *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPolicyPriority.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyPriority_deserialize_KCB(enum LockPolicyPriority *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDate.
 * @return 0 if successful, nonzero on error.
 */
int LockDate_serialize_KCB(struct LockDate *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDate.
 * @return 0 if successful, nonzero on error.
 */
int LockDate_deserialize_KCB(struct LockDate *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockTimeOfDay_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToMinute_serialize_KCB(struct LockTimeOfDay_ToMinute *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockTimeOfDay_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToMinute_deserialize_KCB(struct LockTimeOfDay_ToMinute *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockTimeOfDay_ToQuarterHour.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToQuarterHour_serialize_KCB(struct LockTimeOfDay_ToQuarterHour *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockTimeOfDay_ToQuarterHour.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToQuarterHour_deserialize_KCB(struct LockTimeOfDay_ToQuarterHour *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockTimeOfDay_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToSecond_serialize_KCB(struct LockTimeOfDay_ToSecond *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockTimeOfDay_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToSecond_deserialize_KCB(struct LockTimeOfDay_ToSecond *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDateTime_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToMinute_serialize_KCB(struct LockDateTime_ToMinute *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDateTime_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToMinute_deserialize_KCB(struct LockDateTime_ToMinute *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDateTime_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToSecond_serialize_KCB(struct LockDateTime_ToSecond *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDateTime_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToSecond_deserialize_KCB(struct LockDateTime_ToSecond *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtContent.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_serialize_KCB(struct LockEvtContent *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtContent.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_deserialize_KCB(struct LockEvtContent *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtDelta.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtDelta_serialize_KCB(struct LockEvtDelta *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtDelta.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtDelta_deserialize_KCB(struct LockEvtDelta *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtModifiers_serialize_KCB(struct LockEvtModifiers *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtModifiers_deserialize_KCB(struct LockEvtModifiers *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockStatus.
 * @return 0 if successful, nonzero on error.
 */
int LockStatus_serialize_KCB(struct LockStatus *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockStatus.
 * @return 0 if successful, nonzero on error.
 */
int LockStatus_deserialize_KCB(struct LockStatus *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDstTransition.
 * @return 0 if successful, nonzero on error.
 */
int LockDstTransition_serialize_KCB(struct LockDstTransition *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDstTransition.
 * @return 0 if successful, nonzero on error.
 */
int LockDstTransition_deserialize_KCB(struct LockDstTransition *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockAccessModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessModifiers_serialize_KCB(struct LockAccessModifiers *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockAccessModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessModifiers_deserialize_KCB(struct LockAccessModifiers *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockCredActions.
 * @return 0 if successful, nonzero on error.
 */
int LockCredActions_serialize_KCB(struct LockCredActions *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockCredActions.
 * @return 0 if successful, nonzero on error.
 */
int LockCredActions_deserialize_KCB(struct LockCredActions *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDevActionPermissions.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionPermissions_serialize_KCB(struct LockDevActionPermissions *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDevActionPermissions.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionPermissions_deserialize_KCB(struct LockDevActionPermissions *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockCredTechnologies.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnologies_serialize_KCB(struct LockCredTechnologies *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockCredTechnologies.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnologies_deserialize_KCB(struct LockCredTechnologies *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockFunctionModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockFunctionModifiers_serialize_KCB(struct LockFunctionModifiers *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockFunctionModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockFunctionModifiers_deserialize_KCB(struct LockFunctionModifiers *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPolicyAssertion.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertion_serialize_KCB(struct LockPolicyAssertion *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPolicyAssertion.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertion_deserialize_KCB(struct LockPolicyAssertion *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockHostGrantConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantConfig_serialize_KCB(struct LockHostGrantConfig *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHostGrantConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantConfig_deserialize_KCB(struct LockHostGrantConfig *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPacketContent.
 * @return 0 if successful, nonzero on error.
 */
int LockPacketContent_serialize_KCB(struct LockPacketContent *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPacketContent.
 * @return 0 if successful, nonzero on error.
 */
int LockPacketContent_deserialize_KCB(struct LockPacketContent *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPaginationReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPaginationReq_serialize_KCB(struct LockPaginationReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPaginationReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPaginationReq_deserialize_KCB(struct LockPaginationReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtContent_None.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_None_serialize_KCB(struct LockEvtContent_None *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtContent_None.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_None_deserialize_KCB(struct LockEvtContent_None *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtContent_BatteryLevel.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_BatteryLevel_serialize_KCB(struct LockEvtContent_BatteryLevel *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtContent_BatteryLevel.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_BatteryLevel_deserialize_KCB(struct LockEvtContent_BatteryLevel *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtContent_CredUnid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_CredUnid_serialize_KCB(struct LockEvtContent_CredUnid *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtContent_CredUnid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_CredUnid_deserialize_KCB(struct LockEvtContent_CredUnid *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtContent_SchedOid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_SchedOid_serialize_KCB(struct LockEvtContent_SchedOid *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtContent_SchedOid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_SchedOid_deserialize_KCB(struct LockEvtContent_SchedOid *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvt.
 * @return 0 if successful, nonzero on error.
 */
int LockEvt_serialize_KCB(struct LockEvt *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvt.
 * @return 0 if successful, nonzero on error.
 */
int LockEvt_deserialize_KCB(struct LockEvt *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockTimeZone.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeZone_serialize_KCB(struct LockTimeZone *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockTimeZone.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeZone_deserialize_KCB(struct LockTimeZone *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockCred.
 * @return 0 if successful, nonzero on error.
 */
int LockCred_serialize_KCB(struct LockCred *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockCred.
 * @return 0 if successful, nonzero on error.
 */
int LockCred_deserialize_KCB(struct LockCred *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtPolicy_serialize_KCB(struct LockEvtPolicy *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtPolicy_deserialize_KCB(struct LockEvtPolicy *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockHol.
 * @return 0 if successful, nonzero on error.
 */
int LockHol_serialize_KCB(struct LockHol *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHol.
 * @return 0 if successful, nonzero on error.
 */
int LockHol_deserialize_KCB(struct LockHol *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockSchedElement.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElement_serialize_KCB(struct LockSchedElement *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockSchedElement.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElement_deserialize_KCB(struct LockSchedElement *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockSchedElementPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElementPolicy_serialize_KCB(struct LockSchedElementPolicy *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockSchedElementPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElementPolicy_deserialize_KCB(struct LockSchedElementPolicy *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockSchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedPolicy_serialize_KCB(struct LockSchedPolicy *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockSchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedPolicy_deserialize_KCB(struct LockSchedPolicy *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockSched.
 * @return 0 if successful, nonzero on error.
 */
int LockSched_serialize_KCB(struct LockSched *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockSched.
 * @return 0 if successful, nonzero on error.
 */
int LockSched_deserialize_KCB(struct LockSched *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockConfig_serialize_KCB(struct LockConfig *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockConfig_deserialize_KCB(struct LockConfig *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifier_serialize_KCB(struct LockEvtIdentifier *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifier_deserialize_KCB(struct LockEvtIdentifier *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtIdentifierRange.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifierRange_serialize_KCB(struct LockEvtIdentifierRange *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtIdentifierRange.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifierRange_deserialize_KCB(struct LockEvtIdentifierRange *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockIdentification.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentification_serialize_KCB(struct LockIdentification *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockIdentification.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentification_deserialize_KCB(struct LockIdentification *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockIdentificationResult.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationResult_serialize_KCB(struct LockIdentificationResult *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockIdentificationResult.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationResult_deserialize_KCB(struct LockIdentificationResult *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbChange_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Config_serialize_KCB(struct LockDbChange_Config *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbChange_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Config_deserialize_KCB(struct LockDbChange_Config *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbChangeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChangeResp_serialize_KCB(struct LockDbChangeResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbChangeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChangeResp_deserialize_KCB(struct LockDbChangeResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtControl.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtControl_serialize_KCB(struct LockEvtControl *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtControl.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtControl_deserialize_KCB(struct LockEvtControl *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockEvtBatch.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtBatch_serialize_KCB(struct LockEvtBatch *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockEvtBatch.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtBatch_deserialize_KCB(struct LockEvtBatch *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDevStateRecordControl.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecordControl_serialize_KCB(struct LockDevStateRecordControl *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDevStateRecordControl.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecordControl_deserialize_KCB(struct LockDevStateRecordControl *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDevStateRecord.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecord_serialize_KCB(struct LockDevStateRecord *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDevStateRecord.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecord_deserialize_KCB(struct LockDevStateRecord *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDateTimeConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTimeConfig_serialize_KCB(struct LockDateTimeConfig *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDateTimeConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTimeConfig_deserialize_KCB(struct LockDateTimeConfig *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockGetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeReq_serialize_KCB(struct LockGetTimeReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockGetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeReq_deserialize_KCB(struct LockGetTimeReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockGetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeResp_serialize_KCB(struct LockGetTimeResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockGetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeResp_deserialize_KCB(struct LockGetTimeResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockSetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeReq_serialize_KCB(struct LockSetTimeReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockSetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeReq_deserialize_KCB(struct LockSetTimeReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockSetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeResp_serialize_KCB(struct LockSetTimeResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockSetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeResp_deserialize_KCB(struct LockSetTimeResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPullFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkReq_serialize_KCB(struct LockPullFileChunkReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPullFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkReq_deserialize_KCB(struct LockPullFileChunkReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPullFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkResp_serialize_KCB(struct LockPullFileChunkResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPullFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkResp_deserialize_KCB(struct LockPullFileChunkResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPushFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkReq_serialize_KCB(struct LockPushFileChunkReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPushFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkReq_deserialize_KCB(struct LockPushFileChunkReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPushFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkResp_serialize_KCB(struct LockPushFileChunkResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPushFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkResp_deserialize_KCB(struct LockPushFileChunkResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockUpgradeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeReq_serialize_KCB(struct LockUpgradeReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockUpgradeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeReq_deserialize_KCB(struct LockUpgradeReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockUpgradeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeResp_serialize_KCB(struct LockUpgradeResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockUpgradeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeResp_deserialize_KCB(struct LockUpgradeResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbQuery.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQuery_serialize_KCB(struct LockDbQuery *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbQuery.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQuery_deserialize_KCB(struct LockDbQuery *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbQueryResp_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Config_serialize_KCB(struct LockDbQueryResp_Config *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbQueryResp_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Config_deserialize_KCB(struct LockDbQueryResp_Config *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockHostGrantReq.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReq_serialize_KCB(struct LockHostGrantReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHostGrantReq.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReq_deserialize_KCB(struct LockHostGrantReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockHostGrantResp.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantResp_serialize_KCB(struct LockHostGrantResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockHostGrantResp.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantResp_deserialize_KCB(struct LockHostGrantResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDevActionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionReq_serialize_KCB(struct LockDevActionReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDevActionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionReq_deserialize_KCB(struct LockDevActionReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDevActionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionResp_serialize_KCB(struct LockDevActionResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDevActionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionResp_deserialize_KCB(struct LockDevActionResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPolicyAssertionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionReq_serialize_KCB(struct LockPolicyAssertionReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPolicyAssertionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionReq_deserialize_KCB(struct LockPolicyAssertionReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPolicyAssertionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionResp_serialize_KCB(struct LockPolicyAssertionResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPolicyAssertionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionResp_deserialize_KCB(struct LockPolicyAssertionResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockConnectionTermination.
 * @return 0 if successful, nonzero on error.
 */
int LockConnectionTermination_serialize_KCB(struct LockConnectionTermination *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockConnectionTermination.
 * @return 0 if successful, nonzero on error.
 */
int LockConnectionTermination_deserialize_KCB(struct LockConnectionTermination *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbChange_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Hol_serialize_KCB(struct LockDbChange_Hol *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbChange_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Hol_deserialize_KCB(struct LockDbChange_Hol *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbChange_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Sched_serialize_KCB(struct LockDbChange_Sched *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbChange_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Sched_deserialize_KCB(struct LockDbChange_Sched *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbChange_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_SchedPolicy_serialize_KCB(struct LockDbChange_SchedPolicy *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbChange_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_SchedPolicy_deserialize_KCB(struct LockDbChange_SchedPolicy *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbChange_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Cred_serialize_KCB(struct LockDbChange_Cred *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbChange_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Cred_deserialize_KCB(struct LockDbChange_Cred *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbQueryResp_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Hol_serialize_KCB(struct LockDbQueryResp_Hol *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbQueryResp_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Hol_deserialize_KCB(struct LockDbQueryResp_Hol *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbQueryResp_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Sched_serialize_KCB(struct LockDbQueryResp_Sched *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbQueryResp_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Sched_deserialize_KCB(struct LockDbQueryResp_Sched *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbQueryResp_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_SchedPolicy_serialize_KCB(struct LockDbQueryResp_SchedPolicy *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbQueryResp_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_SchedPolicy_deserialize_KCB(struct LockDbQueryResp_SchedPolicy *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockDbQueryResp_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Cred_serialize_KCB(struct LockDbQueryResp_Cred *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockDbQueryResp_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Cred_deserialize_KCB(struct LockDbQueryResp_Cred *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockCredAuthorization.
 * @return 0 if successful, nonzero on error.
 */
int LockCredAuthorization_serialize_KCB(struct LockCredAuthorization *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockCredAuthorization.
 * @return 0 if successful, nonzero on error.
 */
int LockCredAuthorization_deserialize_KCB(struct LockCredAuthorization *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockAccessReq.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessReq_serialize_KCB(struct LockAccessReq *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockAccessReq.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessReq_deserialize_KCB(struct LockAccessReq *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockAccessResp.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessResp_serialize_KCB(struct LockAccessResp *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockAccessResp.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessResp_deserialize_KCB(struct LockAccessResp *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPublicKeyExchange.
 * @return 0 if successful, nonzero on error.
 */
int LockPublicKeyExchange_serialize_KCB(struct LockPublicKeyExchange *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPublicKeyExchange.
 * @return 0 if successful, nonzero on error.
 */
int LockPublicKeyExchange_deserialize_KCB(struct LockPublicKeyExchange *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockMobileBleChallengeNonce.
 * @return 0 if successful, nonzero on error.
 */
int LockMobileBleChallengeNonce_serialize_KCB(struct LockMobileBleChallengeNonce *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockMobileBleChallengeNonce.
 * @return 0 if successful, nonzero on error.
 */
int LockMobileBleChallengeNonce_deserialize_KCB(struct LockMobileBleChallengeNonce *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockBundleHeader.
 * @return 0 if successful, nonzero on error.
 */
int LockBundleHeader_serialize_KCB(struct LockBundleHeader *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockBundleHeader.
 * @return 0 if successful, nonzero on error.
 */
int LockBundleHeader_deserialize_KCB(struct LockBundleHeader *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockOpaqueContent.
 * @return 0 if successful, nonzero on error.
 */
int LockOpaqueContent_serialize_KCB(struct LockOpaqueContent *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockOpaqueContent.
 * @return 0 if successful, nonzero on error.
 */
int LockOpaqueContent_deserialize_KCB(struct LockOpaqueContent *self, struct BasicDeserializer_KCB *deserializer);



/**
 * Serialize LockPacket.
 * @return 0 if successful, nonzero on error.
 */
int LockPacket_serialize_KCB(struct LockPacket *self, struct BasicSerializer_KCB *serializer);
/**
 * Deserialize LockPacket.
 * @return 0 if successful, nonzero on error.
 */
int LockPacket_deserialize_KCB(struct LockPacket *self, struct BasicDeserializer_KCB *deserializer);

