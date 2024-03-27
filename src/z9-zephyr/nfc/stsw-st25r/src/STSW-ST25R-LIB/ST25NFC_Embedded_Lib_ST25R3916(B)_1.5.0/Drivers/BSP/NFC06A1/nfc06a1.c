/**
  ******************************************************************************
  * @file    nfc06a1.c
  * @author  MMY Application Team
  * @brief   This file provides nfc06a1 specific functions
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

/* Includes ------------------------------------------------------------------*/
#include "nfc06a1.h"

#if 0 /* Code not compiled, reserved for Doxygen */
/** @addtogroup BSP
 * @{
 */

/** @addtogroup NFC06A1
 * @{
 */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/ 
#if 0 /* Code not compiled, reserved for Doxygen */
/** @defgroup NFC06A1_Private_Variables
 * @{
 */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

/** Array including all led pin and port information */
static NFC06A1_Led_TypeDef NFC06A1_Led[6] = { { NFC06A1_LED1_PIN, NFC06A1_LED1_PIN_PORT } , 
                                              { NFC06A1_LED2_PIN, NFC06A1_LED2_PIN_PORT } ,
                                              { NFC06A1_LED3_PIN, NFC06A1_LED3_PIN_PORT } ,
                                              { NFC06A1_LED4_PIN, NFC06A1_LED4_PIN_PORT } , 
                                              { NFC06A1_LED5_PIN, NFC06A1_LED5_PIN_PORT } ,
                                              { NFC06A1_LED6_PIN, NFC06A1_LED6_PIN_PORT } };

#if 0 /* Code not compiled, reserved for Doxygen */ 
/**
 * @}
 */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

/* Private function prototypes -----------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Functions Definition ------------------------------------------------------*/
#if 0 /* Code not compiled, reserved for Doxygen */
/** @defgroup NFC06A1_Private_Functions
 * @{
 */
#endif /* MISRAC2012 4.4 : Avoid a section of code seems to be commented out */

/**
  * @brief  This function initialize the GPIO to manage the Leds
  *         through GPIO
  * @param  None
  * @return None
  */
void NFC06A1_LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  uint8_t led;
  
  /* Enable all GPIO port clock for the Led pins */
  NFC06A1_ALLLED_GPIO_CLK_ENABLE();
  
  /* Configure GPIO for all Led pins */
  for (led = 0; led < (sizeof(NFC06A1_Led) / sizeof(NFC06A1_Led_TypeDef)); led++)
  {
    GPIO_InitStruct.Pin = NFC06A1_Led[led].NFC06A1_LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, &GPIO_InitStruct);
    
    /* Configure Led pin Output Level as off */
    HAL_GPIO_WritePin(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, NFC06A1_Led[led].NFC06A1_LED_PIN, GPIO_PIN_RESET);
  }
}

/**
  * @brief     DeInit LEDs.
  * @note      Led DeInit does not disable the GPIO clock nor disable the Mfx
  * @param[in] Led : LED to be de-init. 
  * @return    None
  */
void NFC06A1_LED_DeInit(const NFC06A1_Led_E led)
{
  GPIO_InitTypeDef gpio_init_structure;

  /* Turn off LED */
  HAL_GPIO_WritePin(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, NFC06A1_Led[led].NFC06A1_LED_PIN, GPIO_PIN_RESET);
  /* DeInit the GPIO_LED pin */
  gpio_init_structure.Pin = NFC06A1_Led[led].NFC06A1_LED_PIN;
  HAL_GPIO_DeInit(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, gpio_init_structure.Pin);
}

/**
  * @brief     This function light on selected Led
  * @param[in] led : Led to be lit on
  * @return    None
  */
void NFC06A1_LED_ON(const NFC06A1_Led_E led)
{
  HAL_GPIO_WritePin(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, NFC06A1_Led[led].NFC06A1_LED_PIN, GPIO_PIN_SET);
}

/**
  * @brief     This function light off selected Led
  * @param[in] led : Led to be lit off
  * @return    None
  */
void NFC06A1_LED_OFF(const NFC06A1_Led_E led)
{
  HAL_GPIO_WritePin(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, NFC06A1_Led[led].NFC06A1_LED_PIN, GPIO_PIN_RESET);
}

/**
  * @brief     Toggles the selected LED
  * @param[in] led : Specifies the Led to be toggled
  * @return    None
  */
void NFC06A1_LED_Toggle(const NFC06A1_Led_E led)
{
  HAL_GPIO_TogglePin(NFC06A1_Led[led].NFC06A1_LED_PIN_PORT, NFC06A1_Led[led].NFC06A1_LED_PIN);
}

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

/******************* (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
