/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "error_handler.h"
#include "command_decoder.h"

int read_stat_cmd(const char* p_inp, char* p_out)
{
    if (!strcmp(p_inp, "ERR")) {
        int8_t err = error_stack_get();
        sprintf(p_out, "%d", err);
        return prepare_and_add_lf(p_out, p_out);
    }
    return CMDDEC_UNKNOWN_CMD;
}
