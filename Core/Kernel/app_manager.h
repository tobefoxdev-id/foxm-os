#ifndef APP_MANAGER_H
#define APP_MANAGER_H

#include <stdint.h>

void AppManager_Init(void);
void AppManager_Launch(uint8_t app_id);
void AppManager_Kill(uint8_t app_id);

#endif