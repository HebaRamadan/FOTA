/*
 * LED_Program.c
 *
 *  Created on: Mar 14, 2021
 *      Author: zas
 */
#include "Std_types.h"
#include "Bit_math.h"

#include "RCC_Interface.h"
#include "DIO_Interface.h"

#include "LED_Interface.h"
#include "LED_Config.h"


void LEDS_vidInit(void)
{
	MRCC_vidEnablePeripheralClock( APB2_BUS , GPIOA_RCC  );
	MRCC_vidEnablePeripheralClock( APB2_BUS , GPIOB_RCC  );


	GPIO_vidSetPinDirection( LED_1 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_2 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_3 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_4 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_5 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_6 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_7 , GPIO_OUTPUT_2MHZ_PP) ;
	GPIO_vidSetPinDirection( LED_8 , GPIO_OUTPUT_2MHZ_PP) ;


}

void Sensor_vidInit(void)
{
	/* Configure Sensor PIN    */
	GPIO_vidSetPinDirection( PORTB , PIN7  , GPIO_INPUT_FLOATING );

}


void LEDS_vidSetPattern(u8 value)
{
	GPIO_vidSetPinValue( LED_1  , GET_BIT( value , 0) );
	GPIO_vidSetPinValue( LED_2  , GET_BIT( value , 1) );
	GPIO_vidSetPinValue( LED_3  , GET_BIT( value , 2) );
	GPIO_vidSetPinValue( LED_4  , GET_BIT( value , 3) );
	GPIO_vidSetPinValue( LED_5  , GET_BIT( value , 4) );
	GPIO_vidSetPinValue( LED_6  , GET_BIT( value , 5) );
	GPIO_vidSetPinValue( LED_7  , GET_BIT( value , 6) );
	GPIO_vidSetPinValue( LED_8  , GET_BIT( value , 7) );

}


void LEDS_vidClearPattern(void)
{
	GPIO_vidSetPinValue( LED_1  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_2  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_3  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_4  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_5  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_6  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_7  , GPIO_u8LOW );
	GPIO_vidSetPinValue( LED_8  , GPIO_u8LOW );

}
