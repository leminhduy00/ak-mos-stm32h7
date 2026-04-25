/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>

#include "io_cfg.h"
//#pragma GCC optimize ("O3")

/******************************************************************************
* button function
*******************************************************************************/
void io_button_mode_init() {
	gpio_init_pin(BUTTON_MODE_IO_PORT, BUTTON_MODE_IO_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);
}

void io_button_up_init() {
	gpio_init_pin(BUTTON_UP_IO_PORT, BUTTON_UP_IO_PIN, GPIO_MODE_INPUT, GPIO_PULLDOWN, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);
}

void io_button_down_init() {
	gpio_init_pin(BUTTON_DOWN_IO_PORT, BUTTON_DOWN_IO_PIN, GPIO_MODE_INPUT, GPIO_PULLDOWN, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);
}

uint8_t io_button_mode_read() {
	return  gpio_read_pin(BUTTON_MODE_IO_PORT,BUTTON_MODE_IO_PIN);
}

uint8_t io_button_up_read() {
	return  gpio_read_pin(BUTTON_UP_IO_PORT,BUTTON_UP_IO_PIN);
}

uint8_t io_button_down_read() {
	return  gpio_read_pin(BUTTON_DOWN_IO_PORT,BUTTON_DOWN_IO_PIN);
}

/******************************************************************************
* led status function
*******************************************************************************/
void led_life_init() {
	gpio_init_pin(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);
}

void led_life_on() {
	gpio_write_pin(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN, GPIO_PIN_SET);
}

void led_life_off() {
	gpio_write_pin(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN, GPIO_PIN_RESET);
}
