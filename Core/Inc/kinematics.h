#ifndef KINEMATICS_H
#define KINEMATICS_H

typedef struct {
    float fl; // Front Left
    float fr; // Front Right
    float rl; // Rear Left
    float rr; // Rear Right
} motor_speeds_t;

/* Translate (Vx, Vy, Vz) to wheel speeds */
motor_speeds_t kinematics_inverse(float vx, float vy, float wz);

#endif
