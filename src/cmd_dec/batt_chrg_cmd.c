/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>
#include <stdbool.h>

#include "pwr_ctrl.h"
#include "command_decoder.h"

int battery_charger_cmd(const char* p_inp, char* p_out)
{
    if (!strncmp(p_inp, "BCHRG", 5)) {          // AT^BCHRG\n
        if (*(p_inp + 5) == '\0') {
            pm_charger_status(p_out);
            return prepare_and_add_lf(p_out, p_out);
        }
        if (*(p_inp + 5) != '=') {
            return prepare_and_add_lf(p_out, "BAD_FORMAT");
        }
        p_inp += 6;
        if (!strcmp(p_inp, "ON")) {             // AT^BCHRG=<ON>\n
            pm_charger_ctrl(true);
            return prepare_and_add_lf(p_out, "OK");
        }
        if (!strcmp(p_inp, "OFF")) {            // AT^BCHRG=<OFF>\n
            pm_charger_ctrl(false);
            return prepare_and_add_lf(p_out, "OK");
        }
        return prepare_and_add_lf(p_out, "BAD_PARAM");
    }
    return CMDDEC_UNKNOWN_CMD;
}
