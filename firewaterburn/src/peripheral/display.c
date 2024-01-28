//
// Created by BelzS on 27.08.2023.
//

#include "display.h"
#include <zephyr/display/cfb.h>
#include <zephyr/logging/log.h>

#include "cfb_font_fsex302.h"
#include "cfb_font_sig_strength.h"
#include "cfb_font_channel.h"

LOG_MODULE_REGISTER(DISPLAY, CONFIG_LOG_DEFAULT_LEVEL);

#define CFB_FONT_FSEX 0
#define CFB_FONT_SIG_STR 1
#define CFB_FONT_CHA 2

// private functions
static void thermo_display_update_header(struct thermo_display *display);
static void thermo_display_update_channel(struct thermo_display *display, double *values);


// public functions
int thermo_display_init(struct thermo_display *display)
{
    display->initialized = 0;
    if (!device_is_ready(display->dev)) {
        LOG_INF("Device %s not ready\n", display->dev->name);
        return 0;
    }

    if (display_set_pixel_format(display->dev, PIXEL_FORMAT_MONO10) != 0) {
        LOG_INF("Failed to set required pixel format\n");
        return 0;
    }

    printf("Initialized %s\n", display->dev->name);

    if (cfb_framebuffer_init(display->dev)) {
        LOG_INF("Framebuffer initialization failed!\n");
        return 0;
    }
    cfb_framebuffer_invert(display->dev);
    cfb_framebuffer_clear(display->dev, true);

    display_blanking_off(display->dev);

    double values[6] = { 0 };
    thermo_display_update(display, values);
    cfb_framebuffer_finalize(display->dev);

    return 0;
}

int thermo_display_update(struct thermo_display *display, double *values)
{
    thermo_display_update_header(display);
    thermo_display_update_channel(display, values);
    cfb_framebuffer_finalize(display->dev);
    display->initialized = 1;
    return 0;
}

void thermo_display_update_header(struct thermo_display *display)
{
    uint8_t font_width;
    uint8_t font_height;

    char signal_buf[4];
    char clock_buf[6];

    if (display->initialized == 1)
    {
        cfb_invert_area(display->dev, 0, 0,
                        cfb_get_display_parameter(display->dev, CFB_DISPLAY_WIDTH),
                        display->layout.header_height);
    }

    cfb_framebuffer_set_font(display->dev, CFB_FONT_SIG_STR);
    snprintf(signal_buf, sizeof(signal_buf), "%d", (uint8_t)display->signal_strength);
    cfb_print(display->dev, signal_buf, 0, 0);

    cfb_get_font_size(display->dev, CFB_FONT_FSEX, &font_width, &font_height);
    cfb_framebuffer_set_font(display->dev, CFB_FONT_FSEX);

    display_get_framebuffer(display->dev);

    snprintf(clock_buf, sizeof(clock_buf), "%d:%d", display->time.tm_hour, display->time.tm_min);
    cfb_print(display->dev,
              clock_buf,
              cfb_get_display_parameter(display->dev, CFB_DISPLAY_WIDTH) - (5 * font_width),
              -3);

    cfb_invert_area(display->dev, 0, 0,
                    cfb_get_display_parameter(display->dev, CFB_DISPLAY_WIDTH),
                    display->layout.header_height);
}

void thermo_display_update_channel(struct thermo_display *display, double *values)
{
    char buf[32];
    char channel_buf[4];

    uint8_t rows = display->layout.rows;
    uint8_t columns = display->layout.columns;

    uint8_t header_offset = 2;
    uint8_t new_line_offset = 28;

    uint8_t font_heigth;
    uint8_t font_width;

    for (uint8_t row = 0; row < rows; ++row)
    {
        uint8_t channel_offset_y = display->layout.header_height + header_offset + new_line_offset * row;
        uint8_t value_offset_y = channel_offset_y + 9; // 9 is the pixel height of the channel font

        cfb_get_font_size(display->dev, CFB_FONT_CHA, &font_width, &font_heigth);
        uint8_t channel_start_x = display->layout.spacing - 1;
        uint8_t channel_offset_x = (cfb_get_display_parameter(display->dev, CFB_DISPLAY_WIDTH)
                - 2 * display->layout.spacing
                - font_width) / (columns -1);

        uint8_t value_start_x = display->layout.spacing - 1 - (columns - 1);
        uint8_t value_offset_x = channel_offset_x;

        for (uint8_t col = 0; col < columns; ++col)
        {
            uint8_t actual_channel = col + row * columns;

            if(actual_channel >= display->layout.channels)
            {
                LOG_INF("skipping channel %d", actual_channel);
                continue;
            }

            LOG_INF("updating channel %d. value: %.2f", actual_channel, values[actual_channel]);

            cfb_framebuffer_set_font(display->dev, CFB_FONT_CHA);
            snprintf(channel_buf, sizeof(channel_buf), "%d", actual_channel );
            cfb_print(display->dev, channel_buf,
                      channel_start_x + col * channel_offset_x,
                      channel_offset_y);

            cfb_framebuffer_set_font(display->dev, CFB_FONT_FSEX);
            snprintf(buf, sizeof(buf), "%03d", (int)(values[actual_channel]));
            cfb_print(display->dev, buf,
                      value_start_x  + col * value_offset_x,
                      value_offset_y);
        }
    }
}
