/*
 * pwm_output_driver.h
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */

#ifndef PWM_OUTPUT_DRIVER_H_
#define PWM_OUTPUT_DRIVER_H_

/* PWM başlatma fonksiyonu (örnek: TIM3, CH1, PA6) */
void PWM_Output_Init(void);

/* Duty değerini %0 - %100 aralığında ayarlar */
void PWM_Output_SetDuty(float duty_percent);

#endif /* PWM_OUTPUT_DRIVER_H_ */
