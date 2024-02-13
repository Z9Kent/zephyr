/*
 * Copyright (C) 2011-Infinity Z9 Security. All rights reserved.
 */

/**
 * @file Z9LockIOProtocol_Current_Serialization.h
 * @author Z9 Security
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "Z9LockIOProtocol_Current.h"

struct BasicSerializer;
struct BasicDeserializer;

/**
 * Serialize LockCredTechnology.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnology_serialize(enum LockCredTechnology *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockCredTechnology.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnology_deserialize(enum LockCredTechnology *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockMode.
 * @return 0 if successful, nonzero on error.
 */
int LockMode_serialize(enum LockMode *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockMode.
 * @return 0 if successful, nonzero on error.
 */
int LockMode_deserialize(enum LockMode *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockEvtCode.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtCode_serialize(enum LockEvtCode *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtCode.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtCode_deserialize(enum LockEvtCode *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockDevActionType.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionType_serialize(enum LockDevActionType *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDevActionType.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionType_deserialize(enum LockDevActionType *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockFunction.
 * @return 0 if successful, nonzero on error.
 */
int LockFunction_serialize(enum LockFunction *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockFunction.
 * @return 0 if successful, nonzero on error.
 */
int LockFunction_deserialize(enum LockFunction *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockHostGrantFallbackMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantFallbackMode_serialize(enum LockHostGrantFallbackMode *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHostGrantFallbackMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantFallbackMode_deserialize(enum LockHostGrantFallbackMode *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockHostGrantInitiationMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantInitiationMode_serialize(enum LockHostGrantInitiationMode *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHostGrantInitiationMode.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantInitiationMode_deserialize(enum LockHostGrantInitiationMode *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockIdentificationType.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationType_serialize(enum LockIdentificationType *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockIdentificationType.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationType_deserialize(enum LockIdentificationType *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockFileCategory.
 * @return 0 if successful, nonzero on error.
 */
int LockFileCategory_serialize(enum LockFileCategory *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockFileCategory.
 * @return 0 if successful, nonzero on error.
 */
int LockFileCategory_deserialize(enum LockFileCategory *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockFileIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockFileIdentifier_serialize(enum LockFileIdentifier *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockFileIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockFileIdentifier_deserialize(enum LockFileIdentifier *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockHostGrantReqType.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReqType_serialize(enum LockHostGrantReqType *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHostGrantReqType.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReqType_deserialize(enum LockHostGrantReqType *self, struct BasicDeserializer *deserializer);


/**
 * Serialize LockPolicyPriority.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyPriority_serialize(enum LockPolicyPriority *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPolicyPriority.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyPriority_deserialize(enum LockPolicyPriority *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDate.
 * @return 0 if successful, nonzero on error.
 */
int LockDate_serialize(struct LockDate *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDate.
 * @return 0 if successful, nonzero on error.
 */
int LockDate_deserialize(struct LockDate *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockTimeOfDay_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToMinute_serialize(struct LockTimeOfDay_ToMinute *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockTimeOfDay_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToMinute_deserialize(struct LockTimeOfDay_ToMinute *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockTimeOfDay_ToQuarterHour.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToQuarterHour_serialize(struct LockTimeOfDay_ToQuarterHour *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockTimeOfDay_ToQuarterHour.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToQuarterHour_deserialize(struct LockTimeOfDay_ToQuarterHour *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockTimeOfDay_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToSecond_serialize(struct LockTimeOfDay_ToSecond *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockTimeOfDay_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeOfDay_ToSecond_deserialize(struct LockTimeOfDay_ToSecond *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDateTime_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToMinute_serialize(struct LockDateTime_ToMinute *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDateTime_ToMinute.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToMinute_deserialize(struct LockDateTime_ToMinute *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDateTime_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToSecond_serialize(struct LockDateTime_ToSecond *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDateTime_ToSecond.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTime_ToSecond_deserialize(struct LockDateTime_ToSecond *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtContent.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_serialize(struct LockEvtContent *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtContent.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_deserialize(struct LockEvtContent *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtDelta.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtDelta_serialize(struct LockEvtDelta *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtDelta.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtDelta_deserialize(struct LockEvtDelta *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtModifiers_serialize(struct LockEvtModifiers *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtModifiers_deserialize(struct LockEvtModifiers *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockStatus.
 * @return 0 if successful, nonzero on error.
 */
int LockStatus_serialize(struct LockStatus *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockStatus.
 * @return 0 if successful, nonzero on error.
 */
int LockStatus_deserialize(struct LockStatus *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDstTransition.
 * @return 0 if successful, nonzero on error.
 */
int LockDstTransition_serialize(struct LockDstTransition *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDstTransition.
 * @return 0 if successful, nonzero on error.
 */
int LockDstTransition_deserialize(struct LockDstTransition *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockAccessModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessModifiers_serialize(struct LockAccessModifiers *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockAccessModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessModifiers_deserialize(struct LockAccessModifiers *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockCredActions.
 * @return 0 if successful, nonzero on error.
 */
int LockCredActions_serialize(struct LockCredActions *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockCredActions.
 * @return 0 if successful, nonzero on error.
 */
int LockCredActions_deserialize(struct LockCredActions *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDevActionPermissions.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionPermissions_serialize(struct LockDevActionPermissions *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDevActionPermissions.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionPermissions_deserialize(struct LockDevActionPermissions *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockCredTechnologies.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnologies_serialize(struct LockCredTechnologies *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockCredTechnologies.
 * @return 0 if successful, nonzero on error.
 */
int LockCredTechnologies_deserialize(struct LockCredTechnologies *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockFunctionModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockFunctionModifiers_serialize(struct LockFunctionModifiers *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockFunctionModifiers.
 * @return 0 if successful, nonzero on error.
 */
int LockFunctionModifiers_deserialize(struct LockFunctionModifiers *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPolicyAssertion.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertion_serialize(struct LockPolicyAssertion *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPolicyAssertion.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertion_deserialize(struct LockPolicyAssertion *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockHostGrantConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantConfig_serialize(struct LockHostGrantConfig *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHostGrantConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantConfig_deserialize(struct LockHostGrantConfig *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPacketContent.
 * @return 0 if successful, nonzero on error.
 */
int LockPacketContent_serialize(struct LockPacketContent *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPacketContent.
 * @return 0 if successful, nonzero on error.
 */
int LockPacketContent_deserialize(struct LockPacketContent *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPaginationReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPaginationReq_serialize(struct LockPaginationReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPaginationReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPaginationReq_deserialize(struct LockPaginationReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtContent_None.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_None_serialize(struct LockEvtContent_None *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtContent_None.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_None_deserialize(struct LockEvtContent_None *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtContent_BatteryLevel.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_BatteryLevel_serialize(struct LockEvtContent_BatteryLevel *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtContent_BatteryLevel.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_BatteryLevel_deserialize(struct LockEvtContent_BatteryLevel *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtContent_CredUnid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_CredUnid_serialize(struct LockEvtContent_CredUnid *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtContent_CredUnid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_CredUnid_deserialize(struct LockEvtContent_CredUnid *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtContent_SchedOid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_SchedOid_serialize(struct LockEvtContent_SchedOid *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtContent_SchedOid.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtContent_SchedOid_deserialize(struct LockEvtContent_SchedOid *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvt.
 * @return 0 if successful, nonzero on error.
 */
int LockEvt_serialize(struct LockEvt *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvt.
 * @return 0 if successful, nonzero on error.
 */
int LockEvt_deserialize(struct LockEvt *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockTimeZone.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeZone_serialize(struct LockTimeZone *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockTimeZone.
 * @return 0 if successful, nonzero on error.
 */
int LockTimeZone_deserialize(struct LockTimeZone *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockCred.
 * @return 0 if successful, nonzero on error.
 */
int LockCred_serialize(struct LockCred *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockCred.
 * @return 0 if successful, nonzero on error.
 */
int LockCred_deserialize(struct LockCred *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtPolicy_serialize(struct LockEvtPolicy *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtPolicy_deserialize(struct LockEvtPolicy *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockHol.
 * @return 0 if successful, nonzero on error.
 */
int LockHol_serialize(struct LockHol *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHol.
 * @return 0 if successful, nonzero on error.
 */
int LockHol_deserialize(struct LockHol *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockSchedElement.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElement_serialize(struct LockSchedElement *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockSchedElement.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElement_deserialize(struct LockSchedElement *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockSchedElementPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElementPolicy_serialize(struct LockSchedElementPolicy *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockSchedElementPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedElementPolicy_deserialize(struct LockSchedElementPolicy *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockSchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedPolicy_serialize(struct LockSchedPolicy *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockSchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockSchedPolicy_deserialize(struct LockSchedPolicy *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockSched.
 * @return 0 if successful, nonzero on error.
 */
int LockSched_serialize(struct LockSched *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockSched.
 * @return 0 if successful, nonzero on error.
 */
int LockSched_deserialize(struct LockSched *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockConfig_serialize(struct LockConfig *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockConfig_deserialize(struct LockConfig *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifier_serialize(struct LockEvtIdentifier *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtIdentifier.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifier_deserialize(struct LockEvtIdentifier *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtIdentifierRange.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifierRange_serialize(struct LockEvtIdentifierRange *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtIdentifierRange.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtIdentifierRange_deserialize(struct LockEvtIdentifierRange *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockIdentification.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentification_serialize(struct LockIdentification *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockIdentification.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentification_deserialize(struct LockIdentification *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockIdentificationResult.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationResult_serialize(struct LockIdentificationResult *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockIdentificationResult.
 * @return 0 if successful, nonzero on error.
 */
int LockIdentificationResult_deserialize(struct LockIdentificationResult *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbChange_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Config_serialize(struct LockDbChange_Config *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbChange_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Config_deserialize(struct LockDbChange_Config *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbChangeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChangeResp_serialize(struct LockDbChangeResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbChangeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChangeResp_deserialize(struct LockDbChangeResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtControl.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtControl_serialize(struct LockEvtControl *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtControl.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtControl_deserialize(struct LockEvtControl *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockEvtBatch.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtBatch_serialize(struct LockEvtBatch *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockEvtBatch.
 * @return 0 if successful, nonzero on error.
 */
int LockEvtBatch_deserialize(struct LockEvtBatch *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDevStateRecordControl.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecordControl_serialize(struct LockDevStateRecordControl *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDevStateRecordControl.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecordControl_deserialize(struct LockDevStateRecordControl *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDevStateRecord.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecord_serialize(struct LockDevStateRecord *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDevStateRecord.
 * @return 0 if successful, nonzero on error.
 */
int LockDevStateRecord_deserialize(struct LockDevStateRecord *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDateTimeConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTimeConfig_serialize(struct LockDateTimeConfig *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDateTimeConfig.
 * @return 0 if successful, nonzero on error.
 */
int LockDateTimeConfig_deserialize(struct LockDateTimeConfig *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockGetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeReq_serialize(struct LockGetTimeReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockGetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeReq_deserialize(struct LockGetTimeReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockGetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeResp_serialize(struct LockGetTimeResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockGetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockGetTimeResp_deserialize(struct LockGetTimeResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockSetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeReq_serialize(struct LockSetTimeReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockSetTimeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeReq_deserialize(struct LockSetTimeReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockSetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeResp_serialize(struct LockSetTimeResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockSetTimeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockSetTimeResp_deserialize(struct LockSetTimeResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPullFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkReq_serialize(struct LockPullFileChunkReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPullFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkReq_deserialize(struct LockPullFileChunkReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPullFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkResp_serialize(struct LockPullFileChunkResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPullFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPullFileChunkResp_deserialize(struct LockPullFileChunkResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPushFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkReq_serialize(struct LockPushFileChunkReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPushFileChunkReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkReq_deserialize(struct LockPushFileChunkReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPushFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkResp_serialize(struct LockPushFileChunkResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPushFileChunkResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPushFileChunkResp_deserialize(struct LockPushFileChunkResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockUpgradeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeReq_serialize(struct LockUpgradeReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockUpgradeReq.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeReq_deserialize(struct LockUpgradeReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockUpgradeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeResp_serialize(struct LockUpgradeResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockUpgradeResp.
 * @return 0 if successful, nonzero on error.
 */
int LockUpgradeResp_deserialize(struct LockUpgradeResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbQuery.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQuery_serialize(struct LockDbQuery *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbQuery.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQuery_deserialize(struct LockDbQuery *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbQueryResp_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Config_serialize(struct LockDbQueryResp_Config *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbQueryResp_Config.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Config_deserialize(struct LockDbQueryResp_Config *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockHostGrantReq.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReq_serialize(struct LockHostGrantReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHostGrantReq.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantReq_deserialize(struct LockHostGrantReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockHostGrantResp.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantResp_serialize(struct LockHostGrantResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockHostGrantResp.
 * @return 0 if successful, nonzero on error.
 */
int LockHostGrantResp_deserialize(struct LockHostGrantResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDevActionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionReq_serialize(struct LockDevActionReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDevActionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionReq_deserialize(struct LockDevActionReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDevActionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionResp_serialize(struct LockDevActionResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDevActionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockDevActionResp_deserialize(struct LockDevActionResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPolicyAssertionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionReq_serialize(struct LockPolicyAssertionReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPolicyAssertionReq.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionReq_deserialize(struct LockPolicyAssertionReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPolicyAssertionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionResp_serialize(struct LockPolicyAssertionResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPolicyAssertionResp.
 * @return 0 if successful, nonzero on error.
 */
int LockPolicyAssertionResp_deserialize(struct LockPolicyAssertionResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockConnectionTermination.
 * @return 0 if successful, nonzero on error.
 */
int LockConnectionTermination_serialize(struct LockConnectionTermination *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockConnectionTermination.
 * @return 0 if successful, nonzero on error.
 */
int LockConnectionTermination_deserialize(struct LockConnectionTermination *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbChange_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Hol_serialize(struct LockDbChange_Hol *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbChange_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Hol_deserialize(struct LockDbChange_Hol *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbChange_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Sched_serialize(struct LockDbChange_Sched *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbChange_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Sched_deserialize(struct LockDbChange_Sched *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbChange_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_SchedPolicy_serialize(struct LockDbChange_SchedPolicy *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbChange_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_SchedPolicy_deserialize(struct LockDbChange_SchedPolicy *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbChange_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Cred_serialize(struct LockDbChange_Cred *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbChange_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbChange_Cred_deserialize(struct LockDbChange_Cred *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbQueryResp_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Hol_serialize(struct LockDbQueryResp_Hol *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbQueryResp_Hol.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Hol_deserialize(struct LockDbQueryResp_Hol *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbQueryResp_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Sched_serialize(struct LockDbQueryResp_Sched *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbQueryResp_Sched.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Sched_deserialize(struct LockDbQueryResp_Sched *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbQueryResp_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_SchedPolicy_serialize(struct LockDbQueryResp_SchedPolicy *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbQueryResp_SchedPolicy.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_SchedPolicy_deserialize(struct LockDbQueryResp_SchedPolicy *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockDbQueryResp_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Cred_serialize(struct LockDbQueryResp_Cred *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockDbQueryResp_Cred.
 * @return 0 if successful, nonzero on error.
 */
int LockDbQueryResp_Cred_deserialize(struct LockDbQueryResp_Cred *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockCredAuthorization.
 * @return 0 if successful, nonzero on error.
 */
int LockCredAuthorization_serialize(struct LockCredAuthorization *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockCredAuthorization.
 * @return 0 if successful, nonzero on error.
 */
int LockCredAuthorization_deserialize(struct LockCredAuthorization *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockAccessReq.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessReq_serialize(struct LockAccessReq *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockAccessReq.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessReq_deserialize(struct LockAccessReq *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockAccessResp.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessResp_serialize(struct LockAccessResp *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockAccessResp.
 * @return 0 if successful, nonzero on error.
 */
int LockAccessResp_deserialize(struct LockAccessResp *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPublicKeyExchange.
 * @return 0 if successful, nonzero on error.
 */
int LockPublicKeyExchange_serialize(struct LockPublicKeyExchange *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPublicKeyExchange.
 * @return 0 if successful, nonzero on error.
 */
int LockPublicKeyExchange_deserialize(struct LockPublicKeyExchange *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockMobileBleChallengeNonce.
 * @return 0 if successful, nonzero on error.
 */
int LockMobileBleChallengeNonce_serialize(struct LockMobileBleChallengeNonce *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockMobileBleChallengeNonce.
 * @return 0 if successful, nonzero on error.
 */
int LockMobileBleChallengeNonce_deserialize(struct LockMobileBleChallengeNonce *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockBundleHeader.
 * @return 0 if successful, nonzero on error.
 */
int LockBundleHeader_serialize(struct LockBundleHeader *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockBundleHeader.
 * @return 0 if successful, nonzero on error.
 */
int LockBundleHeader_deserialize(struct LockBundleHeader *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockOpaqueContent.
 * @return 0 if successful, nonzero on error.
 */
int LockOpaqueContent_serialize(struct LockOpaqueContent *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockOpaqueContent.
 * @return 0 if successful, nonzero on error.
 */
int LockOpaqueContent_deserialize(struct LockOpaqueContent *self, struct BasicDeserializer *deserializer);



/**
 * Serialize LockPacket.
 * @return 0 if successful, nonzero on error.
 */
int LockPacket_serialize(struct LockPacket *self, struct BasicSerializer *serializer);
/**
 * Deserialize LockPacket.
 * @return 0 if successful, nonzero on error.
 */
int LockPacket_deserialize(struct LockPacket *self, struct BasicDeserializer *deserializer);

