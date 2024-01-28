//
// Created by BelzS on 01.04.2023.
//

#ifndef FIREWATERBURN_ADC_CONTROLLER_H
#define FIREWATERBURN_ADC_CONTROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "adc_probe.h"

int adc_controller_init();
int adc_controller_read_channel(uint8_t channel, int16_t *raw_value);
int adc_controller_convert_milli_volt(uint8_t channel, const int16_t *raw_value, int32_t *milli_volts);
uint16_t adc_controller_get_reference(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif //FIREWATERBURN_ADC_CONTROLLER_H
