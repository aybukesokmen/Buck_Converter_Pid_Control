
#ifndef DEFINES_H_
#define DEFINES_H_

#define V1_0 1
#define Version V1_0

//ARR = (56 MHz / (9+1) / 20 kHz) - 1 = 280 - 1 = 279

// === ADC Genel Ayarları ===
#define ADC_RESOLUTION          4095.0f
#define ADC_VREF                3.3f


// === Voltaj Ölçümü ===
// Voltaj bölücü oranı: Vadc = Vout * (R2 / (R1 + R2))
// Örn: 100k / (100k + 10k) → oran = 0.0909
#define VOLTAGE_DIVIDER_GAIN    (11.0f)   // Vadc = Vout / 11 → Vout = Vadc * 11


// === Akım Ölçümü ===
// Iout = Vadc / (Gain * Rshunt)
#define CURRENT_SHUNT_RESISTOR  0.01f     // ohm
#define CURRENT_AMP_GAIN        50.0f
#define CURRENT_CALC_FACTOR     (ADC_VREF / (CURRENT_SHUNT_RESISTOR * CURRENT_AMP_GAIN * ADC_RESOLUTION))

// === 10A Limit için ADC değeri (kaç birim ediyor?)
#define IOUT_10A_ADC_RAW        ((uint16_t)((10.0f * CURRENT_AMP_GAIN * CURRENT_SHUNT_RESISTOR * ADC_RESOLUTION) / ADC_VREF))



typedef enum {
    INIT,
    MODE_EN,
    CONTROL,
    RUN,
    FAULT
} e_state_t;

typedef struct {
    float vout;         // Çıkış voltajı (V)
    float iout;         // Çıkış akımı (A)
    float vin;          // Giriş voltajı (V) - eklendi
    float iin;          // Giriş akımı (A) - eklendi
    float temperature;  // Sıcaklık (°C)
    float pwm_duty;     // PWM görev döngüsü (0–1)
    float vout_target;  // Hedef çıkış voltajı (24V)
    uint8_t overcurrent;// Aşırı akım bayrağı
} SystemState_t;

typedef enum {
    SYS_STATE_IDLE = 0,      // Boşta
    SYS_STATE_RUNNING,      // Çalışıyor
    SYS_STATE_ERROR,        // Genel hata
    SYS_STATE_OVERCURRENT   // Aşırı akım
} SystemCANState_t;

#endif /* DEFINES_H_ */
