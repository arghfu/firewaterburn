#ifndef FIREWATERBURN_PD_CONTROLLER_H
#define FIREWATERBURN_PD_CONTROLLER_H

#include <stdint.h>
#include "pd_controller_register.h"

#ifdef __cplusplus
extern "C" {
#endif

enum PDO_NUMBER
{
    ONE = 1,
    TWO = 2,
    THREE = 3
};

//typedef struct
//{
//    stusb_pd_snk pdo[3];
//    stusb_cc_status_reg cc_status;
//    stusb_rdo_status_reg rdo_status;
//    stusb_alert_status_reg status_reg;
//    stusb_alert_status_mask_reg status_mask;
//    struct gpio_dt_spec pd_alert = GPIO_DT_SPEC_GET_OR(PD_ALERT_NODE, gpios, {0});
//    const struct device *i2c_device;
//} pd_controller;

int pd_controller_init();
int pd_controller_soft_reset();
int pd_controller_read_pdo_snk();
int pd_controller_write_pdo_snk();
int pd_controller_set_pdo_number(uint8_t number);
int pd_controller_set_pdo(uint8_t pdo_number, float voltage, float current);
int pd_controller_print_pdo();
int pd_controller_get_typec_status();
int pd_controller_get_rdo_status();
int pd_controller_print_rdo_status();

#ifdef __cplusplus
}
#endif

#endif //FIREWATERBURN_PD_CONTROLLER_H
