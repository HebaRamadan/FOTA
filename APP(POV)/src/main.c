/*
 * main.c
 *
 *  Created on: Mar 12, 2021
 *      Author: zas
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "RCC_Interface.h"
#include "NVIC_Interface.h"
#include "Timer_Interface.h"
#include "LED_Interface.h"

#include "DIO_Interface.h"
#include "UART_Interface.h"
#include "SyStick_Interface.h"
#include "ESP_Interface.h"
#include "FPEC_Interface.h"
#include "Parse.h"

#define MAX_COUNTS   ((u16)65535)

void App_vidTimerOverFlow (void);
void App_vidHallSensor    (void);
void App_vidDisplayPattern(void);

u8   POV_DisplayCounter = 0;
u16  OverFlowCounter    = 0;
u32  POV_PatternStep    = 0;


/*
 u8   PovDisplayArray[64]={
						   0x03 , 0x03 , 0xff , 0x03 , 0x03 , 0x01 ,  //T
						   0xff , 0x21 , 0x11 , 0x11 , 0xff , 0x01 ,  //h
						   0x39 , 0x55 , 0x59 , 0x99 , 0x01 , 0x01 ,  //e

						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,

						   0x7d , 0x83 , 0xa3 , 0xa3 , 0x56 , 0x01 ,  //G
						   0x71 , 0x89 , 0x89 , 0x71 , 0x81 , 0x01 ,  //a
						   0xf9 , 0x21 , 0x11 , 0x11 , 0xe1 , 0x01 ,  //n
						   0x4d , 0x93 , 0x93 , 0xfd , 0x01 , 0x01 ,  //g

						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,
						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,
						   0x01 , 0x01 , 0x01 , 0x01
						  };

*/

u8 PovDisplayArray[64]={
						   0xff , 0x13 , 0x13 , 0x13 , 0x13 , 0x01 ,//F
						   0x83 , 0x83 , 0xff , 0x83 , 0x83 , 0x01 ,//I
						   0x7d , 0x83 , 0x93 , 0x93 , 0x75 , 0x01 ,//G
						   0xff , 0x11 , 0x11 , 0x11 , 0xff , 0x01 ,//H
						   0x03 , 0x03 , 0xff , 0x03 , 0x03 , 0x01 ,//T
                           0xff , 0x93 , 0x93 , 0x93 , 0x93 , 0x01 ,//E
						   0xff , 0x13 , 0x33 , 0x53 , 0x8d , 0x01 ,//R
						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,//1s
						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,//1s
						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,//1s
						   0x01 , 0x01 , 0x01 , 0x01
						  };

/*
u8   PovDisplayArray[64]={
						   0x83 , 0x83 , 0xff , 0x83 , 0x83 , 0x01 ,  //I
						   0x03 , 0x03 , 0xff , 0x03 , 0x03 , 0x01 ,  //T
						   0x83 , 0x83 , 0xff , 0x83 , 0x83 , 0x01 ,  //I

						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,

						   0x85 , 0xc3 , 0xa3 , 0x93 , 0x8d , 0x01 ,  //2
						   0x7d , 0xa3 , 0x93 , 0x8b , 0x7d , 0x01 ,  //0
						   0x85 , 0xc3 , 0xa3 , 0x93 , 0x8d , 0x01 ,  //2
						   0x7d , 0xa3 , 0x93 , 0x8b , 0x7d , 0x01 ,  //0

						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,
						   0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 ,
						   0x01 , 0x01 , 0x01 , 0x01
						  };


*/

typedef void (*Function)(u8, u8, u8);
Function setPinValue = (Function)(0x0800083d);//0;
//setPinValue = 0;//*(Function_t*)(0x0800083c);

typedef void (*F2)(u8 *, u8 *);
F2 wifiConnect = (F2)(0x08000ae1);

#define SCB_AIRCR 		*((volatile u32 *)0xE000ED0C)


u16 schCounter = 0;
volatile u8 newVerFlag = 0;
void schedulerBG(void);
void JumbToBootLoader();
void connectToServer();
void sendLinkLength();
void sendMetaDataReq();
u8 getVersion();

extern volatile u8  CheckData[200];
u16 metadata[3];

int main(void)
{
	metadata[0]      =  *((volatile u16 *)(0x08002400));
	metadata[1]      =  *((volatile u16 *)(0x08002402));
	metadata[2]      =  *((volatile u16 *)(0x08002404));

	MRCC_vidInit();
	MRCC_vidEnablePeripheralClock( APB2_BUS , AFIO_RCC   );
	MRCC_vidEnablePeripheralClock( APB1_BUS , TIM4_RCC   );
	MRCC_vidEnablePeripheralClock( APB2_BUS , GPIOC_RCC  );

	MTIMER_vidSetCallBackOVF( &App_vidTimerOverFlow );
	MTIMER_vidSetCallBackICP( &App_vidHallSensor    );
	MTIMER_vidSetCallBackCMP( &App_vidDisplayPattern);


	LEDS_vidInit();
	Sensor_vidInit();

	MRCC_vidEnablePeripheralClock( APB2_BUS , USART1_RCC );

	// for the UART (WIFI module)
	GPIO_vidSetPinDirection(PORTA , PIN9  , GPIO_OUTPUT_2MHZ_AF_PP );
	GPIO_vidSetPinDirection(PORTA , PIN10 , GPIO_INPUT_FLOATING    );

	// for input button to enable app download
	GPIO_vidSetPinDirection(PORTB , PIN0  , GPIO_INPUT_FLOATING    );

	// to indicate available new version
	GPIO_vidSetPinDirection(PORTC , PIN13  , GPIO_OUTPUT_2MHZ_PP    );
	GPIO_vidSetPinValue(PORTC, PIN13, GPIO_u8HIGH);

	MNVIC_vidEnableInterrupt(37);
	MNVIC_vidEnableInterrupt(30);
	MUSART1_vidInit();
	MNVIC_vidInit();
	MSTK_vidInit();
	ESP_vidInit();
	u8 connected = 0;
	do{
//		ESP_vidConnectWiFi((u8 *)"mahmoud" , (u8 *)"Ramadan@1011");
		ESP_vidConnectWiFi((u8 *)"Redmi" , (u8 *)"2c15d518");
//		wifiConnect((u8 *)"Redmi" , (u8 *)"2c15d518");
		for(u8 i=0; i<50 ; i++)
		{
			if(CheckData[i]== 'O' && CheckData[i+1]=='K')
			{
				connected = 1;
				break;
			}
		}
	}while(!connected);
	u8 GrantNewVerDownload = 0;


	MTIMER_vidInit();

	MSTK_vidSetIntervalPeriodic(1000000, schedulerBG);
	while(1)
	{
		GrantNewVerDownload = GPIO_u8GetPinValue(PORTB, PIN0);

		if(newVerFlag)
		{
			if(GrantNewVerDownload)
			{
				JumbToBootLoader();
			}
			GPIO_vidTogglePin(PORTC, PIN13);
		}

		for(volatile u32 c=0; c<1000000; c++);
	}
}

void schedulerBG(void)
{
	u8 verNum = 0;
	switch(schCounter)
	{
	case 0:	connectToServer(); break;
	case 1: sendLinkLength(); break;
	case 3: sendMetaDataReq(); break;
	case 4: verNum = getVersion();
			newVerFlag = verNum; break;
	}
	if(schCounter == 30)
	{
		schCounter = 0;
	}
	else
	{
		schCounter++;
	}

}

void connectToServer()
{
	ESP_vidConnectServerTCP((u8 *)"http://fota.freevar.com" , (u8 *)"80");
}

void sendLinkLength()
{
	MUSART1_vidTransmitString((u8 *)"AT+CIPSEND=42\r\n");
}

void sendMetaDataReq()
{
	ESP_vidClearBuffer();
	MUSART1_vidTransmitString((u8 *)"GET http://fota.freevar.com/MetaData.txt\r\n");
}

u8 getVersion()
{
	u8 i, Flag=0;
	for(i=0; i<50; i++)
	{
		if(CheckData[i] == 'V')
		{
			Flag = 1;
			break;
		}
	}
	u8 result=0;
	u8 receivedVerNum;
	if(Flag == 1)
	{
		receivedVerNum = (CheckData[i+1] - '0')*100 + (CheckData[i+2] - '0') * 10 + (CheckData[i+3] - '0');
		u16 actualVerNum =   metadata[2];

		if(actualVerNum != receivedVerNum)
		{
			result = 1;
		}
	}
	return result;
}

void JumbToBootLoader()
{
	metadata[0] = 1; // request for downloading a new version
	FPEC_vidFlashPageErase(9);
	FPEC_vidFlashWrite(0x08002400, metadata, 3);
	// soft reset
	SCB_AIRCR = 0x05FA0000 | (u32)0x04;
}

void App_vidTimerOverFlow(void)
{
	OverFlowCounter++;
}


void App_vidHallSensor    (void)
{
	/* Clear CNT  */
	MTIMER_vidSetCounterReg(0);

	/* Get CCR2 Register Value To determine number of counts for one revolution */
	u16 CCR2_Val = MTIMER_u16GetCaptuerReg();

	/* Number of counts for one step to display pattern                        */
	POV_PatternStep = ( CCR2_Val + (OverFlowCounter * MAX_COUNTS) ) / 64;

	/* Set CCR1 with counts for one step to display pattern                    */
	MTIMER_vidSetCompareReg((u16)POV_PatternStep);

	/* Reset Overflow Counter         */
	OverFlowCounter    = 0;

	/* Reset Display pattern Counter  */
	POV_DisplayCounter = 0;

}


void App_vidDisplayPattern(void)
{
	/* Calculate number of counts for next pattern   */
	u16 Step = MTIMER_u16GetCounterReg() + (u16)POV_PatternStep ;

	/* Re-initiate CCR1 register for next pattern    */
	MTIMER_vidSetCompareReg( Step );

	/* Check Display Counter                        */
	if( POV_DisplayCounter < 64 )
	{
		/* Display Pattern in Our POV				*/
		LEDS_vidSetPattern( PovDisplayArray[ POV_DisplayCounter ] );
	}
	else
	{
		/* Clear this pattern in POV				*/
		LEDS_vidClearPattern();
	}

	/* Increase Display Counter for next pattern	*/
	POV_DisplayCounter++;

}


