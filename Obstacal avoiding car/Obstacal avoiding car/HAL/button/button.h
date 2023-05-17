/*
 * button.h
 *
 * Created: 4/13/2023 11:44:07 PM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_


#include "button_types.h"

void BUTTON_mainTask(void);
u8_en_btnStateType BUTTON_init(uint8_t u8_a_port , uint8_t u8_a_pin, u8_en_btnIdType en_btnId);
u8_en_btnStateType BUTTON_getState(u8_en_btnIdType en_btnId);


#endif /* BUTTON_H_ */