/* saykal_io.c */
#include "saykal_io.h"

// Giriş ve çıkış değişkenlerinin tanımı
s_inputs_t  s_inputs = {
    .a_service_enable_b = {false, false, false},
    .a_canbus_address_b = {false, false, false, false, false},
};

s_outputs_t s_outputs = {
    .fault_led_b = false,
    .status_led_b = false,
};

// Statik sayaç sadece toggle fonksiyonu içinde kullanılır
static void saykal_io_read_inputs(void);
static void saykal_io_write_outputs(void);

void saykal_io_monitoring(void)
{
    saykal_io_read_inputs();
    saykal_io_write_outputs();
}

void saykal_io_set_fault_led(bool value)
{
    s_outputs.fault_led_b = value;
}

void saykal_io_set_status_led(bool value)
{
    s_outputs.status_led_b = value;
}

void saykal_io_toggle_status_led(uint32_t toggle_period)
{
    static uint32_t counter_u32 = 0;
    if ((counter_u32++) > toggle_period)
    {
        counter_u32 = 0;
        s_outputs.status_led_b = !s_outputs.status_led_b;
    }
}

// Giriş pinlerini oku (GPIO'dan)
static void saykal_io_read_inputs(void)
{
    s_inputs.a_service_enable_b[0] = 0;
    s_inputs.a_service_enable_b[1] = 0;
    s_inputs.a_service_enable_b[2] = 0;

    s_inputs.a_canbus_address_b[0] = (bool)((GPIOB->IDR >> 0) & 0x01);  // PB0
    s_inputs.a_canbus_address_b[1] = (bool)((GPIOC->IDR >> 5) & 0x01);  // PC5
    s_inputs.a_canbus_address_b[2] = (bool)((GPIOC->IDR >> 4) & 0x01);  // PC4
    s_inputs.a_canbus_address_b[3] = (bool)((GPIOA->IDR >> 7) & 0x01);  // PA7
    s_inputs.a_canbus_address_b[4] = (bool)((GPIOA->IDR >> 6) & 0x01);  // PA6
}

// Çıkış pinlerini güncelle (LED'ler)
static void saykal_io_write_outputs(void)
{
    if (s_outputs.fault_led_b)
        GPIOC->BSRR = (1U << 7);  // PC7 HIGH
    else
        GPIOC->BRR  = (1U << 7);  // PC7 LOW

    if (s_outputs.status_led_b)
        GPIOC->BSRR = (1U << 6);  // PC6 HIGH
    else
        GPIOC->BRR  = (1U << 6);  // PC6 LOW
}
