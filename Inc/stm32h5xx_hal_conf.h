#ifndef STM32H5xx_HAL_CONF_H
#define STM32H5xx_HAL_CONF_H

#if !defined  (STM32H562xx)
  #define STM32H562xx
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_MODULE_ENABLED
#define HAL_ADC_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_TIM_MODULE_ENABLED
#define HAL_SPI_MODULE_ENABLED

/* Oscillator Values */
#if !defined  (HSE_VALUE)
  #define HSE_VALUE    25000000U
#endif
#define HSE_STARTUP_TIMEOUT    100U
#define CSI_VALUE              4000000UL
#define HSI_VALUE              64000000UL
#define HSI48_VALUE             48000000UL
#define LSI_VALUE  32000UL
#define LSI_STARTUP_TIME          130UL
#define LSE_VALUE  32768UL
#define LSE_STARTUP_TIMEOUT    5000UL
#define EXTERNAL_CLOCK_VALUE    12288000UL

#define  TICK_INT_PRIORITY          (15UL)

/* Assert Selection */
#define assert_param(expr) ((void)0U)

/* Includes */
#include "stm32h5xx_hal_rcc.h"
#include "stm32h5xx_hal_gpio.h"
#include "stm32h5xx_hal_dma.h"
#include "stm32h5xx_hal_cortex.h"
#include "stm32h5xx_hal_adc.h"
#include "stm32h5xx_hal_flash.h"
#include "stm32h5xx_hal_pwr.h"
#include "stm32h5xx_hal_tim.h"
#include "stm32h5xx_hal_exti.h"
#include "stm32h5xx_hal_spi.h"

#ifdef __cplusplus
}
#endif

#endif
