/******************************************************************************
  * @attention
  *
  * COPYRIGHT 2020 STMicroelectronics, all rights reserved
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


#include "main.h"
#include "rfal_platform.h"

#include "demo.h"
#include "timers.h"
#include "task.h"
#include "semphr.h"
#include "st25r3916_irq.h"

/* Private typedef -----------------------------------------------------------*/

 /*! typedef holding platform timer structure */
typedef struct {
  TimerHandle_t      handle;        /*!< Timer Handle                  */
  const char * const name;          /*!< Timer Name                    */
  StaticTimer_t      timerBuf;      /*!< Timer Buffer                  */
  bool               isUsed;        /*!< Timer in use flag             */
} platformTimer;

/* Private define ------------------------------------------------------------*/
#define PLF_TIMER_MAX 10U          /*!< Timers pool size               */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup PTD_Main_Private_Variables
 * @{
 */
/*! NFC Timers pool               */
platformTimer platformTimers[PLF_TIMER_MAX] =
{
    {.name = "0", },
    {.name = "1", },
    {.name = "2", },
    {.name = "3", },
    {.name = "4", },
    {.name = "5", },
    {.name = "6", },
    {.name = "7", },
    {.name = "8", },
    {.name = "9", },
};

SemaphoreHandle_t platformSem;      /*!< Default task wakeup Semaphore */

/**
  * @brief  Function implementing the Timer expiry callback
  * @param  argument: Elapsed timer handle
  * @retval None
  */
void platformTimerCallback(TimerHandle_t xTimer )
{
    xSemaphoreGive(platformSem);
}

/**
  * @brief  Function implementing Timer creation
  * @param  timer: timer value
  * @retval index (from 1 to PLF_TIMER_MAX) in the timer array.
  */
uint32_t plfTimerCreate(uint32_t time)
{
  uint32_t timer = UINT32_MAX;
  uint32_t i;
  BaseType_t rc;

  for( i = 0; i < PLF_TIMER_MAX; i++)
  {
    if( !platformTimers[i].isUsed )
    {
      timer = i;
      break;
    }
  }
  if( timer >= PLF_TIMER_MAX )
  {
    platformLog("platformTimerCreate: timer creation failed\r\n");
    plfErrorHandler();
    return 0;
  }

  rc = xTimerChangePeriod(platformTimers[timer].handle, time + 1U, (TickType_t)0);
  if( rc == pdFAIL )
  {
    platformLog("platformTimerCreate: osTimerStart failed (rc = %d)\r\n", rc);
    plfErrorHandler();
    return 0;
  }
  platformTimers[timer].isUsed = true;
  return timer + 1U;
}

/**
  * @brief  Function implementing Timer expiry check
  * @param  timer: timer index
  * @retval true: timer has expired, false otherwise
  */
bool plfTimerIsExpired(uint32_t timer)
{
  if( timer == 0U )
  {
    return true;
  }
  timer--;
  if( timer >= PLF_TIMER_MAX )
  {
    platformLog("platformTimerIsExpired: invalid timer\r\n");
    plfErrorHandler();
    return true;
  }
  return (xTimerIsTimerActive(platformTimers[timer].handle) == pdFALSE);
}

/**
  * @brief  Function implementing Timer destruction
  * @param  timer: timer index
  * @retval none
  */
void plfTimerDestroy(uint32_t timer)
{
  if( timer == 0U )
  {
    return;
  }
  timer--;
  if( timer >= PLF_TIMER_MAX )
  {
    platformLog("platformTimerDestroy: invalid timer\r\n");
    plfErrorHandler();
    return;
  }
  xTimerStop(platformTimers[timer].handle, (TickType_t)0);
  platformTimers[timer].isUsed = false;
}

/**
  * @brief  Function implementing Error handler
  * @param  none
  * @retval none
  */
void plfErrorHandler(void)
{
    while(1)
    {
    }
}

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void *argument)
{
  bool status;
  uint32_t i = 6;
  platformLog("Welcome to FreeRTOS demo.\r\n");

  status = demoIni();
  platformLog("Initialization %s.\r\n", status ? "succeeded": "failed");
  while( (!status) || (status && (i-- > 0)) )
  {
    platformLedToggle(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
    platformLedToggle(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
    platformLedToggle(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
    platformLedToggle(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
    platformLedToggle(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
    platformLedToggle(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
    platformDelay(status ? 200U : 100U);
  }
  platformLedOff(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
  platformLedOff(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
  platformLedOff(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
  platformLedOff(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
  platformLedOff(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
  platformLedOff(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
  /* Infinite loop */
  for(;;)
  {
    demoCycle();

    xSemaphoreTake(platformSem, 10/portTICK_PERIOD_MS);
  }
}

/**
* @brief Function implementing the nfcIsrTask thread.
* @param argument: Not used
* @retval None
*/
void nfcIsrTaskRunner(void *argument)
{
  /* Infinite loop */
  for(;;)
  {
      ulTaskNotifyTake( pdTRUE, portMAX_DELAY  );             /* Check if IRQ happen execute immediately, otherwise other execute Task meanwhile */
      st25r3916Isr();                                         /* ISR called from main task avoid calling vTaskSuspendAll from ISR (SPI) - NFC IRQ pin is anyhow checked */
      xSemaphoreGive(platformSem);
  }
}

/**
  * @brief  Function implementing the ST25R3916 IRQ callback
  * @param  none
  * @retval none
  */
void BSP_SPI1_IRQ_Callback(void)
{
  static BaseType_t xHigherPriorityTaskWoken;

  xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR( nfcIsrTaskHandle, &xHigherPriorityTaskWoken );     /* Notify NFC Task to execute */
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );                            /* Request a context switch as soon as possible */
}

void BSP_I2C1_IRQ_Callback(void)
{
  static BaseType_t xHigherPriorityTaskWoken;

  xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR( nfcIsrTaskHandle, &xHigherPriorityTaskWoken );     /* Notify NFC Task to execute */
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );                            /* Request a context switch as soon as possible */
}

/**
  * @brief  Function implementing platform initialization
  * @param  argument: timer index
  * @retval none
  */
void plfInit(void)
{
	uint32_t i;

	/* Initialize default task wakeup semaphore */
	platformSem = xSemaphoreCreateCounting( 10, 0 );
	if( platformSem == NULL )
	{
		platformLog("Platform semaphore initialization failed\r\n");
		plfErrorHandler();
	}

	/* Initialize timers */
	for( i = 0; i < PLF_TIMER_MAX; i++ )
	{
		platformTimers[i].handle = xTimerCreateStatic(platformTimers[i].name, (TickType_t)1, pdFALSE, (void*) 0, platformTimerCallback, &platformTimers[i].timerBuf);
		if( platformTimers[i].handle == NULL )
		{
			platformLog("Platform timers initialization failed\r\n");
			plfErrorHandler();
		}
	}
}
