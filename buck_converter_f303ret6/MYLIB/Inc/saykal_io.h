/* saykal_io.h */
#ifndef SAYKAL_IO_H
#define SAYKAL_IO_H

#include <stdint.h>
#include <stdbool.h>
#include "stm32f303xe.h"

// Giriş yapısı (CAN adres pini ve servis enable pinleri)
typedef struct {
    bool a_canbus_address_b[5];
    bool a_service_enable_b[3];
} s_inputs_t;

// Çıkış yapısı (LED kontrolü)
typedef struct {
    bool fault_led_b;
    bool status_led_b;
} s_outputs_t;

// Global değişkenler
extern s_inputs_t  s_inputs;
extern s_outputs_t s_outputs;

// IO kontrol fonksiyonları
void saykal_io_monitoring(void);
void saykal_io_set_fault_led(bool value);
void saykal_io_set_status_led(bool value);
void saykal_io_toggle_status_led(uint32_t toggle_period);

#endif /* SAYKAL_IO_H */
