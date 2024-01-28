#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "adc_controller.h"

LOG_MODULE_REGISTER(ADC_CTRL, CONFIG_LOG_DEFAULT_LEVEL);

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),


/* Data of ADC io-channels specified in devicetree. */
static struct adc_dt_spec adc_contoller_channels[] =
{
        DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
                             DT_SPEC_AND_COMMA)
};

int adc_controller_init()
{
    /* Configure channels individually prior to sampling. */
    for (size_t i = 0U; i < ARRAY_SIZE(adc_contoller_channels); i++) {
        if (!device_is_ready(adc_contoller_channels[i].dev)) {
            LOG_INF("ADC controller device not ready");
            return -EBUSY;
        }

        enum adc_reference reference = adc_contoller_channels[i].channel_cfg.reference;

        switch (reference)
        {
            case ADC_REF_VDD_1:
                adc_contoller_channels[i].vref_mv = 3292;
                break;
            case ADC_REF_VDD_1_2:
                adc_contoller_channels[i].vref_mv = 3292 / 2;
                break;
            case ADC_REF_VDD_1_3:
                adc_contoller_channels[i].vref_mv = 3292 / 3;
                break;
            case ADC_REF_VDD_1_4:
                adc_contoller_channels[i].vref_mv = 3292 / 4;
                break;
            case ADC_REF_INTERNAL:
            case ADC_REF_EXTERNAL0:
            case ADC_REF_EXTERNAL1:
                break;
        }

        int err = adc_channel_setup_dt(&adc_contoller_channels[i]);
        if (err < 0) {
            LOG_INF("Could not setup channel #%d (%d)", i, err);
            return -ENXIO;
        }
    }

    return 0;
}

int adc_controller_read_channel(uint8_t channel, int16_t *raw_value)
{
    struct adc_sequence sequence = {
            .buffer = raw_value,
            /* buffer size in bytes, not number of samples */
            .buffer_size = sizeof(*raw_value),
    };

    (void)adc_sequence_init_dt(&adc_contoller_channels[channel], &sequence);

    int err = adc_read(adc_contoller_channels[channel].dev, &sequence);
    if (err < 0) {
        LOG_INF("Could not read (%d)", err);
    } else {
        LOG_INF("Raw values: %"PRId16, *raw_value);
    }

    return 0;
}

int adc_controller_convert_milli_volt(uint8_t channel, const int16_t *raw_value, int32_t *milli_volts)
{
    int err;

    *milli_volts = *raw_value;
    /* conversion to mV may not be supported, skip if not */
    err = adc_raw_to_millivolts_dt(&adc_contoller_channels[channel],
                                   milli_volts);
    if (err < 0) {
        LOG_INF(" (value in mV not available)");
    } else {
        LOG_INF("value in mV: %"PRId32"", *milli_volts);
    }

    return err;
}

uint16_t adc_controller_get_reference(uint8_t channel)
{
    enum adc_reference reference = adc_contoller_channels[channel].channel_cfg.reference;

    uint16_t factor = 0;
    switch (reference)
    {
        case ADC_REF_VDD_1:
            factor = 1;
            break;
        case ADC_REF_VDD_1_2:
            factor = 2;
            break;
        case ADC_REF_VDD_1_3:
            factor = 3;
            break;
        case ADC_REF_VDD_1_4:
            factor = 4;
            break;
        case ADC_REF_INTERNAL:
        case ADC_REF_EXTERNAL0:
        case ADC_REF_EXTERNAL1:
            factor = -1;
            break;
    }
    return adc_contoller_channels[channel].vref_mv * factor;
}

