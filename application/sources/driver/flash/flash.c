#include <stdbool.h>
#include "flash.h"
#include "w25qxx.h"

static uint8_t is_flash_conneted = false;

/******************************************************************************
* define public function
*******************************************************************************/
void flash_ctrl_init() {
	MX_SPI1_Init();

	gpio_init_pin(_W25QXX_CS_GPIO, _W25QXX_CS_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0, GPIO_PIN_RESET);

	is_flash_conneted = W25qxx_Init();
}

uint8_t flash_read(uint32_t address, uint8_t* pbuf, uint32_t len)
{
	if (!is_flash_conneted)
	{
		return FLASH_DRIVER_NG;
	}

	W25qxx_ReadSector(pbuf, address, 0, len);

	return FLASH_DRIVER_OK;
}

uint8_t flash_write(uint32_t address, uint8_t* pbuf, uint32_t len)
{
	if (!is_flash_conneted)
	{
		return FLASH_DRIVER_NG;
	}
	
	W25qxx_WriteSector(pbuf, address, 0, len);

	return FLASH_DRIVER_OK;
}

uint8_t flash_erase_sector(uint32_t address)
{
	if (!is_flash_conneted)
	{
		return FLASH_DRIVER_NG;
	}

	if (address % W25QXX_FLASH_SECTOR) {
		return FLASH_DRIVER_NG;
	}

	W25qxx_EraseSector(address);

	return FLASH_DRIVER_OK;
}

uint8_t flash_erase_block_64k(uint32_t address)
{
	if (!is_flash_conneted)
	{
		return FLASH_DRIVER_NG;
	}

	if (address % W25QXX_FLASH_BLOCK_64K_SIZE) {
		return FLASH_DRIVER_NG;
	}

	W25qxx_EraseBlock(address);

	return FLASH_DRIVER_OK;
}

uint8_t  flash_erase_full()
{
	if (!is_flash_conneted)
	{
		return FLASH_DRIVER_NG;
	}

	W25qxx_EraseChip();

	return FLASH_DRIVER_OK;
}
