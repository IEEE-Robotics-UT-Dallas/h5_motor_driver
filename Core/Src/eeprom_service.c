#include "eeprom_service.h"
#include <string.h>

#ifdef UNIT_TEST
    #define MOCK_EEPROM_SIZE 128
    static uint32_t mock_eeprom[MOCK_EEPROM_SIZE] = {0};
    static bool mock_init_fail = false;
#endif

eeprom_status_t eeprom_init(void) {
#ifdef UNIT_TEST
    return mock_init_fail ? EEPROM_ERR_INIT : EEPROM_OK;
#else
    /* TODO: For John - Implement X-CUBE-EEPROM HAL linkage here.
     * Configure sectors in the High-Cycle data area (EDATA) 
     * as per stm32h5xx_hal_flash_ex.c */
    return EEPROM_OK;
#endif
}

eeprom_status_t eeprom_write(uint16_t virt_addr, uint32_t data) {
#ifdef UNIT_TEST
    if (virt_addr >= MOCK_EEPROM_SIZE) return EEPROM_ERR_WRITE;
    mock_eeprom[virt_addr] = data;
    return EEPROM_OK;
#else
    /* TODO: For John - Call HAL_FLASH_Program to write to EDATA area. */
    return EEPROM_OK;
#endif
}

eeprom_status_t eeprom_read(uint16_t virt_addr, uint32_t *data) {
#ifdef UNIT_TEST
    if (virt_addr >= MOCK_EEPROM_SIZE) return EEPROM_ERR_READ;
    *data = mock_eeprom[virt_addr];
    return EEPROM_OK;
#else
    /* TODO: For John - Direct memory read from Flash virtual address. */
    return EEPROM_OK;
#endif
}

#ifdef UNIT_TEST
void _eeprom_mock_inject_fail(bool fail) { mock_init_fail = fail; }
void _eeprom_mock_clear(void) { memset(mock_eeprom, 0, sizeof(mock_eeprom)); }
#endif
