/*
 * ESP_Program.c
 *
 *  Created on: Feb 24, 2021
 *      Author: zas
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "UART_Interface.h"
#include "SyStick_Interface.h"
#include "ESP_Interface.h"
#include "ESP_Config.h"
#include "ESP_Private.h"

volatile u8  RealData[MAX_LINES][MAX_CHARS] ={0};

volatile u8  CheckData[200] ={0};

static volatile u8  Counter = 0;
static volatile u8  Program_Flag     = 0;
static volatile u8  StartRecord_Flag = 0;
static volatile u8  StartData_Flag   = 0;

static volatile u8  Line = 0;
static volatile u8  Char = 0;


void ESP_vidInit(void)
{
	MUSART1_vidSetCallBack(MUSART1_CallBackFunction);

	ESP_vidClearBuffer();
	MUSART1_vidTransmitString( (u8 *)"AT+RST\r\n" );
	MSTK_vidSetBusyWait(2000000);

	do
	{
		ESP_vidClearBuffer();
		MUSART1_vidTransmitString( (u8 *)"ATE0\r\n" );
		MSTK_vidSetBusyWait(2000000);
	}while( (CheckData[Counter - 4] != 'O')  &&  (CheckData[Counter - 3] != 'K') );


	do
	{
		ESP_vidClearBuffer();
		MUSART1_vidTransmitString((u8 *)"AT+CWMODE=1\r\n");
		MSTK_vidSetBusyWait(2000000);
	}while( (CheckData[Counter - 4] != 'O')  &&  (CheckData[Counter - 3] != 'K')  );

}


void ESP_vidConnectWiFi( u8* Copy_u8Name  ,  u8* Copy_u8Pasword    )
{

	ESP_vidClearBuffer();
	MUSART1_vidTransmitString( (u8 *)"AT+CWJAP_CUR=\"" );
	MUSART1_vidTransmitString( (u8 *)Copy_u8Name       );
	MUSART1_vidTransmitString( (u8 *)"\",\""           );
	MUSART1_vidTransmitString( (u8 *)Copy_u8Pasword    );
	MUSART1_vidTransmitString( (u8 *)"\"\r\n"          );
	MSTK_vidSetBusyWait(5000000);
	MSTK_vidSetBusyWait(5000000);
	MSTK_vidSetBusyWait(5000000);


}


void ESP_vidConnectServerTCP ( u8 * Copy_u8ServerIP , u8 * Copy_u8Port )
{

	ESP_vidClearBuffer();
	MUSART1_vidTransmitString((u8 *) "AT+CIPSTART=\"TCP\",\"");
	MUSART1_vidTransmitString((u8 *)  Copy_u8ServerIP        );
	MUSART1_vidTransmitString((u8 *)  "\","                  );
	MUSART1_vidTransmitString((u8 *)  Copy_u8Port            );
	MUSART1_vidTransmitString((u8 *)  "\r\n"                 );
//	MSTK_vidSetBusyWait(500000);


}

void ESP_vidGetMetaDataFromServer()
{
	MUSART1_vidTransmitString((u8 *)"AT+CIPSEND=42\r\n");
//	MSTK_vidSetBusyWait(500000);
	ESP_vidClearBuffer();
	MUSART1_vidTransmitString((u8 *)"GET http://fota.freevar.com/MetaData.txt\r\n");
//	MSTK_vidSetBusyWait(500000);

}

void ESP_vidGetPageFromServer( u8   Copy_u8PageNum  )
{
	if( Copy_u8PageNum < 10 )
	{
		MUSART1_vidTransmitString((u8 *)"AT+CIPSEND=54\r\n");
		MSTK_vidSetBusyWait(500000);
		ESP_vidClearBuffer();

		Program_Flag = 1;
		MUSART1_vidTransmitString((u8 *)"GET http://bootloader2.freevar.com/script.php?page=");
		MUSART1_vidTransmitChar(Copy_u8PageNum + '0');
		MUSART1_vidTransmitString((u8 *) "\r\n");

	}
	else if(Copy_u8PageNum >= 10 && Copy_u8PageNum < 100)
	{
		MUSART1_vidTransmitString((u8 *)"AT+CIPSEND=55\r\n");
		MSTK_vidSetBusyWait(1000000);
		ESP_vidClearBuffer();

		Program_Flag = 1;
		MUSART1_vidTransmitString((u8 *)"GET http://bootloader2.freevar.com/script.php?page=");
		MUSART1_vidTransmitChar((Copy_u8PageNum/10) + '0');
		MUSART1_vidTransmitChar((Copy_u8PageNum%10) + '0');
		MUSART1_vidTransmitString((u8 *) "\r\n");

	}

	MSTK_vidSetBusyWait(5000000);
	MSTK_vidSetBusyWait(5000000);


}


/* Function To Clear Buffer */
void ESP_vidClearBuffer (void)
{

	if(Program_Flag == 0)
	{
		for(u8 i=0; i<Counter; i++)
		{
			CheckData[i] = 0 ;
		}
		Counter = 0;
	}
	else
	{
		for(u8 i=0; i<Line; i++)
		{
			for(u8 j=0; j<MAX_CHARS; j++)
			{
				RealData[i][j]= 0;
			}
		}
		Line = 0;
		Char = 0;
		StartRecord_Flag = 0;
		StartData_Flag   = 0;
		Program_Flag     = 0;
	}

}



void MUSART1_CallBackFunction(void)
{
	u8 data = MUSART1_u8ReceiveChar();
	if( Program_Flag == 0)
	{
		CheckData[Counter] = data;
		Counter++;
	}
	else
	{
		//Check first ':'   "+IPD,Size :"
		if( (StartRecord_Flag == 0)  && ( data == ':') )
		{
			StartRecord_Flag = 1;
		}
		//Check second ':'  "Related To Received Record"
		else if( (StartRecord_Flag == 1)  && ( data == ':') )
		{
			StartData_Flag = 1;
		}

		if( StartData_Flag == 1 && data != '\r')
		{
			//Check 'L' in CLOSED "End Of Page"
			if(data == 'L')
			{
				RealData[Line][Char-1] = '\n';
				StartRecord_Flag = 0;
				StartData_Flag   = 0;
			}
			//Save Allowed Data From record
			else
			{
				RealData[Line][Char] = data;
				Char++;
				//Check The End Of Record
				if(data == '\n')
				{
					StartData_Flag   = 0;
					Char = 0;
					Line++;
				}
			}

		}

		//Check Number Of Lines Still Allowed
		if(Line > MAX_LINES)
		{
			StartRecord_Flag = 0;
			StartData_Flag   = 0;
		}
	}

	//Clear Flag
	MUSART1_vidClearFlag();

}


