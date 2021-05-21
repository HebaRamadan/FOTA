/*
 * SyStick_Program.c
 *
 *  Created on: Feb 2, 2021
 *      Author: Heba Ramadan Taha
 */

#include "Std_types.h"
#include "Bit_math.h"

#include "SyStick_Interface.h"
#include "SyStick_Private.h"
#include "SyStick_Config.h"

static void ( *ptr_CallBack ) (void);
static u8 flag = 0 ;
void MSTK_vidInit(void)
{
	#if STK_CLOCK_SOURCE  == CLOCK_AHB
		SET_BIT(STK_CTRL,2);
	#elif STK_CLOCK_SOURCE == CLOCK_DIVIDE_BY_8
		CLR_BIT(STK_CTRL , 2);
	#endif

	CLR_BIT(STK_CTRL,0); //Disable SYSTICK
	CLR_BIT(STK_CTRL,1); //Disable Interrupt


}


void MSTK_vidSetBusyWait( u32 Copy_u32Ticks )
{
	STK_LOAD = Copy_u32Ticks ;

	SET_BIT( STK_CTRL , 0  );
	CLR_BIT( STK_CTRL , 1  );
	while( GET_BIT(STK_CTRL, 16) == 0)
	{

	}

	CLR_BIT( STK_CTRL , 0);
}

void MSTK_vidSetIntervalSingle( u32 Copy_u32Ticks , void (*pf) (void)  )
{
	STK_LOAD     = Copy_u32Ticks ;
	ptr_CallBack = pf;

	flag  = 0;
	SET_BIT( STK_CTRL , 1 );
	SET_BIT( STK_CTRL , 0 );

}

void MSTK_vidSetIntervalPeriodic( u32 Copy_u32Ticks , void (*pf) (void) )
{

	STK_LOAD     = Copy_u32Ticks ;
	ptr_CallBack = pf;

	flag  = 1;
	SET_BIT( STK_CTRL , 1 );
	SET_BIT( STK_CTRL , 0 );
}


u32  MSTK_u32GetElapsed  (void)
{
	return STK_LOAD - STK_VALUE ;
}

u32  MSTK_u32GetRemaining(void)
{
	return STK_VALUE;
}

void MSTK_vidStop(void)
{
    CLR_BIT(STK_CTRL, 0);   //Disable Timer
}

void SysTick_Handler(void)
{
	ptr_CallBack();
    if ( !flag )
    {
        STK_VALUE = 0 ;
        STK_LOAD  = 0;
    }

}



