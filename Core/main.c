/* ============================================
 * FOX.M OS - Main Entry Point
 * Version: 0.1
 * Target: STM32F4 (Cortex-M4)
 * ============================================ */

#include "FreeRTOS.h"
#include "task.h"
#include "foxm_config.h"

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
    /* Hardware Init */
    // HAL_Init();
    // SystemClock_Config();

    /* Create FreeRTOS Tasks */
    xTaskCreate(Task_Event, "Event_Task", STACK_EVENT, NULL, PRIORITY_EVENT, NULL);
    xTaskCreate(Task_IR,    "IR_Task",    STACK_IR,    NULL, PRIORITY_IR,    NULL);
    xTaskCreate(Task_BT,    "BT_Task",    STACK_BT,    NULL, PRIORITY_BT,    NULL);
    xTaskCreate(Task_WiFi,  "WiFi_Task",  STACK_WIFI,  NULL, PRIORITY_WIFI,  NULL);
    xTaskCreate(Task_UI,    "UI_Task",    STACK_UI,    NULL, PRIORITY_UI,    NULL);
    xTaskCreate(Task_Power, "Power_Task", STACK_POWER, NULL, PRIORITY_POWER, NULL);

    /* Start Scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while (1);
}

/* ============================================
 * Task Definitions (Skeleton)
 * ============================================ */
void Task_Event(void *pvParameters)
{
    for (;;)
    {
        /* TODO: Event distribution logic */
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void Task_IR(void *pvParameters)
{
    for (;;)
    {
        /* TODO: IR TX/RX logic */
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void Task_BT(void *pvParameters)
{
    for (;;)
    {
        /* TODO: Bluetooth logic */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Task_WiFi(void *pvParameters)
{
    for (;;)
    {
        /* TODO: WiFi logic */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void Task_UI(void *pvParameters)
{
    for (;;)
    {
        /* TODO: Render GUI or CLI */
        vTaskDelay(pdMS_TO_TICKS(33)); /* ~30fps */
    }
}

void Task_Power(void *pvParameters)
{
    for (;;)
    {
        /* TODO: Power management logic */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}