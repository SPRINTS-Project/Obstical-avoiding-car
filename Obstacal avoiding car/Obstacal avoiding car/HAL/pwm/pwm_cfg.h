/*
 * pwm_cfg.h
 *
 * Created: 5/20/2023 4:02:36 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef PWM_CFG_H_
#define PWM_CFG_H_

#include "pwm.h"
#include "pwm_CBF.h"





st_timerConfigType st_timer0Config = {
	.u8_timerNum = TIMER_0,
	.u8_timerClock = TIMER_F_CPU_1024,
	.u16_timer_InitialValue = 248,							// for 1 ms
	.u8_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_ENABLE,
	.callBackFunction = TIMER0_callBackFunc
};




#endif /* PWM_CFG_H_ */