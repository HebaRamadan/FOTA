/*
 * FPEC_Interface.h
 *
 *  Created on: Feb 19, 2021
 *      Author: zas
 */

#ifndef FPEC_INTERFACE_H_
#define FPEC_INTERFACE_H_

void FPEC_vidEraseAppArea(void);

void FPEC_vidFlashPageErase(u8 Copy_u8PageNumber);

void FPEC_vidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length);



#endif /* FPEC_INTERFACE_H_ */
