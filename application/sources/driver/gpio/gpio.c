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
/**
 * @brief  Enables the RCC clock for the specified GPIO port.
 * @param  GPIOx: Pointer to the GPIO port base address (e.g., GPIOA, GPIOB, etc.).
 * @retval None
 */
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
/**
 * @brief  Initializes a specific GPIO pin with the given configuration.
 * @param  GPIOx: Pointer to the GPIO port base address.
 * @param  Pin: Specifies the GPIO pin to be configured.
 * @param  Mode: Specifies the operating mode for the selected pin.
 * @param  Pull: Specifies the Pull-up or Pull-Down activation for the selected pin.
 * @param  Speed: Specifies the speed for the selected pin.
 * @param  Alternate: Peripheral to be connected to the selected pin.
 * @param  InitialState: Initial pin state if configured as an output.
 * @retval None
 */
void gpio_init_pin(GPIO_TypeDef *GPIOx, uint16_t Pin, uint32_t Mode,
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

GPIO_PinState gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t Pin)
{
	return HAL_GPIO_ReadPin(GPIOx, Pin);
}

void gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t Pin, GPIO_PinState State)
{
	HAL_GPIO_WritePin(GPIOx, Pin, State);
}

/* USER CODE END 1 */

/** Configure pins
		 PH0-OSC_IN (PH0)	 ------> RCC_OSC_IN
		 PH1-OSC_OUT (PH1)	 ------> RCC_OSC_OUT
		 PA13 (JTMS/SWDIO)	 ------> DEBUG_JTMS-SWDIO
		 PA14 (JTCK/SWCLK)	 ------> DEBUG_JTCK-SWCLK
*/

/* USER CODE BEGIN 2 */
/* USER CODE END 2 */
