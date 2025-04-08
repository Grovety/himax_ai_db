/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/reboot.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include "button.h"
#include "himax_control.h"

#ifdef SW2_BUTTON_USED

LOG_MODULE_REGISTER(button);

#define SW2_BUTTON_CONTROL DT_PATH(zephyr_user)
static const struct gpio_dt_spec sw2_button_pin = GPIO_DT_SPEC_GET(SW2_BUTTON_CONTROL, sw2_button_gpios);
static const struct gpio_dt_spec himax_pwron_pin = GPIO_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user), himax_power_gpios, 2);
static struct gpio_callback button_cb_data;

static button_event_handler_t ext_handler;

static void button_event_callback_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
{
    LOG_INF("button_event_callback_handler");
    if (ext_handler) {
        ext_handler();
    }
    else {
        gpio_pin_set_dt(&himax_pwron_pin, 1);
    }
}

int button_sw2_init(button_event_handler_t handler)
{
    if (!gpio_is_ready_dt(&sw2_button_pin)) {
        LOG_ERR("SW2 strip device is not ready");
		return -1;
	}

    ext_handler = handler;

    gpio_pin_configure_dt(&sw2_button_pin, GPIO_INPUT);
    gpio_pin_interrupt_configure_dt(&sw2_button_pin, GPIO_INT_EDGE_FALLING);
	gpio_init_callback(&button_cb_data, button_event_callback_handler, BIT(sw2_button_pin.pin));
	gpio_add_callback(sw2_button_pin.port, &button_cb_data);
    return 0;
}

#endif // SW2_BUTTON_USED
