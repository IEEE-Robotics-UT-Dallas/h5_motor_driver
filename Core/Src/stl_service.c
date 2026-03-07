#include "stl_service.h"
#include <string.h>

#ifdef UNIT_TEST
    static bool mock_ram_fail = false;
    static bool mock_flash_fail = false;
#endif

stl_status_t stl_verify_ram(void) {
#ifdef UNIT_TEST
    return mock_ram_fail ? STL_ERR_RAM : STL_OK;
#else
    /* TODO: For John - Implement March X or C test sequence for SRAM1/2.
     * Use ST's X-CUBE-STL library if available for STM32H5. */
    return STL_OK;
#endif
}

stl_status_t stl_verify_flash(void) {
#ifdef UNIT_TEST
    return mock_flash_fail ? STL_ERR_FLASH : STL_OK;
#else
    /* TODO: For John - Use HW CRC peripheral to verify Flash checksum. */
    return STL_OK;
#endif
}

#ifdef UNIT_TEST
void _stl_mock_inject_failure(stl_status_t type) {
    if (type == STL_ERR_RAM) mock_ram_fail = true;
    if (type == STL_ERR_FLASH) mock_flash_fail = true;
}

void _stl_mock_reset(void) {
    mock_ram_fail = false;
    mock_flash_fail = false;
}
#endif
