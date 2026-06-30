/* ============================================
 * FOX.M OS - BT Scanner App
 * ============================================ */

#include "bt_scanner.h"
#include "FreeRTOS.h"
#include "task.h"

/* UART for output */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))

static void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }
static void uart_print(const char *s) { while (*s) uart_putc(*s++); }
static void uart_print_int(int8_t val)
{
    if (val < 0) { uart_putc('-'); val = -val; }
    if (val >= 100) uart_putc('0' + val / 100);
    if (val >= 10)  uart_putc('0' + (val / 10) % 10);
    uart_putc('0' + val % 10);
}

/* Simulated BT devices */
static BT_Device_t device_list[BT_SCAN_MAX_DEVICES];
static uint8_t device_count = 0;
static uint8_t scanning = 0;

/* Simulated nearby devices */
static const char *sim_names[] = {
    "iPhone 14",
    "Samsung Galaxy S23",
    "AirPods Pro",
    "Xiaomi TV",
    "JBL Speaker"
};
static const int8_t sim_rssi[] = { -45, -62, -38, -75, -55 };
static const uint8_t sim_mac[][6] = {
    {0xAA, 0xBB, 0xCC, 0x11, 0x22, 0x33},
    {0xDD, 0xEE, 0xFF, 0x44, 0x55, 0x66},
    {0x11, 0x22, 0x33, 0xAA, 0xBB, 0xCC},
    {0x77, 0x88, 0x99, 0xDD, 0xEE, 0xFF},
    {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45}
};

static void copy_str(char *dst, const char *src, int max)
{
    int i = 0;
    while (src[i] && i < max - 1) { dst[i] = src[i]; i++; }
    dst[i] = '\0';
}

void BT_Scanner_Init(void)
{
    device_count = 0;
    scanning     = 0;
    uart_print("[BT_SCAN] BT Scanner initialized\r\n");
}

void BT_Scanner_Run(void)
{
    scanning = 1;
    device_count = 0;

    uart_print("\r\n=============================\r\n");
    uart_print("  FOX.M BT Scanner - Running \r\n");
    uart_print("=============================\r\n");
    uart_print("[BT_SCAN] Scanning for BT devices...\r\n\r\n");

    /* Simulate scanning with delay */
    for (int i = 0; i < 5 && device_count < BT_SCAN_MAX_DEVICES; i++)
    {
        vTaskDelay(pdMS_TO_TICKS(300));

        copy_str(device_list[device_count].name, sim_names[i], 32);
        device_list[device_count].rssi = sim_rssi[i];
        device_list[device_count].type = 0x01;
        for (int j = 0; j < 6; j++)
            device_list[device_count].mac[j] = sim_mac[i][j];

        uart_print("[BT_SCAN] Device found: ");
        uart_print(device_list[device_count].name);
        uart_print("\r\n");
        uart_print("  MAC  : ");
        for (int j = 0; j < 6; j++)
        {
            const char hex[] = "0123456789ABCDEF";
            uart_putc(hex[(sim_mac[i][j] >> 4) & 0xF]);
            uart_putc(hex[sim_mac[i][j] & 0xF]);
            if (j < 5) uart_putc(':');
        }
        uart_print("\r\n");
        uart_print("  RSSI : ");
        uart_print_int(sim_rssi[i]);
        uart_print(" dBm\r\n\r\n");

        device_count++;
    }

    uart_print("[BT_SCAN] Scan complete!\r\n");
    uart_print("[BT_SCAN] Total devices found: ");
    uart_putc('0' + device_count);
    uart_print("\r\n");
    uart_print("=============================\r\n");

    scanning = 0;
}

void BT_Scanner_Stop(void)
{
    scanning = 0;
    uart_print("[BT_SCAN] Scanner stopped\r\n");
}

uint8_t BT_Scanner_GetDevices(BT_Device_t *devices, uint8_t max)
{
    uint8_t count = device_count < max ? device_count : max;
    for (int i = 0; i < count; i++)
        devices[i] = device_list[i];
    return count;
}

void BT_Scanner_Clear(void)
{
    device_count = 0;
    uart_print("[BT_SCAN] Device list cleared\r\n");
}