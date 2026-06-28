/* ============================================
 * FOX.M OS - Main Entry Point
 * Version: 0.1
 * Target: STM32F4 (Cortex-M4)
 * ============================================ */

#include "FreeRTOS.h"
#include "task.h"
#include "foxm_config.h"
#include "event_system.h"
#include "ir_tx.h"
#include "ir_rx.h"

/* UART0 mps2-an385 */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_CTRL  (*((volatile uint32_t *)(UART0_BASE + 0x08)))

void uart_init(void)   { UART0_CTRL = 0x1; }
void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }
void uart_print(const char *s) { while (*s) uart_putc(*s++); }

void uart_print_hex(uint32_t val)
{
    const char hex[] = "0123456789ABCDEF";
    uart_print("0x");
    for (int i = 28; i >= 0; i -= 4)
        uart_putc(hex[(val >> i) & 0xF]);
}

/* ---- Task Prototypes ---- */
void Task_Event(void *pvParameters);
void Task_IR(void *pvParameters);
void Task_BT(void *pvParameters);
void Task_WiFi(void *pvParameters);
void Task_UI(void *pvParameters);
void Task_Power(void *pvParameters);

/* ============================================
 * Main
 * ============================================ */
int main(void)
{
    uart_init();

    uart_print("==========================================\r\n");
    uart_print("       FOX.M OS v0.1 - Booting...       \r\n");
    uart_print("  Target : STM32F4 (Cortex-M4)          \r\n");
    uart_print("  Kernel : FreeRTOS                     \r\n");
    uart_print("  Dev    : ToBeFox.Dev                  \r\n");
    uart_print("==========================================\r\n\r\n");

    uart_print("[BOOT] Initializing Event System...\r\n");
    EventSystem_Init();
    uart_print("[BOOT] Event System OK!\r\n");

    uart_print("[BOOT] Initializing IR Driver...\r\n");
    IR_TX_Init();
    IR_RX_Init();
    uart_print("[BOOT] IR Driver OK!\r\n\r\n");

    uart_print("[BOOT] Creating FreeRTOS tasks...\r\n");
    xTaskCreate(Task_Event, "Event_Task", STACK_EVENT, NULL, PRIORITY_EVENT, NULL);
    xTaskCreate(Task_IR,    "IR_Task",    STACK_IR,    NULL, PRIORITY_IR,    NULL);
    xTaskCreate(Task_BT,    "BT_Task",    STACK_BT,    NULL, PRIORITY_BT,    NULL);
    xTaskCreate(Task_WiFi,  "WiFi_Task",  STACK_WIFI,  NULL, PRIORITY_WIFI,  NULL);
    xTaskCreate(Task_UI,    "UI_Task",    STACK_UI,    NULL, PRIORITY_UI,    NULL);
    xTaskCreate(Task_Power, "Power_Task", STACK_POWER, NULL, PRIORITY_POWER, NULL);

    uart_print("[BOOT] Starting FreeRTOS scheduler...\r\n\r\n");
    vTaskStartScheduler();

    uart_print("[ERROR] Scheduler failed!\r\n");
    while (1);
}

/* ============================================
 * Task Definitions
 * ============================================ */
void Task_Event(void *pvParameters)
{
    FoxEvent_t event;
    uart_print("[TASK] Event_Task  -> Running\r\n");

    for (;;)
    {
        if (EventSystem_Receive(&event, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            switch (event.id)
            {
                case EVENT_IR_RECEIVED:
                    uart_print("[EVENT] IR signal received! Data: ");
                    uart_print_hex(event.data);
                    uart_print("\r\n");
                    break;
                case EVENT_BT_CONNECTED:
                    uart_print("[EVENT] Bluetooth connected!\r\n");
                    break;
                case EVENT_POWER_LOW:
                    uart_print("[EVENT] Power low warning!\r\n");
                    break;
                default:
                    break;
            }
        }
    }
}

void Task_IR(void *pvParameters)
{
    uart_print("[TASK] IR_Task     -> Running\r\n");
    vTaskDelay(pdMS_TO_TICKS(500));

    /* Simulate IR TX - send NEC signal */
    uart_print("[IR] Transmitting NEC signal (addr=0x01, cmd=0x45)...\r\n");
    IR_TX_SendNEC(0x01, 0x45);

    /* Small delay then check RX */
    vTaskDelay(pdMS_TO_TICKS(100));

    /* Simulate IR RX - loopback */
    if (IR_RX_IsDataAvailable())
    {
        IR_Result_t result;
        IR_RX_Read(&result);

        uart_print("[IR] Signal received!\r\n");
        uart_print("[IR] Protocol : NEC\r\n");
        uart_print("[IR] Address  : ");
        uart_print_hex(result.address);
        uart_print("\r\n");
        uart_print("[IR] Command  : ");
        uart_print_hex(result.command);
        uart_print("\r\n");
        uart_print("[IR] Valid    : ");
        uart_print(result.valid ? "YES\r\n" : "NO\r\n");

        /* Send event to Event_Task */
        FoxEvent_t event = {
            .id     = EVENT_IR_RECEIVED,
            .source = TASK_IR,
            .target = TASK_EVENT,
            .data   = result.raw_data
        };
        EventSystem_Send(&event);
    }

    for (;;) vTaskDelay(pdMS_TO_TICKS(50));
}

void Task_BT(void *pvParameters)
{
    uart_print("[TASK] BT_Task     -> Running\r\n");
    vTaskDelay(pdMS_TO_TICKS(800));

    FoxEvent_t event = {
        .id     = EVENT_BT_CONNECTED,
        .source = TASK_BT,
        .target = TASK_EVENT,
        .data   = 0x01
    };
    EventSystem_Send(&event);
    uart_print("[BT] Connected, event sent!\r\n");

    for (;;) vTaskDelay(pdMS_TO_TICKS(100));
}

void Task_WiFi(void *pvParameters)
{
    uart_print("[TASK] WiFi_Task   -> Running\r\n");
    for (;;) vTaskDelay(pdMS_TO_TICKS(100));
}

void Task_UI(void *pvParameters)
{
    uart_print("[TASK] UI_Task     -> Running\r\n");
    for (;;) vTaskDelay(pdMS_TO_TICKS(33));
}

void Task_Power(void *pvParameters)
{
    uart_print("[TASK] Power_Task  -> Running\r\n");
    vTaskDelay(pdMS_TO_TICKS(1200));

    FoxEvent_t event = {
        .id     = EVENT_POWER_LOW,
        .source = TASK_POWER,
        .target = TASK_EVENT,
        .data   = 15
    };
    EventSystem_Send(&event);
    uart_print("[POWER] Battery low, event sent!\r\n");

    for (;;) vTaskDelay(pdMS_TO_TICKS(1000));
}