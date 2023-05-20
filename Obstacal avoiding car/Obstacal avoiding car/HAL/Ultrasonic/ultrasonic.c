/*
 * ultrasonic.c
 *
 *  Created on: May 15, 2023
 *      Author: hp
 */
/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include "../../MCAL/dio/dio.h"
#include "../../MCAL/timer/timer2_Interface.h"
#include "../../MCAL/ExtInt/EXTINT_Interface.h"
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "ultrasonic.h"
#include "ultrasonic_cfg.h"




/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/
volatile Uint32_t g_v_u16_ovfCounts = 0, g_v_u16_ovf;
volatile uint8_t g_v_u8_flag = 0;
volatile uint8_t g_v_u8_cap;

static float64_t global_f64distance;
static Uint32_t global_u32Ticks;


/************************************************************************************************/
/*									Functions for CBF										*/
/************************************************************************************************/
/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidTimerCBF
 * description 	: OVF counter
 * input param 	: void
 * return		: void
 * */
void HULTRASONIC_vidTimerCBF(void)
{
	g_v_u16_ovfCounts++;
}


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: HULTRASONIC_vidSigCalc
 * description 	: calculate Distance from Ultrasonic sensor
 * input param 	: void
 * return		: void
 * */
void HULTRASONIC_vidSigCalc(void)
{
	if (g_v_u8_flag == 0)
	{
		MTIMER_vidResetTCNT();
		(void) vidExtInt_init(INT_2 , FALL_EDGE);
		g_v_u8_flag = 1;
		g_v_u16_ovfCounts = 0;
		(void) vidTimer2_start();	
	}
	else if (g_v_u8_flag == 1)
	{
		vidTimer2_stop();
		g_v_u8_cap = MTIMER_u8GetTCNT();
		g_v_u16_ovf = g_v_u16_ovfCounts;
	
		/*********************  Calculate total ticks   *******************************************/
		global_u32Ticks = g_v_u8_cap + (256*g_v_u16_ovf);

		/* sound velocity = 34300 cm/sec
			 tick time = 1/(F_CPU) as 1 is prescalar -> tick_time = 62.5 ns -> 62.5e-9 sec
			 total_time = t_ticks * 62.5e-9 sec
			 distance = (sound_velocity * total_time)/2 -> (343000 * total_time)/2 -> (17150 * t_ticks * 62.5e-9) -> (t_ticks / 932.95)
		 */		
		global_f64distance = (float64_t)global_u32Ticks / 932.95;

		/*********************  reset global ovf counts and flag    *******************************************/
		g_v_u16_ovf = 0; g_v_u16_ovfCounts = 0;  g_v_u8_flag = 0;

		/*********************  Set EXTINT sense Rising Edge    *******************************************/
		(void) vidExtInt_init(INT_2 , RISE_EDGE);

	}
}


/************************************************************************************************/
/*									Function Implementation										*/
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
void HULTRASONIC_vidInit(void)
{
	(void) DIO_init(TRIG_PIN, STD_OUTPUT);
	(void) DIO_init(SIG_PIN, STD_INPUT);
	(void) DIO_writePIN(SIG_PIN, STD_LOW);

	(void) vidExtInt_init(INT_2 , RISE_EDGE);

	(void) enuTimer2_init (OVF_MODE);
	(void) u8Timer2_setPrescallar(TIMER_PRE_1);
}

void HULTRASONIC_vidInterruptEnable(void)
{
	(void) vidTimer2_OvfIrqEnable();
	MEXTINT2_vidEnableInterrupt();
	MTIMER_vidEnableGlobalInterrupt();
}

void HULTRASONIC_vidInterruptDisable(void)
{
	(void) vidTimer2_OvfIrqDisable();
	MEXTINT2_vidDisableInterrupt();
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
 * return		: Uint8_t (Distance)
 * */
float64_t HULTRASONIC_u8Read(void)
{
	HULTRASONIC_vidTrigger();
	
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
	vidTimer2_setcbf_OVF(TIMER_ptrFunction2);
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

