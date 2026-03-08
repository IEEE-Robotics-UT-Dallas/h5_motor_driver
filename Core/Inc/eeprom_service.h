#ifndef EEPROM_SERVICE_H
#define EEPROM_SERVICE_H

#include <stdint.h>
#include <stdbool.h>

/* EEPROM Emulation Status */
typedef enum {
    EEPROM_OK = 0,
    EEPROM_ERR_INIT,
    EEPROM_ERR_WRITE,
    EEPROM_ERR_READ
} eeprom_status_t;

/* Initialize EEPROM emulation (Uses High-Cycle Flash on H5) */
eeprom_status_t eeprom_init(void);

/* Write a 32-bit variable to virtual address */
eeprom_status_t eeprom_write(uint16_t virt_addr, uint32_t data);

/* Read a 32-bit variable from virtual address */
eeprom_status_t eeprom_read(uint16_t virt_addr, uint32_t *data);

#endif
