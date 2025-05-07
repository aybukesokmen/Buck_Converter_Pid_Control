/*
 * adc_reader.h
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */

#ifndef ADC_READER_H_
#define ADC_READER_H_

#include <stdint.h>

typedef enum {
    ADC_CHANNEL_VOUT = 0,   // PA0 -> ADC1_IN0
    ADC_CHANNEL_IOUT = 1,   // PA1 -> ADC1_IN1
    ADC_CHANNEL_TEMP = 16   // Dahili sıcaklık sensörü
} ADC_ChannelID_t;

/* ADC DMA buffer erişimi */
extern volatile uint16_t adc_dma_buffer[2];

/* Başlatma */
void ADC_Reader_Init_DMA(void);

/* Ham değeri voltaja çevirme */
float ADC_Reader_ConvertToVoltage(uint16_t adc_raw, float vref);

#endif /* ADC_READER_H_ */
