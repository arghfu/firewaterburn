/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */


#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <soc.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/types.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/i2c.h>


#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

#define STUSB_I2C_ADDR 0x28

#define DEVICE_NAME             CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN         (sizeof(DEVICE_NAME) - 1)

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);



#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
        DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels, DT_SPEC_AND_COMMA)
};

static int write_bytes(const struct device *i2c_dev, uint16_t addr,
                       uint8_t *data, uint32_t num_bytes)
{
    uint8_t wr_addr[2];
    struct i2c_msg msgs[2];

    /* FRAM address */
    wr_addr[0] = (addr >> 8) & 0xFF;
    wr_addr[1] = addr & 0xFF;

    /* Setup I2C messages */

    /* Send the address to write to */
    msgs[0].buf = wr_addr;
    msgs[0].len = 2U;
    msgs[0].flags = I2C_MSG_WRITE;

    /* Data to be written, and STOP after this. */
    msgs[1].buf = data;
    msgs[1].len = num_bytes;
    msgs[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

    return i2c_transfer(i2c_dev, &msgs[0], 2, STUSB_I2C_ADDR);
}

//static int read_bytes(const struct device *i2c_dev, uint16_t addr,
//                      uint8_t *data, uint32_t num_bytes)
//{
//    uint8_t wr_addr[2];
//    struct i2c_msg msgs[2];
//
//
//    wr_addr[0] = (addr >> 8) & 0xFF;
//    wr_addr[1] = addr & 0xFF;
//
//
//    msgs[0].buf = wr_addr;
//    msgs[0].len = 2U;
//    msgs[0].flags = I2C_MSG_WRITE;
//
//    /* Read from device. STOP after this. */
//    msgs[1].buf = data;
//    msgs[1].len = num_bytes;
//    msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;
//
//    return i2c_transfer(i2c_dev, &msgs[0], 2, STUSB_I2C_ADDR);
//}

void main(void)
{
    printk("Hello World! %s\n", CONFIG_BOARD);

    const struct device *const i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
    uint8_t data[16];
    data[0] = 0xAE;

    if (!device_is_ready(i2c_dev)) {
        printk("I2C: Device is not ready.\n");
        return;
    }


    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);

    int err;
    int16_t buf;
    struct adc_sequence sequence = {
            .buffer = &buf,
            /* buffer size in bytes, not number of samples */
            .buffer_size = sizeof(buf),
    };

    /* Configure channels individually prior to sampling. */
    for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
        if (!device_is_ready(adc_channels[i].dev)) {
            printk("ADC controller device not ready\n");
            return;
        }

        err = adc_channel_setup_dt(&adc_channels[i]);
        if (err < 0) {
            printk("Could not setup channel #%d (%d)\n", i, err);
            return;
        }
    }


    while (1) {
        gpio_pin_toggle_dt(&led0);
        gpio_pin_toggle_dt(&led1);
        gpio_pin_toggle_dt(&led2);

        write_bytes(i2c_dev, 0x00, &data[0], 1);

        printk("ADC reading:\n");
        for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
            int32_t val_mv;

            printk("- %s, channel %d: ",
                   adc_channels[i].dev->name,
                   adc_channels[i].channel_id);

            (void)adc_sequence_init_dt(&adc_channels[i], &sequence);

            err = adc_read(adc_channels[i].dev, &sequence);
            if (err < 0) {
                printk("Could not read (%d)\n", err);
                continue;
            } else {
                printk("%"PRId16, buf);
            }

            /* conversion to mV may not be supported, skip if not */
            val_mv = buf;
            err = adc_raw_to_millivolts_dt(&adc_channels[i],
                                           &val_mv);
            if (err < 0) {
                printk(" (value in mV not available)\n");
            } else {
                printk(" = %"PRId32" mV\n", val_mv);
            }
        }

        k_msleep(SLEEP_TIME_MS);
    }
}