/*
 * adc_reader.c
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */


#include "adc_reader.h"
#include "stm32f4xx.h"  // CMSIS: Register tanımları

void ADC_Reader_Init(void)
{
    /* GPIOA saatini aç (PA0, PA1 analog) */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    /* PA0, PA1 -> Analog mode */
    GPIOA->MODER |= (3 << (0 * 2)) | (3 << (1 * 2));

    /* ADC1 saatini aç */
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    /* Ortak ayarlar: ADC saati -> PCLK2 / 4 */
    ADC->CCR &= ~ADC_CCR_ADCPRE;
    ADC->CCR |= (1 << 16);  // PCLK2 / 4

    /* Çözünürlük: 12 bit */
    ADC1->CR1 &= ~ADC_CR1_RES;

    /* Hizalama: Sağ (ALIGN = 0) */
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    /* Sıcaklık sensörü ve Vref aktif (opsiyonel) */
    ADC->CCR |= ADC_CCR_TSVREFE;

    /* ADC etkinleştirme */
    ADC1->CR2 |= ADC_CR2_ADON;
}

/* Tek kanal ölçüm (yavaş ama taşınabilir, scan mode yok) */
uint16_t ADC_Reader_ReadRaw(ADC_ChannelID_t channel)
{
    /* Kanalı seç (SQR3 -> SQ1) */
    ADC1->SQR3 = channel & 0x1F;

    /* Örnekleme süresi: 84 ADC clk (en uzun, en güvenli) */
    if (channel <= 9)
        ADC1->SMPR2 |= (7 << (channel * 3));
    else
        ADC1->SMPR1 |= (7 << ((channel - 10) * 3));

    /* Çevrimi başlat */
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* EOC bekle */
    while (!(ADC1->SR & ADC_SR_EOC));

    /* Sonucu oku */
    return (uint16_t)ADC1->DR;
}

/* ADC değerini voltaja çevir (örneğin Vref = 3.3V için) */
float ADC_Reader_ConvertToVoltage(uint16_t adc_raw, float vref)
{
    return ((float)adc_raw * vref) / 4095.0f;
}
