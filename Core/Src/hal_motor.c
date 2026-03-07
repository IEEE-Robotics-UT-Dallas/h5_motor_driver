#include "hal_motor.h"
#include "hw_bridge.h"
#include <stdio.h>

static int32_t encoder_counts[MOTOR_COUNT] = {0};

#ifdef UNIT_TEST
    /* Mocked Hardware State for Unit Testing (Final PCB) */
    float mock_pwm_outputs[MOTOR_COUNT] = {0.0f};
    int32_t mock_phase_pins[MOTOR_COUNT] = {0};
    float mock_currents[MOTOR_COUNT] = {0.0f};
#endif

void hal_motor_init(void) {
    /* TODO: For John - Add any board-specific initialization sequences here 
     * (e.g. enabling PWM output stages, clearing initial faults). 
     * Base peripheral init is handled in main.c. */
}

void hal_motor_set_speed(motor_id_t motor, float speed) {
    if (motor >= MOTOR_COUNT) return;
    
    /* Global current safety check */
    if (hal_motor_get_current(motor) > CURRENT_LIMIT_AMPS) {
        speed = 0.0f; // Force stop if overcurrent detected
    }

    /* Clamp speed */
    if (speed > 1.0f) speed = 1.0f;
    if (speed < -1.0f) speed = -1.0f;

    float abs_speed = (speed < 0) ? -speed : speed;
    int phase = (speed >= 0) ? 1 : 0;

#ifdef UNIT_TEST
    mock_pwm_outputs[motor] = abs_speed;
    mock_phase_pins[motor] = phase;
#else
    hw_write_pwm(motor, abs_speed);
    hw_write_phase(motor, phase);
#endif
}

void hal_motor_stop_all(void) {
    for (int i=0; i<MOTOR_COUNT; i++) {
        hal_motor_set_speed(i, 0.0f);
    }
}

void diagnostic_startup(void) {
    printf("\r\nAssembly Diagnostic Start\r\n");
    printf("Target: STM32H562 Verification\r\n");
    
    for (int i = 0; i < MOTOR_COUNT; i++) {
        printf("Channel %d: ", i + 1);
        
        hal_motor_set_speed(i, 0.3f);
        float current = hal_motor_get_current(i);
        
        if (current > 0.01f) {
            printf("PASSED (%.2f A)\r\n", current);
        } else {
            printf("FAILED (Low current)\r\n");
        }
        
        hal_motor_set_speed(i, 0.0f);
    }
    printf("Assembly Diagnostic Complete\r\n\r\n");
}

int32_t hal_motor_get_encoder(motor_id_t motor) { return encoder_counts[motor]; }

float hal_motor_get_speed_rpm(motor_id_t motor) {
    if (motor >= MOTOR_COUNT) return 0.0f;
    
#ifdef UNIT_TEST
    // In mock, assume 100 ticks per update cycle for testing
    return (100.0f / ENCODER_TPR) * 60.0f * 100.0f; // Mock 454 RPM
#else
    /* TODO: For John - Calculate RPM based on delta ticks over DT. 
     * Formula: (delta_ticks / ENCODER_TPR) * (60 / DT_seconds) */
    return 0.0f;
#endif
}

void hal_motor_reset_encoder(motor_id_t motor) { encoder_counts[motor] = 0; }

float hal_motor_get_current(motor_id_t motor) {
    if (motor >= MOTOR_COUNT) return 0.0f;
    
#ifdef UNIT_TEST
    return mock_currents[motor];
#else
    return hw_read_current((int)motor);
#endif
}

/* Test Interface */
void _hal_motor_mock_set_current(motor_id_t motor, float current) {
    if (motor < MOTOR_COUNT) {
        mock_currents[motor] = current;
    }
}

void _hal_motor_mock_encoder_increment(motor_id_t motor, int32_t amount) { encoder_counts[motor] += amount; }
