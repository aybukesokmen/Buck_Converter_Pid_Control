#include "stm32f303xe.h"
#include "f303_Init.h"

uint16_t a_adc1_data_u16[INIT_ADC1_BUFFER_SIZE] = {0, 0, 0, 0};
//uint16_t a_dac_data_u16[INIT_DAC_BUFFER_SIZE]   = {0, 0};

void cpu_init(void)
{

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    FLASH->ACR  |=  (1U << 0);            // One latency, if 24 MHz < HCLK ≤ 48 MHz
    while(!(FLASH->ACR & 7U));            // Wait for one latency ready

    RCC->CR     |=  (1U << 0);            // HSI oscillator ON
    while(!(RCC->CR & 2));                // Wait for HSI oscillator ready

    RCC->CFGR   |=  (1U << 15);           // HSI used as PREDIV1 entry
    RCC->CFGR   &= ~(1U << 16);           //

    RCC->CFGR   |=  (1U << 18);           // PLL input clock x 7
    RCC->CFGR   &= ~(1U << 19);           //
    RCC->CFGR   |=  (1U << 20);           //
    RCC->CFGR   &= ~(1U << 21);           //

    RCC->CFGR2  &= ~(15U << 0);           // HSE input to PLL not divided

    RCC->CR     |=  (1U << 24);           // PLL ON
    while(!(RCC->CR & 25U));              // Wait for PLL locked

    RCC->CFGR   &= ~(1U << 7);            // SYSCLK not divided
    RCC->CFGR   &= ~(1U << 8);            // APB1 (PLCK1): HCLK divided by 2
    RCC->CFGR   &= ~(1U << 9);            //
    RCC->CFGR   |=  (1U << 10);           //
    RCC->CFGR   &= ~(1U << 13);           // APB2 (PCLK2): HCLK not divided

    RCC->CFGR   &= ~(1U << 0);            // PLL selected as system clock
    RCC->CFGR   |=  (1U << 1);            //
    while(((RCC->CFGR >> 2) & 3U) != 2U); // Wait for PLL used as system clock

    RCC->CFGR2  |=  (1U << 8);            // PLL clock divided by 1 for ADC1 and ADC2
    RCC->CFGR3  &= ~(1U << 0);            // PCLK2 selected as USART1 clock source
    RCC->CFGR3  &= ~(1U << 1);            //
    RCC->CFGR3  &= ~(1U << 8);            // PCLK2 selected as TIM1 clock source
    RCC->CFGR3  &= ~(1U << 24);           // PCLK2 selected as TIM2 clock source
    RCC->CFGR3  &= ~(1U << 25);           // PCLK2 selected as TIM3 and TIM4 clock source

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= (3U << 20);  /* Set CP10 full access */
    SCB->CPACR |= (3U << 22);  /* Set CP11 full access */
#endif
}

void adc1_init(void)
{
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    RCC->AHBENR |= RCC_AHBENR_ADC12EN;
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    GPIOC->MODER |=  (3U << 0);              // PC0 Analog mode
    GPIOC->PUPDR &= ~(3U << 0);              // PC0 No pull-up, pull-down

    GPIOC->MODER |=  (3U << 2);              // PC1 Analog mode
    GPIOC->PUPDR &= ~(3U << 2);              // PC1 No pull-up, pull-down

    GPIOC->MODER |=  (3U << 4);              // PC2 Analog mode
    GPIOC->PUPDR &= ~(3U << 4);              // PC2 No pull-up, pull-down

    GPIOC->MODER |=  (3U << 6);              // PC3 Analog mode
    GPIOC->PUPDR &= ~(3U << 6);              // PC3 No pull-up, pull-down

    GPIOA->MODER |=  (3U << 0);              // PA0 Analog mode
    GPIOA->PUPDR &= ~(3U << 0);              // PA0 No pull-up, pull-down

    GPIOA->MODER |=  (3U << 2);              // PA1 Analog mode
    GPIOA->PUPDR &= ~(3U << 2);              // PA1 No pull-up, pull-down

    GPIOA->MODER |=  (3U << 4);              // PA2 Analog mode
    GPIOA->PUPDR &= ~(3U << 4);              // PA2 No pull-up, pull-down

    GPIOA->MODER |=  (3U << 6);              // PA3 Analog mode
    GPIOA->PUPDR &= ~(3U << 6);              // PA3 No pull-up, pull-down

    GPIOB->MODER     |= (3U << 22);  		 // PA3 Analog mode
    GPIOB->PUPDR     &= ~(3U << 22);   	 // PB11 No pull-up, pull-down


    DMA1_Channel1->CCR &= ~(1U << 4);        // Read from peripheral
    DMA1_Channel1->CCR |=  (1U << 5);        // Circular mode enabled
    DMA1_Channel1->CCR &= ~(1U << 6);        // Peripheral increment mode disabled
    DMA1_Channel1->CCR |=  (1U << 7);        // Memory increment mode enabled
    DMA1_Channel1->CCR |=  (1U << 8);        // Peripheral size 16 bit
    DMA1_Channel1->CCR &= ~(1U << 9);        //
    DMA1_Channel1->CCR |=  (1U << 10);       // Memory size 16 bit
    DMA1_Channel1->CCR &= ~(1U << 11);       //
    DMA1_Channel1->CCR &= ~(3U << 12);       // Priority Low
    DMA1_Channel1->CCR &= ~(1U << 14);       // Memory to memory mode disabled

    ADC1->CFGR         |=  (1U  << 0);       // DMA mode enabled
    ADC1->CFGR         |=  (1U  << 1);       // DMA Circular Mode selected
    ADC1->CFGR         &= ~(3U  << 4);       // Data resolution 12 bit
    ADC1->CFGR         &= ~(1U  << 5);       // Right alignment
    ADC1->CFGR         &= ~(15U << 6);       // External trigger selection Event 0
    ADC1->CFGR         &= ~(3U  << 10);      // Hardware trigger detection disabled (conversions can be launched by software)
    ADC1->CFGR         |=  (1U  << 12);      // ADCx_DR register is overwritten with the last conversion result when an overrun is detected.
    ADC1->CFGR         |=  (1U  << 13);      // Continuous conversion mode
    ADC1->CFGR         &= ~(1U  << 14);      // Auto-delayed conversion mode off
    ADC1->CFGR         &= ~(1U  << 16);      // Discontinuous mode for regular channels disabled
    ADC1->CFGR         &= ~(7U  << 17);      // Discontinuous mode channel count 1 channel

    ADC1->SQR1         |=  (9U << 0);        // Regular channel sequence length 9 conversions
    ADC1->SQR1         |=  (1U << 6);        // 1. conversion channel 1
    ADC1->SQR1         |=  (2U << 12);       // 2. conversion channel 2
    ADC1->SQR1         |=  (3U << 18);       // 3. conversion channel 3
    ADC1->SQR1         |=  (4U << 24);       // 4. conversion channel 4

    ADC1->SQR2         |=  (6U << 0);        // 5. conversion channel 6
    ADC1->SQR2         |=  (7U << 6);        // 6. conversion channel 7
    ADC1->SQR2         |=  (8U << 12);       // 7. conversion channel 8
    ADC1->SQR2         |=  (9U << 18);       // 8. conversion channel 9
    ADC1->SQR2         |=  (16U << 24);      // 9. conversion channel 16
    ADC1->SQR3         |=  (14U << 0);      // 9. conversion channel 16

    ADC1->SMPR1        |=  (7U << 3);        // Channel 1 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 6);        // Channel 2 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 9);        // Channel 3 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 12);       // Channel 4 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 18);       // Channel 6 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 21);       // Channel 7 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 24);       // Channel 8 601.5 ADC clock cycles
    ADC1->SMPR1        |=  (7U << 27);       // Channel 9 601.5 ADC clock cycles
    ADC1->SMPR2        |=  (7U << 18);       // Channel 16 601.5 ADC clock cycles
    ADC1->SMPR2        |=  (7U << 12);       // Channel 14 601.5 ADC clock cycles
    ADC1->DIFSEL       &= ~(0x3FFFFU << 1);  // All channels are single ended

    ADC12_COMMON->CCR  &= ~(31U << 0);       // Independent mode
    ADC12_COMMON->CCR  &= ~(15U << 8);       // Delay 0
    ADC12_COMMON->CCR  &= ~(3U << 14);       // MDMA mode disabled
    ADC12_COMMON->CCR  &= ~(3U << 16);       // Asynchronous clock mode
    ADC12_COMMON->CCR  |=  (1U << 23);       // Temperature sensor is enabled

    ADC1->CR           |=  (1U << 28);       // ADC Voltage regulator enabled
    ADC1->CR           &= ~(1U << 29);       //
    ADC1->CR           |=  (1U << 31);       // ADC Calibration

    uint32_t i = INIT_ADC_DELAY;
    while(i--);                              // Wait for ADC internal voltage regulator stabilization */

    DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
    DMA1_Channel1->CMAR = (uint32_t)(a_adc1_data_u16);

    DMA1_Channel1->CNDTR |=  (10U << 0);      // Number of data to transfer
    DMA1_Channel1->CCR   |=  (1U << 1);      // TC interrupt enabled
    DMA1_Channel1->CCR   |=  (1U << 0);      // Channel enabled

    ADC1->CR             |=  (1U << 0);      // Write 1 to enable the ADC
    while(!(ADC1->ISR & (1U << 0)));         // Wait for ADC is ready to start conversion
    ADC1->CR             |=  (1U << 2);      // Write 1 to start regular conversions
}



void gpio_init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

    /* Configure Inputs */
    GPIOB->MODER   &= ~(3U << 0);   // PB0 Reserved Input
    GPIOB->PUPDR   &= ~(1U << 0);   // Pull-down
    GPIOB->PUPDR   |=  (1U << 1);   //

    GPIOC->MODER   &= ~(3U << 10);  // PC5 Reserved Input
    GPIOC->PUPDR   &= ~(1U << 10);  // Pull-down
    GPIOC->OTYPER  |=  (1U << 10);  //

    GPIOC->MODER   &= ~(3U << 8);   // PC4 Reserved Input
    GPIOC->PUPDR   &= ~(1U << 8);   // Pull-down
    GPIOC->PUPDR   |=  (1U << 8);   //

    GPIOA->MODER   &= ~(3U << 14);  // PA7 Reserved Input
    GPIOA->PUPDR   &= ~(1U << 14);  // Pull-down
    GPIOA->PUPDR   |=  (1U << 15);  //

    GPIOA->MODER   &= ~(3U << 12);  // PA6 Reserved Input
    GPIOA->PUPDR   &= ~(1U << 12);  // Pull-down
    GPIOA->PUPDR   |=  (1U << 13);  //

    /* Configure Outputs */
    GPIOC->BRR      =  (1U << 12);  // PC6 status led
    GPIOC->MODER   |=  (1U << 12);  //
    GPIOC->MODER   &= ~(1U << 13);  //
    GPIOC->PUPDR   &= ~(3U << 12);  //
    GPIOC->OSPEEDR &= ~(3U << 12);  //
    GPIOC->OTYPER  &= ~(1U << 6);   //

    GPIOC->BRR      =  (1U << 14);  // PC7 fault led
    GPIOC->MODER   |=  (1U << 14);  //
    GPIOC->MODER   &= ~(1U << 15);  //
    GPIOC->PUPDR   &= ~(3U << 14);  //
    GPIOC->OSPEEDR &= ~(3U << 14);  //
    GPIOC->OTYPER  &= ~(1U << 7);   //
}


/* PWM signals configuration  */
void tim1_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;

    /* PWM 1 */
    GPIOA->MODER      &= ~(1U << 16);    // PA8 Alternate function mode
    GPIOA->MODER      |=  (1U << 17);    //
    GPIOA->PUPDR      &= ~(1U << 16);    // PA8 No pull-up, pull-down
    GPIOA->PUPDR      &= ~(1U << 17);    //
    GPIOA->OSPEEDR    &= ~(1U << 16);    // PA8 Low speed
    GPIOA->OSPEEDR    &= ~(1U << 17);    //
    GPIOA->OTYPER     &= ~(1U << 8);     // PA8 Output push-pull
    GPIOA->AFR[1]     &= ~(1U << 0);     // AF6 (TIM1)
    GPIOA->AFR[1]     |=  (1U << 1);     //
    GPIOA->AFR[1]     |=  (1U << 2);     //
    GPIOA->AFR[1]     &= ~(1U << 3);     //

    /* PWM 2 */
    GPIOA->MODER      &= ~(1U << 18);    // PA9 Alternate function mode
    GPIOA->MODER      |=  (1U << 19);    //
    GPIOA->PUPDR      &= ~(1U << 18);    // PA9 No pull-up, pull-down
    GPIOA->PUPDR      &= ~(1U << 19);    //
    GPIOA->OSPEEDR    &= ~(1U << 18);    // PA9 Low speed
    GPIOA->OSPEEDR    &= ~(1U << 19);    //
    GPIOA->OTYPER     &= ~(1U << 9);     // PA9 Output push-pull
    GPIOA->AFR[1]     &= ~(1U << 4);     // AF6 (TIM1)
    GPIOA->AFR[1]     |=  (1U << 5);     //
    GPIOA->AFR[1]     |=  (1U << 6);     //
    GPIOA->AFR[1]     &= ~(1U << 7);     //

    TIM1->CR1         &= ~(1U << 4);     // Counter used as upcounter
    TIM1->CR1         &= ~(1U << 7);     // Disable ARR Preload
    TIM1->CR1         &= ~(3U << 8);     // Clock division 1
    TIM1->CR2         &= ~(7U << 4);     // Master mode selection reset

    TIM1->CR2         &= ~(1U << 8);     // OC1  idle state low
    TIM1->CR2         &= ~(1U << 9);     // OC1N idle state low
    TIM1->CR2         &= ~(1U << 10);    // OC2  idle state low
    TIM1->CR2         &= ~(1U << 11);    // OC2N idle state low

    TIM1->CCMR1       &= ~(1U << 2);     // OC1 fast disable
    TIM1->CCMR1       &= ~(1U << 10);    // OC2 fast disable

    TIM1->CCMR1       |=  (1U << 3);     // OC1 preload enable
    TIM1->CCMR1       |=  (1U << 11);    // OC2 preload enable

    TIM1->CCMR1       &= ~(7U << 4);     // OC1 PWM mode 1
    TIM1->CCMR1       |=  (1U << 5);     //
    TIM1->CCMR1       |=  (1U << 6);     //
    TIM1->CCMR1       &= ~(7U << 12);    // OC2 PWM mode 1
    TIM1->CCMR1       |=  (1U << 13);    //
    TIM1->CCMR1       |=  (1U << 14);    //

    TIM1->CCER        &= ~(1U << 2);     // OC1N is not active
    TIM1->CCER        &= ~(1U << 6);     // OC2N is not active

    TIM1->CCER        &= ~(1U << 0);     // OC1  is not active
    TIM1->CCER        &= ~(1U << 4);     // OC2  is not active

    TIM1->CCER        |=  (1U << 3);     // OC1N polarity is active low
    TIM1->CCER        |=  (1U << 7);     // OC2N polarity is active low

    TIM1->CCER        &= ~(1U << 1);     // OC1  polarity is active high
    TIM1->CCER        &= ~(1U << 5);     // OC2  polarity is active high

    TIM1->BDTR        |=  (255U << 0);   // Dead-time
    TIM1->BDTR        &= ~(3U << 8);     // Lock level off
    TIM1->BDTR        &= ~(1U << 10);    // OC/OCN are disabled in idle
    TIM1->BDTR        &= ~(1U << 11);    // OC/OCN are disabled in run
    TIM1->BDTR        &= ~(1U << 12);    // Break inputs disabled
    TIM1->BDTR        |=  (1U << 13);    // Break input BRK is active high
    TIM1->BDTR        &= ~(1U << 14);    // Automatic output disable
    TIM1->BDTR        &= ~(1U << 15);    // Main output disable
    TIM1->BDTR        &= ~(15U << 16);   // No filter, BRK  acts asynchronously
    TIM1->BDTR        &= ~(15U << 20);   // No filter, BRK2 acts asynchronously
    TIM1->BDTR        &= ~(1U << 24);    // Break input BRK2 disabled
    TIM1->BDTR        |=  (1U << 25);    // Break input BRK2 is active high

    TIM1->CCR1         =  0;             // Capture Compare Register 1
    TIM1->CCR2         =  0;             // Capture Compare Register 2
    TIM1->PSC = 9;
    TIM1->ARR = 279; // 56 MHz / (9+1) / (279+1) = 20 kHz

    TIM1->CCR1         =  0;             // Capture compare 1 zero
    TIM1->CCR2         =  0;             // Capture compare 2 zero
    TIM1->CCER        |=  (1U << 0);     // PWM1  enabled
    TIM1->CCER        |=  (1U << 4);     // PWM2  enabled
    TIM1->BDTR        |=  (1U << 15);    // Main output enabled
    TIM1->CR1         |=  (1U << 0);     // Counter enabled
}

/* Timebase counter for state machine */
void tim4_init(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    TIM4->CR1  &= ~(1U << 4);    // Counter used as upcounter
    TIM4->CR1  &= ~(1U << 7);    // Disable ARR Preload
    TIM4->CR1  &= ~(3U << 8);    // Clock division 1
    TIM4->CR2  &= ~(7U << 4);    // Master mode selection reset
    TIM4->SMCR &= ~(1U << 7);    // Disable master slave mode

    TIM4->PSC   =  55;           // Prescaler
    TIM4->ARR   =  65535;        // Auto-reload register

    TIM4->CR1  |=  (1U << 0);    // Counter enabled

    while(!(TIM4->SR & 0x01));   // Wait for Update interrupt flag
}

void dac_init(void)
{
    RCC->AHBENR  |= RCC_AHBENR_GPIOAEN;                   // Gpio A Port Clock Line Enable
    RCC->AHBENR  |= RCC_AHBENR_DMA1EN;                    // Dma1 Clock Line Enable
    RCC->APB1ENR |= RCC_APB1ENR_DAC1EN;                   // Dac1 Clock Line Enable
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;                   // Timer6 Clock Line Enable

    GPIOA->MODER |= (3U << 8);                            // Gpio A Port Pin 4 Mode Analog
    GPIOA->MODER |= (3U << 10);                           // Gpio A Port Pin 5 Mode Analog
    GPIOA->PUPDR |= (3U << 8);                            // Gpio A Port Pin 4 No Pull
    GPIOA->PUPDR |= (3U << 10);                           // Gpio A Port Pin 5 No Pull

    DMA1_Channel3->CCR |=  (1U << 4);                     // Dma1 Channel 3 Direction P->M
    DMA1_Channel3->CCR &= ~(3U << 12);                    // Dma1 Channel 3 Priority Low
    DMA1_Channel3->CCR |=  (1U << 5);                     // Dma1 Channel 3 Circular Mode
    DMA1_Channel3->CCR &= ~(1U << 6);                     // Dma1 Channel 3 Pinc Disabled
    DMA1_Channel3->CCR |=  (1U << 7);                     // Dma1 Channel 3 Minc Enabled
    DMA1_Channel3->CCR &= ~(1U << 8);                     // Dma1 Channel 3 Psize Word
    DMA1_Channel3->CCR |=  (1U << 9);
    DMA1_Channel3->CCR &= ~(1U << 10);                    // Dma1 Channel 3 Msize Word
    DMA1_Channel3->CCR |=  (1U << 11);

    SYSCFG->CFGR1 |= (1U << 13);                          // Dma1 Tim6 Dac1 Remap

    DMA1_Channel4->CCR |=  (1U << 4);                     // Dma1 Channel 4 Direction P->M
    DMA1_Channel4->CCR &= ~(3U << 12);                    // Dma1 Channel 4 Priority Low
    DMA1_Channel4->CCR |=  (1U << 5);                     // Dma1 Channel 4 Circular Mode
    DMA1_Channel4->CCR &= ~(1U << 6);                     // Dma1 Channel 4 Pinc Disabled
    DMA1_Channel4->CCR |=  (1U << 7);                     // Dma1 Channel 4 Minc Enabled
    DMA1_Channel4->CCR |=  (1U << 8);                     // Dma1 Channel 4 Psize Word
    DMA1_Channel4->CCR &= ~(1U << 9);
    DMA1_Channel4->CCR |=  (1U << 10);                    // Dma1 Channel 4 Msize Word
    DMA1_Channel4->CCR &= ~(1U << 11);

    SYSCFG->CFGR1 |= (1U << 14);                          // Dma1 Tim6 Dac1 Remap

    DAC->CR &= ~(7U << 3);                                // Dac1 Channel1 Trigger Source Tim6 Trgo
    DAC->CR &= ~(3U << 6);                                // Dac1 Channel1 Wave Gen None
    DAC->CR &= ~(1U << 1);                                // Dac1 Channel1 Output Buffer Enabled
    DAC->CR |=  (1U << 2);                                // Dac1 Channel1 Trigger Enabled
    DAC->CR &= ~(7U << 19);                               // Dac1 Channel2 Trigger Source Tim6 Trgo
    DAC->CR &= ~(3U << 22);                               // Dac1 Channel2 Wave Gen None
    DAC->CR &= ~(1U << 17);                               // Dac1 Channel2 Output Buffer Enabled
    DAC->CR |=  (1U << 18);                               // Dac1 Channel2 Trigger Enabled

    DMA1_Channel3->CPAR = (uint32_t)(&(DAC->DHR12R1));    // Dma Channel3 Peripheral Address
    DMA1_Channel3->CMAR = (uint32_t)(&a_dac_data_u16[0]); // Dma Channel3 Memory Address
    DMA1_Channel4->CPAR = (uint32_t)(&(DAC->DHR12R2));    // Dma Channel4 Peripheral Address
    DMA1_Channel4->CMAR = (uint32_t)(&a_dac_data_u16[1]); // Dma Channel3 Memory Address
    DMA1_Channel3->CNDTR |= (1U << 0);                    // Dma Channel3 Data Length 1*/
    DMA1_Channel4->CNDTR |= (1U << 0);                    // Dma Channel4 Data Length 1*/

    DAC->CR |= (1U << 12);                                // Dac1 Channel1 Dma Enabled
    DAC->CR |= (1U << 28);                                // Dac1 Channel2 Dma Enabled

    DMA1_Channel3->CCR |= (1U << 0);                      // Dma Channel3 Enabled*/
    DMA1_Channel4->CCR |= (1U << 0);                      // Dma Channel4 Enabled*/

    TIM6->PSC = 0;                                        // Timer6 Prescaler 0 (For 1mhz Timer At 56mhz Sysclk)
    TIM6->ARR = 55;                                       // Timer6 Autoreload 55 (For 1mhz Timer At 56mhz Sysclk)
    TIM6->CR1 &= ~(1U << 7);                              // Timer6 Autoreload Buffer Disabled
    TIM6->CR2 |=  (2U << 4);                              // Timer6 Trigger Output Enabled
    TIM6->CR1 &= ~(1U << 1);                              // Timer6 Enable Update Event
    TIM6->CR1 |=  (1U << 0);                              // Timer6 Enable Counter

    DAC->CR |= (1U << 0);                                 // Dac1 Channel1 Enabled
    DAC->CR |= (1U << 16);                                // Dac1 Channel2 Enabled
}
