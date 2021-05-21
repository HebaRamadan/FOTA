/*
 * NVIC_Private.h
 *
 *  Created on: Jan 26, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef NVIC_PRIVATE_H_
#define NVIC_PRIVATE_H_

#define  NVIC_BASE_ADD 0xE000E100

#define  NVIC_ISER0    *((u32 *)(NVIC_BASE_ADD + 0x000))
#define  NVIC_ISER1    *((u32 *)(NVIC_BASE_ADD + 0x004))

#define  NVIC_ICER0    *((u32 *)(NVIC_BASE_ADD + 0x080))
#define  NVIC_ICER1    *((u32 *)(NVIC_BASE_ADD + 0x084))


#define  NVIC_ISPR0    *((u32 *)(NVIC_BASE_ADD + 0x100))
#define  NVIC_ISPR1    *((u32 *)(NVIC_BASE_ADD + 0x104))


#define  NVIC_ICPR0    *((u32 *)(NVIC_BASE_ADD + 0x180))
#define  NVIC_ICPR1    *((u32 *)(NVIC_BASE_ADD + 0x184))


/****Read Only****/
#define  NVIC_IABR0    *((volatile u32 *)(NVIC_BASE_ADD + 0x200))
#define  NVIC_IABR1    *((volatile u32 *)(NVIC_BASE_ADD + 0x204))


#define  NVIC_IPR        ((u8 *)(NVIC_BASE_ADD + 0x300))


#define MNVIC_GROUP4_SUB_0   0x05FA0300
#define MNVIC_GROUP3_SUB_1   0x05FA0400
#define MNVIC_GROUP2_SUB_2   0x05FA0500
#define MNVIC_GROUP1_SUB_3   0x05FA0600
#define MNVIC_GROUP0_SUB_4   0x05FA0700

#endif /* NVIC_PRIVATE_H_ */
