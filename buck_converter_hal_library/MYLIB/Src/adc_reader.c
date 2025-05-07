/*
 * adc_reader.c
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */

/*
 * adc_reader.c
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */
#include "adc_reader.h"
#include "stm32f4xx.h"

volatile uint16_t adc_dma_buffer[2];  // DMA ile doldurulacak

void ADC_Reader_Init_DMA(void)
{
    // 1. GPIOA saat ve analog moda al
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (3 << (0 * 2)) | (3 << (1 * 2));  // PA0 & PA1 analog

    // 2. DMA2 saatini aç (ADC1 için DMA2 Stream 0 kullanılır)
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // 3. ADC1 saatini aç
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // 4. ADC ortak clock prescaler ayarı (PCLK2 / 4)
    ADC->CCR &= ~ADC_CCR_ADCPRE;
    ADC->CCR |= (1 << 16); // PCLK2 / 4

    // 5. DMA2 Stream 0 konfigürasyonu (ADC1 için)
    DMA2_Stream0->CR &= ~DMA_SxCR_EN; // önce DMA'yı kapat
    while (DMA2_Stream0->CR & DMA_SxCR_EN); // emin olmak için bekle

    DMA2_Stream0->PAR = (uint32_t)&ADC1->DR;
    DMA2_Stream0->M0AR = (uint32_t)adc_dma_buffer;
    DMA2_Stream0->NDTR = 2;  // 2 kanal veri

    DMA2_Stream0->CR = 0;
    DMA2_Stream0->CR |= (0 << 25);  // Channel 0 (ADC1)
    DMA2_Stream0->CR |= DMA_SxCR_MINC     // Memory increment
                      | DMA_SxCR_CIRC     // Circular mode
                      | DMA_SxCR_PSIZE_0  // 16-bit peripheral
                      | DMA_SxCR_MSIZE_0  // 16-bit memory
                      | DMA_SxCR_PL_1;    // High priority

    DMA2_Stream0->FCR = 0; // FIFO devre dışı (direct mode)

    DMA2_Stream0->CR |= DMA_SxCR_EN;

    // 6. ADC ayarları
    ADC1->CR2 &= ~ADC_CR2_CONT;  // Tek çevrim
    ADC1->CR1 |= ADC_CR1_SCAN;   // Çok kanallı okuma (scan mode)
    ADC1->CR2 |= ADC_CR2_CONT;  // ADC sürekli çevrim moduna alınır

    // Sıralama: SQR3[4:0] = kanal 0 (VOUT), SQR3[9:5] = kanal 1 (IOUT)
    ADC1->SQR1 = (1 << 20);  // L[3:0] = 1 → 2 kanal
    ADC1->SQR3 = (ADC_CHANNEL_VOUT << 0) | (ADC_CHANNEL_IOUT << 5);

    // Örnekleme süresi: her kanal için 84 clk
    ADC1->SMPR2 |= (7 << (0 * 3)) | (7 << (1 * 3));  // IN0 ve IN1

    // DMA ayarları ADC içinde
    ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_DDS;  // DMA + sürekli istek

    // ADC etkinleştir
    ADC1->CR2 |= ADC_CR2_ADON;

    // 7. ADC çevrim başlat
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

float ADC_Reader_ConvertToVoltage(uint16_t adc_raw, float vref)
{
    return ((float)adc_raw * vref) / 4095.0f;
}
