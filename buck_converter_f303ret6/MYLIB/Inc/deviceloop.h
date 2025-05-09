
#ifndef DEVICELOOP_H_
#define DEVICELOOP_H_

#include "stdint.h"
#include "stm32f303xe.h"
#include "Defines.h"
#include "can_receiver.h"



extern SystemState_t s_sys_state;
extern SystemCANState_t s_can_state;


void DeviceMainLoop();


#endif /* DEVICELOOP_H_ */
