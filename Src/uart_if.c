/*
 * uart_if.c
 *
 *  Created on: 02-Mar-2026
 *      Author: HARSHA
 */

#include<uart_if.h>

#include<stm32f411xe.h>

void uart_init(uint32_t baudrate){

	RCC->AHB1ENR |= (1U<<0);
	RCC->APB1ENR |= (1U<<17);

	// enable AF for PA2
	GPIOA->MODER &= ~(1U<<4);
	GPIOA->MODER |= (1U<<5);

	// enable AF for PA3
	GPIOA->MODER &= ~(1U<<6);
	GPIOA->MODER |= (1U<<7);

	// switch to USART2 for PA2 to push it into USART2_TX
	GPIOA->AFR[0] &= ~(0xFU<<8);
	GPIOA->AFR[0] |= (7U<<8);

	//switch to USART2 for PA3 to push it into USART2_RX
	GPIOA->AFR[0] &= ~(0xFU<<12);
	GPIOA->AFR[0] |= (7U<<12);

	USART2->BRR = (16000000 / baudrate);

	USART2->CR1 |= (8204U<<0);
}


void uart_tx_byte(uint8_t data_byte){
	while(!(USART2->SR & (1U<<7))){}
	USART2->DR = data_byte;
}
uint8_t uart_rx_byte(void){
	while (!(USART2->SR & (1U<<5))){}
	return USART2->DR;
}
void uart_tx_buffer(uint8_t *buffer, uint16_t length){
	for(int i=0; i<length; i++){
		uart_tx_byte(buffer[i]);
	}
}
void uart_rx_buffer(uint8_t *buffer, uint16_t length){
	for(int i=0; i<length; i++){
		buffer[i] = uart_rx_byte();
	}
}
