#ifndef HAL_IMU_H
#define HAL_IMU_H

#include <stdint.h>

typedef struct {
    float x, y, z;
} imu_vec3_t;

/* Initialize IMU (I2C for MPU6050, SPI for Final) */
void hal_imu_init(void);

/* Get Gyroscope data in deg/s */
imu_vec3_t hal_imu_get_gyro(void);

/* Get Accelerometer data in Gs */
imu_vec3_t hal_imu_get_accel(void);

/* Get filtered Yaw heading in degrees */
float hal_imu_get_yaw(void);

#endif
