/*
 * ultrasonic.c
 *
 *  Created on: May 15, 2023
 *      Author: hp
 */
/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include <util/delay.h>
#include "../../MCAL/dio/dio.h"
// #include "../../MCAL/Timer/TIMER_Interface.h"
#include "../../MCAL/timer/timer.h"
#include "../../MCAL/ExtInt/EXTINT_Interface.h"
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "ultrasonic.h"
#include "ultrasonic_cfg.h"




/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/
volatile uint32_t g_v_u16_ovfCounts = 0, g_v_u16_ovf;
volatile uint8_t g_v_u8_flag = 0;
volatile uint8_t g_v_u8_cap;

static float64_t global_f64distance;
static uint32_t global_u32Ticks;


extern st_timerConfigType st_timer2Config;
/************************************************************************************************/
/*									Functions for CBF										*/
/************************************************************************************************/
void HULTRASONIC_vidTimerCBF(void)
{
	g_v_u16_ovfCounts++;
}

void HULTRASONIC_vidSigCalc(void)
{
	if (g_v_u8_flag == 0)
	{
		MTIMER_vidResetTCNT();
		g_v_u16_ovfCounts = 0;
		(void) vidExtInt_init(INT_0 , FALL_EDGE);
		g_v_u8_flag = 1;
	}
	else if (g_v_u8_flag == 1)
	{
		(void) TIMER_stop (&st_timer2Config);
		g_v_u8_cap = MTIMER_u8GetTCNT();
		g_v_u16_ovf = g_v_u16_ovfCounts;
		g_v_u8_flag = 2;
		(void) vidTimer2_OvfIrqDisable();
		MEXTINT_vidDisableInterrupt();
	}
}


/************************************************************************************************/
/*									Function Implementation										*/
/************************************************************************************************/
/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidInit
 * description 	: - Set SIG pin as output and Pull down
 * 				  - Set trig pin as output
 * 				  - Initialize external interrupt
 * 				  - Initialize Timer
 * Param		: void
 * return		: void
 * */
void HULTRASONIC_vidInit(void)
{
	(void) DIO_init(TRIG_PIN, STD_OUTPUT);
	(void) DIO_init(SIG_PIN, STD_INPUT);
	(void) DIO_writePIN(SIG_PIN, STD_LOW);

	(void) vidExtInt_init(INT_0 , RISE_EDGE);

	(void) TIMER_init(&st_timer2Config);
	(void) TIMER_start(&st_timer2Config);

}

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidTrigger
 * description 	: Sending pulse
 * input param 	: void
 * return		: void
 * */
static void HULTRASONIC_vidTrigger(void)
{
	(void) DIO_writePIN(TRIG_PIN, STD_HIGH);
	_delay_us(10);
	(void) DIO_writePIN(TRIG_PIN, STD_LOW);
}

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_u8Read
 * description 	: Read distance from ultrasonic sensor
 * input param 	: void
 * return		: float64_t (Distance)
 * */
float64_t HULTRASONIC_u8Read(void)
{
	HULTRASONIC_vidTrigger();

	if (g_v_u8_flag == 2)
	{
		/*********************  reset global flag    *******************************************/
		g_v_u8_flag = 0;
		/*********************  Calculate total ticks   *******************************************/
		global_u32Ticks = g_v_u8_cap + (256*g_v_u16_ovf);

		/* sound velocity = 34300 cm/sec
			 tick time = 1/(F_CPU) as 1 is prescalar -> tick_time = 62.5 ns -> 62.5e-9 sec
			 total_time = t_ticks * 62.5e-9 sec
			 distance = (sound_velocity * total_time)/2 -> (34300 * total_time)/2 -> (17150 * t_ticks * 62.5e-9) -> (t_ticks / 932.95)
		 */
		global_f64distance = (float64_t)global_u32Ticks / 932.95;

		/*********************  reset global ovf counts    *******************************************/
		g_v_u16_ovf = 0;
		g_v_u16_ovfCounts = 0;
		/*********************  Set EXTINT sense Rising Edge    *******************************************/
		(void) vidExtInt_init(INT_0 , RISE_EDGE);

		/*********************  Start Timer    *******************************************/
		(void) TIMER_start(&st_timer2Config);

		/*********************  Enable EXTITNT and Timer interrupts    *******************************************/
		(void) vidTimer2_OvfIrqEnable();
		MEXTINT_vidEnableInterrupt();

	}
	return global_f64distance;
}


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidCBF_TIM
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: void
 * return		: void
 * */
void HULTRASONIC_vidCBF_TIM(HULTRASONIC_ptr_func TIMER_ptrFunction2)
{
	(void) TIMER_setCallBack(TIMER_ptrFunction2, st_timer2Config.u8_timerNum);
}


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidCBF_INT
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: void
 * return		: void
 * */
void HULTRASONIC_vidCBF_INT(HULTRASONIC_ptr_func EXTINT_ptrFunction2)
{
	MEXTINT_vidCallBackFunc(EXTINT_ptrFunction2);
}


/************************************************************************************************/
/*									END															*/
/************************************************************************************************/

