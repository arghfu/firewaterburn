#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

#include "peripheral/pd_controller.h"
#include "peripheral/adc_controller.h"

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000


//static const struct pwm_dt_spec pwr_fan = PWM_DT_SPEC_GET(DT_ALIAS(fan));

void main(void)
{
    printk("Hello World! %s\n", CONFIG_BOARD);

    pd_controller_init();
    adc_controller_init();

    pd_controller_read_pdo_snk();
    pd_controller_pdo_set(1, 5.0f, 1.5f);
    pd_controller_pdo_set(2, 9.0f, 1.5f);
    pd_controller_pdo_set(3, 12.0f, 1.5f);
    pd_controller_write_pdo_snk();

    pd_controller_set_pdo_number(3);
    pd_controller_soft_reset();

//    if (!device_is_ready(pwr_fan.dev)) {
//        printk("Error: PWM device %s is not ready\n",
//               pwr_fan.dev->name);
//        return;
//    }
//
//    int ret = pwm_set_dt(&pwr_fan, pwr_fan.period, pwr_fan.period / 2U);
//    if (ret) {
//        printk("Error %d: failed to set pulse width\n", ret);
//        return;
//    }    if (!device_is_ready(pwr_fan.dev)) {
//        printk("Error: PWM device %s is not ready\n",
//               pwr_fan.dev->name);
//        return;
//    }

    while (1)
    {
        adc_controller_read();
        k_msleep(SLEEP_TIME_MS);
    }
}