/*
 * NVIC_Interface.h
 *
 *  Created on: Jan 26, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_


void MNVIC_vidInit(void);
void MNVIC_vidSetPriority     ( u8 Copy_u8IntNumber  ,  u8 Copy_u8Group  ,  u8 Copy_u8Priority );
void MNVIC_vidEnableInterrupt ( u8 Copy_u8IntNumber );
void MNVIC_vidDisableInterrupt( u8 Copy_u8IntNumber );
void MNVIC_vidSetPendingFlag  ( u8 Copy_u8IntNumber );
void MNVIC_vidClrPendingFlag  ( u8 Copy_u8IntNumber );

u8   MNVIC_u8GetActiveFlag    ( u8 Copy_u8IntNumber );


#endif /* NVIC_INTERFACE_H_ */
