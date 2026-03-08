#include "unity.h"
#include "hal_motor.h"
#include "kinematics.h"
#include "hal_imu.h"
#include "stl_service.h"
#include "eeprom_service.h"
#include <stdbool.h>

extern float mock_pwm_outputs[MOTOR_COUNT];
extern int32_t mock_phase_pins[MOTOR_COUNT];
extern void _hal_imu_mock_set_yaw(float yaw);
extern void _hal_motor_mock_encoder_increment(motor_id_t motor, int32_t amount);
extern void _hal_motor_mock_set_current(motor_id_t motor, float current);
extern void _stl_mock_inject_failure(stl_status_t type);
extern void _stl_mock_reset(void);
extern void _eeprom_mock_clear(void);

void setUp(void) {
    hal_motor_init();
    hal_imu_init();
    _stl_mock_reset();
    _eeprom_mock_clear();
    for(int i=0; i<MOTOR_COUNT; i++) {
        mock_pwm_outputs[i] = 0.0f;
        mock_phase_pins[i] = 0;
        hal_motor_reset_encoder(i);
        _hal_motor_mock_set_current(i, 0.0f);
    }
    _hal_imu_mock_set_yaw(0.0f);
}

void tearDown(void) {}

/* Kinematics */

void test_kinematics_straight_forward(void) {
    // Physics: 333 RPM @ 65mm radius = 2.26 m/s max velocity
    // Requesting 0.5 m/s -> Expected Duty Cycle = 0.5 / 2.26 = ~0.221
    motor_speeds_t speeds = kinematics_inverse(0.5f, 0.0f, 0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.221f, speeds.fl);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.221f, speeds.fr);
}

void test_kinematics_rotation_inplace(void) {
    motor_speeds_t speeds = kinematics_inverse(0.0f, 0.0f, 1.0f);
    TEST_ASSERT_TRUE(speeds.fl < 0);
    TEST_ASSERT_TRUE(speeds.fr > 0);
    TEST_ASSERT_TRUE(speeds.rl < 0);
    TEST_ASSERT_TRUE(speeds.rr > 0);
}

/* Motor, Encoder & Current */

void test_hal_motor_mapping_all_six(void) {
    for (int i=0; i<MOTOR_COUNT; i++) {
        hal_motor_set_speed(i, 0.5f);
        TEST_ASSERT_FLOAT_WITHIN(0.01f, 0.5f, mock_pwm_outputs[i]);
        TEST_ASSERT_EQUAL_INT(1, mock_phase_pins[i]); 
    }
}

void test_encoder_counters(void) {
    for (int i=0; i<MOTOR_COUNT; i++) {
        _hal_motor_mock_encoder_increment(i, 100);
        TEST_ASSERT_EQUAL_INT32(100, hal_motor_get_encoder(i));
        hal_motor_reset_encoder(i);
        TEST_ASSERT_EQUAL_INT32(0, hal_motor_get_encoder(i));
    }
}

void test_motor_current_polling(void) {
    for (int i=0; i<MOTOR_COUNT; i++) {
        _hal_motor_mock_set_current(i, 1.25f);
        TEST_ASSERT_FLOAT_WITHIN(0.01f, 1.25f, hal_motor_get_current(i));
    }
    TEST_ASSERT_EQUAL_FLOAT(0.0f, hal_motor_get_current(MOTOR_ID_MAX));
}

void test_overcurrent_safety_cutoff(void) {
    // Simulate current just over the 2.5A limit
    _hal_motor_mock_set_current(MOTOR_FL, 2.6f);
    hal_motor_set_speed(MOTOR_FL, 0.5f);
    
    // Motor should be forced to 0% PWM due to safety logic
    TEST_ASSERT_EQUAL_FLOAT(0.0f, mock_pwm_outputs[MOTOR_FL]);
}

/* IMU */

void test_imu_yaw_reading(void) {
    _hal_imu_mock_set_yaw(45.5f);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 45.5f, hal_imu_get_yaw());
}

/* Memory (STL) */

void test_memory_integrity_check(void) {
    TEST_ASSERT_EQUAL_INT(STL_OK, stl_verify_ram());
    TEST_ASSERT_EQUAL_INT(STL_OK, stl_verify_flash());

    _stl_mock_inject_failure(STL_ERR_RAM);
    TEST_ASSERT_EQUAL_INT(STL_ERR_RAM, stl_verify_ram());
}

/* EEPROM (X-CUBE-EEPROM) */

void test_eeprom_write_read(void) {
    uint32_t write_val = 0xDEADBEEF;
    uint32_t read_val = 0;
    
    TEST_ASSERT_EQUAL_INT(EEPROM_OK, eeprom_write(10, write_val));
    TEST_ASSERT_EQUAL_INT(EEPROM_OK, eeprom_read(10, &read_val));
    TEST_ASSERT_EQUAL_HEX32(write_val, read_val);
}

/* Safety */

void test_emergency_stop(void) {
    hal_motor_set_speed(MOTOR_FL, 1.0f);
    hal_motor_stop_all();
    TEST_ASSERT_EQUAL_FLOAT(0.0f, mock_pwm_outputs[MOTOR_FL]);
}

void test_diagnostic_routine_safe_exit(void) {
    for(int i=0; i<MOTOR_COUNT; i++) _hal_motor_mock_set_current(i, 0.5f);
    diagnostic_startup();
    for (int i=0; i<MOTOR_COUNT; i++) {
        TEST_ASSERT_EQUAL_FLOAT(0.0f, mock_pwm_outputs[i]);
    }
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_kinematics_straight_forward);
    RUN_TEST(test_kinematics_rotation_inplace);
    RUN_TEST(test_hal_motor_mapping_all_six);
    RUN_TEST(test_encoder_counters);
    RUN_TEST(test_motor_current_polling);
    RUN_TEST(test_overcurrent_safety_cutoff);
    RUN_TEST(test_imu_yaw_reading);
    RUN_TEST(test_memory_integrity_check);
    RUN_TEST(test_eeprom_write_read);
    RUN_TEST(test_emergency_stop);
    RUN_TEST(test_diagnostic_routine_safe_exit);
    return UNITY_END();
}
