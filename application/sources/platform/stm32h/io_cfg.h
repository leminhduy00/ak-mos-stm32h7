/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#ifndef __IO_CFG_H__
#define __IO_CFG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#include "stm32h7xx_hal.h"
#include "system_stm32h7xx.h"
#include "core_cm7.h"
#include "cmsis_gcc.h"

#include "gpio.h"

/******************************************************************************
 *Pin map button
*******************************************************************************/
#define BUTTON_DOWN_IO_PIN				(GPIO_PIN_4)
#define BUTTON_DOWN_IO_PORT				(GPIOC)

#define BUTTON_UP_IO_PIN				(GPIO_PIN_5)
#define BUTTON_UP_IO_PORT				(GPIOC)

#define BUTTON_MODE_IO_PIN				(GPIO_PIN_13)
#define BUTTON_MODE_IO_PORT				(GPIOC)

/*****************************************************************************
 *Pin map led life
******************************************************************************/
#define LED_LIFE_IO_PIN					(GPIO_PIN_3)
#define LED_LIFE_IO_PORT				(GPIOE)

/*****************************************************************************
 *Pin map buzzer
******************************************************************************/

#define BUZZER_IO_PIN					(GPIO_PIN_7)
#define BUZZER_IO_PORT					(GPIOA)
#define BUZZER_TIM                      (TIM3)

/*****************************************************************************
 *Pin map Flash W25q64
******************************************************************************/

#define FLASH_CE_IO_PIN					(GPIO_PIN_6)
#define FLASH_CE_IO_PORT				(GPIOD)

/****************************************************************************
 *Pin map ssd1106
*****************************************************************************/
#define OLED_RST_PIN					(GPIO_PIN_11)
#define OLED_RST_GPIO_PORT				(GPIOB)

#define OLED_DC_PIN						(GPIO_PIN_5)
#define OLED_DC_GPIO_PORT				(GPIOA)

#define OLED_CS_PIN						(GPIO_PIN_1)
#define OLED_CS_GPIO_PORT				(GPIOA)

/******************************************************************************
* button function
*******************************************************************************/
extern void io_button_mode_init();
extern void io_button_up_init();
extern void io_button_down_init();

extern uint8_t io_button_mode_read();
extern uint8_t io_button_up_read();
extern uint8_t io_button_down_read();

/******************************************************************************
* led status function
*******************************************************************************/
extern void led_life_init();
extern void led_life_on();
extern void led_life_off();

/******************************************************************************
* display function
*******************************************************************************/

extern void io_display_init();

#ifdef __cplusplus
}
#endif

#endif //__IO_CFG_H__
