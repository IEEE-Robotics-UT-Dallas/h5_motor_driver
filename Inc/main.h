#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h5xx_hal.h"

void Error_Handler(void);

/* Motor Labels for Designer (John) */
#define M1_PH_Pin GPIO_PIN_4
#define M1_PH_GPIO_Port GPIOC
#define M2_PH_Pin GPIO_PIN_5
#define M2_PH_GPIO_Port GPIOC
#define M3_PH_Pin GPIO_PIN_4
#define M3_PH_GPIO_Port GPIOB
#define M4_PH_Pin GPIO_PIN_5
#define M4_PH_GPIO_Port GPIOB
#define M5_PH_Pin GPIO_PIN_13
#define M5_PH_GPIO_Port GPIOC
#define M6_PH_Pin GPIO_PIN_14
#define M6_PH_GPIO_Port GPIOC

/* Designer Handles */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
extern ADC_HandleTypeDef hadc1;
extern SPI_HandleTypeDef hspi2;

#ifdef __cplusplus
}
#endif

#endif
