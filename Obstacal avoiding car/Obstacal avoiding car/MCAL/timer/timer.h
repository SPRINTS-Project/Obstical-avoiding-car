/*
 * timer.h
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "timer_types.h"


/*
 * Description:  Function to Initialize Timer Driver
 *                 - Working in Interrupt Mode
 *                 - Choose Timer initial value
 *                 - Choose Timer_ID (Timer0, Timer1, Timer2)
 *                 - Choose Timer_Mode to be normal mode
 *                 
 * 
 *@param A Reference of the Timer configuration
 * @return status of the function
 * TIMER_E_OK :the function done successfully
 * TIMER_E_NOT_OK :the function has issues performing the function
 */
u8_en_timerErrorsType TIMER_init (st_timerConfigType* st_config);

/*
* Description : TIMER START COUNTING BY CONFIGURE THE TIMER CLOCK
* @param A Reference of the Timer configuration
* @return Std_ReturnType: status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_start (st_timerConfigType* st_config);

/*
* Description :Function to Halt the timer (stop)
* @param the  timer type 
* @return status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_stop (u8_en_timerNumberType u8_a_timerNum);

/*

* Description :Function to make the timer to start again from the initial value (reset)

* @param A Reference of the Timer configuration
* @return status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_reset (st_timerConfigType* st_config);

/*
* Description : Call the Call Back function in the application after timer did its job
* @param A pointer to function & the  timer type
* @return status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_setCallBack( void(*a_timerCallBack)(void), u8_en_timerNumberType u8_a_timerNum );




/********************************************************************************************
 * 								Edit by Bassel Yasser Mahmoud
*********************************************************************************************/


#endif	/*	TIMER_H	*/