/*
 * control_pid_regulator.h
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */

#ifndef CONTROL_PID_REGULATOR_H_
#define CONTROL_PID_REGULATOR_H_

#include <stdint.h>

typedef struct {
    float Kp;
    float Ki;
    float Kd;

    float dt;               // Zaman adımı (saniye)
    float integral;
    float previous_error;

    float out_min;
    float out_max;
} PID_Controller_t;

/* PID kontrolcü başlatma fonksiyonu */
void PID_Init(PID_Controller_t *pid, float Kp, float Ki, float Kd, float dt, float out_min, float out_max);

/* PID hesaplama fonksiyonu */
float PID_Update(PID_Controller_t *pid, float setpoint, float measurement);

#endif /* CONTROL_PID_REGULATOR_H_ */
