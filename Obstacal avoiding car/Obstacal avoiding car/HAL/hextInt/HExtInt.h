/*
 * HExtInt.h
 *
 *  Created on: Apr 5, 2023
 *      Author: hp
 */

#ifndef HAL_HEXTINT_HEXTINT_H_
#define HAL_HEXTINT_HEXTINT_H_

#include "../../MCAL/ExtInt/EXTINT_Interface.h"



#define HEXTINT_INT0		0
#define HEXTINT_INT1		1
#define HEXTINT_INT2		2


typedef enum
{
	HEXTINT_OK = 0,
	HEXTINT_NOK = 5

}enu_HExtIntError_t;



//typedef void(*ptr_func)(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enInit
 * description 	: External Interrupt Initialization
 * in[1]	 	: enExtint : Interrupt type [INT0, INT1. INT2]
 * in[2]		: snsCtrl  : Sense Control {ANY_LOGICAL, FALL_EDGE, RISE_EDGE}
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enInit(en_int_type_t enExtint, en_sns_ctrl_t snsCtrl);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enCBF
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enCBFInt0(ptr_func pFunc);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HExtInt_enCBFInt1
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
enu_HExtIntError_t HExtInt_enCBFInt1(ptr_func pFunc);


void HExtInt0_enIntDisable(void);
void HExtInt0_enIntEnable(void);

#endif /* HAL_HEXTINT_HEXTINT_H_ */
