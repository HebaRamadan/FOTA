/*
 * SyStick_Interface.h
 *
 *  Created on: Feb 2, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


void MSTK_vidInit(void);
void MSTK_vidSetBusyWait( u32 Copy_u32Ticks  );
void MSTK_vidSetIntervalSingle  (u32 Copy_u32Ticks , void (*pf) (void));
void MSTK_vidSetIntervalPeriodic(u32 Copy_u32Ticks , void (*pf) (void));

u32  MSTK_u32GetElapsed  (void);
u32  MSTK_u32GetRemaining(void);
void MSTK_vidStop(void);

#endif /* SYSTICK_INTERFACE_H_ */
