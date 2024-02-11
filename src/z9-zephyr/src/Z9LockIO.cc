
#include "Z9LockIOProtocol_Current.h"

// Notes: #31->34 dest listed as SP-Core, not Authoratative source
// 


#define CHECK_THROW(...)

void Z9Lock_Received(KCB *kcb)
{
    auto contentType = kcb.peek();

    LOG_INF("%s: Received packet: %d", __func__, contentType);
    
    
    // 42 types of packets (#36 & #39 not assigned)
    //  
    switch (contentType)
	{
        // ALL
		case LockIdentification_DISCRIMINATOR:
		case LockIdentificationResult_DISCRIMINATOR:
			// origin MOBILE, HUB_CONTROLLER
			CHECK_THROW( Task_ApplicationLogic_onLockPacket_IdentificationResult(self, packet, origin, originId) );
			break;
		
		case LockBundleHeader_DISCRIMINATOR:
			// origin MOBILE, HUB_CONTROLLER, AUTH_SOURCE
			break;

		case LockOpaqueContent_DISCRIMINATOR:
			// Task_HostBundleIO:269 (onLockPacket) -> fail
			// Task_HostIO:680 (handle_incomingLockPacket) -> decrypt (CS_NOC)
			break;
  
  
        // BOTH
        case LockConnectionTermination_DISCRIMINATOR:
			// origin MOBILE, HUB_CONTROLLER
			CHECK_THROW( Task_ApplicationLogic_onLockPacket_ConnectionTermination(self, packet, origin) );
			break;

		// Lock <=> Authoritative Source
		case LockPublicKeyExchange_DISCRIMINATOR:
			// origin Auth Source
			break;

        // Lock <= Authoritative Source
			// origin Auth Source, HUB
		case LockDbChange_Config_DISCRIMINATOR:
		case LockDbChange_Hol_DISCRIMINATOR:
		case LockDbChange_Sched_DISCRIMINATOR:
		case LockDbChange_SchedPolicy_DISCRIMINATOR:
		case LockDbChange_Cred_DISCRIMINATOR:
			break;

		case LockEvtControl_DISCRIMINATOR:
			// origin: not tested
			break;
		case LockCredAuthorization_DISCRIMINATOR:
			// origin Auth Source
			CHECK_THROW( Task_ApplicationLogic_onLockPacket_LockDbChange(self, packet, origin, originId, intermediary, intermediaryId) );
			break;
		
        // Lock => Authoritative Source
        case LockDbChangeResp_DISCRIMINATOR:
		case LockEvtBatch_DISCRIMINATOR:
			break;

		// Lock <= Mobile Device
			// origin: If mobile validate ID, else accept
		case LockGetTimeReq_DISCRIMINATOR:
		case LockSetTimeReq_DISCRIMINATOR:
		case LockAccessReq_DISCRIMINATOR:
		case LockMobileBleChallengeNonce_DISCRIMINATOR:
			break;

		// Lock => Mobile Device
		case LockGetTimeResp_DISCRIMINATOR:
		case LockSetTimeReq_DISCRIMINATOR:
		 case LockAccessReq_DISCRIMINATOR:
			break;

	   	// NB: File xfer to ctrl is via Z9IO protocol 
		// Lock <= SP-Core
		case LockPushFileChunkReq_DISCRIMINATOR:
		case LockPullFileChunkReq_DISCRIMINATOR:
		case LockUpgradeReq_DISCRIMINATOR:
		// Lock => SP-Core
		case LockPushFileChunkResp_DISCRIMINATOR:
		case LockPullFileChunkResp_DISCRIMINATOR:
		case LockUpgradeResp_DISCRIMINATOR:
			break;
		
		// Lock <= SP-Core
		case LockDbQuery_DISCRIMINATOR:
		case LockHostGrantResp_DISCRIMINATOR:
		case LockPolicyAssertionReq_DISCRIMINATOR:
			break;

		// Lock => SP-Core
		case LockDbQueryResp_Config_DISCRIMINATOR:
		case LockHostGrantResp_DISCRIMINATOR:
		case LockPolicyAssertionResp_DISCRIMINATOR:

		case LockDbQueryResp_Hol_DISCRIMINATOR:
		case LockDbQueryResp_Sched_DISCRIMINATOR:
		case LockDbQueryResp_SchedPolicy_DISCRIMINATOR:
		case LockDbQueryResp_Cred_DISCRIMINATOR:
			break;

		// Lock <= Mobile, Lock <= SP-Core
		case LockDevActionReq_DISCRIMINATOR:
			// origin: unimpl
			break;

		// Lock => Mobile, Lock => SP-Core
		case LockDevActionResp_DISCRIMINATOR:
			// unimpl
			break;

		// TBD
		case LockDevStateRecordControl_DISCRIMINATOR:
		case LockDevStateRecord_DISCRIMINATOR:
			break;
		
		default:
			//LOG_INF("%s: %s (%d): TODO, origin=%s", __func__, LockPacket_contentTypeToString(contentType), (int) contentType, LockIdentificationType_toString(origin));
			break;
	}
	
}