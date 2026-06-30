#ifndef IR_SCANNER_H
#define IR_SCANNER_H

/* ============================================
 * FOX.M OS - IR Scanner App
 * ============================================ */

#include <stdint.h>

#define IR_SCAN_MAX_RESULTS 16

typedef struct {
    uint8_t  protocol;
    uint8_t  address;
    uint8_t  command;
    uint8_t  valid;
    uint32_t raw_data;
    uint32_t timestamp;
} IR_ScanResult_t;

void IR_Scanner_Init(void);
void IR_Scanner_Run(void);
void IR_Scanner_Stop(void);
uint8_t IR_Scanner_GetResults(IR_ScanResult_t *results, uint8_t max);
void IR_Scanner_Clear(void);

#endif /* IR_SCANNER_H */