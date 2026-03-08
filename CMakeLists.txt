cmake_minimum_required(VERSION 3.22)

# Set the toolchain file
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi.cmake)

project(h5_motor_driver C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Add definitions
add_definitions(-DSTM32H562xx -DUSE_HAL_DRIVER)

# Include directories
include_directories(
    Core/Inc
    Inc
    Drivers/STM32H5xx_HAL_Driver/Inc
    Drivers/STM32H5xx_HAL_Driver/Inc/Legacy
    Drivers/CMSIS/Device/ST/STM32H5xx/Include
    Drivers/CMSIS/Include
)

# Source files
set(SOURCES
    Core/Src/hal_motor.c
    Core/Src/kinematics.c
    Core/Src/hal_imu_mpu6050.c
    Core/Src/stl_service.c
    Core/Src/eeprom_service.c
    Src/main.c
    Src/stm32h5xx_it.c
    Src/stm32h5xx_hal_msp.c
    Src/system_stm32h5xx.c
    
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_adc.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_adc_ex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_rcc.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_rcc_ex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_flash.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_flash_ex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_gpio.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_dma.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_dma_ex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pwr.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_pwr_ex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_cortex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_exti.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_tim.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_tim_ex.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_spi.c
    Drivers/STM32H5xx_HAL_Driver/Src/stm32h5xx_hal_spi_ex.c
    
    startup_stm32h562xx.s
)

# Executable
set(ELF_FILE ${PROJECT_NAME}.elf)
add_executable(${ELF_FILE} ${SOURCES})

# Linker script
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32H562xx_FLASH.ld)
target_link_options(${ELF_FILE} PRIVATE -T${LINKER_SCRIPT})

# Post-build commands to generate .bin and .hex
add_custom_command(TARGET ${ELF_FILE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${ELF_FILE} ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${ELF_FILE} ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_SIZE} ${ELF_FILE}
    COMMENT "Generating binary and hex files"
)
