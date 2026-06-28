#ifndef IR_TX_H
#define IR_TX_H

#include <stdint.h>

/* ============================================
 * FOX.M OS - IR Transmitter Driver
 * ============================================ */

/* IR Protocols */
#define IR_PROTOCOL_NEC     0x01
#define IR_PROTOCOL_SONY    0x02
#define IR_PROTOCOL_RC5     0x03
#define IR_PROTOCOL_RAW     0xFF

/* NEC Protocol timing (microseconds) */
#define NEC_HEADER_MARK     9000
#define NEC_HEADER_SPACE    4500
#define NEC_BIT_MARK        562
#define NEC_ONE_SPACE       1687
#define NEC_ZERO_SPACE      562
#define NEC_REPEAT_SPACE    2250

/* IR TX struct */
typedef struct {
    uint8_t  protocol;
    uint8_t  address;
    uint8_t  command;
    uint32_t raw_data;
} IR_Signal_t;

/* API */
void IR_TX_Init(void);
void IR_TX_Send(IR_Signal_t *signal);
void IR_TX_SendNEC(uint8_t address, uint8_t command);
void IR_TX_SendRaw(uint32_t *data, uint16_t length);

#endif /* IR_TX_H */