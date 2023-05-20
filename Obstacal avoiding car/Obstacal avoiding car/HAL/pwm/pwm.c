/*
 * pwm.c
 *
 * Created: 5/19/2023 7:59:07 PM
 *  Author: Mahmoud Sarhan
 */ 


#include "pwm.h"
#include "pwm_cfg.h"
#include "pwm_CBF.h"
//#include <avr/io.h>
//#define F_CPU 8000000UL
//#include <util/delay.h>
#define INIT		1
#define NOT_INIT	0
#define START		2
#define STOP		3


extern st_timerConfigType st_timer0Config;


static uint8_t u8_gs_pwm_state = NOT_INIT;
static uint8_t u8_gs_pwm_counter = 0;
static uint8_t u8_gs_duty = 0;
static uint8_t u8_gs_duty_counter = 0;
static uint8_t u8_gs_cycle = 0;
static uint8_t u8_gs_dir = 0;

u8_pwmErrorType PWM_init(void)
{
	//DDRB = 0xff;
	uint8_t u8_retVal = PWM_ERROR_OK;
	u8_retVal = TIMER_Manager_init(&st_timer0Config);
	u8_retVal |= CAR_init();
	if (u8_retVal == PWM_ERROR_OK)
	{
		u8_gs_pwm_state = INIT;
	}
	return u8_retVal;
}
u8_pwmErrorType PWM_start(uint8_t u8_duty , uint8_t u8_cycle , en_motor_dir_t u8_motor_dir)
{
	
	uint8_t u8_retVal = PWM_ERROR_OK;
	if (u8_gs_pwm_state != NOT_INIT)
	{
		if (u8_gs_pwm_state == START &&  (u8_gs_duty != u8_duty || u8_gs_cycle != u8_cycle || u8_gs_dir != u8_motor_dir ))
		{
			u8_gs_pwm_counter = 0;
		}
		u8_gs_duty = u8_duty;
		u8_gs_cycle = u8_cycle;
		u8_gs_dir = u8_motor_dir;
		u8_duty = (u8_cycle * u8_duty) / 100;
		u8_gs_duty_counter = u8_duty;
		u8_retVal |= TIMER_Manager_start(&st_timer0Config);
		/*while (u8_gs_pwm_counter < u8_duty)
		{
			if (u8_motor_dir == FORWARD)
			{
				u8_retVal |= CAR_forward();
			}
			else if (u8_motor_dir == BACKWARD)
			{
				u8_retVal |= CAR_backword();
			}
			else{
				// do nothing
			}
		}
		if (u8_gs_pwm_counter < u8_cycle && u8_gs_pwm_counter>= u8_duty)
		{
			u8_retVal |= CAR_stop();
		}
		else{
			u8_gs_pwm_counter = 0;
		}
		*/
		u8_gs_pwm_state = START;
	}
	else{
		u8_retVal = PWM_ERROR_NOT_OK;
	}
	return u8_retVal;
}
u8_pwmErrorType PWM_stop(void)
{
	uint8_t u8_retVal = PWM_ERROR_OK;
	if (u8_gs_pwm_state == START )
	{
		TIMER_Manager_stop(st_timer0Config.u8_timerNum);
		u8_gs_pwm_counter = 0;
		u8_gs_pwm_state = STOP;
	}
	else{
		u8_retVal = PWM_ERROR_NOT_OK;
	}
	return u8_retVal;
}



void TIMER0_callBackFunc(void)
{
	u8_gs_pwm_counter++;
	if (u8_gs_pwm_counter < u8_gs_duty_counter)
	{
		if (u8_gs_dir == FORWARD)
		{
			CAR_forward();
		}
		else if (u8_gs_dir == BACKWARD)
		{
			CAR_backword();
		}
		else{
			// do nothing
		}
	}
	else if (u8_gs_pwm_counter < u8_gs_cycle && u8_gs_pwm_counter>= u8_gs_duty_counter)
	{
		CAR_stop();
	}
	else{
		u8_gs_pwm_counter = 0;
	}
	TIMER_Manager_reset(&st_timer0Config);
}