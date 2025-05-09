#include "can_transmitter.h"

void can_transmitter_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_CANEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOB->MODER |=  (GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1);

    GPIOB->AFR[1] &= ~((0xF << (0 * 4)) | (0xF << (1 * 4)));  // temizle
    GPIOB->AFR[1] |=  (4 << (0 * 4)) | (4 << (1 * 4));         // PB8, PB9 AF4

    CAN->MCR |= CAN_MCR_INRQ;
    while ((CAN->MSR & CAN_MSR_INAK) == 0);

    CAN->BTR = (0 << 30) | (0 << 24) | (12 << 16) | (1 << 20) | (3 << 0);

    CAN->MCR &= ~CAN_MCR_INRQ;
    while (CAN->MSR & CAN_MSR_INAK);
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
