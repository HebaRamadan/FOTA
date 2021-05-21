/*
 * DIO_Program.c
 *
 *  Created on: Jan 23, 2021
 *      Author: Heba Ramadan Taha
 */

#include "Std_types.h"
#include "Bit_math.h"

#include "DIO_Private.h"
#include "DIO_Interface.h"

void GPIO_vidSetPinDirection(u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Mode )
{
	switch(Copy_u8PORT)
	{
		case PORTA:
			if( Copy_u8PIN <= 7)
			{
				(GPIOA -> CRL) &= ~(0b1111      << (Copy_u8PIN * 4));
				(GPIOA -> CRL) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
			}
			else if( Copy_u8PIN <= 15)
			{
				Copy_u8PIN      =  (Copy_u8PIN - 8 );
				(GPIOA -> CRH) &= ~(0b1111      << (Copy_u8PIN * 4));
				(GPIOA -> CRH) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
			}

			break;


		case PORTB:
			if( Copy_u8PIN <= 7)
			{
				(GPIOB -> CRL) &= ~(0b1111      << (Copy_u8PIN * 4));
				(GPIOB -> CRL) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
			}
			else if( Copy_u8PIN <= 15)
			{
				Copy_u8PIN = Copy_u8PIN - 8 ;
				(GPIOB -> CRH) &= ~(0b1111      << (Copy_u8PIN * 4));
				(GPIOB -> CRH) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
			}

			break;


		case PORTC:
			if( Copy_u8PIN <= 7)
			{
				(GPIOC -> CRL) &= ~(0b1111      << (Copy_u8PIN * 4));
				(GPIOC -> CRL) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
			}
			else if( Copy_u8PIN <= 15)
			{
				Copy_u8PIN = Copy_u8PIN - 8 ;
				(GPIOC -> CRH) &= ~(0b1111      << (Copy_u8PIN * 4));
				(GPIOC -> CRH) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
			}

			break;

	}


}


void GPIO_vidSetPinValue (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value)
{
	switch(Copy_u8PORT)
	{
		case PORTA:
			if( Copy_u8Value == GPIO_u8HIGH )
			{
				SET_BIT( GPIOA -> ODR , Copy_u8PIN);
			}
			else if( Copy_u8Value == GPIO_u8LOW )
			{
				CLR_BIT( GPIOA -> ODR , Copy_u8PIN);
			}
			break;


		case PORTB:
			if( Copy_u8Value == GPIO_u8HIGH )
			{
				SET_BIT( GPIOB -> ODR , Copy_u8PIN);
			}
			else if( Copy_u8Value == GPIO_u8LOW )
			{
				CLR_BIT( GPIOB -> ODR , Copy_u8PIN);
			}
			break;


		case PORTC:
			if( Copy_u8Value == GPIO_u8HIGH )
			{
				SET_BIT( GPIOC -> ODR , Copy_u8PIN);
			}
			else if( Copy_u8Value == GPIO_u8LOW )
			{
				CLR_BIT( GPIOC -> ODR , Copy_u8PIN);
			}
			break;
	}

}


u8   GPIO_u8GetPinValue    (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
	u8 Loc_u8ReturnedValue = 0 ;
	switch(Copy_u8PORT)
	{
		case PORTA: Loc_u8ReturnedValue = GET_BIT( GPIOA -> IDR , Copy_u8PIN); break;
		case PORTB: Loc_u8ReturnedValue = GET_BIT( GPIOB -> IDR , Copy_u8PIN); break;
		case PORTC: Loc_u8ReturnedValue = GET_BIT( GPIOC -> IDR , Copy_u8PIN); break;
	}

	return Loc_u8ReturnedValue;
}


void GPIO_vidTogglePin (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
	switch(Copy_u8PORT)
	{
		case PORTA:  TOGGLE_BIT( GPIOA -> ODR , Copy_u8PIN); break;
		case PORTB:  TOGGLE_BIT( GPIOB -> ODR , Copy_u8PIN); break;
		case PORTC:  TOGGLE_BIT( GPIOC -> ODR , Copy_u8PIN); break;
	}

}


void GPIO_vidSetPortDirection(u8 Copy_u8PORT , u8 Copy_u8Position , u8 Copy_u8Mode  )
{
	switch(Copy_u8PORT)
	{
		case PORTA:
			if( Copy_u8Position == PORT_LSB )
			{
				(GPIOA -> CRL)  = 0x00000000 ;

				for(u8 Copy_u8PIN=0; Copy_u8PIN<=7; Copy_u8PIN++)
				{
					(GPIOA -> CRL) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
				}
			}
			else if( Copy_u8Position == PORT_MSB )
			{
				(GPIOA -> CRH)  = 0x00000000 ;

				for(u8 Copy_u8PIN=0; Copy_u8PIN<=7; Copy_u8PIN++)
				{
					(GPIOA -> CRH) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
				}
			}

			break;

		case PORTB:

			if( Copy_u8Position == PORT_LSB )
			{
				(GPIOB -> CRL)  = 0x00000000 ;

				for(u8 Copy_u8PIN=0; Copy_u8PIN<=7; Copy_u8PIN++)
				{
					(GPIOB -> CRL) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
				}
			}
			else if( Copy_u8Position == PORT_MSB )
			{
				(GPIOB -> CRH)  = 0x00000000 ;

				for(u8 Copy_u8PIN=0; Copy_u8PIN<=7; Copy_u8PIN++)
				{
					(GPIOB -> CRH) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
				}
			}
			break;

		case PORTC:

			if( Copy_u8Position == PORT_LSB )
			{
				(GPIOC -> CRL)  = 0x00000000 ;

				for(u8 Copy_u8PIN=0; Copy_u8PIN<=7; Copy_u8PIN++)
				{
					(GPIOC -> CRL) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
				}
			}
			else if( Copy_u8Position == PORT_MSB )
			{
				(GPIOC -> CRH)  = 0x00000000 ;

				for(u8 Copy_u8PIN=0; Copy_u8PIN<=7; Copy_u8PIN++)
				{
					(GPIOC -> CRH) |=  (Copy_u8Mode << (Copy_u8PIN * 4));
				}
			}
			break;

	}
}


void GPIO_vidSetPortValue (u8 Copy_u8PORT , u8 Copy_u8Position , u8 Copy_u8Value )
{

	switch(Copy_u8PORT)
	{
		case PORTA:
			if( Copy_u8Position == PORT_LSB )
			{
				GPIOA -> ODR &= 0xFF00;
				GPIOA -> ODR |= Copy_u8Value ;
			}
			else if( Copy_u8Position == PORT_MSB )
			{
				GPIOA -> ODR  &=  0x00FF;
				GPIOA -> ODR  |= (Copy_u8Value << 8) ;
			}
			break;


		case PORTB:
			if( Copy_u8Position == PORT_LSB )
			{
				GPIOB -> ODR &= 0xFF00;
				GPIOB -> ODR |= Copy_u8Value ;
			}
			else if( Copy_u8Position == PORT_MSB )
			{
				GPIOB -> ODR  &=  0x00FF;
				GPIOB -> ODR  |= (Copy_u8Value << 8) ;
			}
			break;


		case PORTC:
			if( Copy_u8Position == PORT_LSB )
			{
				GPIOC -> ODR &= 0xFF00;
				GPIOC -> ODR |= Copy_u8Value ;
			}
			else if( Copy_u8Position == PORT_MSB )
			{
				GPIOC -> ODR  &=  0x00FF;
				GPIOC -> ODR  |= (Copy_u8Value << 8) ;
			}
			break;
	}

}


void GPIO_vidSetPinValueBSRR (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
	if( Copy_u8PIN < 16 )
	{
		switch( Copy_u8PORT )
		{
			case PORTA :	GPIOA -> BSRR = (1 << Copy_u8PIN);		break;
			case PORTB :	GPIOB -> BSRR = (1 << Copy_u8PIN);		break;
			case PORTC :	GPIOC -> BSRR = (1 << Copy_u8PIN);		break;
		}
	}
	else
	{
		/*****Error*****/
	}
}


void GPIO_vidClrPinValueBSRR (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
	if( Copy_u8PIN < 16 )
	{
		Copy_u8PIN += 16;

		switch( Copy_u8PORT )
		{
			case PORTA :	GPIOA -> BSRR = (1 << Copy_u8PIN);		break;
			case PORTB :	GPIOB -> BSRR = (1 << Copy_u8PIN);		break;
			case PORTC :	GPIOC -> BSRR = (1 << Copy_u8PIN);		break;
		}
	}
	else
	{
		/*****Error*****/
	}
}


void GPIO_vidClrPinValueBRR  (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
	if( Copy_u8PIN < 16 )
	{
		switch( Copy_u8PORT )
		{
			case PORTA :	GPIOA -> BRR = (1 << Copy_u8PIN);		break;
			case PORTB :	GPIOB -> BRR = (1 << Copy_u8PIN);		break;
			case PORTC :	GPIOC -> BRR = (1 << Copy_u8PIN);		break;
		}
	}
	else
	{
		/*****Error*****/
	}
}

