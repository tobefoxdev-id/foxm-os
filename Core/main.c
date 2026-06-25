/* ============================================
 * FOX.M OS - Main Entry Point
 * Version: 0.1 (QEMU Compatible)
 * ============================================ */

#include <stdint.h>

/* UART0 mps2-an385 */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_CTRL  (*((volatile uint32_t *)(UART0_BASE + 0x08)))

void uart_init(void)   { UART0_CTRL = 0x1; }
void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }
void uart_print(const char *s) { while (*s) uart_putc(*s++); }

/* Simulated task delay */
void delay(volatile uint32_t n) { while (n--); }

/* Task functions */
void Task_Event(void)  { uart_print("[TASK] Event_Task  -> Running\r\n"); }
void Task_IR(void)     { uart_print("[TASK] IR_Task     -> Running\r\n"); }
void Task_BT(void)     { uart_print("[TASK] BT_Task     -> Running\r\n"); }
void Task_WiFi(void)   { uart_print("[TASK] WiFi_Task   -> Running\r\n"); }
void Task_UI(void)     { uart_print("[TASK] UI_Task     -> Running\r\n"); }
void Task_Power(void)  { uart_print("[TASK] Power_Task  -> Running\r\n"); }

int main(void)
{
    uart_init();

    uart_print("==========================================\r\n");
    uart_print("       FOX.M OS v0.1 - Booting...       \r\n");
    uart_print("  Target : STM32F4 (Cortex-M4)          \r\n");
    uart_print("  Kernel : FreeRTOS                     \r\n");
    uart_print("  Dev    : ToBeFox.Dev                  \r\n");
    uart_print("==========================================\r\n\r\n");

    uart_print("[BOOT] Initializing FOX.M OS...\r\n");
    delay(100000);

    uart_print("[BOOT] Starting tasks...\r\n\r\n");
    delay(100000);

    /* Simulate task execution */
    Task_Event();
    delay(50000);
    Task_IR();
    delay(50000);
    Task_BT();
    delay(50000);
    Task_WiFi();
    delay(50000);
    Task_UI();
    delay(50000);
    Task_Power();
    delay(50000);

    uart_print("\r\n[BOOT] All systems operational!\r\n");
    uart_print("[FOX.M OS] Ready.\r\n");

    while (1);
}