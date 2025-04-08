/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <stdio.h>

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/led_strip.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>

#include "himax_spi.h"
#include "himax_control.h"
#include "leds_ctrl.h"
#include "mutex_wrapper.h"

#define LOG_MODULE_NAME himax_control
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define HIMAX_CONTROL DT_PATH(zephyr_user)
static const struct gpio_dt_spec himax_wakeup_pin = GPIO_DT_SPEC_GET_BY_IDX(HIMAX_CONTROL, himax_power_gpios, 0);
static const struct gpio_dt_spec himax_pwron_pin = GPIO_DT_SPEC_GET_BY_IDX(HIMAX_CONTROL, himax_power_gpios, 2);

static void himax_wakeup()
{
    gpio_pin_set_dt(&himax_wakeup_pin, 1);
    k_sleep(K_MSEC(HIMAX_WAKEUP_TIME_MS));
    gpio_pin_set_dt(&himax_wakeup_pin, 0);
}

static void himax_pwrctl(bool on)
{
    gpio_pin_set_dt(&himax_pwron_pin, on);
    k_sleep(K_MSEC(HIMAX_PCTL_DELAY_MS));
}

K_MUTEX_DEF(himax_ctrl_mutext)

static himax_next_mode_t cur_mode;

int himax_ctrl_init()
{
    K_MUTEX_INIT(himax_ctrl_mutext)
    gpio_pin_configure_dt(&himax_wakeup_pin, GPIO_OUTPUT | GPIO_OPEN_DRAIN);
	gpio_pin_set_dt(&himax_wakeup_pin, 0);
    gpio_pin_configure_dt(&himax_pwron_pin, GPIO_OUTPUT | GPIO_OUTPUT_INIT_LOW);
    k_sleep(K_MSEC(100));
    himax_pwrctl(true);
    cur_mode = HIMAX_MODE_CONT_WORK;
    himax_set_mode(HIMAX_INIT_MODE, HIMAX_ADV_DO_NOTHING);
    return 0;
}

himax_next_mode_t himax_get_mode()
{
    himax_next_mode_t ret;
    K_MUTEX_LOCK(himax_ctrl_mutext)
    ret = cur_mode;
    K_MUTEX_UNLOCK(himax_ctrl_mutext)
    return ret;
}

static uint8_t adv_ctl_code(himax_adv_action_t adv_act)
{
    uint8_t ret = 0;
    if (adv_act == HIMAX_ADV_READ_IMAGE) {
        ret = HIMAX_CTL_READ_IMAGE;
    } else if (adv_act == HIMAX_ADV_STOP_RDIMG) {
        ret = HIMAX_CTL_RDIMG_CMPL;
    } else if (adv_act == HIMAX_ADV_RCGN_IMIT_ON) {
        ret = HIMAX_CTL_IMIT_ON;
    } else if (adv_act == HIMAX_ADV_RCGN_IMIT_OFF) {
        ret = HIMAX_CTL_IMIT_OFF;
    }
    return ret;
}

bool himax_set_mode(himax_next_mode_t new_mode, himax_adv_action_t adv_action)
{
    bool ret = false;
    K_MUTEX_LOCK(himax_ctrl_mutext)
    if (new_mode == HIMAX_MODE_CONT_WORK) {
        himax_spis_set_ctrl(HIMAX_CTL_CONT_WORK | adv_ctl_code(adv_action));
        if (cur_mode == HIMAX_MODE_POWER_OFF) {
            himax_pwrctl(true);
        }
        else {
            himax_wakeup();
        }
        cur_mode = HIMAX_MODE_CONT_WORK;
        ret = true;
    }
    else if (new_mode == HIMAX_MODE_POWER_DOWN) {
        if (cur_mode == HIMAX_MODE_CONT_WORK) {
            himax_spis_set_ctrl(HIMAX_CTL_PWR_DOWN);
            cur_mode = HIMAX_MODE_POWER_DOWN;
            ret = true;
        }
    }
    else if (new_mode == HIMAX_MODE_DPOWER_DOWN) {
        if (cur_mode == HIMAX_MODE_CONT_WORK) {
            himax_spis_set_ctrl(HIMAX_CTL_DPWR_DOWN);
            cur_mode = HIMAX_MODE_DPOWER_DOWN;
            ret = true;
        }
    }
    else if (new_mode == HIMAX_MODE_POWER_OFF) {
        if (cur_mode == HIMAX_MODE_CONT_WORK) {
            himax_pwrctl(false);
            cur_mode = HIMAX_MODE_POWER_OFF;
            ret = true;
        }
    }
    led_red_ctrl(cur_mode == HIMAX_MODE_CONT_WORK ? LED_ON : LED_OFF);
    K_MUTEX_UNLOCK(himax_ctrl_mutext)
    return ret;
}
