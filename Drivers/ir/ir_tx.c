/* ============================================
 * FOX.M OS - IR Transmitter Driver
 * Implementation (QEMU Simulation)
 * ============================================ */

#include "ir_tx.h"
#include "ir_rx.h"

/* UART for debug output */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_CTRL  (*((volatile uint32_t *)(UART0_BASE + 0x08)))

static void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }
static void uart_print(const char *s) { while (*s) uart_putc(*s++); }

/* Simulated TX buffer */
static IR_Signal_t tx_buffer;
static uint8_t tx_ready = 0;

void IR_TX_Init(void)
{
    tx_ready = 0;
    uart_print("[IR_TX] Transmitter initialized\r\n");
}

void IR_TX_SendNEC(uint8_t address, uint8_t command)
{
    tx_buffer.protocol = 0x01;
    tx_buffer.address  = address;
    tx_buffer.command  = command;
    tx_buffer.raw_data = ((uint32_t)address << 24) |
                         ((uint32_t)(address ^ 0xFF) << 16) |
                         ((uint32_t)command << 8) |
                         ((uint32_t)(command ^ 0xFF));
    tx_ready = 1;

    uart_print("[IR_TX] Sending NEC signal\r\n");
}

void IR_TX_Send(IR_Signal_t *signal)
{
    if (signal == 0) return;
    tx_buffer = *signal;
    tx_ready = 1;
    uart_print("[IR_TX] Signal transmitted\r\n");
}

void IR_TX_SendRaw(uint32_t *data, uint16_t length)
{
    if (data == 0 || length == 0) return;
    tx_buffer.protocol = 0xFF;
    tx_buffer.raw_data = data[0];
    tx_ready = 1;
    uart_print("[IR_TX] Raw signal transmitted\r\n");
}

/* Get last transmitted signal (for loopback simulation) */
uint8_t IR_TX_GetLastSignal(IR_Signal_t *out)
{
    if (!tx_ready || out == 0) return 0;
    *out = tx_buffer;
    tx_ready = 0;
    return 1;
}