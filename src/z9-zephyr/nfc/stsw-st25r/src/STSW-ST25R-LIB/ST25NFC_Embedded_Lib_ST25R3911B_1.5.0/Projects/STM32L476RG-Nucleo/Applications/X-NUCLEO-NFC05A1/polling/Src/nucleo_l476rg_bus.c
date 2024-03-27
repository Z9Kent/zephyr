/**
  ******************************************************************************
  * @file    nucleo_l476rg_bus.c
  * @author  MMY Application Team
  * @brief   source file for the BSP BUS IO driver
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
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
#include "nucleo_l476rg_bus.h"
#include "st25r3911_interrupt.h"
#include <string.h>

/** @addtogroup BSP
  * @{
  */

/** @addtogroup NUCLEO_L476RG
  * @{
  */

/** @defgroup NUCLEO_L476RG_BUS NUCLEO_L476RG BUS
  * @{
  */
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/

#define VALID_PRESC_NBR                 100
#define PRESC_MAX                       16
#define SCLDEL_MAX                      16
#define SDADEL_MAX                      16
#define SCLH_MAX                        256
#define SCLL_MAX                        256

#define NSEC_PER_SEC                    1000000000L

/* Private macros ------------------------------------------------------------*/
#define DIV_ROUND_CLOSEST(x, d)  (((x) + ((d) / 2)) / (d))

/* Private variables ---------------------------------------------------------*/
/** @defgroup NUCLEO_L476RG_Private_Variables BUS Private Variables
  * @{
  */

SPI_HandleTypeDef Handle_Spi1;
EXTI_HandleTypeDef hExti0 = {.Line=BSP_SPI1_IRQ_EXTI_LINE};
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
static uint32_t IsSPI1MspCbValid = 0;										
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Private function prototypes -----------------------------------------------*/
/** @defgroup NUCLEO_L476RG_Private_FunctionPrototypes  Private Function Prototypes
  * @{
  */
static uint32_t SPI_GetPrescaler(const uint32_t clock_src_hz, const uint32_t baudrate_mbps );
static void SPI1_MspInit(SPI_HandleTypeDef * const spiHandle);
static void SPI1_MspDeInit(SPI_HandleTypeDef * const spiHandle);
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
int32_t BSP_SPI1_RegisterMspCallbacks (BSP_SPI_Cb_t * const Callback);
int32_t BSP_SPI1_RegisterDefaultMspCallbacks(void);
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Functions Definition ------------------------------------------------------*/
/** @defgroup NUCLEO_L476RG_BUS_Exported_Functions NUCLEO_L476RG_BUS Exported Functions
  * @{
  */
/**
  * @brief  Return system tick in ms
  * @param  None
  * @return Current HAL time base time stamp
  */
int32_t BSP_GetTick(void)
{
  return HAL_GetTick();
}

/* BUS IO driver over SPI Peripheral */
/*******************************************************************************
                            BUS OPERATIONS OVER SPI
*******************************************************************************/
/**
  * @brief  Initialize the SPI1 bus
  * @param  None
  * @return BSP status
  */
int32_t BSP_SPI1_Init(void)
{
  int32_t ret = BSP_ERROR_NONE;

  Handle_Spi1.Instance  = BUS_SPI1;

  if (HAL_SPI_GetState(&Handle_Spi1) == HAL_SPI_STATE_RESET)
  {
#if (USE_HAL_SPI_REGISTER_CALLBACKS == 0)
    /* Init the SPI Msp */
    SPI1_MspInit(&Handle_Spi1);
#else
    if(IsSPI1MspCbValid == 0U)
    {
      if(BSP_SPI1_RegisterDefaultMspCallbacks() != BSP_ERROR_NONE)
      {
        return BSP_ERROR_MSP_FAILURE;
      }
    }
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */
    /* Init the SPI */
    if ((MX_SPI1_Init(&Handle_Spi1, SPI_GetPrescaler(HAL_RCC_GetPCLK2Freq(), BUS_SPI1_BAUDRATE) )) != HAL_OK)
    {
      ret = BSP_ERROR_BUS_FAILURE;
    }
    else
    {
      ret = BSP_ERROR_NONE;
    }
  }

  return ret;
}

/**
  * @brief  DeInitialize SPI bus
  * @param  None
  * @retval BSP status
  */
int32_t BSP_SPI1_DeInit(void)
{
  int32_t ret = BSP_ERROR_NONE;

  /* DeInit the SPI */
  if (HAL_SPI_DeInit(&Handle_Spi1) != HAL_OK)
  {
    ret = BSP_ERROR_BUS_FAILURE;
  }
  
  /* DeInit the SPI Msp */
  SPI1_MspDeInit(&Handle_Spi1);

  return ret;
}

/**
  * @brief      SPI Write byte(s) to device
  * @param[in]  pTxData : Pointer to data buffer to write
  * @param[in]  Length : number of bytes to write
  * @return     BSP status
  */
int32_t BSP_SPI1_Send(const uint8_t * const pData, const uint16_t Length)
{
  HAL_StatusTypeDef status;
  uint8_t   tx[256];
  int32_t ret = BSP_ERROR_NONE;

  if (pData != NULL)
  {
    (void)memcpy(tx, pData, Length);
  }

  status = HAL_SPI_Transmit(&Handle_Spi1, tx, Length, BUS_SPI1_TIMEOUT);

  /* Check the communication status */
  if (status != HAL_OK)
  {
    /* Execute user timeout callback */
    ret = BSP_SPI1_Init();
  }

  return ret;
}

/**
  * @brief      SPI Read and Write byte(s) to device
  * @param[in]  pTxData : Pointer to data buffer to write
  * @param[out] pRxData : Pointer to data buffer for read data
  * @param[in]  Length : number of bytes to write
  * @return     BSP status
  */
int32_t BSP_SPI1_Recv(uint8_t * const pData, const uint16_t Length)
{
  HAL_StatusTypeDef status;
  uint8_t   rx[256];
  int32_t ret = BSP_ERROR_BUS_FAILURE;

  status = HAL_SPI_Receive(&Handle_Spi1, (pData != NULL) ? (uint8_t *)pData : rx, Length, BUS_SPI1_TIMEOUT);

  /* Check the communication status */
  if (status != HAL_OK)
  {
    /* Execute user timeout callback */
    ret = BSP_SPI1_Init();
  }
  else
  {
    ret = BSP_ERROR_NONE;
  }

  return ret;
}

/**
  * @brief      SPI Read and Write byte(s) to device
  * @param[in]  pTxData : Pointer to data buffer to write
  * @param[out] pRxData : Pointer to data buffer for read data
  * @param[in]  Length : number of bytes to write
  * @return     BSP status
  */
int32_t BSP_SPI1_SendRecv(const uint8_t * const pTxData, uint8_t * const pRxData, uint16_t Length)
{
  HAL_StatusTypeDef status;
  int32_t ret = BSP_ERROR_NONE;

  if((pTxData != NULL)&&(pRxData != NULL))
  {
    status = HAL_SPI_TransmitReceive(&Handle_Spi1, (uint8_t *)pTxData, (uint8_t *)pRxData, Length, BUS_SPI1_TIMEOUT);
  } else if ((pTxData != NULL)&&(pRxData == NULL)) {
    status = HAL_SPI_Transmit(&Handle_Spi1, (uint8_t *)pTxData, Length, BUS_SPI1_TIMEOUT);
  } else if ((pTxData == NULL)&&(pRxData != NULL)) {
    status = HAL_SPI_Receive(&Handle_Spi1, (uint8_t *)pRxData, Length, BUS_SPI1_TIMEOUT);
  }
  /* Check the communication status */
  if (status != HAL_OK)
  {
    /* Execute user timeout callback */
    ret = BSP_SPI1_Init();
  }

  return ret;
}

/**
  * @brief  SPI error treatment function
  * @param  None
  * @return BSP status
  */
int32_t BSP_SPI1_Error(void)
{
  /* De-initialize the SPI communication BUS */
  (void)HAL_SPI_DeInit(&Handle_Spi1);

  /* Re-Initiaize the SPI communication BUS */
  return BSP_SPI1_Init();
}

#if (USE_HAL_SPI_REGISTER_CALLBACKS == 1)
/**
  * @brief     BSP SPI1 Bus Msp Callback registering
  * @param[in] Callback: pointer to SPI1 MspInit/MspDeInit callback functions
  * @return    BSP status
  */
int32_t BSP_SPI1_RegisterMspCallbacks (BSP_SPI_Cb_t * const Callback)
{
  int32_t ret = BSP_ERROR_NONE;

  __HAL_SPI_RESET_HANDLE_STATE(&Handle_Spi1);

  /* Register MspInit/MspDeInit Callbacks */
  if (HAL_SPI_RegisterCallback(&Handle_Spi1, HAL_SPI_MSPINIT_CB_ID, Callback->pMspSpiInitCb) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else if (HAL_SPI_RegisterCallback(&Handle_Spi1, HAL_SPI_MSPDEINIT_CB_ID, Callback->pMspSpiDeInitCb) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    IsSPI1MspCbValid = 1U;
  }

  /* BSP status */
  return ret;
}

/**
  * @brief  Register Default BSP SPI1 Bus Msp Callbacks
  * @param  None
  * @return BSP status
  */
int32_t BSP_SPI1_RegisterDefaultMspCallbacks(void)
{
  int32_t ret = BSP_ERROR_NONE;

  __HAL_SPI_RESET_HANDLE_STATE (&Handle_Spi1);

  /* Register default MspInit/MspDeInit Callback */
  if (HAL_SPI_RegisterCallback(&Handle_Spi1, HAL_SPI_MSPINIT_CB_ID, SPI1_MspInit) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else if (HAL_SPI_RegisterCallback(&Handle_Spi1, HAL_SPI_MSPDEINIT_CB_ID, SPI1_MspDeInit) != HAL_OK)
  {
    ret = BSP_ERROR_PERIPH_FAILURE;
  }
  else
  {
    IsSPI1MspCbValid = 1U;
  }

  /* BSP status */
  return ret;
}
#endif /* USE_HAL_SPI_REGISTER_CALLBACKS */

/**
  * @brief         Configure the SPI1 peripheral
  * @param[in,out] p_SpiHandle: Handle to the SPI peripheral
  * @param[in]     Baudrate_Presc: Prescaler value, to achieve the baudrate, with respect to sysclock
  * @return        HAL status
  */
__weak HAL_StatusTypeDef MX_SPI1_Init(SPI_HandleTypeDef* const p_SpiHandle, const uint32_t Baudrate_Presc)
{
  HAL_StatusTypeDef ret = HAL_OK;

  p_SpiHandle->Init.Mode              = SPI_MODE_MASTER;
  p_SpiHandle->Init.Direction         = SPI_DIRECTION_2LINES;
  p_SpiHandle->Init.DataSize          = SPI_DATASIZE_8BIT;
  p_SpiHandle->Init.CLKPolarity       = SPI_POLARITY_LOW;
  p_SpiHandle->Init.CLKPhase          = SPI_PHASE_2EDGE;
  p_SpiHandle->Init.NSS               = SPI_NSS_SOFT;
  p_SpiHandle->Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
  p_SpiHandle->Init.BaudRatePrescaler = Baudrate_Presc;
  p_SpiHandle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
  p_SpiHandle->Init.TIMode            = SPI_TIMODE_DISABLE;
  p_SpiHandle->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  p_SpiHandle->Init.CRCLength         = SPI_CRC_LENGTH_DATASIZE;
  p_SpiHandle->Init.CRCPolynomial     = 7;

  if (HAL_SPI_Init(p_SpiHandle) != HAL_OK)
  {
    ret = HAL_ERROR;
  }

  return ret;
}

/**
  * @brief     Retrieve prescaler value to achieve baudrate with respect to sysclock
  * @param[in] Clock_Src_Hz: spi source clock
  * @param[in] Baudrate_Mbps: baudrate value to achieve in mbps
  * @return    Prescaler value
  */
static uint32_t SPI_GetPrescaler(const uint32_t Clock_Src_Hz, const uint32_t Baudrate_Mbps )
{
  uint32_t divisor = 0;
  uint32_t spi_clk = Clock_Src_Hz;
  uint32_t presc = 0;
  static const uint32_t baudrate[]= {
                                      SPI_BAUDRATEPRESCALER_2,
                                      SPI_BAUDRATEPRESCALER_4,
                                      SPI_BAUDRATEPRESCALER_8,
                                      SPI_BAUDRATEPRESCALER_16,
                                      SPI_BAUDRATEPRESCALER_32,
                                      SPI_BAUDRATEPRESCALER_64,
                                      SPI_BAUDRATEPRESCALER_128,
                                      SPI_BAUDRATEPRESCALER_256,
                                    };

  while (spi_clk > Baudrate_Mbps)
  {
    presc = baudrate[divisor];
    if (++divisor > 7)
    {
      break;
    }

    spi_clk = (spi_clk >> 1);
  }

  return presc;
}

/**
  * @brief         Initialize SPI1 MSP.
  * @param[in,out] p_SpiHandle: Handle to the SPI1 peripheral
  * @return        None
  */
static void SPI1_MspInit(SPI_HandleTypeDef* const p_SpiHandle)
{
  GPIO_InitTypeDef  gpioinitstruct;

  /* Enable GPIO clock */
  BUS_SPI1_NSS_GPIO_CLK_ENABLE();
  BUS_SPI1_IRQ_GPIO_CLK_ENABLE();
  BUS_SPI1_SCK_GPIO_CLK_ENABLE();
  BUS_SPI1_MISO_GPIO_CLK_ENABLE();
  BUS_SPI1_MOSI_GPIO_CLK_ENABLE();

  /*** Configure GPIOs ***/
  /* Configure SPI NSS */
  /* Configure SPI NSS as GPIO function */
  gpioinitstruct.Pin        = BUS_SPI1_NSS_GPIO_PIN;
  gpioinitstruct.Mode       = BUS_SPI1_NSS_MODE;
  gpioinitstruct.Pull       = GPIO_NOPULL;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_MEDIUM;
  gpioinitstruct.Alternate  = BUS_SPI1_NSS_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_NSS_GPIO_PORT, &gpioinitstruct);

  /* Configure SPI NSS pin Output Level */
  HAL_GPIO_WritePin(BUS_SPI1_NSS_GPIO_PORT, BUS_SPI1_NSS_GPIO_PIN, GPIO_PIN_SET);

  /* Configure SPI IRQ as GPIO interrupt function */
  gpioinitstruct.Pin        = BUS_SPI1_IRQ_GPIO_PIN;
  gpioinitstruct.Mode       = BUS_SPI1_IRQ_MODE;
  HAL_GPIO_Init(BUS_SPI1_IRQ_GPIO_PORT, &gpioinitstruct);

  /* Configure SPI SCK, MISO and MOSI */
  /* Configure SPI SCK as alternate function */
  gpioinitstruct.Pin        = BUS_SPI1_SCK_GPIO_PIN;
  gpioinitstruct.Mode       = BUS_SPI1_SCK_MODE;
  gpioinitstruct.Alternate  = BUS_SPI1_SCK_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_SCK_GPIO_PORT, &gpioinitstruct);

  /* Configure SPI MISO as alternate function */
  gpioinitstruct.Pin        = BUS_SPI1_MISO_GPIO_PIN;
  gpioinitstruct.Mode       = BUS_SPI1_MISO_MODE;
  gpioinitstruct.Alternate  = BUS_SPI1_MISO_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_MISO_GPIO_PORT, &gpioinitstruct);

  /* Configure SPI MOSI as alternate function */
  gpioinitstruct.Pin        = BUS_SPI1_MOSI_GPIO_PIN;
  gpioinitstruct.Mode       = BUS_SPI1_MOSI_MODE;
  gpioinitstruct.Alternate  = BUS_SPI1_MOSI_GPIO_AF;
  HAL_GPIO_Init(BUS_SPI1_MOSI_GPIO_PORT, &gpioinitstruct);

  /*** Configure the SPI peripheral ***/
  /* Enable SPI clock */
  BUS_SPI1_CLK_ENABLE();

  /* Configure interrupt callback */
  (void)HAL_EXTI_GetHandle(&hExti0, hExti0.Line);
  (void)HAL_EXTI_RegisterCallback(&hExti0, HAL_EXTI_COMMON_CB_ID, BSP_SPI1_IRQ_Callback);

  /* Enable interruption */
  HAL_NVIC_SetPriority(BSP_SPI1_IRQ_EXTI_IRQn, BSP_SPI1_IRQ_PRIO, 0);
  HAL_NVIC_EnableIRQ(BSP_SPI1_IRQ_EXTI_IRQn);

}

/**
  * @brief         DeInitialize SPI1 MSP.
  * @param[in,out] spiHandle: Handle to the SPI1 peripheral
  * @return        None
  */
static void SPI1_MspDeInit(SPI_HandleTypeDef* const spiHandle)
{
  /* Disable IRQ interrupts */
  HAL_NVIC_DisableIRQ((IRQn_Type)(BSP_SPI1_IRQ_EXTI_IRQn));

  /* Restore Gpio configuration */
  HAL_GPIO_DeInit(BUS_SPI1_NSS_GPIO_PORT, BUS_SPI1_NSS_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_SPI1_IRQ_GPIO_PORT, BUS_SPI1_IRQ_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_SPI1_SCK_GPIO_PORT, BUS_SPI1_SCK_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_SPI1_MISO_GPIO_PORT, BUS_SPI1_MISO_GPIO_PIN);
  HAL_GPIO_DeInit(BUS_SPI1_MOSI_GPIO_PORT, BUS_SPI1_MOSI_GPIO_PIN);

  /* Peripheral clock disable */
  __HAL_RCC_SPI1_CLK_DISABLE();
}

/**
  * @brief  BSP SPI1 callback
  * @param  None
  * @return None
  */
__weak void BSP_SPI1_IRQ_Callback(void)
{
  /* Prevent unused argument(s) compilation warning */

  /* This function should be implemented by the user application.
   * It is called into this driver when an event from ST25R3916 is triggered.
   */
  st25r3911Isr();
}

/**
  * @brief  BSP SPI1 interrupt Handler
  * @param  None
  * @return None
  */
void BSP_SPI1_IRQHandler(void)
{
  HAL_EXTI_IRQHandler(&hExti0);
}

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
