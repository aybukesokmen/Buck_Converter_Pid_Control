#ifndef CAN_RECEIVER_H_
#define CAN_RECEIVER_H_

#include <stdint.h>
#include "stm32f303xe.h"

typedef struct {
    uint16_t cmd_id;
    uint8_t  data[8];
    uint8_t  dlc;
} can_rx_msg_t;

void can_receiver_init(void);
void can_receiver_poll(void);  // polling yöntemiyle mesaj kontrolü
void can_read_msg(can_rx_msg_t* msg);
void can_receive_callback(const can_rx_msg_t* msg);

#endif /* CAN_RECEIVER_H_ */
