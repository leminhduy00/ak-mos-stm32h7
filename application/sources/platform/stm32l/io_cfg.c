/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>

#include "io_cfg.h"
#include "platform.h"

#include "sys_dbg.h"
#include "sys_ctrl.h"

#include "app_dbg.h"

#include "system.h"

//#pragma GCC optimize ("O3")

/******************************************************************************
* button function
*******************************************************************************/
void io_button_mode_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_MODE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_MODE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_MODE_IO_PORT, &GPIO_InitStructure);
}

void io_button_up_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_UP_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_UP_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_UP_IO_PORT, &GPIO_InitStructure);
}

void io_button_down_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_DOWN_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_DOWN_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_DOWN_IO_PORT, &GPIO_InitStructure);
}

uint8_t io_button_mode_read() {
	return  GPIO_ReadInputDataBit(BUTTON_MODE_IO_PORT,BUTTON_MODE_IO_PIN);
}

uint8_t io_button_up_read() {
	return  GPIO_ReadInputDataBit(BUTTON_UP_IO_PORT,BUTTON_UP_IO_PIN);
}

uint8_t io_button_down_read() {
	return  GPIO_ReadInputDataBit(BUTTON_DOWN_IO_PORT,BUTTON_DOWN_IO_PIN);
}

/******************************************************************************
* led status function
*******************************************************************************/
void led_life_init() {
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(LED_LIFE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_LIFE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_LIFE_IO_PORT, &GPIO_InitStructure);
}

void led_life_on() {
	GPIO_SetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void led_life_off() {
	GPIO_ResetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

/******************************************************************************
* flash IO config
*******************************************************************************/
void flash_io_ctrl_init() {
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(FLASH_CE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = FLASH_CE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(FLASH_CE_IO_PORT, &GPIO_InitStructure);
}

void flash_cs_low() {
	GPIO_ResetBits(FLASH_CE_IO_PORT, FLASH_CE_IO_PIN);
}

void flash_cs_high() {
	GPIO_SetBits(FLASH_CE_IO_PORT, FLASH_CE_IO_PIN);
}

uint8_t flash_transfer(uint8_t data) {
	unsigned long rxtxData = data;
	uint32_t counter;

	/* waiting send idle then send data */
	counter = system_info.cpu_clock / 1000;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) {
		if (counter-- == 0) {
			FATAL("spi", 0x01);
		}
	}

	SPI_I2S_SendData(SPI1, (uint8_t)rxtxData);

	/* waiting conplete rev data */
	counter = system_info.cpu_clock / 1000;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) {
		if (counter-- == 0) {
			FATAL("spi", 0x02);
		}
	}

	rxtxData = (uint8_t)SPI_I2S_ReceiveData(SPI1);

	return (uint8_t)rxtxData;
}

/******************************************************************************
* ssd1306 oled IO function
*******************************************************************************/
void ssd1306_clk_input_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_CLK_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_CLK_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SSD1306_CLK_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_clk_output_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_CLK_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SSD1306_CLK_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SSD1306_CLK_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_clk_digital_write_low() {
	GPIO_ResetBits(SSD1306_CLK_IO_PORT,SSD1306_CLK_IO_PIN);
}

void ssd1306_clk_digital_write_high() {
	GPIO_SetBits(SSD1306_CLK_IO_PORT,SSD1306_CLK_IO_PIN);
}

int ssd1306_clk_digital_read() {
	return (int)(GPIO_ReadInputDataBit(SSD1306_CLK_IO_PORT, SSD1306_CLK_IO_PIN));
}

void ssd1306_data_input_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_DATA_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_DATA_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SSD1306_DATA_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_data_output_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(SSD1306_DATA_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_DATA_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SSD1306_DATA_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_data_digital_write_low() {
	GPIO_ResetBits(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN);
}

void ssd1306_data_digital_write_high() {
	GPIO_SetBits(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN);
}

int ssd1306_data_digital_read() {
	return (int)(GPIO_ReadInputDataBit(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN));
}

/* SH1106 driver */
void ssd1306_res_input_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_RES_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_RES_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(SSD1306_RES_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_res_output_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(SSD1306_RES_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_RES_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SSD1306_RES_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_res_digital_write_low() {
	GPIO_ResetBits(SSD1306_RES_IO_PORT, SSD1306_RES_IO_PIN);
}

void ssd1306_res_digital_write_high() {
	GPIO_SetBits(SSD1306_RES_IO_PORT, SSD1306_RES_IO_PIN);
}

int ssd1306_res_digital_read() {
	return (int)(GPIO_ReadInputDataBit(SSD1306_RES_IO_PORT, SSD1306_RES_IO_PIN));
}

void internal_flash_unlock() {
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
					FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);
}

void internal_flash_lock() {
	FLASH_Lock();
}

void internal_flash_erase_pages_cal(uint32_t address, uint32_t len) {
	uint32_t page_number;
	uint32_t index;

	page_number = len / 256;

	if ((page_number * 256) < len) {
		page_number++;
	}

	for (index = 0; index < page_number; index++) {
		FLASH_ErasePage(address + (index * 256));
	}
}

uint8_t internal_flash_write_cal(uint32_t address, uint8_t* data, uint32_t len) {
	uint32_t temp;
	uint32_t index = 0;
	FLASH_Status flash_status = FLASH_BUSY;

	while (index < len) {
		temp = 0;

		memcpy(&temp, &data[index], (len - index) >= sizeof(uint32_t) ? sizeof(uint32_t) : (len - index));

		flash_status = FLASH_FastProgramWord(address + index, temp);

		if(flash_status == FLASH_COMPLETE) {
			index += sizeof(uint32_t);
		}
		else {
			FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR |
							FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR | FLASH_FLAG_OPTVERRUSR);
		}
	}

	return 1;
}
