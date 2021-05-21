/*
 * Timer_Private.h
 *
 *  Created on: Mar 12, 2021
 *      Author:  Heba Ramadan Taha
 */

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_


/****************General Purpose Timers***************/

typedef struct
{
	volatile u32 CR1  ;
	volatile u32 CR2  ;
	volatile u32 SMCR ;
	volatile u32 DIER ;
	volatile u32 SR   ;
	volatile u32 EGR  ;
	volatile u32 CCMR1;
	volatile u32 CCMR2;
	volatile u32 CCER ;
	volatile u32 CNT  ;
	volatile u32 PSC  ;
	volatile u32 ARR  ;
	volatile u32 Reserved1 ;
	volatile u32 CCR1 ;
	volatile u32 CCR2 ;
	volatile u32 CCR3 ;
	volatile u32 CCR4 ;
	volatile u32 Reserved2 ;
	volatile u32 DCR  ;
	volatile u32 DMAR ;
}TIMx_Type;


#define TIMER2   ((volatile TIMx_Type *)0x40000000)
#define TIMER3   ((volatile TIMx_Type *)0x40000400)
#define TIMER4   ((volatile TIMx_Type *)0x40000800)
#define TIMER5   ((volatile TIMx_Type *)0x40000C00)



/*      CR1 Register       */
#define CEN     0
#define UDIS    1
#define URS     2
#define OPM     3
#define DIR     4
#define CMS0    5
#define CMS1    6
#define ARPE    7



/*      DIER Register        */
#define UIE      0
#define CC1IE    1
#define CC2IE    2
#define CC3IE    3
#define CC4IE    4


/*      SR Register          */
#define UIF    	  0
#define CC1IF     1
#define CC2IF  	  2
#define CC3IF     3
#define CC4IF     4


/*      CCMR1 Register        */
//Use Channel1 as CMP
#define CC1S0     0
#define CC1S1     1
#define OC1FE     2
#define OC1PE     3
#define OC1M0     4
#define OC1M1     5
#define OC1M2     6
#define OC1CE     7
//Use Channel2 as Input Capture
#define CC2S0     8
#define CC2S1     9
#define IC2PSC0   10
#define IC2PSC1   11
#define IC2F0     12
#define IC2F1     13
#define IC2F2     14
#define IC2F3     15


/*      CCER Register        */
#define CC1E      0
#define CC1P      1
#define CC2E      4
#define CC2P      5
#define CC3E      8
#define CC3P      9
#define CC4E      12
#define CC4P      13


#endif /* TIMER_PRIVATE_H_ */
