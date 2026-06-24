#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <stdint.h>

void EventSystem_Init(void);
void EventSystem_Send(uint8_t event_id, void *data);
void EventSystem_Process(void);

#endif