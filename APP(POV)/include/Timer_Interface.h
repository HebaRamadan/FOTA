/*
 * Timer_Interface.h
 *
 *  Created on: Mar 12, 2021
 *      Author:  Heba Ramadan Taha
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

void MTIMER_vidInit(void);
void MTIMER_vidSetCounterReg(u16 Copy_u16CNTValue);
void MTIMER_vidSetCompareReg(u16 Copy_u16CCRValue);
u16  MTIMER_u16GetCaptuerReg(void);
u16  MTIMER_u16GetCounterReg(void);

void MTIMER_vidSetCallBackOVF( void (*pf)(void) );
void MTIMER_vidSetCallBackICP( void (*pf)(void) );
void MTIMER_vidSetCallBackCMP( void (*pf)(void) );



#endif /* TIMER_INTERFACE_H_ */
