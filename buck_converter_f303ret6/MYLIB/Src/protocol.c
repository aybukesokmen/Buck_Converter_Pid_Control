#include "protocol.h"
#include "can_transmitter.h"

void protocol_init(const SystemState_t* sys, SystemCANState_t status)
{
    can_payload_t payload;

    payload.vout_mV   = (uint16_t)(sys->vout * 100.0f);
    payload.iout_mA   = (uint16_t)(sys->iout * 100.0f);
    payload.temp_cC   = (uint16_t)(sys->temperature * 100.0f);
    payload.status    = (uint8_t)status;
    payload.reserved  = 0x00;

    can_transmitter_send(&payload);
}
