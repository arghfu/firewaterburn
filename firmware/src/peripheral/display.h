//
// Created by BelzS on 27.08.2023.
//

#ifndef FIREWATERBURN_DISPLAY_H
#define FIREWATERBURN_DISPLAY_H

#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/sys/timeutil.h>

enum wifi_signal_strength
{
    WIFI_SIGNAL_STRENGTH_LOWER = 1,
    WIFI_SIGNAL_STRENGTH_LOW = 2,
    WIFI_SIGNAL_STRENGTH_MEDIUM = 3,
    WIFI_SIGNAL_STRENGTH_HIGH = 4,
    WIFI_SIGNAL_STRENGTH_HIGHER = 5,
    WIFI_SIGNAL_STRENGTH_DISCONNECTED = 6
};

struct thermo_display_layout
{
    uint8_t rows;
    uint8_t columns;
    uint8_t channels;
    uint8_t spacing;
    uint16_t header_height;
};

struct thermo_display
{
    const struct device *dev;
    struct thermo_display_layout layout;
    enum wifi_signal_strength signal_strength;
    struct tm time;
    uint8_t initialized;
};

int thermo_display_init(struct thermo_display *display);
int thermo_display_update(struct thermo_display *display, double *values);

#endif //FIREWATERBURN_DISPLAY_H
