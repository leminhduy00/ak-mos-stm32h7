#ifndef __FLASH_INTERNAL_H__
#define __FLASH_INTERNAL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stm32h7xx_hal.h>

void internal_flash_unlock(void);
void internal_flash_lock(void);
void internal_flash_erase_pages_cal(uint32_t address, uint32_t len);
uint8_t internal_flash_write_cal(uint32_t address, uint8_t* data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif //__FLASH_INTERNAL_H__
