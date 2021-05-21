/*
 * UART_Interface.h
 *
 *  Created on: Feb 7, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void MUSART1_vidInit(void);
void MUSART1_vidTransmitChar  ( u8   Copy_u8Char    );
void MUSART1_vidTransmitString( u8 * Copy_ptrString );
void MUSART1_vidSetCallBack( void (* ptrFunc )(void));
u8   MUSART1_u8ReceiveChar( void );
void MUSART1_vidNewLine   ( void );

void MUSART1_vidClearFlag(void);

#endif /* UART_INTERFACE_H_ */
