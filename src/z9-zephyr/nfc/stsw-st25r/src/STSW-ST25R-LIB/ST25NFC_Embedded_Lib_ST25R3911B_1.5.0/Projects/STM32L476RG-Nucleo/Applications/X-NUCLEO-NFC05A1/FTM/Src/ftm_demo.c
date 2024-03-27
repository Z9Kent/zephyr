/******************************************************************************
  * @attention
  *
  * COPYRIGHT 2019 STMicroelectronics, all rights reserved
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
 */

/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include <stdlib.h>
#include <string.h>

#include "st25ftm_protocol.h"
#include "st25ftm_config.h"
#include "bigecho.h"
#include "ftm_demo.h"

#define ST25_PRODUCT_CODE_UID_INDEX (5)

static void sendReceive(uint8_t *cmd, uint32_t cmdLen, uint8_t *rsp, uint32_t* rspLen)
{
  uint32_t time;

  platformLog("Starting FTM transmission (%d bytes)\r\n", cmdLen);
  time = HAL_GetTick();

  ST25FTM_SendCommand(cmd, cmdLen, ST25FTM_SEND_WITH_ACK,NULL);

  while(!ST25FTM_IsTransmissionComplete() && !ST25FTM_IsIdle())
  {
    ST25FTM_Runner();
    HAL_Delay(5);
  }

  if(ST25FTM_IsTransmissionComplete())
  {
    time = (int)HAL_GetTick() - (int)time;
    platformLog("FTM transmission completed in %d ms\r\n", time);
  } else {
    platformLog("FTM transmission failed, aborting\r\n");
    return;
  }

  ST25FTM_ReceiveCommand(rsp,rspLen,NULL);
  platformLog("Ready for FTM reception\r\n");
  time = HAL_GetTick();

  while(!ST25FTM_IsReceptionComplete() && !ST25FTM_IsIdle())
  {
    ST25FTM_Runner();
    HAL_Delay(5);
  }

  if(ST25FTM_IsReceptionComplete())
  {
    time = (int)HAL_GetTick() - (int)time;
    platformLog("FTM reception completed (%d bytes) in %d ms\r\n", *rspLen,time);
  } else {
    platformLog("FTM reception failed\r\n");
    *rspLen = 0;
    return;
  }
}


int ftm_demo(rfalNfcvListenDevice *nfcvDev)
{
  uint8_t rsp[8192];
  uint32_t send_len = sizeof(echo_cmd);
  uint32_t buf_len = sizeof(rsp);

  if((nfcvDev->InvRes.UID[ST25_PRODUCT_CODE_UID_INDEX] < 0x24)
     || (nfcvDev->InvRes.UID[ST25_PRODUCT_CODE_UID_INDEX] > 0x27))
  {
    /* This is not a ST25DV-I2C: return */
    return 1;
  }

  ST25FTM_Init();
  ST25FTM_SetRxFrameMaxLength(256);
  ST25FTM_SetTxFrameMaxLength(256);

  ST25FTM_SetDevice(nfcvDev);
  if(ST25FTM_DeviceInit() != 0)
  {
    ST25FTM_SetDevice(NULL);
    platformLog("Initialization error\r\n\r\n");
    return 1;
  }

  sendReceive(echo_cmd,send_len,rsp, &buf_len);

  /* Check received length against sent length */
  if(buf_len != send_len)
  {
    ST25FTM_SetDevice(NULL);
    platformLog("FTM demo terminated with error\r\n\r\n");
    return 1;
  }
  /* Check received buffer against sent buffer */
  if(memcmp(echo_cmd,rsp,send_len))
  {
    ST25FTM_SetDevice(NULL);
    platformLog("FTM demo terminated with error\r\n\r\n");
    return 1;
  }
  ST25FTM_SetDevice(NULL);
  platformLog("FTM demo successfully completed\r\n\r\n");

  return 0;
}
