#ifndef CAN_TRANSMITTER_H_
#define CAN_TRANSMITTER_H_

#include <stdint.h>
#include "deviceloop.h"
#include "stm32f303xe.h"

#define CAN1 CAN


typedef struct {
    uint16_t vout_mV;     // 0.01V çözünürlük
    uint16_t iout_mA;     // 0.01A çözünürlük
    uint16_t temp_cC;     // 0.01°C çözünürlük
    uint8_t  status;      // SystemCANState_t
    uint8_t  reserved;    // Sabit 0x00
} can_payload_t;

void can_transmitter_init(void);
void can_transmitter_send(const can_payload_t* payload);

#endif /* CAN_TRANSMITTER_H_ */
