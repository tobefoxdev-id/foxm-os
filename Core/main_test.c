/* ============================================
 * FOX.M OS - QEMU Test (No FreeRTOS)
 * ============================================ */

#include <stdint.h>

/* UART0 base address for mps2-an385 */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_CTRL  (*((volatile uint32_t *)(UART0_BASE + 0x08)))

void uart_init(void)
{
    UART0_CTRL = 0x1; /* Enable UART TX */
}

void uart_putc(char c)
{
    while (UART0_STATE & 0x1); /* Wait if TX busy */
    UART0_DATA = c;
}

void uart_print(const char *str)
{
    while (*str) uart_putc(*str++);
}

int main(void)
{
    uart_init();
    uart_print("==========================================\r\n");
    uart_print("  FOX.M OS v0.1 - Booting...\r\n");
    uart_print("  Target: STM32F4 (Cortex-M4)\r\n");
    uart_print("  Base: FreeRTOS\r\n");
    uart_print("==========================================\r\n");
    uart_print("[BOOT] FOX.M OS Ready!\r\n");

    while (1);
}