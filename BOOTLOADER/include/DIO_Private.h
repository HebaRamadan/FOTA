/*
 * DIO_Private.h
 *
 *  Created on: Jan 23, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

typedef struct
{
	volatile u32 CRL   ;
	volatile u32 CRH   ;
	volatile u32 IDR   ;
	volatile u32 ODR   ;
	volatile u32 BSRR  ;
	volatile u32 BRR   ;
	volatile u32 LCKR  ;

}PORTx_Reg;

#define GPIOA     ((PORTx_Reg *)0x40010800)
#define GPIOB     ((PORTx_Reg *)0x40010C00)
#define GPIOC     ((PORTx_Reg *)0x40011000)




#endif /* DIO_PRIVATE_H_ */
