/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "himax_control.h"

// #define SW2_BUTTON_USED

#ifdef SW2_BUTTON_USED
    #if HIMAX_INIT_MODE == HIMAX_MODE_POWER_DOWN || \
        HIMAX_POFF_MODE == HIMAX_MODE_POWER_DOWN || \
        HIMAX_INIT_MODE == HIMAX_MODE_DPOWER_DOWN || \
        HIMAX_POFF_MODE == HIMAX_MODE_DPOWER_DOWN
            #error The button wire is shared with Himax wake-up pin!
    #endif

typedef void (*button_event_handler_t)(void);

int button_sw2_init(button_event_handler_t handler);

#endif // SW2_BUTTON_USED

#endif // BUTTON_H