/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "himax_control.h"
#include "image_proc.h"
#include "error_handler.h"
#include "error_codes.h"

#define LOG_MODULE_NAME image_proc
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

static struct {
    uint8_t data[IMAGE_MAX_SIZE];
    bool rd_busy;
    unsigned rd_cnt;
    unsigned wr_cnt;
} image_ctx = {{0}, false, 0, 0};

static struct k_event image_udate_event;

static image_control_proc_t image_control_proc;

static int image_read(char* buf, bool first)
{
    int ret;

    if (k_event_wait(&image_udate_event, 1, false, K_MSEC(1000)) == 0) {
        strcpy(buf, "NRDY\n");
        ret = 5;
        goto exit;
    }

    if (first) {
        image_ctx.rd_busy = true;
        image_ctx.rd_cnt = 0;
    }

    if (image_ctx.rd_busy == false) {
        strcpy(buf, "BSEQ\n");
        ret = 5;
        goto exit;
    }

    if (image_ctx.wr_cnt <= image_ctx.rd_cnt) {
        strcpy(buf, "RERR\n");
        ret = 5;
        goto exit;
    }

    unsigned rest_size = image_ctx.wr_cnt - image_ctx.rd_cnt;
    unsigned copy_size;

    if (rest_size > IMAGE_READ_CHUNK_SIZE) {
        sprintf(buf, "#%03d", IMAGE_READ_CHUNK_SIZE);
        copy_size = IMAGE_READ_CHUNK_SIZE;
    }
    else {
        sprintf(buf, "!%03d", rest_size);
        copy_size = rest_size;
    }
    memcpy(buf + IMAGE_READ_HEADER_LEN, image_ctx.data + image_ctx.rd_cnt, copy_size);
    image_ctx.rd_cnt += copy_size;

    if (image_ctx.rd_cnt >= image_ctx.wr_cnt) {
        image_ctx.rd_busy = false;
        k_event_clear(&image_udate_event, 1);
    }

    ret = IMAGE_READ_HEADER_LEN + copy_size;

exit:

    return ret;
}

int image_read_first(char* buf)
{
    int ret = image_read(buf, true);
    return ret;
}

int image_read_next(char* buf)
{
    int ret = image_read(buf, false);
    return ret;
}

bool image_take_one()
{
    k_event_clear(&image_udate_event, 1);

    if (image_control_proc) {
        image_control_proc(true);
    }

    k_sleep(K_MSEC(100));

    return true;
}

bool image_update(char* buf, uint16_t prm)
{
    bool ret = true;
    static unsigned prev_idx;
    static unsigned idx_mask;

    unsigned last = SPI_JPG_LAST(prm);
    unsigned index = SPI_JPG_INDX(prm);
    unsigned size = SPI_JPG_SIZE(prm);

    if (index == 0) {
        image_ctx.wr_cnt = 0;
        idx_mask = 1;
    }
    else {
        if (index != prev_idx + 1) {
            error_stack_add(ERR_IMG_BAD_SEQ1);
            idx_mask = 0;
            ret = false;
            goto exit;
        }
        else {
            idx_mask |= (1 << index);
        }
    }
    prev_idx = index;

    if (image_ctx.wr_cnt + size > IMAGE_MAX_SIZE) {
        error_stack_add(ERR_IMG_BAD_SIZE);
        idx_mask = 0;
        ret = false;
        goto exit;
    }

    memcpy(image_ctx.data + image_ctx.wr_cnt, buf, size);
    image_ctx.wr_cnt += size;

    if (last) {
        if (idx_mask == ((1 << (index + 1)) - 1)) {
            k_event_set(&image_udate_event, 1);
            if (image_control_proc) {
                image_control_proc(false);
            }
        }
        else {
            error_stack_add(ERR_IMG_BAD_SEQ0);
            ret = false;
        }
        idx_mask = 0;
    }

exit:

    return ret;
}

void image_reader_init(image_control_proc_t proc)
{
    image_control_proc = proc;
    k_event_init(&image_udate_event);
}