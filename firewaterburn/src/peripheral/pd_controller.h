#ifndef FIREWATERBURN_PD_CONTROLLER_H
#define FIREWATERBURN_PD_CONTROLLER_H

#include <stdint.h>
#include <zephyr/drivers/gpio.h>
#include "pd_controller_register.h"

#ifdef __cplusplus
extern "C" {
#endif

struct stusb_pd_controller
{
    stusb_pd_snk pdo[3];
    stusb_cc_status_reg cc_status;
    stusb_rdo_status_reg rdo_status;
    stusb_alert_status_reg status_reg;
    stusb_alert_status_mask_reg status_mask;
    struct gpio_dt_spec pd_alert;
    const struct device *i2c_device;
};

int pd_controller_init();
int pd_controller_soft_reset();
int pd_controller_read_pdo_snk();
int pd_controller_write_pdo_snk();
int pd_controller_set_pdo_number(uint8_t number);
int pd_controller_pdo_set(uint8_t pdo_number, float voltage, float current);
int pd_controller_pdo_set_current(uint8_t pdo_number, float current);
int pd_controller_pdo_set_voltage(uint8_t pdo_number, float voltage);

#ifdef __cplusplus
}
#endif

#endif //FIREWATERBURN_PD_CONTROLLER_H
