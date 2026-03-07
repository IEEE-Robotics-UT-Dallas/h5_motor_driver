#include "kinematics.h"
#include "Board_Config.h"

/* Mechanum drive geometry constants */
const float ROBOT_LX = 0.15f;    // Length X (center to axle)
const float ROBOT_LY = 0.15f;    // Length Y (center to wheel)

motor_speeds_t kinematics_inverse(float vx, float vy, float wz) {
    motor_speeds_t speeds;
    
    // Calculate raw required linear speeds (m/s)
    speeds.fl = vx - vy - wz * (ROBOT_LX + ROBOT_LY);
    speeds.fr = vx + vy + wz * (ROBOT_LX + ROBOT_LY);
    speeds.rl = vx + vy - wz * (ROBOT_LX + ROBOT_LY);
    speeds.rr = vx - vy + wz * (ROBOT_LX + ROBOT_LY);
    
    // Scale speeds based on physical MAX_LINEAR_VEL (1.0 = 100% PWM)
    speeds.fl /= MAX_LINEAR_VEL;
    speeds.fr /= MAX_LINEAR_VEL;
    speeds.rl /= MAX_LINEAR_VEL;
    speeds.rr /= MAX_LINEAR_VEL;
    
    return speeds;
}
