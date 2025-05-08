/*
 * pwm_output_driver.c
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */


#include "pwm_output_driver.h"
#include "stm32f4xx.h"

#define PWM_TIMER        TIM3
#define PWM_CHANNEL      1
#define PWM_GPIO_PORT    GPIOA
#define PWM_GPIO_PIN     6
#define PWM_GPIO_AF      2   // PA6 → TIM3_CH1
#define PWM_RESOLUTION   4199  // ARR değeri → 20 kHz için

void PWM_Output_Init(void)
{
    // 1. GPIOA saatini aç, PA6 alternate function
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    PWM_GPIO_PORT->MODER &= ~(3 << (PWM_GPIO_PIN * 2));
    PWM_GPIO_PORT->MODER |=  (2 << (PWM_GPIO_PIN * 2));  // AF mode
    PWM_GPIO_PORT->AFR[0] |= (PWM_GPIO_AF << (PWM_GPIO_PIN * 4));  // AF2: TIM3_CH1

    // 2. TIM3 saatini aç
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // 3. PWM frekansı ayarla → 84 MHz / (PSC+1) / (ARR+1) = 20 kHz
    PWM_TIMER->PSC = 0;             // Prescaler
    PWM_TIMER->ARR = PWM_RESOLUTION;  // Auto-reload → 4199 için 20 kHz
    PWM_TIMER->CCR1 = 0;            // Başlangıç duty: 0%

    // 4. PWM mode 1 seç → CCMR1, kanal 1
    PWM_TIMER->CCMR1 &= ~TIM_CCMR1_OC1M;
    PWM_TIMER->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);  // PWM mode 1
    PWM_TIMER->CCMR1 |= TIM_CCMR1_OC1PE;            // Ön yükleme aktif

    // 5. Kanal aktif et → CCER
    PWM_TIMER->CCER |= TIM_CCER_CC1E;

    // 6. Auto-reload register yüklemesi etkinleştir
    PWM_TIMER->EGR |= TIM_EGR_UG;

    // 7. Timer başlat
    PWM_TIMER->CR1 |= TIM_CR1_CEN;
}

void PWM_Output_SetDuty(float duty_percent)
{
    if (duty_percent < 0.0f) duty_percent = 0.0f;
    if (duty_percent > 100.0f) duty_percent = 100.0f;

    uint32_t compare_val = (uint32_t)((duty_percent / 100.0f) * PWM_RESOLUTION);
    PWM_TIMER->CCR1 = compare_val;
}
