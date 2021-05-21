/*
 * LED_Interface.h
 *
 *  Created on: Mar 14, 2021
 *      Author: zas
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


void LEDS_vidInit          (void);
void LEDS_vidSetPattern(u8 value);
void LEDS_vidClearPattern  (void);


void Sensor_vidInit(void);

#endif /* LED_INTERFACE_H_ */
