/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
/* USART Communication boards Interface */
#define USARTx                           USART1
#define USARTx_IRQn                      USART1_IRQn

#define USARTx_TX_PIN                    GPIO_PIN_14
#define USARTx_TX_GPIO_PORT              GPIOB
#define USARTx_TX_AF                     GPIO_AF4_USART1

#define USARTx_RX_PIN                    GPIO_PIN_15
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF4_USART1
/* USER CODE END 0 */

UART_HandleTypeDef uart_console;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	uart_console.Instance = USART1;
	uart_console.Init.BaudRate = 115200;
	uart_console.Init.WordLength = UART_WORDLENGTH_8B;
	uart_console.Init.StopBits = UART_STOPBITS_1;
	uart_console.Init.Parity = UART_PARITY_NONE;
	uart_console.Init.Mode = UART_MODE_TX_RX;
	uart_console.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uart_console.Init.OverSampling = UART_OVERSAMPLING_16;
	uart_console.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	uart_console.Init.ClockPrescaler = UART_PRESCALER_DIV1;
	uart_console.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&uart_console) != HAL_OK)
	{
		FATAL("USART", 0x01);
	}
	if (HAL_UARTEx_SetTxFifoThreshold(&uart_console, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		FATAL("USART", 0x02);
	}
	if (HAL_UARTEx_SetRxFifoThreshold(&uart_console, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
	{
		FATAL("USART", 0x03);
	}
	if (HAL_UARTEx_DisableFifoMode(&uart_console) != HAL_OK)
	{
		FATAL("USART", 0x04);
	}
	/* USER CODE BEGIN USART1_Init 2 */
    __HAL_UART_ENABLE_IT(&uart_console, UART_IT_RXNE);
	/* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	if(uartHandle->Instance==USART1)
	{
	/* USER CODE BEGIN USART1_MspInit 0 */

	/* USER CODE END USART1_MspInit 0 */

	/** Initializes the peripherals clock
	 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1;
		PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			FATAL("USART", 0x05);
		}

		/* USART1 clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**USART1 GPIO Configuration
		PB14     ------> USART1_TX
		PB15     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = USARTx_TX_PIN|USARTx_RX_PIN;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		GPIO_InitStruct.Alternate = USARTx_TX_AF;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USART1 interrupt Init */
		HAL_NVIC_SetPriority(USART1_IRQn, 2, 0);
		HAL_NVIC_EnableIRQ(USART1_IRQn);
	/* USER CODE BEGIN USART1_MspInit 1 */
		__HAL_UART_ENABLE_IT(&uart_console, UART_IT_RXNE);
	/* USER CODE END USART1_MspInit 1 */
	}
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PB14     ------> USART1_TX
    PB15     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_14|GPIO_PIN_15);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void uart_put_char_block(uint8_t c)
{
	HAL_UART_Transmit(&uart_console, (uint8_t*)&c, 1, HAL_MAX_DELAY);
}

void uart_switch_to_non_block(void)
{
	__HAL_UART_ENABLE_IT(&uart_console, UART_IT_TXE);
}

void uart_switch_to_block(void)
{
	__HAL_UART_DISABLE_IT(&uart_console, UART_IT_TXE);
}

uint8_t uart_get_char(void)
{
	volatile uint8_t c;
	if (__HAL_UART_GET_FLAG(&uart_console, UART_FLAG_RXNE))
    {
        c = (uint8_t)uart_console.Instance->RDR;
    }

	return c;
}
/* USER CODE END 1 */

