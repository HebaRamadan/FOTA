/*
 * SyStick_Private.h
 *
 *  Created on: Feb 2, 2021
 *      Author: Heba Ramadan Taha
 */

#ifndef SYSTICK_PRIVATE_H_
#define SYSTICK_PRIVATE_H_




#define BASE_ADDRESS    0xE000E010

#define STK_CTRL       *((volatile u32*)(BASE_ADDRESS + 0x00))
#define STK_LOAD       *((volatile u32*)(BASE_ADDRESS + 0x04))
#define STK_VALUE      *((volatile u32*)(BASE_ADDRESS + 0x08))

#endif /* SYSTICK_PRIVATE_H_ */
