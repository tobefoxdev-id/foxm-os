#ifndef IR_TX_H
#define IR_TX_H

#include <stdint.h>

void IR_TX_Init(void);
void IR_TX_Send(uint32_t *data, uint16_t length);
void IR_TX_SendNEC(uint8_t address, uint8_t command);

#endif