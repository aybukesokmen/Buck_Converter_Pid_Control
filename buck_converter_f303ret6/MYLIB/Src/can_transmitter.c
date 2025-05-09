#include "can_transmitter.h"


// STM32F303 bxCAN register tabanlı gönderim
void can_transmitter_init(void)
{

    // CAN saatini aç (RCC üzerinden), filtre vs. burada ayarlanabilir (opsiyonel)
    // NOT: Eğer başka bir yerde yapılandırıldıysa burası boş bırakılabilir.
}

// DBC'ye uygun veri gönderir (CAN1, mailbox 0)
void can_transmitter_send(const can_payload_t* payload)
{
    // Boş mailbox kontrolü
    if ((CAN1->TSR & CAN_TSR_TME0) == 0)
        return;

    uint8_t* data = (uint8_t*)payload;

    // Mesaj başlık yapılandırması
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_TXRQ;      // Önce temizle
    CAN1->sTxMailBox[0].TIR = (0x555 << 21);        // StdID: 0x555 (11-bit)

    CAN1->sTxMailBox[0].TDTR = 8;  // 8 byte veri

    CAN1->sTxMailBox[0].TDLR = ((uint32_t)data[0]) |
                               ((uint32_t)data[1] << 8) |
                               ((uint32_t)data[2] << 16) |
                               ((uint32_t)data[3] << 24);

    CAN1->sTxMailBox[0].TDHR = ((uint32_t)data[4]) |
                               ((uint32_t)data[5] << 8) |
                               ((uint32_t)data[6] << 16) |
                               ((uint32_t)data[7] << 24);

    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;  // Gönder
}
