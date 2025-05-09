#ifndef CONTROL_PID_REGULATOR_H_
#define CONTROL_PID_REGULATOR_H_

#include <stdint.h>

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    float dt;
    float integral;
    float previous_error;
    float out_min;
    float out_max;
} PID_Controller_t;

extern PID_Controller_t pid_controller;


void PID_Init(PID_Controller_t *pid, float Kp, float Ki, float Kd, float dt, float out_min, float out_max);
float PID_Update(PID_Controller_t *pid, float setpoint, float measurement);

#endif /* CONTROL_PID_REGULATOR_H_ */
