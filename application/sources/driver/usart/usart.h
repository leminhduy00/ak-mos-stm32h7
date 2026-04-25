/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* USER CODE BEGIN Includes */
#include <stdint.h>
#include <stdbool.h>

#include "stm32h7xx_hal.h"
#include "ring_buffer.h"

#include "system.h"
#include "sys_dbg.h"
/* USER CODE END Includes */

extern UART_HandleTypeDef uart_console;

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void uart_put_char_block(uint8_t c);
uint8_t uart_get_char(void);
void uart_switch_to_non_block(void);
void uart_switch_to_block(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

