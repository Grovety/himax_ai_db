/*
 * Copyright (c) 2025 Grovety Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/usb/usb_device.h>

#include "acm_uart.h"
#include "lists_common_defs.h"

#define LOG_MODULE_NAME acm_uart
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#define ACM_UART_THREAD_STACKSIZE 1024
#define ACM_UART_THREAD_PRIORITY 4

static uart_data_proc_t uart_data_proc;

static void uart_data_handler_thread_proc();

static K_THREAD_DEFINE( uart_data_handler_thread_id, ACM_UART_THREAD_STACKSIZE,  uart_data_handler_thread_proc, NULL, NULL, NULL,
	ACM_UART_THREAD_PRIORITY, 0, 0);
static K_EVENT_DEFINE(command_is_ready_event);

static const struct device *uart_device = DEVICE_DT_GET(DT_CHOSEN(nordic_shell));

static uart_ctx_t uart_ctx;

static void direct_uart_callback(const struct device *uart_device, void *user_data)
{
	uart_ctx_t* p_uart_ctx = (uart_ctx_t*)user_data;

	uart_irq_update(uart_device);

#ifndef TX_WITH_POLLING
	if (uart_irq_tx_ready(uart_device)) {
		uart_irq_tx_disable(uart_device);
	}
#endif

	if (uart_irq_rx_ready(uart_device)) {
		uint8_t rx_char = 0;
		while (uart_fifo_read(uart_device, &rx_char, 1)) {
#ifdef SR_AT_CMD_ECHO
			(void)uart_fifo_fill(uart_device, &rx_char, 1);
#endif
			if (rx_char == '\r') { // bluetooth has '\n' but putty send '\r' instead
				rx_char = '\n';
			}
			p_uart_ctx->rx_buf[p_uart_ctx->is_read] = rx_char;
			p_uart_ctx->is_read = (p_uart_ctx->is_read + 1) % SR_OUT_BUF_SIZE;
			if (rx_char == '\n') {
				k_event_set(&command_is_ready_event, 0x001);
				break;
			}
		}
	}
}

void  uart_data_handler_thread_proc()
{
	while (1)
	{
		if (k_event_wait(&command_is_ready_event, 1, true, K_FOREVER))
		{
			k_sleep(K_MSEC(20));
			uart_ctx.rx_buf[uart_ctx.is_read] = 0;
			// LOG_HEXDUMP_INF(uart_ctx.rx_buf, 8, "Rx:");
			uart_ctx.to_write = uart_data_proc(USBUART_INTERFACE, uart_ctx.rx_buf, uart_ctx.is_read, uart_ctx.tx_buf, SR_OUT_BUF_SIZE);
			// LOG_HEXDUMP_INF(uart_ctx.tx_buf, 8, "Tx:");
			uart_ctx.is_read = 0;
			if (uart_ctx.to_write > 0) {
#ifndef TX_WITH_POLLING
				uart_irq_tx_enable(uart_device);
				(void)uart_fifo_fill(uart_device, uart_ctx.tx_buf, uart_ctx.to_write);
#else // TX_WITH_POLLING
				for(unsigned i = 0; i < uart_ctx.to_write; i++) {
					uart_poll_out(uart_device, uart_ctx.tx_buf[i]);
				}
#endif
			}
		}
	}
}

int acm_uart_init(uart_data_proc_t proc)
{
	if (!device_is_ready(uart_device)) {
		return -1;
	}

	if (!proc) {
		return -2;
	}

	uart_data_proc = proc;

	uart_irq_rx_disable(uart_device);

	int err = uart_irq_callback_user_data_set(uart_device, direct_uart_callback, &uart_ctx);

	uart_irq_rx_enable(uart_device);

    return err;
}
