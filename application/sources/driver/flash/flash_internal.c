#include "flash_internal.h"

static void flash_clear_all_errors(void)
{
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_ALL_ERRORS_BANK1 | FLASH_FLAG_ALL_ERRORS_BANK2);
}

static uint32_t flash_get_sector(uint32_t address, uint32_t bank)
{
    /* Check if address is within Bank 1 flash range */
    if (address >= FLASH_BANK1_BASE && address < FLASH_BANK2_BASE) {
        uint32_t offset = address - FLASH_BANK1_BASE;
        uint32_t sector = offset >> 17; /* Divide by 128KB (0x20000) */
        return (sector <= 7) ? sector : 0xFFFFFFFFU;
    }
    
    /* Check if address is within Bank 2 flash range */
#ifdef DUAL_BANK
    if (address >= FLASH_BANK2_BASE && address <= FLASH_END) {
        uint32_t offset = address - FLASH_BANK2_BASE;
        uint32_t sector = offset >> 17; /* Divide by 128KB (0x20000) */
        return (sector <= 7) ? sector : 0xFFFFFFFFU;
    }
#endif
    
    /* Invalid address */
    return 0xFFFFFFFFU;
}

void internal_flash_unlock() {
	flash_clear_all_errors();

	HAL_FLASH_Unlock();
}

void internal_flash_lock() {
	HAL_FLASH_Lock();
}

/* ===================== ERASE ===================== */
void internal_flash_erase_pages_cal(uint32_t address, uint32_t len)
{
    if (len == 0) return;

    uint32_t start = address;
    uint32_t end   = address + len - 1;

    uint32_t sector_start = flash_get_sector(start, FLASH_BANK_1);
    uint32_t sector_end   = flash_get_sector(end,   FLASH_BANK_1);

    FLASH_EraseInitTypeDef erase = {0};
    uint32_t err;

    internal_flash_unlock();

    erase.TypeErase    = FLASH_TYPEERASE_SECTORS;
    erase.Banks        = FLASH_BANK_1;
    erase.Sector       = sector_start;
    erase.NbSectors    = sector_end - sector_start + 1;
    erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    if (HAL_FLASHEx_Erase(&erase, &err) != HAL_OK)
    {
        internal_flash_lock();
        return;
    }

    internal_flash_lock();
    return;
}

/* ===================== WRITE ===================== */

uint8_t internal_flash_write_cal(uint32_t address, uint8_t *data, uint32_t len)
{
    if (len == 0) return 0;

    uint32_t index = 0;
    uint32_t flash_data[8]; /* 256-bit buffer */
    uint32_t aligned_addr;

    internal_flash_unlock();

    while (index < len)
    {
        aligned_addr = (address + index) & ~0x1F; /* align 32 bytes */

        /* Read current flash word */
        uint32_t *flash_ptr = (uint32_t *)aligned_addr;
        for (int i = 0; i < 8; i++)
        {
            flash_data[i] = flash_ptr[i];
        }

        /* Merge data */
        while (index < len && ((address + index) - aligned_addr) < 32)
        {
            uint32_t byte_offset = (address + index) - aligned_addr;
            uint32_t word_index  = byte_offset >> 2;
            uint32_t byte_index  = byte_offset & 0x3;

            uint32_t mask     = 0xFF << (byte_index * 8);
            uint32_t new_byte = ((uint32_t)data[index]) << (byte_index * 8);

            /* Flash rule: only 1 -> 0 */
            if ((flash_data[word_index] & mask) != mask)
            {
                internal_flash_lock();
                return 0;
            }

            flash_data[word_index] &= ~mask;
            flash_data[word_index] |= new_byte;

            index++;
        }

        /* Program 256-bit word */
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD,
                             aligned_addr,
                             (uint32_t)flash_data) != HAL_OK)
        {
            internal_flash_lock();
            return 0;
        }
    }

    internal_flash_lock();

    /* Cacheable is used */
    SCB_CleanInvalidateDCache();
    SCB_InvalidateICache();

    return 1;
}