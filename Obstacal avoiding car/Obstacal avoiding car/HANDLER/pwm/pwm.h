/*
 * pwm.h
 *
 * Created: 5/19/2023 7:59:20 PM
 *  Author: engma
 */ 


#ifndef PWM_H_
#define PWM_H_
#include "../../STD_LIBRARIES/STD_TYPES.h"

typedef uint8_t u8_pwmErrorType;


u8_pwmErrorType PWM_init(void);
u8_pwmErrorType PWM_start(uint8_t u8_duty , uint8_t u8_ferq);
u8_pwmErrorType PWM_stop(void);
#endif /* PWM_H_ */