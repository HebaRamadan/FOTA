/*
 * UART_Config.h
 *
 *  Created on: Feb 7, 2021
 *      Author: zas
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define F_CPU                    8000000UL
#define USART1_BAUD_RATE         (u32)115200

#define USART1_WORD_LENGTH       WORD_LENGTH_8BIT

#define USART1_PARITY            PARITY_DISABLE
#define USART1_STOP_BITS         ONE_STOP_BIT

#define USART1_TX_STATUS         TX_ENABLE
#define USART1_RX_STATUS         RX_ENABLE

#define USART1_INTERRUPT_STATE   RXNE_INT_ENABLE




#endif /* UART_CONFIG_H_ */
