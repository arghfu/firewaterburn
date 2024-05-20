//
// Created by BelzS on 13.09.2023.
//

#ifndef FIREWATERBURN_ADC_PROBE_H
#define FIREWATERBURN_ADC_PROBE_H

#define ADC_PROBE_COUNT 6

enum adc_probe_status
{
    DISCONNECTED = 0,
    CONNECTED
};

struct adc_probe_config
{
    double coef[3];
    struct circuit
    {
        double Rv;
        double Rp;
    } configuration;
};

struct adc_probe
{
    uint8_t channel;
    enum adc_probe_status status;
    struct adc_probe_config probe_config;
    struct adc_probe_values
    {
        int16_t raw;
        double resistance;
        double temperature;
    } value ;
};

int adc_probe_init(struct adc_probe *probes);
int adc_probe_read_all(struct adc_probe *probes);
int adc_probe_read_channel(struct adc_probe *probes, uint8_t channel);
int adc_probe_get_value(struct adc_probe *probes, double *values);
#endif //FIREWATERBURN_ADC_PROBE_H
