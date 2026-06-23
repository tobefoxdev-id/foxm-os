/* ============================================
 * FOX.M OS - IR Receiver Driver
 * ============================================ */

#include "ir_rx.h"

void IR_RX_Init(void)
{
    /* TODO: Initialize IR RX hardware */
}

uint8_t IR_RX_IsDataAvailable(void)
{
    /* TODO: Check if IR data received */
    return 0;
}

void IR_RX_Read(uint32_t *buffer, uint16_t *length)
{
    /* TODO: Read received IR signal */
}

void IR_RX_DecodeNEC(uint32_t *data, uint8_t *address, uint8_t *command)
{
    /* TODO: Decode NEC protocol signal */
}