#ifndef IR_RX_H
#define IR_RX_H

#include <stdint.h>

void IR_RX_Init(void);
uint8_t IR_RX_IsDataAvailable(void);
void IR_RX_Read(uint32_t *buffer, uint16_t *length);
void IR_RX_DecodeNEC(uint32_t *data, uint8_t *address, uint8_t *command);

#endif