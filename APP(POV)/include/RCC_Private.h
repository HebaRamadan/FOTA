/*
 * RCC_Private.h
 *
 *  Created on: Jan 17, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef RCC_PRIVATE_H_
#define RCC_PRIVATE_H_

/***************************************************************
#define RCC_BASE_ADD     (0X40021000)
#define RCC_CR           (*(volatile u32 *)(RCC_BASE_ADD + 0x00))
#define RCC_CFGR         (*(volatile u32 *)(RCC_BASE_ADD + 0x04))
#define RCC_CIR          (*(volatile u32 *)(RCC_BASE_ADD + 0x08))
#define RCC_APB2RSTR     (*(volatile u32 *)(RCC_BASE_ADD + 0x0C))
#define RCC_APB1RSTR     (*(volatile u32 *)(RCC_BASE_ADD + 0x10))
#define RCC_AHBENR       (*(volatile u32 *)(RCC_BASE_ADD + 0x14))
#define RCC_APB2ENR      (*(volatile u32 *)(RCC_BASE_ADD + 0x18))
#define RCC_APB1ENR      (*(volatile u32 *)(RCC_BASE_ADD + 0x1C))
#define RCC_BDCR         (*(volatile u32 *)(RCC_BASE_ADD + 0x20))
#define RCC_CSR          (*(volatile u32 *)(RCC_BASE_ADD + 0x24))
****************************************************************/

typedef struct{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC;

// M is Refer To MCal

#define MRCC ((volatile RCC *)0x40021000)

#endif /* RCC_PRIVATE_H_ */
