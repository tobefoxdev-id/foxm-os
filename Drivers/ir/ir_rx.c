/* ============================================
 * FOX.M OS - IR Receiver Driver
 * Implementation (QEMU Simulation)
 * ============================================ */

#include "ir_rx.h"
#include "ir_tx.h"

/* UART for debug output */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_CTRL  (*((volatile uint32_t *)(UART0_BASE + 0x08)))

static void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }
static void uart_print(const char *s) { while (*s) uart_putc(*s++); }

/* Simulated RX buffer */
static IR_Result_t rx_buffer;
static uint8_t rx_available = 0;

void IR_RX_Init(void)
{
    rx_available = 0;
    uart_print("[IR_RX] Receiver initialized\r\n");
}

uint8_t IR_RX_IsDataAvailable(void)
{
    /* Simulate: check if TX sent something (loopback) */
    IR_Signal_t tx_signal;
    if (IR_TX_GetLastSignal(&tx_signal))
    {
        IR_RX_DecodeNEC(tx_signal.raw_data, &rx_buffer);
        rx_available = 1;
    }
    return rx_available;
}

void IR_RX_Read(IR_Result_t *result)
{
    if (result == 0) return;
    *result = rx_buffer;
    rx_available = 0;
}

void IR_RX_DecodeNEC(uint32_t raw, IR_Result_t *result)
{
    if (result == 0) return;

    result->protocol = 0x01;
    result->address  = (raw >> 24) & 0xFF;
    result->command  = (raw >> 8)  & 0xFF;
    result->raw_data = raw;

    /* Validate: address + ~address, command + ~command */
    uint8_t addr_inv = (raw >> 16) & 0xFF;
    uint8_t cmd_inv  = (raw >> 0)  & 0xFF;

    result->valid = ((result->address ^ addr_inv) == 0xFF) &&
                    ((result->command  ^ cmd_inv)  == 0xFF);
}

void IR_RX_Flush(void)
{
    rx_available = 0;
}