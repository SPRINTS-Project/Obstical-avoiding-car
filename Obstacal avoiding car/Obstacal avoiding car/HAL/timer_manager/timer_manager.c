/*
 * timer_manager.c
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 


#include "timer_manager.h"
#include "../../MCAL/timer/timer.h"


u8_en_timerErrorsType TIMER_Manager_init (st_timerConfigType* st_config)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==st_config || st_config->u8_timerNum >= TIMER_INVALID_NUM || st_config->u8_timerClock >= TIMER_INVALID_CLOCK)
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		l_ret  = TIMER_init(st_config);
		l_ret |= TIMER_setCallBack(st_config->callBackFunction,st_config->u8_timerNum);
	}
	return l_ret;
}
u8_en_timerErrorsType TIMER_Manager_start (st_timerConfigType* st_config)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==st_config || st_config->u8_timerNum >= TIMER_INVALID_NUM || st_config->u8_timerClock >= TIMER_INVALID_CLOCK)
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		l_ret = TIMER_start(st_config);
	}
	return l_ret;
}
u8_en_timerErrorsType TIMER_Manager_stop (u8_en_timerNumberType u8_en_timerNum)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if( u8_en_timerNum >= TIMER_INVALID_NUM )
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		l_ret = TIMER_stop(u8_en_timerNum);
	}
	return l_ret;
}
u8_en_timerErrorsType TIMER_Manager_reset (st_timerConfigType* st_config)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==st_config || st_config->u8_timerNum >= TIMER_INVALID_NUM || st_config->u8_timerClock >= TIMER_INVALID_CLOCK)
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		l_ret = TIMER_reset(st_config);
	}
	return l_ret;
}