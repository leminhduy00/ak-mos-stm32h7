/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file		gpio.h
	* @brief	 This file contains all the function prototypes for
	*					the gpio.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void gpio_init_pin(GPIO_TypeDef *GPIOx, uint16_t Pin, uint32_t Mode,
										 uint32_t Pull, uint32_t Speed, uint32_t Alternate,
										 GPIO_PinState InitialState);
GPIO_PinState gpio_read_pin(GPIO_TypeDef *GPIOx, uint16_t Pin);
void gpio_write_pin(GPIO_TypeDef *GPIOx, uint16_t Pin, GPIO_PinState State);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

