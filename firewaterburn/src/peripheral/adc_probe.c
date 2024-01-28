//
// Created by BelzS on 13.09.2023.
//

#include <math.h>
#include <zephyr/logging/log.h>
#include "adc_probe.h"
#include "adc_controller.h"

LOG_MODULE_REGISTER(ADC_PROBE, CONFIG_LOG_DEFAULT_LEVEL);

static void convert_value(struct adc_probe *probe);
static double calc_probe_resistance(struct adc_probe *probe);
static double filter(double old_value, double new_value, double weight);

int adc_probe_init(struct adc_probe *probes)
{
    for (int i = 0; i < ADC_PROBE_COUNT; ++i)
    {
        probes[i].channel = i;
        probes[i].probe_config.coef[0] = 0.000697978647644538;
        probes[i].probe_config.coef[1] = 0.00024341037655289377;
        probes[i].probe_config.coef[2] = 2.2801562225985592e-08;
        probes[i].probe_config.configuration.Rp = 3400;
        probes[i].probe_config.configuration.Rv = 4420;

        probes[i].value.raw = 0;
        probes[i].value.resistance = 0;
        probes[i].value.temperature = 0;
        probes[i].status = CONNECTED;
    }

    return adc_controller_init();
}

int adc_probe_read_channel(struct adc_probe *probes, uint8_t channel)
{
    adc_controller_read_channel(probes[channel].channel,
                                &probes[channel].value.raw);

    double old_value = probes[channel].value.resistance;
    probes[channel].value.resistance = calc_probe_resistance(&probes[channel]);

    probes[channel].value.resistance = filter(
            old_value,
            probes[channel].value.resistance,
            0.2);

    convert_value(&probes[channel]);

    return 0;
}

int adc_probe_read_all(struct adc_probe *probes)
{
    for (int i = 0; i < ADC_PROBE_COUNT; ++i)
    {
        adc_probe_read_channel(probes, i);
    }

    return 0;
}

int adc_probe_get_value(struct adc_probe *probes, double *values)
{
    for (int i = 0; i < ADC_PROBE_COUNT; ++i)
    {
        values[i] = probes[i].value.temperature;
    }
    return 0;
}


void convert_value(struct adc_probe *probe)
{
    double probe_resistance = probe->value.resistance;

    double a0 = probe->probe_config.coef[0];
    double a1 = probe->probe_config.coef[1];
    double a3 = probe->probe_config.coef[2];

    probe->value.temperature = 1 / (a0
            + a1 * log(probe_resistance)
            + a3 * log(probe_resistance)
                 * log(probe_resistance)
                 * log(probe_resistance)) - 273.15;

    LOG_INF("Channel %d temperature: %.2f °C", probe->channel, probe->value.temperature);
}

double calc_probe_resistance(struct adc_probe *probe)
{
    int32_t milli_volts;
    uint16_t ref_voltage = adc_controller_get_reference(probe->channel);
    adc_controller_convert_milli_volt(probe->channel, &probe->value.raw, &milli_volts);

    double Rp = probe->probe_config.configuration.Rv / (ref_voltage - milli_volts) * milli_volts;
    double Rt = (probe->probe_config.configuration.Rp * Rp)/(probe->probe_config.configuration.Rp - Rp);

    LOG_DBG("Probe resistance: %f ohm", Rt);
    return Rt;
}

double filter(double old_value, double new_value, double weight)
{
    return weight * new_value + (1 - weight) * old_value;
}
