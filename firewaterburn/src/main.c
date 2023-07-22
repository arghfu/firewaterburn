//#include <zephyr/sys/printk.h>
//#include <zephyr/kernel.h>
//#include <zephyr/drivers/pwm.h>
//
//#include "peripheral/pd_controller.h"
//#include "peripheral/adc_controller.h"
//
///* 1000 msec = 1 sec */
//#define SLEEP_TIME_MS   1000
//
//
////static const struct pwm_dt_spec pwr_fan = PWM_DT_SPEC_GET(DT_ALIAS(fan));
//
//void main(void)
//{
//    printk("Hello World! %s\n", CONFIG_BOARD);
//
//    pd_controller_init();
//    adc_controller_init();
//
//    pd_controller_read_pdo_snk();
//    pd_controller_pdo_set(1, 5.0f, 1.5f);
//    pd_controller_pdo_set(2, 9.0f, 1.5f);
//    pd_controller_pdo_set(3, 12.0f, 1.5f);
//    pd_controller_write_pdo_snk();
//
//    pd_controller_set_pdo_number(3);
//    pd_controller_soft_reset();
//
////    if (!device_is_ready(pwr_fan.dev)) {
////        printk("Error: PWM device %s is not ready\n",
////               pwr_fan.dev->name);
////        return;
////    }
////
////    int ret = pwm_set_dt(&pwr_fan, pwr_fan.period, pwr_fan.period / 2U);
////    if (ret) {
////        printk("Error %d: failed to set pulse width\n", ret);
////        return;
////    }    if (!device_is_ready(pwr_fan.dev)) {
////        printk("Error: PWM device %s is not ready\n",
////               pwr_fan.dev->name);
////        return;
////    }
//
//    while (1)
//    {
//        adc_controller_read();
//        k_msleep(SLEEP_TIME_MS);
//    }
//}


/*
 * Copyright (c) 2022 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 * @brief WiFi scan sample
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/display/cfb.h>
#include <stdio.h>

int main(void)
{
    const struct device *dev;
    uint16_t rows;
    uint8_t ppt;
    uint8_t font_width;
    uint8_t font_height;

    dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(dev)) {
        printf("Device %s not ready\n", dev->name);
        return 0;
    }

    if (display_set_pixel_format(dev, PIXEL_FORMAT_MONO10) != 0) {
        printf("Failed to set required pixel format\n");
        return 0;
    }

    printf("Initialized %s\n", dev->name);

    if (cfb_framebuffer_init(dev)) {
        printf("Framebuffer initialization failed!\n");
        return 0;
    }

    cfb_framebuffer_clear(dev, true);

    display_blanking_off(dev);

    rows = cfb_get_display_parameter(dev, CFB_DISPLAY_ROWS);
    ppt = cfb_get_display_parameter(dev, CFB_DISPLAY_PPT);

    for (int idx = 0; idx < 42; idx++) {
        if (cfb_get_font_size(dev, idx, &font_width, &font_height)) {
            break;
        }
        cfb_framebuffer_set_font(dev, idx);
        printf("font width %d, font height %d\n",
               font_width, font_height);
    }

    printf("x_res %d, y_res %d, ppt %d, rows %d, cols %d\n",
           cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH),
           cfb_get_display_parameter(dev, CFB_DISPLAY_HEIGH),
           ppt,
           rows,
           cfb_get_display_parameter(dev, CFB_DISPLAY_COLS));

    while (1)
    {
            cfb_framebuffer_clear(dev, false);

            cfb_print(dev, "123°!\"123°!",0, 0);
            cfb_framebuffer_finalize(dev);

            k_msleep(100);
    }
    return 0;
}
