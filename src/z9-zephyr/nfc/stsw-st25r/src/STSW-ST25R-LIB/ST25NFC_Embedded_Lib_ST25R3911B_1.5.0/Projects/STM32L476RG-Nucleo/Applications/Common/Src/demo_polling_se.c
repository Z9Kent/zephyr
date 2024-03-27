/******************************************************************************
  * @attention
  *
  * COPYRIGHT  2019-2022 STMicroelectronics, all rights reserved
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/


/*! \file
 *
 *  \author 
 *
 *  \brief Demo application
 *
 *  This demo shows how to poll for several types of NFC cards/devices 
 *  in single-ended mode, using the RFAL library.
 *  The demo sets the ST25R in single-ended mode, and it switchs between 
 *  the two antennas using different RFO/RFI pairs (RFx) every 
 *  time the polling loog is started.
 *
 *  This demo does not fully implement the activities according to the standards,
 *  it performs the required to communicate with a card/device and retrieve 
 *  its UID.
 * 
 */
 
/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include "demo.h"
#include "utils.h"
#include "logger.h"
#include "rfal_nfc.h"
#include "rfal_chip.h"

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

/* Definition of possible states the demo state machine could have */
#define DEMO_ST_NOTINIT               0     /*!< Demo State:  Not initialized | Stopped */
#define DEMO_ST_START_DISCOVERY       1     /*!< Demo State:  Start Discovery           */
#define DEMO_ST_DISCOVERY             2     /*!< Demo State:  Discovery                 */

/*
 ******************************************************************************
 * GLOBAL MACROS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */



/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */

static rfalNfcDiscoverParam discParam;
static uint8_t              state = DEMO_ST_NOTINIT;
static bool                 multiSel;
static bool                 curAnt;

/*
******************************************************************************
* LOCAL FUNCTION PROTOTYPES
******************************************************************************
*/


/*!
 *****************************************************************************
 * \brief Returns the RFAL NFC Discovery Parameter: Tech2Find
 *****************************************************************************
 */
uint16_t demoGetDiscoverTechs2Find( void )
{
    return discParam.techs2Find;
}

/*!
 *****************************************************************************
 * \brief Returns the RFAL NFC Discovery Parameter: Total Duration
 *****************************************************************************
 */
uint16_t demoGetDiscoverTotalDuration( void )
{
    return discParam.totalDuration;
}

/*!
 *****************************************************************************
 * \brief Demo Notification
 *
 *  This function receives the event notifications from RFAL
 *****************************************************************************
 */
static void demoNotif( rfalNfcState st )
{
    uint8_t       devCnt;
    rfalNfcDevice *dev;
    
    if( st == RFAL_NFC_STATE_POLL_SELECT )
    {
        /* Check if in case of multiple devices, selection is already attempted */
        if( (!multiSel) )
        {
            multiSel = true;
            /* Multiple devices were found, activate first of them */
            rfalNfcGetDevicesFound( &dev, &devCnt );
            rfalNfcSelect( 0 );
            
            platformLog("Multiple Tags detected: %d \r\n", devCnt);
        }
        else
        {
            rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_DISCOVERY );
        }
    }
    else if( st == RFAL_NFC_STATE_START_DISCOVERY )
    {
        /* Clear multiple device selection flag */
        multiSel = false;
		
        /* Toggle the single-ended antenna to be used */
        curAnt = (!curAnt);
        rfalChipSetAntennaMode( true, curAnt );
    }
}

/*!
 *****************************************************************************
 * \brief Demo Ini
 *
 *  This function initializes the required layers for the demo
 *
 * \return true  : Initialization ok
 * \return false : Initialization failed
 *****************************************************************************
 */
bool demoIni( void )
{
    ReturnCode err;

    err = rfalNfcInitialize();
    if( err == ERR_NONE )
    {
        curAnt = false;
			
        rfalNfcDefaultDiscParams( &discParam );
        
        discParam.devLimit      = 1U;

        discParam.notifyCb             = demoNotif;
        discParam.totalDuration        = 1000U;
        discParam.techs2Find           = RFAL_NFC_TECH_NONE;          /* For the demo, enable the NFC Technologies based on RFAL Feature switches */

#if RFAL_FEATURE_NFCA
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_A;
#endif /* RFAL_FEATURE_NFCA */

#if RFAL_FEATURE_NFCB
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_B;
#endif /* RFAL_FEATURE_NFCB */

#if RFAL_FEATURE_NFCF
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_F;
#endif /* RFAL_FEATURE_NFCF */

#if RFAL_FEATURE_NFCV
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_V;
#endif /* RFAL_FEATURE_NFCV */

#if RFAL_FEATURE_ST25TB
        discParam.techs2Find          |= RFAL_NFC_POLL_TECH_ST25TB;
#endif /* RFAL_FEATURE_ST25TB */


#if RFAL_SUPPORT_MODE_POLL_ACTIVE_P2P && RFAL_FEATURE_NFC_DEP
        discParam.techs2Find |= RFAL_NFC_POLL_TECH_AP2P;
#endif /* RFAL_SUPPORT_MODE_POLL_ACTIVE_P2P && RFAL_FEATURE_NFC_DEP */


        err = rfalNfcDiscover( &discParam );        
        if( err != ERR_NONE )
        {
            return false;
        }
        
        state = DEMO_ST_START_DISCOVERY;
        return true;
    }
    return false;
}

/*!
 *****************************************************************************
 * \brief Demo Cycle
 *
 *  This function executes the demo state machine. 
 *  It must be called periodically
 *****************************************************************************
 */
void demoCycle( void )
{
    static rfalNfcDevice *nfcDevice;
    
    rfalNfcWorker();                                    /* Run RFAL worker periodically */
	
    switch( state )
    {
        /*******************************************************************************/
        case DEMO_ST_START_DISCOVERY:

          platformLedOff(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
          platformLedOff(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
          platformLedOff(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
          platformLedOff(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
          platformLedOff(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
          platformLedOff(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
        
          multiSel = false;
          state    = DEMO_ST_DISCOVERY;
          break;

        /*******************************************************************************/
        case DEMO_ST_DISCOVERY:
        
            if( rfalNfcIsDevActivated( rfalNfcGetState() ) )
            {
                rfalNfcGetActiveDevice( &nfcDevice );
                
                switch( nfcDevice->type )
                {
                    /*******************************************************************************/
                    case RFAL_NFC_LISTEN_TYPE_NFCA:
                    
                        platformLedOn(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
                        switch( nfcDevice->dev.nfca.type )
                        {
                            case RFAL_NFCA_T1T:
                                platformLog("ISO14443A/Topaz (NFC-A T1T) TAG found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                                break;
                            
                            case RFAL_NFCA_T4T:
                                platformLog("NFCA Passive ISO-DEP device found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                                break;
                            
                            case RFAL_NFCA_T4T_NFCDEP:
                            case RFAL_NFCA_NFCDEP:
                                platformLog("NFCA Passive P2P device found on %s. NFCID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                                break;
                                
                            default:
                                platformLog("ISO14443A/NFC-A card found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                                break;
                        }
                        break;
                    
                    /*******************************************************************************/
                    case RFAL_NFC_LISTEN_TYPE_NFCB:
                        
                        platformLedOn(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
                        platformLog("ISO14443B/NFC-B card found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                        break;
                        
                    /*******************************************************************************/
                    case RFAL_NFC_LISTEN_TYPE_NFCF:
                        
                        platformLedOn(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
                        if( rfalNfcfIsNfcDepSupported( &nfcDevice->dev.nfcf ) )
                        {
                            platformLog("NFCF Passive P2P device found on %s. NFCID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ) );
                        }
                        else
                        {
                            platformLog("Felica/NFC-F card found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ));
                        }
                        
                        break;
                    
                    /*******************************************************************************/
                    case RFAL_NFC_LISTEN_TYPE_NFCV:
                        {
                            uint8_t devUID[RFAL_NFCV_UID_LEN];
                            
                            platformLedOn(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
                            
                            ST_MEMCPY( devUID, nfcDevice->nfcid, nfcDevice->nfcidLen );   /* Copy the UID into local var */
                            REVERSE_BYTES( devUID, RFAL_NFCV_UID_LEN );                 /* Reverse the UID for display purposes */
                            platformLog("ISO15693/NFC-V card found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str(devUID, RFAL_NFCV_UID_LEN));
                        }
                        break;
                        
                    /*******************************************************************************/
                    case RFAL_NFC_LISTEN_TYPE_ST25TB:
                        
                        platformLedOn(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
                        platformLog("ST25TB card found on %s. UID: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str( nfcDevice->nfcid, nfcDevice->nfcidLen ));
                        break;
                    
                    /*******************************************************************************/
                    case RFAL_NFC_LISTEN_TYPE_AP2P:
                        
                        platformLedOn(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
                        platformLog("NFC Active P2P device found on %s. NFCID3: %s\r\n", (curAnt ? "RFx2" : "RFx1"), hex2Str(nfcDevice->nfcid, nfcDevice->nfcidLen));
                        break;
                    
                    /*******************************************************************************/
                    case RFAL_NFC_POLL_TYPE_NFCA:
                    case RFAL_NFC_POLL_TYPE_NFCF:
                    case RFAL_NFC_POLL_TYPE_AP2P:
                        break;
                    
                    /*******************************************************************************/
                    default:
                        break;
                }
                
                rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_DISCOVERY );
                state = DEMO_ST_START_DISCOVERY;
            }
            break;

        /*******************************************************************************/
        case DEMO_ST_NOTINIT:
        default:
            break;
    }
}

/*!
 *****************************************************************************
 * \brief Demo Stop
 *
 *  This function stops the demo operation
 *
 *****************************************************************************
 */
void demoStop( void )
{
    rfalNfcDeactivate( RFAL_NFC_DEACTIVATE_IDLE );
    state = DEMO_ST_NOTINIT;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
