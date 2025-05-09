#include "can_receiver.h"
#include "control_pid_regulator.h"


void can_receiver_init(void)
{
    /** 1. Filtreyi yapılandır **/
    CAN->FMR |= CAN_FMR_FINIT;      // filtre init moduna geç

    // Filtre bank 0, mask mode, 32-bit
    CAN->FA1R |= (1 << 0);          // filtreyi etkinleştir (filter 0)
    CAN->FM1R &= ~(1 << 0);         // mask mode
    CAN->FS1R |= (1 << 0);          // 32-bit
    CAN->FFA1R &= ~(1 << 0);        // FIFO 0'a yönlendir

    // Tüm ID'leri kabul et (mask = 0x00000000)
    CAN->sFilterRegister[0].FR1 = 0x00000000;
    CAN->sFilterRegister[0].FR2 = 0x00000000;

    CAN->FMR &= ~CAN_FMR_FINIT;     // filtre init modundan çık
}

void can_receiver_poll(void)
{
    if ((CAN->RF0R & CAN_RF0R_FMP0) != 0)  // FIFO 0’da mesaj var mı?
    {
        can_rx_msg_t rx;

        rx.cmd_id = (CAN->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
        rx.dlc = CAN->sFIFOMailBox[0].RDTR & 0x0F;

        uint32_t low = CAN->sFIFOMailBox[0].RDLR;
        uint32_t high = CAN->sFIFOMailBox[0].RDHR;

        for (int i = 0; i < 4; ++i) {
            rx.data[i] = (low >> (i * 8)) & 0xFF;
            rx.data[i + 4] = (high >> (i * 8)) & 0xFF;
        }

        CAN->RF0R |= CAN_RF0R_RFOM0;  // FIFO boşalt

        can_receive_callback(&rx);    // kullanıcıya mesajı yönlendir
    }
}

void can_read_msg(can_rx_msg_t* msg)
{
    msg->cmd_id = (CAN->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
    msg->dlc = CAN->sFIFOMailBox[0].RDTR & 0x0F;

    uint32_t low = CAN->sFIFOMailBox[0].RDLR;
    uint32_t high = CAN->sFIFOMailBox[0].RDHR;

    for (int i = 0; i < 4; ++i) {
        msg->data[i] = (low >> (i * 8)) & 0xFF;
        msg->data[i + 4] = (high >> (i * 8)) & 0xFF;
    }
}

void can_receive_callback(const can_rx_msg_t* msg)
{
	if (msg->cmd_id == 0x600 && msg->dlc >= 2) {
	    float new_kp = ((msg->data[0] << 8) | msg->data[1]) / 100.0f;
	    pid_controller.Kp = new_kp;
	}

}
