/**
  ******************************************************************************
  * @file    main.c
  * @author  MMY Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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
#include "demo.h"
#include "rfal_platform.h"
#include "logger.h"
#include "st_errno.h"
#include "rfal_rf.h"
#include "rfal_analogConfig.h"

/** @addtogroup X-CUBE-NFC5_Applications
 *  @{
 */

/** @addtogroup ndef_rwTagDetect
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
uint8_t globalCommProtectCnt = 0;   /*!< Global Protection counter     */
UART_HandleTypeDef hlogger;         /*!< Handler to the UART HW logger */
SPI_HandleTypeDef hspi1;
/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* Private functions ---------------------------------------------------------*/
/** @defgroup PTD_Main_Private_Functions
 * @{
 */

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

  MX_GPIO_Init();

  BSP_SPI1_Init();

  /* Initialize log module */
  MX_USART2_UART_Init();
  logUsartInit(&hlogger);

  platformLog("Welcome to X-NUCLEO-NFC05A1\r\n");

  /* Initialize RFAL */
  if( !demoIni() )
  {
    /*
    * in case the rfal initialization failed signal it by flashing all LED
    * and stopping all operations
    */
    platformLog("Initialization failed..\r\n");
    while(1)
    {
      platformLedToggle(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
      platformLedToggle(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
      platformLedToggle(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
      platformLedToggle(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
      platformLedToggle(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
      platformLedToggle(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
      platformDelay(100);
    }
  }
  else
  {
    platformLog("Initialization succeeded..\r\n");
    for (int i = 0; i < 6; i++)
    {
      platformLedToggle(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
      platformLedToggle(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
      platformLedToggle(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
      platformLedToggle(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
      platformLedToggle(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
      platformLedToggle(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
      platformDelay(200);
    }

    platformLedOff(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
    platformLedOff(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
    platformLedOff(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
    platformLedOff(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
    platformLedOff(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
    platformLedOff(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
  }

  /* Infinite loop */
  while (1)
  {
    /* Run Demo Application */
    demoCycle();
  }
}


/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through
        * the Code Generation settings)
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_F_Pin|LED_B_Pin|LED_FIELD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_A_Pin|LED_V_Pin|LED_AP2P_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7
                           PC8 PC9 PC10 PC11
                           PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_F_Pin LED_B_Pin LED_FIELD_Pin */
  GPIO_InitStruct.Pin = LED_F_Pin|LED_B_Pin|LED_FIELD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_A_Pin LED_V_Pin LED_AP2P_Pin SPI1_CS_Pin */
  GPIO_InitStruct.Pin = LED_A_Pin|LED_V_Pin|LED_AP2P_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB10 PB11
                           PB12 PB13 PB14 PB15
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA9 PA10 PA11 PA12
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

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
      platformLedToggle(PLATFORM_LED_FIELD_PORT, PLATFORM_LED_FIELD_PIN);
      platformLedToggle(PLATFORM_LED_A_PORT, PLATFORM_LED_A_PIN);
      platformLedToggle(PLATFORM_LED_B_PORT, PLATFORM_LED_B_PIN);
      platformLedToggle(PLATFORM_LED_F_PORT, PLATFORM_LED_F_PIN);
      platformLedToggle(PLATFORM_LED_V_PORT, PLATFORM_LED_V_PIN);
      platformLedToggle(PLATFORM_LED_AP2P_PORT, PLATFORM_LED_AP2P_PIN);
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
