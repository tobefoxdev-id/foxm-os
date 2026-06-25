#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include "FreeRTOS.h"
#include "queue.h"
#include <stdint.h>

/* ============================================
 * FOX.M OS - Event System
 * ============================================ */

/* Event IDs */
#define EVENT_NONE          0x00
#define EVENT_IR_RECEIVED   0x01
#define EVENT_BT_CONNECTED  0x02
#define EVENT_BT_DATA       0x03
#define EVENT_WIFI_CONNECTED 0x04
#define EVENT_WIFI_DATA     0x05
#define EVENT_UI_UPDATE     0x06
#define EVENT_POWER_LOW     0x07
#define EVENT_POWER_CRITICAL 0x08

/* Event struct */
typedef struct {
    uint8_t  id;
    uint8_t  source;
    uint8_t  target;
    uint32_t data;
} FoxEvent_t;

/* Source/Target IDs */
#define TASK_EVENT  0x01
#define TASK_IR     0x02
#define TASK_BT     0x03
#define TASK_WIFI   0x04
#define TASK_UI     0x05
#define TASK_POWER  0x06

/* Queue handle - accessible by all tasks */
extern QueueHandle_t xEventQueue;

/* API */
void EventSystem_Init(void);
BaseType_t EventSystem_Send(FoxEvent_t *event);
BaseType_t EventSystem_Receive(FoxEvent_t *event, TickType_t timeout);

#endif /* EVENT_SYSTEM_H */