/*
 * NVIC_Program.c
 *
 *  Created on: Jan 26, 2021
 *      Author:Heba Ramadan Taha
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "NVIC_Interface.h"
#include "NVIC_Private.h"
#include "NVIC_Config.h"


void MNVIC_vidInit(void)
{

	/*    Number Of Groups and Sub    */
    #ifndef SCB_AIRCR
	#define SCB_AIRCR   *((u32 *)(0xE000ED00 + 0x0C))
	#endif

	SCB_AIRCR = MNVIC_GROUPS_SUBS ;

}


void MNVIC_vidSetPriority(u8 Copy_u8IntNumber ,  u8 Copy_u8Group  ,  u8 Copy_u8Priority )
{

	/* Range Check                       */
	if( Copy_u8IntNumber < 60)
	{
		#if MNVIC_GROUPS_SUBS == MNVIC_GROUP4_SUB_0
			NVIC_IPR[Copy_u8IntNumber] = Copy_u8Group << 4;

		#elif MNVIC_GROUPS_SUBS == MNVIC_GROUP3_SUB_1
			NVIC_IPR[Copy_u8IntNumber] = (Copy_u8Priority | (Copy_u8Group << 1)) << 4 ;

		#elif MNVIC_GROUPS_SUBS == MNVIC_GROUP2_SUB_2
			NVIC_IPR[Copy_u8IntNumber] = (Copy_u8Priority | (Copy_u8Group << 2)) << 4 ;

		#elif MNVIC_GROUPS_SUBS == MNVIC_GROUP1_SUB_3
			NVIC_IPR[Copy_u8IntNumber] = (Copy_u8Priority | (Copy_u8Group << 3)) << 4 ;

		#elif MNVIC_GROUPS_SUBS == MNVIC_GROUP0_SUB_4
			NVIC_IPR[Copy_u8IntNumber] = (Copy_u8Priority << 4 );

		#endif

	}
	else
	{
		/* ERROR STATE */
	}

}

/*    Peripheral interrupt NVIC Enable   */
void MNVIC_vidEnableInterrupt(u8 Copy_u8IntNumber)
{

	/* Range Check                       */
	if( Copy_u8IntNumber < 32 )
	{
		NVIC_ISER0        = ( 1 << Copy_u8IntNumber);
	}
	else if( Copy_u8IntNumber < 60 )
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISER1        = ( 1 << Copy_u8IntNumber);
	}
	else
	{
		/* ERROR STATE */
	}
}


void MNVIC_vidDisableInterrupt(u8 Copy_u8IntNumber)
{

	/* Range Check                         */
	if( Copy_u8IntNumber < 32 )
	{
		NVIC_ICER0        = ( 1 << Copy_u8IntNumber);
	}
	else if( Copy_u8IntNumber < 60 )
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICER1        = ( 1 << Copy_u8IntNumber);
	}
	else
	{
		/* return error state */
	}
}


void MNVIC_vidSetPendingFlag(u8 Copy_u8IntNumber)
{
	/* Range Check                          */
	if( Copy_u8IntNumber < 32 )
	{
		NVIC_ISPR0        = ( 1 << Copy_u8IntNumber);
	}
	else if( Copy_u8IntNumber < 60 )
	{
		Copy_u8IntNumber -= 32;
		NVIC_ISPR1        = ( 1 << Copy_u8IntNumber);
	}
	else
	{
		/* return error state */
	}
}


void MNVIC_vidClrPendingFlag(u8 Copy_u8IntNumber)
{
	/* Range Check */
	if( Copy_u8IntNumber < 32 )
	{
		NVIC_ICPR0        = ( 1 << Copy_u8IntNumber);
	}
	else if( Copy_u8IntNumber < 60 )
	{
		Copy_u8IntNumber -= 32;
		NVIC_ICPR1        = ( 1 << Copy_u8IntNumber);
	}
	else
	{
		/* return error state */
	}
}


u8   MNVIC_u8GetActiveFlag(u8 Copy_u8IntNumber)
{

	u8 Loc_u8ActiveValue = 0xff;

	/* Range Check                               */
	if( Copy_u8IntNumber < 32 )
	{
		Loc_u8ActiveValue = GET_BIT( NVIC_IABR0 , Copy_u8IntNumber);
	}
	else if( Copy_u8IntNumber < 60 )
	{
		Copy_u8IntNumber -= 32;
		Loc_u8ActiveValue = GET_BIT( NVIC_IABR1 , Copy_u8IntNumber);
	}
	else
	{
		/* return error state */
	}

	return Loc_u8ActiveValue;
}


/*
ErrorStatus  MNVIC_u8GetActiveFlag(u8 Copy_u8IntNumber , u8 Copy_PuActiveValue)
{
	return  ErrorStatus;
}
*/
