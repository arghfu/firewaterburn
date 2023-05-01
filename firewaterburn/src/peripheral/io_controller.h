//
// Created by BelzS on 03.04.2023.
//

#ifndef FIREWATERBURN_IO_CONTROLLER_H
#define FIREWATERBURN_IO_CONTROLLER_H

/* The devicetree node identifier for the "led" aliases. */
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

const struct gpio_dt_spec PERI_gpio_led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct gpio_dt_spec PERI_gpio_led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
const struct gpio_dt_spec PERI_gpio_led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);

int PERI_gpio_init();
#endif //FIREWATERBURN_IO_CONTROLLER_H
