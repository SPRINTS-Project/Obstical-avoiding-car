/*
 * TIMER_Interface.h
 *
 *  Created on: Apr 3, 2023
 *      Author: Bassel Yasser
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_


/************************************************************************************************/
/*									MACROS														*/
/************************************************************************************************/


/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
typedef enum
{
	TIMER_OK,
	TIMER_NOK,

}enu_timerStatus_t;


/********************************/
/*	 TIMER 0 					*/
/********************************/
typedef enum
{
	OVF_MODE,
	PHASE_CORRECT_PWM_MODE,
	CTC_MODE,
	FAST_PWM_MODE,

	TIMER_MODE_INVALID,

}enu_timerMode_t;



typedef enum
{
	TIMER_NO_CLK_SRC,
	TIMER_PRE_1,
	TIMER_PRE_8,
	TIMER_PRE_64,
	TIMER_PRE_256,
	TIMER_PRE_1024,
	TIMER_EXT_CLK_FALLING,
	TIMER_EXT_CLK_RISING,

	TIMER_PRESCALR_INVALID,


}enu_timerPrescalar_t;



typedef enum
{
	CTC_NORMAL=0,
	CTC_TOGGLE_ON_CMP,
	CTC_CLR_ON_CMP,
	CTC_SET_ON_CMP,
	CTC_INVALID,

}enu_ctcMode_t;

typedef enum
{
	PWM_NORMAL=0,
	PWM_CLR_ON_CMP,
	PWM_SET_ON_CMP,
	PWM_INVALID,

}enu_pwmMode_t;






typedef void (*ptrFunc)(void);

typedef void(*cbf_t)(void);

/************************************************************************************************/
/*									FUNCTIONS PROTOTYPE											*/
/************************************************************************************************/

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: enuTimer2_init
 * description 	: Timer Initialization
 * input param 	: enTimerMode { OVF_MODE, PHASE_CORRECT_PWM_MODE, CTC_MODE, FAST_PWM_MODE}
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t enuTimer2_init (enu_timerMode_t enTimerMode);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: u8Timer2_setPrescallar
 * description 	: Timer Initialization
 * input param 	: Copy_enPrescal { 	TIMER_NO_CLK_SRC,
									TIMER_PRE_1,
									TIMER_PRE_8,
									TIMER_PRE_64,
									TIMER_PRE_256,
									TIMER_PRE_1024,
									TIMER_EXT_CLK_FALLING,
									TIMER_EXT_CLK_RISING,}
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t u8Timer2_setPrescallar(enu_timerPrescalar_t Copy_enPrescal);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidTimer2_OvfIrqEnable
 * description 	: Timer2 Interrupt Enable
 * input param 	: void
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t vidTimer2_OvfIrqEnable(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidTimer2_OvfIrqDisable
 * description 	: Timer2 Interrupt Disable
 * input param 	: void
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t vidTimer2_OvfIrqDisable(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidTimer2_start
 * description 	: Timer2 Start Counting
 * input param 	: void
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t vidTimer2_start(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidTimer2_stop
 * description 	: Timer2 Stop
 * input param 	: void
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t vidTimer2_stop(void);

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: u8Timer2_setTime_ms
 * description 	: Set time in ms
 * input param 	: u32_time_ms
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t u8Timer2_setTime_ms(Uint32_t u32_time_ms);


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: u8Timer2_setPrescallar
 * description 	: Timer Initialization
 * in[1]		: Copy_enPWMmode : {PWM_NORMAL=0, PWM_CLR_ON_CMP, PWM_SET_ON_CMP}
 * in[2] 		: Copy_enPrescal : { TIMER_NO_CLK_SRC,
 *									 TIMER_PRE_1,
 *									 TIMER_PRE_8,
 *									 TIMER_PRE_64,
 *  								 TIMER_PRE_256,
 *									 TIMER_PRE_1024,
 *									 TIMER_EXT_CLK_FALLING,
 *									 TIMER_EXT_CLK_RISING,}
 *
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 **/
enu_timerStatus_t enuFastPWM2_init(enu_pwmMode_t Copy_enPWMmode,enu_timerPrescalar_t Copy_enPrescal);


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidPWM2_Generate
 * description 	: PWM generation
 * input param 	: Copy_u8DutyCycle : Take duty cycle {0 ~ 100}
 * return		: enu_timerStatus_t {TIMER_OK, TIMER_NOK}
 * */
enu_timerStatus_t vidPWM2_Generate(uint8_t Copy_u8DutyCycle);


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidTimer2_setcbf_OVF
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: cbf  : call back function
 * return		: void
 * */
void vidTimer2_setcbf_OVF(cbf_t cbf);


/*
* Author    : Bassel Yasser
* Description : Set_TCNT2 to zero
* @param void
* @return void
*/
void MTIMER_vidResetTCNT(void);

/*
* Author    : Bassel Yasser
* Description : Call the Call Back function in the application after timer did its job
* @param    void
* @return value of TCNT register
*/
uint8_t MTIMER_u8GetTCNT(void);


void MTIMER_vidEnableGlobalInterrupt(void);

/***********************************************************************/



#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
