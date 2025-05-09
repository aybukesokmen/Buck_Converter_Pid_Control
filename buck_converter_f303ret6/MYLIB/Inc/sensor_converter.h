/*
 * sensor_converter.h
 *
 *  Created on: May 8, 2025
 *      Author: 90545
 */

#ifndef SENSOR_CONVERTER_H_
#define SENSOR_CONVERTER_H_

#include <stdint.h>
#include "Defines.h"
/* Ham ADC verilerini fiziksel birimlere çevirir */
float Sensor_ConvertToVoltage(uint16_t adc_val);
float Sensor_ConvertToCurrent(uint16_t adc_val);

#endif /* SENSOR_CONVERTER_H_ */
