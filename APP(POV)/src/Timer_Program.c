/*
 * Timer_Program.c
 *
 *  Created on: Mar 12, 2021
 *      Author:  Heba Ramadan Taha
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "Timer_Interface.h"
#include "Timer_Private.h"
#include "Timer_Config.h"

#define NULL    (void *)(0)

static  void( * CMP_CallBack )(void) = NULL ;
static  void( * OVF_CallBack )(void) = NULL ;
static  void( * ICP_CallBack )(void) = NULL ;


void MTIMER_vidInit(void)
{
	/*      Set Pre_scaler Register   */
	TIMER4 -> PSC  = TIMRE_PRESCALER    ;

	/*      Set Pre_load Register     */
	TIMER4 -> ARR  = TIMER_PRELOAD_REG  ;

	TIMER4 -> CNT  = 0;

	/*      Set Compare Register      */
	//TIMER4 -> CCR1 = TIMER_COMPAARE_REG ;

	TIMER4 -> SR   = 0     ;

	/*      Select UP Counter         */
	CLR_BIT( (TIMER4 -> CR1) , DIR  );

	/*      Edge-Aligned Mode         */
	CLR_BIT( (TIMER4 -> CR1) , CMS0 );
	CLR_BIT( (TIMER4 -> CR1) , CMS1 );

	/*      Configure Update Event    */
	CLR_BIT( (TIMER4 -> CR1) , UDIS );
	CLR_BIT( (TIMER4 -> CR1) , URS  );

	/*      Disable Auto Reload       */
	CLR_BIT( (TIMER4 -> CR1) , ARPE );


	/*    Link Channel1 With CMP Mode        */
	CLR_BIT(  (TIMER4 -> CCMR1) , CC1S0 );
	CLR_BIT(  (TIMER4 -> CCMR1) , CC1S1 );

	CLR_BIT(  (TIMER4 -> CCMR1) , OC1PE );


	/*  Link Channel2 With Input Capture Mode  */
	SET_BIT(  (TIMER4 -> CCMR1)  , CC2S0 );
	CLR_BIT(  (TIMER4 -> CCMR1)  , CC2S1 );

	/*      No Pre_Scaler Input        */
	CLR_BIT(  (TIMER4 -> CCMR1) , IC2PSC0 );
	CLR_BIT(  (TIMER4 -> CCMR1) , IC2PSC1 );

	/*      Filter for input Signal (Optional) */
	SET_BIT(  (TIMER4 -> CCMR1) , IC2F0   );
	SET_BIT(  (TIMER4 -> CCMR1) , IC2F1   );
	CLR_BIT(  (TIMER4 -> CCMR1) , IC2F2   );
	CLR_BIT(  (TIMER4 -> CCMR1) , IC2F3   );

	SET_BIT( (TIMER4 -> CCER)  , CC2P);  // Falling Edge
	/*       Enable Input Capture           */
	SET_BIT( (TIMER4 -> CCER)  , CC2E);


	/*      Enable Update Interrupt           */
	SET_BIT( (TIMER4 -> DIER ) , UIE   );

	/*  	Enable Compare Match Interrupt Channel1  */
	SET_BIT( (TIMER4 -> DIER ) , CC1IE );

	/*  	Enable Input Capture Interrupt Channel2  */
	SET_BIT( (TIMER4 -> DIER ) , CC2IE );


	/*        Enable Timer            */
	SET_BIT( (TIMER4 -> CR1)   , CEN   );


}


void MTIMER_vidSetCounterReg(u16 Copy_u16CNTValue)
{
	TIMER4 -> CNT = Copy_u16CNTValue;
}


void MTIMER_vidSetCompareReg(u16 Copy_u16CCRValue)
{
	/* SET Value in Channel1 which configured as CMP */
	TIMER4 -> CCR1 = Copy_u16CCRValue;
}


u16  MTIMER_u16GetCaptuerReg(void)
{
	/* GET Value in Channel2 which configured as ICP */
	return TIMER4 -> CCR2;
}


u16  MTIMER_u16GetCounterReg(void)
{
	/*  GET Value in CNT Register    */
	return TIMER4 -> CNT;
}

void MTIMER_vidSetCallBackOVF(void (*pf)(void) )
{
	if( pf != NULL )
	{
		OVF_CallBack = pf ;
	}
}


void MTIMER_vidSetCallBackCMP(void (*pf)(void) )
{
	if( pf != NULL )
	{
		CMP_CallBack = pf ;
	}
}


void MTIMER_vidSetCallBackICP( void (*pf)(void) )
{
	if( pf != NULL )
	{
		ICP_CallBack = pf ;
	}
}


void TIM4_IRQHandler(void)
{

	if( GET_BIT((TIMER4 -> SR) , CC2IF ) )
	{
		ICP_CallBack();
		CLR_BIT( (TIMER4 -> SR) , CC2IF  );
	}
	else if( GET_BIT((TIMER4 -> SR) , UIF ))
	{
		OVF_CallBack();
		CLR_BIT( (TIMER4 -> SR) , UIF  );
	}
	else if( GET_BIT((TIMER4 -> SR) , CC1IF ) )
	{
		CMP_CallBack();
		CLR_BIT( (TIMER4 -> SR) , CC1IF  );
	}


}


/*  Link Channel1 With Input Capture Mode  */
//	CLR_BIT(  (TIMER4 -> CCR1) , CC1S0 );
//	SET_BIT(  (TIMER4 -> CCR1) , CC1S1 );

/*      No Pre_Scaler Input        */
//	CLR_BIT(  (TIMER4 -> CCR1) , IC1PSC0 );
//	CLR_BIT(  (TIMER4 -> CCR1) , IC1PSC1  );

/*      Select Falling Edge       */
