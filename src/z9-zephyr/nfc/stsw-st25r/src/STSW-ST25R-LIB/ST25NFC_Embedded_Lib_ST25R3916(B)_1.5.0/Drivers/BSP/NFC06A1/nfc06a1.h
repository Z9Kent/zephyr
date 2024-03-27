/**
  ******************************************************************************
  * @file    nfc06a1.h
  * @author  MMY Application Team
  * @brief   This file contains definitions for the nfc06a1.c
  *          board specific functions.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef NFC06A1_H
#define NFC06A1_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if (defined (USE_STM32L4XX_NUCLEO))
#include "stm32l4xx_nucleo.h"
#elif (defined (USE_STM32F4XX_NUCLEO))
#include "stm32f4xx_nucleo.h"
#endif
#include "nfc06a1_conf.h"

#if 0 /* Code not compiled, reserved for Doxygen */
/** @addtogroup BSP
  * @{
  */

/** @defgroup NFC06A1
  * @{
  */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

/* Exported types ------------------------------------------------------------*/
#if 0 /* Code not compiled, reserved for Doxygen */
/** @defgroup NFC06A1_Exported_Types
  * @{
  */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */
/**
 * @brief  NFC06A1 Led enumerator definition
 */
typedef enum 
{
  TF_LED = 0,         /*!< Led Type F   */
  TB_LED,             /*!< Led Type B   */
  TA_LED,             /*!< Led Type A   */
  TV_LED,             /*!< Led Type V   */
  AP2P_LED,           /*!< Led Type P2P */
  TX_LED              /*!< Led Field    */
}NFC06A1_Led_E;

/**
 * @brief  NFC06A1 Led structure definition
 */
typedef struct
{
  uint16_t          NFC06A1_LED_PIN;
  GPIO_TypeDef *    NFC06A1_LED_PIN_PORT;
}NFC06A1_Led_TypeDef;

#if 0 /* Code not compiled, reserved for Doxygen */
/**
  * @}
  */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#if 0 /* Code not compiled, reserved for Doxygen */
/** @defgroup NFC06A1_Exported_Functions
  * @{
  */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

void NFC06A1_LED_Init(void);
void NFC06A1_LED_DeInit(const NFC06A1_Led_E led);
void NFC06A1_LED_ON(const NFC06A1_Led_E led);
void NFC06A1_LED_OFF(const NFC06A1_Led_E led);
void NFC06A1_LED_Toggle(const NFC06A1_Led_E led);

#if 0 /* Code not compiled, reserved for Doxygen */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */ 
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

#ifdef __cplusplus
  }
#endif
#endif /* NFC06A1_H */

/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
