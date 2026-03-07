#ifndef HW_BRIDGE_H
#define HW_BRIDGE_H

#include "Board_Config.h"

/* 
 * Integration Requirements:
 * 1. Generate code using CubeMX/CubeIDE for TIM8, TIM1, ADC1, and LPTIM1-4.
 * 2. Assign User Labels in CubeMX to match Board_Config.h (e.g., M1_PH).
 *
 * TODO: For John - Verify that htim8 and htim1 handles are correctly declared 
 * in main.h after CubeMX generation. Update switch cases below if custom 
 * timer assignments are made.
 */

#ifdef UNIT_TEST
    /* Mock Macros for Local Testing */
    #define WRITE_PWM(motor, val) mock_pwm_outputs[motor] = val
    #define WRITE_PHASE(motor, val) mock_phase_pins[motor] = val
#else
    /* Physical STM32 HAL Mapping */
    #include "main.h" 
    #include "tim.h"
    #include "adc.h"

    // Helper to write to specific TIM channels based on motor ID
    static inline void hw_write_pwm(int motor, float duty) {
        uint32_t pulse = (uint32_t)(duty * PWM_PERIOD);
        switch(motor) {
            case 0: __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, pulse); break;
            case 1: __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, pulse); break;
            case 2: __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, pulse); break;
            case 3: __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, pulse); break;
            case 4: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pulse); break;
            case 5: __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pulse); break;
        }
    }

    // Helper to write to Phase pins (Use CubeMX Labels: M1_PH_GPIO_Port, etc.)
    static inline void hw_write_phase(int motor, int state) {
        GPIO_PinState pin_state = (state) ? GPIO_PIN_SET : GPIO_PIN_RESET;
        switch(motor) {
            case 0: HAL_GPIO_WritePin(M1_PH_GPIO_Port, M1_PH_Pin, pin_state); break;
            case 1: HAL_GPIO_WritePin(M2_PH_GPIO_Port, M2_PH_Pin, pin_state); break;
            case 2: HAL_GPIO_WritePin(M3_PH_GPIO_Port, M3_PH_Pin, pin_state); break;
            case 3: HAL_GPIO_WritePin(M4_PH_GPIO_Port, M4_PH_Pin, pin_state); break;
            case 4: HAL_GPIO_WritePin(M5_PH_GPIO_Port, M5_PH_Pin, pin_state); break;
            case 5: HAL_GPIO_WritePin(M6_PH_GPIO_Port, M6_PH_Pin, pin_state); break;
        }
    }
    // Helper to read current from ADC1 (IPROPI channels)
    static inline float hw_read_current(int motor) {
        uint32_t channel;
        switch(motor) {
            case 0: channel = ADC_CHANNEL_0; break; // PA0
            case 1: channel = ADC_CHANNEL_1; break; // PA1
            case 2: channel = ADC_CHANNEL_2; break; // PA2
            case 3: channel = ADC_CHANNEL_3; break; // PA3
            case 4: channel = ADC_CHANNEL_6; break; // PA6
            case 5: channel = ADC_CHANNEL_7; break; // PA7
            default: return 0.0f;
        }

        /* TODO: For John - Implement ADC polling or DMA fetch here.
         * Example: Configure rank, start ADC, poll, and convert raw value 
         * to Amps using the DRV8874 IPROPI gain formula. */
        return 0.1f; // Placeholder until ADC logic is finalized
    }
#endif

#endif /* HW_BRIDGE_H */
