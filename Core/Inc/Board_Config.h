#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include <stdint.h>

/* Primary Target: Final PCB Verification (H562RIT6 / H562RGT6) */
#define USE_PCB_V5 1

/* TODO: For John - Confirm final motor pin assignments and ADC channels 
 * against the latest board revision before running physical diagnostics. */

/* Motor Mapping (DRV8874 PWM + Phase) */
#define MOTOR_COUNT 6

// Motor 1 - Front Left
#define M1_PWM_PIN        6   // PC6 (TIM8_CH1)
#define M1_PH_PIN         0   // PB0
#define M1_ENCA_PIN       0   // PC0
#define M1_ENCB_PIN       1   // PC1
#define M1_IPROPI_CHAN    0   // PA0 (ADC1_IN0)

// Motor 2 - Front Right
#define M2_PWM_PIN        7   // PC7 (TIM8_CH2)
#define M2_PH_PIN         1   // PB1
#define M2_ENCA_PIN       2   // PC2
#define M2_ENCB_PIN       3   // PC3
#define M2_IPROPI_CHAN    1   // PA1 (ADC1_IN1)

// Motor 3 - Rear Left
#define M3_PWM_PIN        8   // PC8 (TIM8_CH3)
#define M3_PH_PIN         2   // PB2
#define M3_ENCA_PIN       4   // PC4
#define M3_ENCB_PIN       5   // PC5
#define M3_IPROPI_CHAN    2   // PA2 (ADC1_IN2)

// Motor 4 - Rear Right
#define M4_PWM_PIN        9   // PC9 (TIM8_CH4)
#define M4_PH_PIN         10  // PB10
#define M4_ENCA_PIN       10  // PC10
#define M4_ENCB_PIN       11  // PC11
#define M4_IPROPI_CHAN    3   // PA3 (ADC1_IN3)

// Motor 5 - Auxiliary 1
#define M5_PWM_PIN        8   // PA8 (TIM1_CH1)
#define M5_PH_PIN         4   // PA4
#define M5_ENCA_PIN       4   // PB4
#define M5_ENCB_PIN       5   // PB5
#define M5_IPROPI_CHAN    6   // PA6 (ADC1_IN6)

// Motor 6 - Auxiliary 2
#define M6_PWM_PIN        9   // PA9 (TIM1_CH2)
#define M6_PH_PIN         5   // PA5
#define M6_ENCA_PIN       6   // PB6
#define M6_ENCB_PIN       7   // PB7
#define M6_IPROPI_CHAN    7   // PA7 (ADC1_IN7)

/* BNO IMU SPI2 Mapping */
#define IMU_CS_PIN        12  // PB12
#define IMU_SCK_PIN       13  // PB13
#define IMU_MISO_PIN      14  // PB14
#define IMU_MOSI_PIN      15  // PB15
#define IMU_INT_PIN       8   // PB8
#define IMU_RST_PIN       3   // PB3

/* Global Safety */
#define DRV_FAULT_PIN     12  // PC12
#define NSLEEP_PIN        2   // PD2

/* Motor Physical Specs */
#define MOTOR_GEAR_RATIO  30.0f
#define MOTOR_MAX_RPM     333.0f   // Output shaft RPM
#define MOTOR_STALL_AMPS  3.2f
#define WHEEL_RADIUS_M    0.065f   // 65mm radius
#define MAX_LINEAR_VEL    2.26f    // m/s calculated from 333 RPM & 65mm wheels

/* Encoder Specs (11-line magnetic ring) */
#define ENCODER_LINES     11
#define ENCODER_TPR       (ENCODER_LINES * 4 * MOTOR_GEAR_RATIO) // 1320 ticks/rev

#define PWM_PERIOD 1000
#define CURRENT_LIMIT_AMPS 3.0f    // Safety margin below 3.2A stall

#endif /* BOARD_CONFIG_H */
