#ifndef HAL_MOTOR_H
#define HAL_MOTOR_H

#include <stdint.h>
#include "Board_Config.h"

typedef enum {
    MOTOR_FL = 0,
    MOTOR_FR = 1,
    MOTOR_RL = 2,
    MOTOR_RR = 3,
    MOTOR_AUX1 = 4,
    MOTOR_AUX2 = 5,
    MOTOR_ID_MAX
} motor_id_t;

void hal_motor_init(void);
void hal_motor_set_speed(motor_id_t motor, float speed);
int32_t hal_motor_get_encoder(motor_id_t motor);
float hal_motor_get_speed_rpm(motor_id_t motor);
void hal_motor_reset_encoder(motor_id_t motor);
float hal_motor_get_current(motor_id_t motor);
void hal_motor_stop_all(void);
void diagnostic_startup(void);

#endif /* HAL_MOTOR_H */
