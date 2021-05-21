/*
 * FPEC_Program.c
 *
 *  Created on: Feb 19, 2021
 *      Author: zas
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "FPEC_Interface.h"

u16 Data[100] = {0};
u32 Address= 0x08000000;

u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;
	}

	else
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}

u8 checksum(u8* record, u8 length)
{
	u16 Loc_u8Sum = 0;
	for(u8 i=0; i<length; i++)
	{
		Loc_u8Sum += record[i];
	}
	return (u8)Loc_u8Sum;
}

u8 ParseData(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;

	u8 oneRecord[22];

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	oneRecord[0]=CC;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & 0xFFFF0000;
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

	oneRecord[1]= (DataDigit0<<4) | (DataDigit1);
	oneRecord[2]= (DataDigit2<<4) | (DataDigit3);

	DataDigit0 = AsciToHex (Copy_u8BufData[7]);
	DataDigit1 = AsciToHex (Copy_u8BufData[8]);
	oneRecord[3] = (DataDigit0<<4) | (DataDigit1);

	for (i=0;i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;

		oneRecord[4+i*2]= (DataDigit0<<4) | (DataDigit1);
		oneRecord[5+i*2]= (DataDigit2<<4) | (DataDigit3);
	}

	if(CC % 2 == 1)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		oneRecord[4+i*2] = (DataDigit0<<4) | (DataDigit1);

		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+11 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+12]);
		oneRecord[5+i*2] = (DataDigit0<<4) | (DataDigit1);
	}
	else
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		oneRecord[4+i*2] = (DataDigit0<<4) | (DataDigit1);
	}


	if(checksum(oneRecord, CC+5) == 0)
	{
		FPEC_vidFlashWrite(Address,Data,CC/2);
		return 0;
	}

//	FPEC_vidFlashWrite(Address,Data,CC/2);
	return 2;
}

void ParseUpperAddress(u8* Copy_u8BufData)
{
//	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
//
//	/* Get Address */
//	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
//	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
//	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
//	DataDigit3 = AsciToHex (Copy_u8BufData[6]);
//
//	/* Clear Low Part of Address */
//	Address = Address & (u32)0x0000FFFF;
//	Address = Address | (u32)((u32)(DataDigit3 << 28) | (u32)(DataDigit2 << 24) | (u32)(DataDigit1 << 20) | (u32)(DataDigit0 << 16));
}

u8 Parser_vidParseRecord(u8* Copy_u8BufData)
{
	u8 Loc_u8Return  = 0;
	switch (Copy_u8BufData[8])
	{
	case '0': Loc_u8Return = ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); break;
	case '1': Loc_u8Return = 1;    break;
	}

	return Loc_u8Return;
}
