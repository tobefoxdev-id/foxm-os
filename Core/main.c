/* ============================================
 * FOX.M OS - Main Entry Point
 * Version: 0.1
 * Target: STM32F4 (Cortex-M4)
 * ============================================ */

#include "FreeRTOS.h"
#include "task.h"
#include "foxm_config.h"
#include <stdio.h>

/* ---- Task Prototypes ---- */
void Task_Event(void *pvParameters);
void Task_IR(void *pvParameters);
void Task_BT(void *pvParameters);
void Task_WiFi(void *pvParameters);
void Task_UI(void *pvParameters);
void Task_Power(void *pvParameters);

/* ---- Simple UART print via semihosting ---- */
void foxm_print(const char *msg)
{
    printf("%s\n", msg);
    fflush(stdout);
}

/* ============================================
 * Main
 * ============================================ */
int main(void)
{
    foxm_print("==========================================");
    foxm_print("  FOX.M OS v0.1 - Booting...");
    foxm_print("  Target: STM32F4 (Cortex-M4)");
    foxm_print("  Base: FreeRTOS");
    foxm_print("==========================================");

    foxm_print("[BOOT] Initializing tasks...");

    /* Create FreeRTOS Tasks */
    xTaskCreate(Task_Event, "Event_Task", STACK_EVENT, NULL, PRIORITY_EVENT, NULL);
    xTaskCreate(Task_IR,    "IR_Task",    STACK_IR,    NULL, PRIORITY_IR,    NULL);
    xTaskCreate(Task_BT,    "BT_Task",    STACK_BT,    NULL, PRIORITY_BT,    NULL);
    xTaskCreate(Task_WiFi,  "WiFi_Task",  STACK_WIFI,  NULL, PRIORITY_WIFI,  NULL);
    xTaskCreate(Task_UI,    "UI_Task",    STACK_UI,    NULL, PRIORITY_UI,    NULL);
    xTaskCreate(Task_Power, "Power_Task", STACK_POWER, NULL, PRIORITY_POWER, NULL);

    foxm_print("[BOOT] All tasks created!");
    foxm_print("[BOOT] Starting FreeRTOS scheduler...");

    /* Start Scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    foxm_print("[ERROR] Scheduler failed!");
    while (1);
}

/* ============================================
 * Task Definitions (Skeleton)
 * ============================================ */
void Task_Event(void *pvParameters)
{
    foxm_print("[TASK] Event_Task running!");
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void Task_IR(void *pvParameters)
{
    foxm_print("[TASK] IR_Task running!");
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void Task_BT(void *pvParameters)
{
    foxm_print("[TASK] BT_Task running!");
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Task_WiFi(void *pvParameters)
{
    foxm_print("[TASK] WiFi_Task running!");
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Task_UI(void *pvParameters)
{
    foxm_print("[TASK] UI_Task running!");
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(33));
    }
}

void Task_Power(void *pvParameters)
{
    foxm_print("[TASK] Power_Task running!");
    for (;;)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}