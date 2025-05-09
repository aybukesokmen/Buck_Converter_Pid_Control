/*
 * Init.h
 *
 *  Created on: May 9, 2025
 *      Author: 90545
 */

#ifndef INIT_H_
#define INIT_H_

#define INIT_ADC1_BUFFER_SIZE               4
#define INIT_DAC_BUFFER_SIZE 			    2
#define INIT_DAC_MAX_VALUE                 4095

#define CPU_CLOCK_FREQ_MHZ						56*1000000
#define INIT_ADC_DELAY                     10 * CPU_CLOCK_FREQ_MHZ
#define SENSOR_ADC_MAX_DATA                4095
#define SENSOR_ADC_MAX_VOLT                330


#define VDD_REF_VOLT                       3300    // 3300 mV = Reference voltage
#define VDD_REF_ADC                        4095    // 4095 = 12 bit max ADC value
#define V24_VOLT                           1430

extern uint16_t a_adc1_data_u16[INIT_ADC1_BUFFER_SIZE];
extern uint16_t a_dac_data_u16[INIT_DAC_BUFFER_SIZE];

void cpu_init(void);

void adc1_init(void);
void adc2_init(void);
void gpio_init(void);
void spi2_init(void);
void spi3_init(void);
void tim1_init(void);
void tim4_init(void);
void uart_init(void);
void dac_init(void);


#endif /* INIT_H_ */
