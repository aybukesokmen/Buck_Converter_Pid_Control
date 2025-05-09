/*
 * deviceloop.h
 *
 *  Created on: May 9, 2025
 *      Author: haydar.gungor
 */

#ifndef DEVICELOOP_H_
#define DEVICELOOP_H_

#include "stdint.h"
#include "stm32f303xe.h"


typedef struct {
    float vout;
    float iout;
    float temperature;
    float pwm_duty;
    float vout_target;
    uint8_t overcurrent;
} SystemState_t;

typedef enum {
    SYS_STATE_IDLE = 0,
    SYS_STATE_RUNNING,
    SYS_STATE_ERROR,
    SYS_STATE_OVERCURRENT
} SystemCANState_t;


void DeviceMainLoop();


#endif /* DEVICELOOP_H_ */
