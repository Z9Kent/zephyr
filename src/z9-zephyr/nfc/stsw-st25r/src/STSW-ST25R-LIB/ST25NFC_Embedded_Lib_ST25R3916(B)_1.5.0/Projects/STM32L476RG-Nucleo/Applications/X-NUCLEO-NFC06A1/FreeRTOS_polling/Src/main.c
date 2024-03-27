/**
  ******************************************************************************
  * @file    main.c
  * @author  MMY Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "rfal_platform.h"
#include "logger.h"
#include "st_errno.h"
#include "rfal_rf.h"
#include "rfal_analogConfig.h"


/** @addtogroup X-CUBE-NFC6_Applications
 *  @{
 */

/** @addtogroup PollingTagDetect
 *  @{
 */

/** @addtogroup PTD_Main
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/** @defgroup PTD_Main_Private_Variables
 * @{
 */
UART_HandleTypeDef hlogger;         /*!< Handler to the UART HW logger */
osThreadId_t defaultTaskHandle;     /*!< Default Task Handle           */
osThreadId_t nfcIsrTaskHandle;      /*!< ST25R3916 ISR task Handle     */
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/
/** @defgroup PTD_Main_Private_Functions
 * @{
 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{
  hlogger.Instance = USART2;
  hlogger.Init.BaudRate = 115200;
  hlogger.Init.WordLength = UART_WORDLENGTH_8B;
  hlogger.Init.StopBits = UART_STOPBITS_1;
  hlogger.Init.Parity = UART_PARITY_NONE;
  hlogger.Init.Mode = UART_MODE_TX_RX;
  hlogger.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  hlogger.Init.OverSampling = UART_OVERSAMPLING_16;
  hlogger.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  hlogger.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&hlogger) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  *****************************************************************************
  * @brief  Main program
  *
  * @param  None
  *
  * @return None
  *****************************************************************************
  */
int main(void)
{
  /* STM32L4xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user
             can eventually implement his proper time base source (a general purpose
             timer for example or other time source), keeping in mind that Time base
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
             handled in milliseconds basis.
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the System clock to have a frequency of 80 MHz */
  SystemClock_Config();

  NFC06A1_LED_Init();
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
#ifdef RFAL_USE_I2C
  BSP_I2C1_Init();
#else
  BSP_SPI1_Init();
#endif /* RFAL_USE_I2C */
  /* Initialize log module */
  MX_USART2_UART_Init();
  logUsartInit(&hlogger);

  /* Initialize FreeRTOS */
  osKernelInitialize();
  plfInit();
  
  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 1664
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of nfcIsrTask */
  const osThreadAttr_t nfcIsrTask_attributes = {
    .name = "nfcIsrTask",
    .priority = (osPriority_t) osPriorityHigh,
    .stack_size = 384
  };
  nfcIsrTaskHandle = osThreadNew(nfcIsrTaskRunner, NULL, &nfcIsrTask_attributes);
  
  /* add threads, ... */
  
  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  while (1)
  {
  
  }
}

/**
  *****************************************************************************
  * @brief  This function is executed in case of error occurrence.
  *
  * @param  None
  *
  * @return None
  *****************************************************************************
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  platformLog("Unrecoverable error in %s:%d", file, line);
  while(1)
  {
      NFC06A1_LED_Toggle( TX_LED );
      NFC06A1_LED_Toggle( TA_LED );
      NFC06A1_LED_Toggle( TB_LED );
      NFC06A1_LED_Toggle( TF_LED );
      NFC06A1_LED_Toggle( TV_LED );
      NFC06A1_LED_Toggle( AP2P_LED );
      platformDelay(100);
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
  *****************************************************************************
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  *
  * @param[in]  file: pointer to the source file name
  * @param[in]  line: assert_param error line source number
  *
  * @return None
  *****************************************************************************
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
