/*
 * FPEC_Private.h
 *
 *  Created on: Feb 19, 2021
 *      Author: zas
 */

#ifndef FPEC_PRIVATE_H_
#define FPEC_PRIVATE_H_


typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 AR;
	volatile u32 RESERVED;
	volatile u32 OBR;
	volatile u32 WRPR;
}FPEC_TYPE;

#define FPEC ((FPEC_TYPE*)0x40022000)


#endif /* FPEC_PRIVATE_H_ */
