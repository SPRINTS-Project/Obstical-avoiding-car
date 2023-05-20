/*
 * pwm.h
 *
 * Created: 5/19/2023 7:59:20 PM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../car_control/car_control.h"
#include "../timer_manager/timer_manager.h"


typedef enum
{
	FORWARD = 0 ,
	BACKWARD
	}en_motor_dir_t;

typedef uint8_t u8_pwmErrorType;

#define PWM_ERROR_OK		((u8_pwmErrorType)0x0)
#define PWM_ERROR_NOT_OK	((u8_pwmErrorType)0x0A)

u8_pwmErrorType PWM_init(void);
u8_pwmErrorType PWM_start(uint8_t u8_duty , uint8_t u8_cycle , en_motor_dir_t u8_motor_dir);
u8_pwmErrorType PWM_stop(void);
#endif /* PWM_H_ */