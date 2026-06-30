#ifndef BT_SCANNER_H
#define BT_SCANNER_H

/* ============================================
 * FOX.M OS - BT Scanner App
 * ============================================ */

#include <stdint.h>

#define BT_SCAN_MAX_DEVICES 8

typedef struct {
    char     name[32];
    uint8_t  mac[6];
    int8_t   rssi;
    uint8_t  type;
} BT_Device_t;

void BT_Scanner_Init(void);
void BT_Scanner_Run(void);
void BT_Scanner_Stop(void);
uint8_t BT_Scanner_GetDevices(BT_Device_t *devices, uint8_t max);
void BT_Scanner_Clear(void);

#endif /* BT_SCANNER_H */