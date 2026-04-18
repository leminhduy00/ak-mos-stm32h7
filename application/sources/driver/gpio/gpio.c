/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
static void MX_GPIO_EnablePortClock(GPIO_TypeDef *GPIOx)
{
  if (GPIOx == GPIOA)
  {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  }
  else if (GPIOx == GPIOB)
  {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  }
  else if (GPIOx == GPIOC)
  {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
  else if (GPIOx == GPIOD)
  {
    __HAL_RCC_GPIOD_CLK_ENABLE();
  }
  else if (GPIOx == GPIOE)
  {
    __HAL_RCC_GPIOE_CLK_ENABLE();
  }
  else if (GPIOx == GPIOF)
  {
    __HAL_RCC_GPIOF_CLK_ENABLE();
  }
  else if (GPIOx == GPIOG)
  {
    __HAL_RCC_GPIOG_CLK_ENABLE();
  }
  else if (GPIOx == GPIOH)
  {
    __HAL_RCC_GPIOH_CLK_ENABLE();
  }
  else if (GPIOx == GPIOI)
  {
    __HAL_RCC_GPIOI_CLK_ENABLE();
  }
#if defined(GPIOJ)
  else if (GPIOx == GPIOJ)
  {
    __HAL_RCC_GPIOJ_CLK_ENABLE();
  }
#endif
#if defined(GPIOK)
  else if (GPIOx == GPIOK)
  {
    __HAL_RCC_GPIOK_CLK_ENABLE();
  }
#endif
}

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
void MX_GPIO_InitPin(GPIO_TypeDef *GPIOx, uint16_t Pin, uint32_t Mode,
                     uint32_t Pull, uint32_t Speed, uint32_t Alternate,
                     GPIO_PinState InitialState)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  MX_GPIO_EnablePortClock(GPIOx);

  if ((Mode == GPIO_MODE_OUTPUT_PP) || (Mode == GPIO_MODE_OUTPUT_OD))
  {
    HAL_GPIO_WritePin(GPIOx, Pin, InitialState);
  }

  GPIO_InitStruct.Pin = Pin;
  GPIO_InitStruct.Mode = Mode;
  GPIO_InitStruct.Pull = Pull;
  GPIO_InitStruct.Speed = Speed;
  GPIO_InitStruct.Alternate = Alternate;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

/* USER CODE END 1 */

/** Configure pins
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_LIFE_IO_GPIO_Port, LED_LIFE_IO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, OLED_RST_Pin|OLED_DC_Pin|OLED_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FLASH_CE_IO_GPIO_Port, FLASH_CE_IO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_LIFE_IO_Pin */
  GPIO_InitStruct.Pin = LED_LIFE_IO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_LIFE_IO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_MODE_IO_Pin */
  GPIO_InitStruct.Pin = BUTTON_MODE_IO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_MODE_IO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OLED_RST_Pin OLED_DC_Pin OLED_CS_Pin */
  GPIO_InitStruct.Pin = OLED_RST_Pin|OLED_DC_Pin|OLED_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_UP_IO_Pin */
  GPIO_InitStruct.Pin = BUTTON_UP_IO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_UP_IO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FLASH_CE_IO_Pin */
  GPIO_InitStruct.Pin = FLASH_CE_IO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FLASH_CE_IO_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_DOWN_IO_Pin */
  GPIO_InitStruct.Pin = BUTTON_DOWN_IO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUTTON_DOWN_IO_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
/* USER CODE END 2 */
