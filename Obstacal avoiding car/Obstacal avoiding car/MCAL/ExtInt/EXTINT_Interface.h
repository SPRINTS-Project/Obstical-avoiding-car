/*
 * EXTINT_Interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_EXTINT_EXTINT_INTERFACE_H_
#define MCAL_EXTINT_EXTINT_INTERFACE_H_


/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/

#define E_INT_OK		0
#define E_INT_NOK		4

/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
typedef enum
{
	INT_0 = 0,
	INT_1,
	INT_2,
	INT_TYPE_INVALID,

}en_int_type_t;

typedef enum
{
	LOW_LEVEL = 0,
	ANY_LOGICAL,
	FALL_EDGE,
	RISE_EDGE,
	SENS_CONTROL_INVALID,
}en_sns_ctrl_t;


typedef void(*ptr_func)(void);

/************************************************************************************************/
/*									FUNCTION_PROTOTYPE											*/
/************************************************************************************************/

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidExtInt_init
 * description 	: func to write integer number on lcd
 * in[1]	 	: enExtint : Interrupt type [INT0, INT1. INT2]
 * in[2]		: snsCtrl  : Sense Control {ANY_LOGICAL, FALL_EDGE, RISE_EDGE}
 * return		: Uint8_t : return error Status  {E_INT_OK ,E_INT_NOK }
 * */
uint8_t vidExtInt_init(en_int_type_t, en_sns_ctrl_t);


void MEXTINT_vidCallBackFuncInt0(ptr_func funcCopy);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidCallBackFunc
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
void MEXTINT_vidCallBackFunc(ptr_func funcCopy);


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidCallBackFuncInt1
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
void MEXTINT_vidCallBackFuncInt1(ptr_func funcCopy);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidWaitFlag
 * description 	: it INT is disabled , this function pollying on flag
 * input param 	: void
 * return		: void
 * */
void MEXTINT_vidWaitFlag(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidDisableInterrupt
 * description 	: Disable EXTINT
 * input param 	: void
 * return		: void
 * */
void MEXTINT_vidDisableInterrupt(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidEnableInterrupt
 * description 	: ENABLE extint
 * input param 	: void
 * return		: void
 * */
void MEXTINT_vidEnableInterrupt(void);



void MEXTINT2_vidDisableInterrupt(void);
void MEXTINT2_vidEnableInterrupt(void);

#endif /* 04_MCAL_EXTINT_EXTINT_INTERFACE_H_ */
