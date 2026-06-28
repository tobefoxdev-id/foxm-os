#ifndef IR_RX_H
#define IR_RX_H

#include <stdint.h>

/* ============================================
 * FOX.M OS - IR Receiver Driver
 * ============================================ */

#define IR_RX_BUFFER_SIZE   128

/* Decoded IR result */
typedef struct {
    uint8_t  protocol;
    uint8_t  address;
    uint8_t  command;
    uint8_t  valid;
    uint32_t raw_data;
} IR_Result_t;

/* API */
void IR_RX_Init(void);
uint8_t IR_RX_IsDataAvailable(void);
void IR_RX_Read(IR_Result_t *result);
void IR_RX_DecodeNEC(uint32_t raw, IR_Result_t *result);
void IR_RX_Flush(void);

#endif /* IR_RX_H */