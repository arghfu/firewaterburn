#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>

#include "adc_controller.h"

LOG_MODULE_REGISTER(ADC, CONFIG_LOG_DEFAULT_LEVEL);

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static struct adc_dt_spec adc_channels[] = {
        DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
                             DT_SPEC_AND_COMMA)
};

int adc_controller_init()
{
    /* Configure channels individually prior to sampling. */
    for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
        if (!device_is_ready(adc_channels[i].dev)) {
            LOG_INF("ADC controller device not ready");
            return -EBUSY;
        }

        int err = adc_channel_setup_dt(&adc_channels[i]);
        if (err < 0) {
            LOG_INF("Could not setup channel #%d (%d)", i, err);
            return -ENXIO;
        }
    }

    return 0;
}

int adc_controller_read()
{
    int16_t buf;

    struct adc_sequence sequence = {
            .buffer = &buf,
            /* buffer size in bytes, not number of samples */
            .buffer_size = sizeof(buf),
    };

    printk("ADC reading:\n");
    for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
        int32_t val_mv;

        if(adc_channels[i].channel_cfg.reference != ADC_REF_INTERNAL)
        {
            adc_channels[i].vref_mv = 3292 / 4;
        }

        printk("- %s, channel %d: ",
               adc_channels[i].dev->name,
               adc_channels[i].channel_id);

        (void)adc_sequence_init_dt(&adc_channels[i], &sequence);

        int err = adc_read(adc_channels[i].dev, &sequence);
        if (err < 0) {
            LOG_INF("Could not read (%d)", err);
            continue;
        } else {
            LOG_INF("%"PRId16, buf);
        }

        /* conversion to mV may not be supported, skip if not */
        val_mv = buf;
        err = adc_raw_to_millivolts_dt(&adc_channels[i],
                                       &val_mv);
        if (err < 0) {
            LOG_INF(" (value in mV not available)");
        } else {
            LOG_INF(" = %"PRId32" mV", val_mv);
        }
    }
    return 0;
}

