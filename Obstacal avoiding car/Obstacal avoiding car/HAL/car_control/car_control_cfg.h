/*
 * car_control_cfg.h
 *
 * Created: 5/20/2023 5:10:03 AM
 *  Author: Mahmoud Sarhan
 */ 


#ifndef CAR_CONTROL_CFG_H_
#define CAR_CONTROL_CFG_H_

#include "car_control.h"


ST_motor_t ST_motor_1 = {
	.pin_num1 = pin3,
	.pin_num2 = pin4,
	.port = porta
};

ST_motor_t ST_motor_2 = {
	.pin_num1 = pin0,
	.pin_num2 = pin1,
	.port = porta
};



#endif /* CAR_CONTROL_CFG_H_ */