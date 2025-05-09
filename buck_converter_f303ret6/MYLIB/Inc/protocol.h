#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>
#include "deviceloop.h"
#include "can_transmitter.h"

typedef struct
{
    uint8_t vout_raw[2];
    uint8_t iout_raw[2];
    uint8_t temp_raw[2];
    uint8_t status_u8;
    uint8_t reserved_u8;
}s_transmit_msg_format_t;

extern s_transmit_msg_format_t transmit_msg;

void protocol_init(const SystemState_t* sys, SystemCANState_t status);

#endif /* PROTOCOL_H_ */
