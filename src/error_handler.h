/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdint.h>
#include <stdbool.h>

#include "error_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_STACK_BIT_SHIFT 3
#define MAX_ERR_CODE_NUM (1<<ERR_STACK_BIT_SHIFT)
typedef struct {
    int8_t code[MAX_ERR_CODE_NUM];
    int widx;
    int ridx;
} error_stack_t;

void error_stack_init();

bool error_stack_add(int8_t code);

int8_t error_stack_get();

void error_stack_print();

#ifdef __cplusplus
}
#endif

#endif // ERROR_HANDLER_H