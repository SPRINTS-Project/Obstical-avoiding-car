/*
 * ultrasonic.h
 *
 *  Created on: May 11, 2023
 *      Author: hp
 */
/************************************************************************************************/
/*									File Guard										*/
/************************************************************************************************/
#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_



/************************************************************************************************/
/*									User Defined types									*/
/************************************************************************************************/
typedef void(*HULTRASONIC_ptr_func)(void);




/************************************************************************************************/
/*									Function Protoyypes											*/
/************************************************************************************************/
/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidInit
 * description 	: Set Echo pin as input
 * 				  Set trig pin as output
 * 				  Initialize external interrupt
 *				  Initialize timer2
 * Param		: void
 * return		: void
 * */
void HULTRASONIC_vidInit(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidTrigger
 * description 	: Sending pulse
 * input param 	: void
 * return		: void
 * */
//static void HULTRASONIC_vidTrigger(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_u8Read
 * description 	: Read distance from ultrasonic sensor
 * input param 	: void
 * return		: Uint8_t (Distance)
 * */
float64_t HULTRASONIC_u8Read(void);


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidCBF_TIM
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
void HULTRASONIC_vidCBF_TIM(HULTRASONIC_ptr_func TIMER_ptrFunction2);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidCBF_INT
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
void HULTRASONIC_vidCBF_INT(HULTRASONIC_ptr_func EXTINT_ptrFunction2);


void HULTRASONIC_vidInterruptEnable(void);
void HULTRASONIC_vidInterruptDisable(void);

#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
/************************************************************************************************/
/*									END									*/
/************************************************************************************************/
