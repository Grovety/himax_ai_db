/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <stdio.h>

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

#include "mutex_wrapper.h"
#include "error_handler.h"

#define LOG_MODULE_NAME error_handler
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

K_MUTEX_DEF(error_stack_mutex)

static error_stack_t error_stack;

#define IDX_MASK ((1<<ERR_STACK_BIT_SHIFT)-1)
#define CMP_MASK ((1<<(ERR_STACK_BIT_SHIFT+1))-1)
#define ERROR_STACK_INDEX(IDX) ((IDX) & IDX_MASK)
#define ERROR_STACK_COMP(IDX) ((IDX) & CMP_MASK)
#define ERROR_STACK_EMPTY (ERROR_STACK_COMP(error_stack.widx) == ERROR_STACK_COMP(error_stack.ridx))
#define ERROR_STACK_FULL (ERROR_STACK_COMP(error_stack.widx) == (ERROR_STACK_COMP(error_stack.ridx) ^ (1<<ERR_STACK_BIT_SHIFT)))

void error_stack_init()
{
	K_MUTEX_INIT(error_stack_mutex)
	memset(&error_stack, 0, sizeof(error_stack_t));
	//!!! for (int i = -1; i > -9; i--) error_stack_add(i);
}

bool error_stack_add(int8_t code)
{
	bool ret = true;
	K_MUTEX_LOCK(error_stack_mutex)
	if (ERROR_STACK_FULL) {
		ret = false;
		goto exit;
	}
	unsigned idx = ERROR_STACK_INDEX(error_stack.widx - 1);
	if (error_stack.code[idx] == code) {
		ret = false;
		goto exit;
	}
	idx = ERROR_STACK_INDEX(error_stack.widx);
	error_stack.code[idx] = code;
	error_stack.widx = ERROR_STACK_COMP(error_stack.widx + 1);
exit:
	K_MUTEX_UNLOCK(error_stack_mutex)
	return ret;
}

int8_t error_stack_get()
{
	int ret = 0;
	K_MUTEX_LOCK(error_stack_mutex)
	if (ERROR_STACK_EMPTY)
	{
		goto exit;
	}
	ret = error_stack.code[ERROR_STACK_INDEX(error_stack.ridx)];
	error_stack.code[ERROR_STACK_INDEX(error_stack.ridx)] = 0;
	error_stack.ridx = ERROR_STACK_COMP(error_stack.ridx + 1);
exit:
	K_MUTEX_UNLOCK(error_stack_mutex)
	return ret;
}

void error_stack_print()
{
	K_MUTEX_LOCK(error_stack_mutex)
	for (unsigned i = 0; i < MAX_ERR_CODE_NUM; i++)
	{
		LOG_INF("%d,", error_stack.code[i]);
	}
	LOG_INF("\n");
	K_MUTEX_UNLOCK(error_stack_mutex)
}
