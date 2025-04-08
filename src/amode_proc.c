/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "amode_proc.h"
#include "himax_control.h"
#include "tof_sensor_core.h"
#include "leds_ctrl.h"
#include "pwr_ctrl.h"
#include "detect_handler.h"
#include "error_handler.h"
#include "mutex_wrapper.h"

#define LOG_MODULE_NAME amode_proc
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

static void amode_timer_handler(struct k_timer *dummy);
static void amode_timer_work_proc(struct k_work *work);

static K_TIMER_DEFINE(amode_timer, amode_timer_handler, NULL);
static K_WORK_DEFINE(amode_timer_work, amode_timer_work_proc);

#define AMODE_THREAD_STACKSIZE 1024
#define AMODE_THREAD_PRIORITY 7

static void amode_thread_proc();

static K_THREAD_DEFINE(amode_thread_id, AMODE_THREAD_STACKSIZE, amode_thread_proc, NULL, NULL, NULL, AMODE_THREAD_PRIORITY, 0, 0);
static K_EVENT_DEFINE(amode_process_run_event);
static K_EVENT_DEFINE(amode_process_end_event);

K_MUTEX_DEF(amode_setup_mutex)

int amode_proc_init()
{
	K_MUTEX_INIT(amode_setup_mutex)
	return 0;
}

bool img_busy;

void amode_setup_for_image_read(bool start_or_finish)
{
	K_MUTEX_LOCK(amode_setup_mutex)
	img_busy = start_or_finish;
    tof_sensor_set_auto_mode(TOF_MODE_MEAS_DISTANCE_TIMER);
    himax_set_mode(HIMAX_MODE_CONT_WORK, start_or_finish ? HIMAX_ADV_READ_IMAGE : HIMAX_ADV_STOP_RDIMG);
	K_MUTEX_UNLOCK(amode_setup_mutex)
}

static void amode_setup_for_recognition()
{
	K_MUTEX_LOCK(amode_setup_mutex)
	if (!img_busy) { // do recognition and read image at the same time - read operation has priority
		tof_sensor_set_auto_mode(TOF_MODE_DISABLED_WHILE_RECOGN);
		himax_set_mode(HIMAX_MODE_CONT_WORK, HIMAX_ADV_DO_NOTHING);
	}
	K_MUTEX_UNLOCK(amode_setup_mutex)
}

static void amode_setup_for_is_target_waiting()
{ // procedure is called only when timer expired,it is protected by mutex inside the upper function
	himax_set_mode(HIMAX_POFF_MODE, HIMAX_ADV_DO_NOTHING);
	tof_sensor_set_auto_mode(TOF_MODE_AUTO_WAIT_FOR_OBJECTS);
}

static unsigned asleep_cntr;

static void amode_setup_for_not_target_waiting()
{ // waiting for car will leave,once again image read operartion has priority
	K_MUTEX_LOCK(amode_setup_mutex)
	if (!img_busy) { //
		himax_set_mode(HIMAX_POFF_MODE, HIMAX_ADV_DO_NOTHING);
		if (tof_sensor_get_mode() == TOF_MODE_DISABLED_WHILE_RECOGN) {
			tof_sensor_set_auto_mode(TOF_MODE_WAIT_UNTIL_OBJ_LEAVES);
		}
	}
	K_MUTEX_UNLOCK(amode_setup_mutex)
}

void amode_timer_cmd_recv_notify()
{
	K_MUTEX_LOCK(amode_setup_mutex)
	asleep_cntr = AUTO_MODE_TIMER_ASLEEP_PERIOD_SEC;
	k_timer_start(&amode_timer, K_MSEC(1000), K_MSEC(1000));
	K_MUTEX_UNLOCK(amode_setup_mutex)
}

void amode_timer_wakeup_notify()
{ // the same actions
	amode_timer_cmd_recv_notify();
}

static void amode_timer_handler(struct k_timer *dummy)
{
	k_work_submit(&amode_timer_work);
}

static void amode_timer_work_proc(struct k_work *work)
{
	K_MUTEX_LOCK(amode_setup_mutex)
	if (asleep_cntr == 1) {
		// LOG_INF("!!!asleep_cntr %d", asleep_cntr);
		if (!img_busy) {
			amode_setup_for_is_target_waiting();
		}
		else {
			asleep_cntr = AUTO_MODE_TIMER_ASLEEP_PERIOD_SEC;
		}
	}
	if (asleep_cntr > 0) {
		
		asleep_cntr -= 1;
	}
	//> LOG_INF("asleep_cntr %d,pwroff_cntr %d", asleep_cntr, pwroff_cntr);
	if (asleep_cntr == 0) {
		k_timer_stop(&amode_timer);
	}
	K_MUTEX_UNLOCK(amode_setup_mutex)
}

void amode_do_recognize()
{
    k_event_set(&amode_process_run_event, 1);
}

static atomic_t recgn_dummy_iter = ATOMIC_INIT(AMODE_MAX_RCGN_DUMMY_ITER);
static atomic_t recgn_found_iter = ATOMIC_INIT(0);

void amode_recognize_results_update(bool found, bool permission)
{
    if (atomic_get(&recgn_dummy_iter) < AMODE_MAX_RCGN_DUMMY_ITER)
    {
        atomic_inc(&recgn_dummy_iter);

        if (permission) {
            atomic_set(&recgn_dummy_iter, AMODE_MAX_RCGN_DUMMY_ITER);
			k_event_set(&amode_process_end_event, 1);
            detect_handler();
        }
        else {
            if (found) {
                if (atomic_get(&recgn_found_iter) < AMODE_MAX_RCGN_FOUND_ITER) {
                    atomic_inc(&recgn_found_iter);
                }
                else {
                    atomic_set(&recgn_dummy_iter, AMODE_MAX_RCGN_DUMMY_ITER);
					k_event_set(&amode_process_end_event, 2);
                }
            }
        }
    }
	if (atomic_get(&recgn_dummy_iter) >= AMODE_MAX_RCGN_DUMMY_ITER) {
		k_event_set(&amode_process_end_event, 4);
	}
	//if (k_event_test(&amode_process_end_event, 7)) {
    //	LOG_INF("(%d,%d): %ld,%ld", found, permission, atomic_get(&recgn_dummy_iter), atomic_get(&recgn_found_iter));
	//}
}

static void gbox_rcgn_proc()
{
	atomic_set(&recgn_found_iter, 0);
	atomic_set(&recgn_dummy_iter, 0);
	amode_setup_for_recognition();

	if (k_event_wait(&amode_process_end_event, 7, true, K_MSEC(AMODE_RECGN_TOUT_MSEC)) == false) {
		error_stack_add(ERR_RECOGN_TOUT);
		LOG_ERR("Recognition timeout");
	}
	amode_setup_for_not_target_waiting();
}

static void amode_thread_proc()
{
    while (1)
    {
        uint32_t event = k_event_wait(&amode_process_run_event, 7, false, K_FOREVER);
		if (event & 1) { // recognition
			gbox_rcgn_proc();
			k_event_clear(&amode_process_run_event, 1);
		}
	}
}
