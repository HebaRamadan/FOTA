/*
 * DIO_Interface.h
 *
 *  Created on: Jan 23, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#define GPIO_u8LOW     0
#define GPIO_u8HIGH    1


#define PORTA          0
#define PORTB          1
#define PORTC          2


#define PORT_LSB       0
#define PORT_MSB       1


#define PIN0           0
#define PIN1           1
#define PIN2           2
#define PIN3           3
#define PIN4           4
#define PIN5           5
#define PIN6           6
#define PIN7           7
#define PIN8           8
#define PIN9           9
#define PIN10          10
#define PIN11          11
#define PIN12          12
#define PIN13          13
#define PIN14          14
#define PIN15          15


/* MODES OF INPUT PIN            */
#define GPIO_INPUT_ANALOG            0b0000
#define GPIO_INPUT_FLOATING          0b0100
#define GPIO_INPUT_PULL_UD           0b1000


/* MODES OF OUTPUT PIN AT SPEED 10MHZ  */
#define GPIO_OUTPUT_10MHZ_PP         0b0001
#define GPIO_OUTPUT_10MHZ_OD         0b0101
#define GPIO_OUTPUT_10MHZ_AF_PP      0b1001
#define GPIO_OUTPUT_10MHZ_AF_OD      0b1101


/* MODES OF OUTPUT PIN AT SPEED 2MHZ  */
#define GPIO_OUTPUT_2MHZ_PP          0b0010
#define GPIO_OUTPUT_2MHZ_OD          0b0110
#define GPIO_OUTPUT_2MHZ_AF_PP       0b1010
#define GPIO_OUTPUT_2MHZ_AF_OD       0b1110


/* MODES OF OUTPUT PIN AT SPEED 50MHZ  */
#define GPIO_OUTPUT_50MHZ_PP         0b0011
#define GPIO_OUTPUT_50MHZ_OD         0b0111
#define GPIO_OUTPUT_50MHZ_AF_PP      0b1011
#define GPIO_OUTPUT_50MHZ_AF_OD      0b1111


void GPIO_vidSetPinDirection (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Mode );
void GPIO_vidSetPinValue     (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Value);

void GPIO_vidSetPortDirection(u8 Copy_u8PORT , u8 Copy_u8Position , u8 Copy_u8Mode  );
void GPIO_vidSetPortValue    (u8 Copy_u8PORT , u8 Copy_u8Position , u8 Copy_u8Value );

void GPIO_vidSetPinValueBSRR (u8 Copy_u8PORT , u8 Copy_u8PIN );
void GPIO_vidClrPinValueBSRR (u8 Copy_u8PORT , u8 Copy_u8PIN );
void GPIO_vidClrPinValueBRR  (u8 Copy_u8PORT , u8 Copy_u8PIN );

u8   GPIO_u8GetPinValue      (u8 Copy_u8PORT , u8 Copy_u8PIN );
void GPIO_vidTogglePin       (u8 Copy_u8PORT , u8 Copy_u8PIN );




#endif /* DIO_INTERFACE_H_ */
