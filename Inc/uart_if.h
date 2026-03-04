
#ifndef UART_IF_H_
#define UART_IF_H_

#include<stdint.h>

void uart_init(uint32_t baudrate);
void uart_tx_byte(uint8_t data_byte);
uint8_t uart_rx_byte(void);
void uart_tx_buffer(uint8_t *buffer, uint16_t length);
void uart_rx_buffer(uint8_t *buffer, uint16_t length);
#endif /* UART_IF_H_ */
