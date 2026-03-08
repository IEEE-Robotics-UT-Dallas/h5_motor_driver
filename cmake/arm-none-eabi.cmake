set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(TOOLCHAIN_PREFIX arm-none-eabi-)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)
set(CMAKE_SIZE ${TOOLCHAIN_PREFIX}size)

set(MCU_FLAGS "-mcpu=cortex-m33 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard")

set(CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -fdata-sections -ffunction-sections" CACHE INTERNAL "c flags")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp" CACHE INTERNAL "asm flags")
set(CMAKE_EXE_LINKER_FLAGS "${MCU_FLAGS} -Wl,--gc-sections -specs=nano.specs -specs=nosys.specs" CACHE INTERNAL "linker flags")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
