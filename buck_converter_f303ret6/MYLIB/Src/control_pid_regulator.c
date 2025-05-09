/*
 * control_pid_regulator.c
 *
 *  Created on: May 8, 2025
 *      Author: asokmen
 */


#include "control_pid_regulator.h"

//extern PID_Controller_t pid_controller;

PID_Controller_t pid_controller = {
    .Kp = 0.5f,
    .Ki = 0.1f,
    .Kd = 0.01f,
    .dt = 0.0001f,
    .integral = 0.0f,
    .previous_error = 0.0f,
    .out_min = 0.0f,
    .out_max = 0.95f
};

void PID_Init(PID_Controller_t *pid, float Kp, float Ki, float Kd, float dt, float out_min, float out_max)
{
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->dt = dt;

    pid->integral = 0.0f;
    pid->previous_error = 0.0f;

    pid->out_min = out_min;
    pid->out_max = out_max;
}

float PID_Update(PID_Controller_t *pid, float setpoint, float measurement)
{
    float error = setpoint - measurement;

    // P terimi
    float P = pid->Kp * error;

    // I terimi
    pid->integral += error * pid->dt;
    float I = pid->Ki * pid->integral;

    // Anti-windup
    if (I > pid->out_max) I = pid->out_max;
    if (I < pid->out_min) I = pid->out_min;

    // D terimi
    float derivative = (error - pid->previous_error) / pid->dt;
    float D = pid->Kd * derivative;

    pid->previous_error = error;

    float output = P + I + D;

    // Çıkışı sınırlama
    if (output > pid->out_max) output = pid->out_max;
    if (output < pid->out_min) output = pid->out_min;

    return output;
}


int32_t MAP(int32_t au32_IN, int32_t au32_INmin, int32_t au32_INmax, int32_t au32_OUTmin, int32_t au32_OUTmax)
{
     return ((((au32_IN - au32_INmin) *(au32_OUTmax - au32_OUTmin)) / (au32_INmax - au32_INmin)) + au32_OUTmin);
}
