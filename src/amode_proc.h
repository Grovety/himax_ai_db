/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef AMODE_PROC_H
#define AMODE_PROC_H

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <nrfx_timer.h>

#define AMODE_MAX_RCGN_DUMMY_ITER 10
#define AMODE_MAX_RCGN_FOUND_ITER 3
#define AMODE_RECGN_TOUT_MSEC 5000

#define AUTO_MODE_NRF_SYS_PWR_OFF
#define AUTO_MODE_TIMER_ASLEEP_PERIOD_SEC 20
#define AUTO_MODE_TIMER_PWROFF_PERIOD_SEC 20

int amode_proc_init();

void amode_timer_cmd_recv_notify();

void amode_timer_wakeup_notify();

void amode_recognize_results_update(bool found, bool permission);

void amode_do_recognize();

void amode_setup_for_image_read(bool start_or_finish);

#endif // AMODE_PROC_H

