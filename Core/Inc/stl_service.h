#ifndef STL_SERVICE_H
#define STL_SERVICE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    STL_OK = 0,
    STL_ERR_RAM,
    STL_ERR_FLASH
} stl_status_t;

/* Run SRAM March test (destructive/non-destructive based on context) */
stl_status_t stl_verify_ram(void);

/* Run Flash CRC verification */
stl_status_t stl_verify_flash(void);

#endif
