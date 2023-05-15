/*
 * timer_manager.h
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include "../../MCAL/timer/timer_types.h"


/*
 * Description:  Function to Initialize Timer Driver & Call the Call Back function in the application after timer did its job
 *                 - Working in Interrupt Mode
 *                 - Choose Timer initial value
 *                 - Choose Timer_ID (Timer0, Timer1, Timer2)
 *                 - Choose Timer_Mode to be normal mode
 *				   - Set the call-back function
 *                 
 * 
 *@param A Reference of the Timer configuration
 * @return status of the function
 * TIMER_E_OK :the function done successfully
 * TIMER_E_NOT_OK :the function has issues performing the function
 */
u8_en_timerErrorsType TIMER_Manager_init (st_timerConfigType* st_config);
/*
* Description : TIMER START COUNTING BY CONFIGURE THE TIMER CLOCK
* @param A Reference of the Timer configuration
* @return Std_ReturnType: status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_Manager_start (st_timerConfigType* st_config);
/*
* Description :Function to Halt the timer (stop)
* @param the  timer type
* @return status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_Manager_stop (u8_en_timerNumberType u8_en_timerNum);
/*

* Description :Function to make the timer to start again from  initial value(reset)

* @param A Reference of the Timer configuration
* @return status of the function
* TIMER_E_OK :the function done successfully
* TIMER_E_NOT_OK :the function has issues performing the function
*/
u8_en_timerErrorsType TIMER_Manager_reset (st_timerConfigType* st_config);

#endif /*	TIMER_MANAGER_H_	*/