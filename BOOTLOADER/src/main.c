/*
 * main.c
 *
 *  Created on: Feb 24, 2021
 *      Author: zas
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "RCC_Interface.h"
#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "NVIC_Interface.h"
#include "SyStick_Interface.h"
#include "ESP_Interface.h"
#include "FPEC_Interface.h"
#include "Parse.h"

#define MAX_SIZE           (u16)55296
#define APP_REQ_FLAG        0x08002400
#define VALID_APP_FLAG      0x08002402
#define VALID_VERSION       0x08002404

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08002800;

	addr_to_call = *(Function_t*)(0x08002804);
	addr_to_call();
}


extern volatile u8  RealData[MAX_LINES][MAX_CHARS];
extern volatile u16 Size;
extern volatile u8  Version;
static volatile u8  FinishFlash = 0;


int main(void)
{

	u16 Loc_u16ValidApp      =  *((u16 *)VALID_APP_FLAG);
	u16 Loc_u16AppReq        =  *((u16 *)APP_REQ_FLAG  );
	u16 Loc_u16ValidVersion  =  *((u16 *)VALID_VERSION );

	if( (Loc_u16ValidApp) != 1 || (Loc_u16AppReq == 1) )
	{
		u8  Loc_u8PageNumber = 0;
		u8  Loc_u8PareArray[50] ;
		u16 DataInFlash[3];

		MRCC_vidInit();
		MRCC_vidEnablePeripheralClock( APB2_BUS , GPIOA_RCC  );
		MRCC_vidEnablePeripheralClock( APB2_BUS , USART1_RCC );


		GPIO_vidSetPinDirection(PORTA , PIN9  , GPIO_OUTPUT_2MHZ_AF_PP );
		GPIO_vidSetPinDirection(PORTA , PIN10 , GPIO_INPUT_FLOATING    );

		GPIO_vidSetPinDirection(PORTA , PIN0  , GPIO_OUTPUT_2MHZ_PP    );

		MNVIC_vidSetPriority( 37  , 1 , 0 );
		MNVIC_vidEnableInterrupt(37);

		MUSART1_vidInit();
		MNVIC_vidInit();
		MSTK_vidInit();

		/* Initiate ESP Module */
		ESP_vidInit();
		/* Connect WIFI        */
//		ESP_vidConnectWiFi((u8 *)"mahmoud" , (u8 *)"Ramadan@1011");
		ESP_vidConnectWiFi((u8 *)"OPPO A37fw" , (u8 *)"12345678");
		ESP_vidConnectServerTCP((u8 *)"http://fota.freevar.com" , (u8 *)"80");
		ESP_vidControlUploading(1);
		ESP_vidGetMetaData();

		DataInFlash[0] = 0;
		DataInFlash[1] = 1;
		DataInFlash[2] = Version;

		if( Size <= MAX_SIZE )
		{
			FPEC_vidEraseAppArea();

			while( FinishFlash == 0 )
			{

				ESP_vidConnectServerTCP((u8 *)"http://fota.freevar.com" , (u8 *)"80");
				ESP_vidGetPageFromServer(Loc_u8PageNumber);

				for(u8 i=0; i<MAX_LINES; i++)
				{
					u8 CHARS = 0 ;

					while( RealData[i][CHARS] != '\n' )
					{
						Loc_u8PareArray[CHARS] = RealData[i][CHARS];
						CHARS++;
					}

					FinishFlash = Parser_vidParseRecord(Loc_u8PareArray);

					if( FinishFlash == 1 || FinishFlash ==  2)
					{
						break;
					}
				}
				if(FinishFlash == 2)
				{
					// here the check sum of some record is wrong
					// so don't increment the page number, and repeat the loop again
					FinishFlash = 0;
				}
				else
				{
					Loc_u8PageNumber++;
				}
				ESP_vidClearBuffer();
			}
			FPEC_vidFlashPageErase(9);
			FPEC_vidFlashWrite( APP_REQ_FLAG , DataInFlash , 3);
		}
		else if(Loc_u16ValidApp == 1)
		{
			FPEC_vidFlashPageErase(9);
			FPEC_vidFlashWrite( APP_REQ_FLAG , DataInFlash , 3);
			ESP_vidConnectServerTCP((u8 *)"http://fota.freevar.com" , (u8 *)"80");
			ESP_vidControlUploading(0);
			func();
		}
		else
		{
			GPIO_vidSetPinValue(PORTA , PIN0 , GPIO_u8HIGH);
			ESP_vidConnectServerTCP((u8 *)"http://fota.freevar.com" , (u8 *)"80");
			ESP_vidControlUploading(0);
			while(1);
		}

		ESP_vidConnectServerTCP((u8 *)"http://fota.freevar.com" , (u8 *)"80");
		ESP_vidControlUploading(0);

	}

	func();


	return 0;
}



/*typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}*/
