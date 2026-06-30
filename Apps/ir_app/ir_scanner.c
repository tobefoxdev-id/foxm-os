/* ============================================
 * FOX.M OS - IR Scanner App
 * ============================================ */

#include "ir_scanner.h"
#include "ir_rx.h"
#include "ir_tx.h"
#include "FreeRTOS.h"
#include "task.h"

/* UART for output */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))

static void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }
static void uart_print(const char *s) { while (*s) uart_putc(*s++); }
static void uart_print_hex(uint32_t val)
{
    const char hex[] = "0123456789ABCDEF";
    uart_print("0x");
    for (int i = 28; i >= 0; i -= 4)
        uart_putc(hex[(val >> i) & 0xF]);
}

/* Scan results buffer */
static IR_ScanResult_t scan_results[IR_SCAN_MAX_RESULTS];
static uint8_t scan_count = 0;
static uint8_t scanning = 0;
static uint32_t scan_tick = 0;

void IR_Scanner_Init(void)
{
    scan_count = 0;
    scanning   = 0;
    scan_tick  = 0;
    uart_print("[IR_SCAN] IR Scanner initialized\r\n");
}

void IR_Scanner_Run(void)
{
    scanning = 1;
    uart_print("\r\n=============================\r\n");
    uart_print("  FOX.M IR Scanner - Running \r\n");
    uart_print("=============================\r\n");
    uart_print("[IR_SCAN] Scanning for IR signals...\r\n\r\n");

    /* Simulate scanning - send test signals and capture */
    uint8_t test_addrs[] = {0x01, 0x04, 0x08};
    uint8_t test_cmds[]  = {0x45, 0x46, 0x47};

    for (int i = 0; i < 3 && scan_count < IR_SCAN_MAX_RESULTS; i++)
    {
        /* Transmit test signal */
        IR_TX_SendNEC(test_addrs[i], test_cmds[i]);
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Receive and decode */
        if (IR_RX_IsDataAvailable())
        {
            IR_Result_t result;
            IR_RX_Read(&result);

            scan_results[scan_count].protocol  = result.protocol;
            scan_results[scan_count].address   = result.address;
            scan_results[scan_count].command   = result.command;
            scan_results[scan_count].valid     = result.valid;
            scan_results[scan_count].raw_data  = result.raw_data;
            scan_results[scan_count].timestamp = scan_tick++;

            uart_print("[IR_SCAN] Signal #");
            uart_putc('0' + scan_count + 1);
            uart_print(" captured!\r\n");
            uart_print("  Protocol : NEC\r\n");
            uart_print("  Address  : ");
            uart_print_hex(result.address);
            uart_print("\r\n");
            uart_print("  Command  : ");
            uart_print_hex(result.command);
            uart_print("\r\n");
            uart_print("  Valid    : ");
            uart_print(result.valid ? "YES" : "NO");
            uart_print("\r\n\r\n");

            scan_count++;
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }

    uart_print("[IR_SCAN] Scan complete!\r\n");
    uart_print("[IR_SCAN] Total signals captured: ");
    uart_putc('0' + scan_count);
    uart_print("\r\n");
    uart_print("=============================\r\n");

    scanning = 0;
}

void IR_Scanner_Stop(void)
{
    scanning = 0;
    uart_print("[IR_SCAN] Scanner stopped\r\n");
}

uint8_t IR_Scanner_GetResults(IR_ScanResult_t *results, uint8_t max)
{
    uint8_t count = scan_count < max ? scan_count : max;
    for (int i = 0; i < count; i++)
        results[i] = scan_results[i];
    return count;
}

void IR_Scanner_Clear(void)
{
    scan_count = 0;
    uart_print("[IR_SCAN] Results cleared\r\n");
}