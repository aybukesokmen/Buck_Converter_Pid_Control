/*
 * can_transmitter.h
 *
 *  Created on: May 9, 2025
 *      Author: asokmen
 */

#ifndef CAN_TRANSMITTER_H_
#define CAN_TRANSMITTER_H_

#include <stdint.h>
#include "main.h"

// Sistem durumu enumu
typedef enum {
    SYS_STATE_IDLE = 0,
    SYS_STATE_RUNNING = 1,
    SYS_STATE_ERROR = 2,
    SYS_STATE_OVERCURRENT = 3
} SystemCANState_t;

// Başlatma fonksiyonu
void CAN_Transmitter_Init(void);

// 100 ms'de bir çağrılacak telemetri gönderici
void CAN_Transmitter_SendTelemetry(const SystemState_t *state, SystemCANState_t status);

#endif /* CAN_TRANSMITTER_H_ */
