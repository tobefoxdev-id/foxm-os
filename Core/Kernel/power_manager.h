#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#include <stdint.h>

void PowerManager_Init(void);
void PowerManager_Sleep(void);
void PowerManager_Wake(void);
uint8_t PowerManager_GetBatteryLevel(void);

#endif