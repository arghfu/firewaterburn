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
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>

#include "display.h"
#include "adc_probe.h"

void display_init_data(struct thermo_display *display);


int main(void)
{
    struct thermo_display display;
    struct adc_probe probes[ADC_PROBE_COUNT];
    double temperature[ADC_PROBE_COUNT] = { 2.0 , 3.0, 5.0, 6.0, 7.0, 123.0};

    display_init_data(&display);
    thermo_display_init(&display);

    adc_probe_init(probes);

    while (1)
    {
        adc_probe_read_all(probes);
        adc_probe_get_value(probes, temperature);
        thermo_display_update(&display, temperature);

        k_msleep(1000);
    }
}



void display_init_data(struct thermo_display *display)
{
    display->layout.rows = 2;
    display->layout.columns = 3;
    display->layout.channels = 6;
    display->layout.spacing = 10;
    display->layout.header_height = 12;

    display->time.tm_hour = 13;
    display->time.tm_min = 37;

    display->dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    display->signal_strength = WIFI_SIGNAL_STRENGTH_DISCONNECTED;
    display->time.tm_hour = 13;
}

