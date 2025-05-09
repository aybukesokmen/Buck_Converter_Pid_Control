
#include "sensor_converter.h"

float Sensor_ConvertToVoltage(uint16_t adc_val)
{
    float v_adc = ((float)adc_val * ADC_VREF) / ADC_RESOLUTION;
    return v_adc * VOLTAGE_DIVIDER_GAIN;
}

float Sensor_ConvertToCurrent(uint16_t adc_val)
{
    return ((float)adc_val) * CURRENT_CALC_FACTOR;
}
