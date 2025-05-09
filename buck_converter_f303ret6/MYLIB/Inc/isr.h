#ifndef ISR_H_
#define ISR_H_

#include <stdint.h>
#include "stm32f303xe.h"
#include "can_receiver.h"
#include "f303_Init.h"
#include "control_pid_regulator.h"
#include "sensor_converter.h"

// Harici değişkenler (örneğin sistem durumları)
extern uint8_t sine_enable;
extern uint8_t delta_i;
extern int32_t max_value;

// Timer ve CAN interrupt fonksiyon prototipleri
void TIM3_IRQHandler(void);
void USB_LP_CAN_RX0_IRQHandler(void);

#endif /* ISR_H_ */
