/*
 * FPEC_Program.c
 *
 *  Created on: Feb 19, 2021
 *      Author: zas
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "FPEC_Interface.h"
#include "FPEC_Private.h"
#include "FPEC_Config.h"

void FPEC_vidEraseAppArea(void)
{
	u8 i;

	for (i=8;i<64;i++)
	{
		FPEC_vidFlashPageErase(i);
	}
}

void FPEC_vidFlashPageErase(u8 Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,7) == 1)
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}

	/* Page Erase Operation */
	SET_BIT(FPEC->CR,1);

	/* Write Page address */
	FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,6);

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,5);
	CLR_BIT(FPEC->CR,1);
}

void FPEC_vidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 i;
	volatile u16 Temp;

	while (GET_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( /* FPEC_CR->BitAccess.LOCK == 1 */ GET_BIT(FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}


	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,0);

		/* Half word operation */

		Temp = Copy_u16Data[i];
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,0) == 1);

		/* EOP */
		SET_BIT(FPEC->SR,5);
		CLR_BIT(FPEC->CR,0);
	}

}
