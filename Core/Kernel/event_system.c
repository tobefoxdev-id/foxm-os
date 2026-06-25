/* ============================================
 * FOX.M OS - Event System Implementation
 * ============================================ */

#include "event_system.h"

/* Global event queue */
QueueHandle_t xEventQueue = NULL;

#define EVENT_QUEUE_LENGTH 16

void EventSystem_Init(void)
{
    xEventQueue = xQueueCreate(EVENT_QUEUE_LENGTH, sizeof(FoxEvent_t));
}

BaseType_t EventSystem_Send(FoxEvent_t *event)
{
    if (xEventQueue == NULL) return pdFAIL;
    return xQueueSend(xEventQueue, event, pdMS_TO_TICKS(10));
}

BaseType_t EventSystem_Receive(FoxEvent_t *event, TickType_t timeout)
{
    if (xEventQueue == NULL) return pdFAIL;
    return xQueueReceive(xEventQueue, event, timeout);
}