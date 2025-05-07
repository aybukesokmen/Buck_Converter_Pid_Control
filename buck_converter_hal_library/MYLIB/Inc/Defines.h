/*
 * Defines.h
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */

#ifndef DEFINES_H_
#define DEFINES_H_

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


#endif /* DEFINES_H_ */
