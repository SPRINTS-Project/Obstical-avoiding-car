/*
 * car_control.c
 *
 * Created: 4/15/2023 12:32:00 PM
 *  Author: basel
 */ 
#include "car_control.h"
#include "car_control_cfg.h"




extern ST_motor_t ST_motor_1;
extern ST_motor_t ST_motor_2;




/*APIs impelementation*/


/************************************************************************
*description : used to initialize the two motor as output 
*input       : this function take two pointers to motor structure
*return      : MOTOR_OK, MOTOR_NOK                                                             
************************************************************************/
EN_car_error_t CAR_init(void)
{
	EN_car_error_t ret_val=CAR_OK;
	EN_motor_error_t motor_error1=MOTOR_INIT(&ST_motor_1);
	EN_motor_error_t motor_error2=MOTOR_INIT(&ST_motor_2);
	
	if(motor_error1 != MOTOR_OK || motor_error2 != MOTOR_OK)
	{
		ret_val=CAR_NOK;
	}
	else
	{
		// do nothing
	}
	return ret_val;
}


/************************************************************************
*description : used to move the car forward by specific speed
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_forward(void)
{
	EN_car_error_t ret_val=CAR_OK;
	EN_motor_error_t motor_error1=MOTOR_FORWARD(&ST_motor_1);
	EN_motor_error_t motor_error2=MOTOR_FORWARD(&ST_motor_2);
	if(motor_error1 != MOTOR_OK || motor_error2 != MOTOR_OK)
	{
		ret_val=CAR_NOK;
	}
	else
	{
		// do nothing
	}
	return ret_val;
}



/************************************************************************
*description : used to move the car backward by specific speed
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_backword(void)
{
	EN_car_error_t ret_val=CAR_OK;
	EN_motor_error_t motor_error1=MOTOR_BACKWARD(&ST_motor_1);
	EN_motor_error_t motor_error2=MOTOR_BACKWARD(&ST_motor_2);
	
	if(motor_error1 != MOTOR_OK || motor_error2 != MOTOR_OK)
	{
		ret_val=CAR_NOK;
	}
	else
	{
		// do nothing
	}
	return ret_val;
}



/************************************************************************
*description : used to reverse the car to the right
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_reverse_right(void)
{
	EN_car_error_t ret_val=CAR_OK;
	EN_motor_error_t motor_error1=MOTOR_FORWARD(&ST_motor_1);
	EN_motor_error_t motor_error2=MOTOR_BACKWARD(&ST_motor_2);
	
	if(motor_error1 != MOTOR_OK || motor_error2 != MOTOR_OK)
	{
		ret_val=CAR_NOK;
	}
	else
	{
		// do nothing
	}
	return ret_val;
}



/************************************************************************
*description : used to reverse the car to the left
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_reverse_left(void)
{
	EN_car_error_t ret_val=CAR_OK;
	EN_motor_error_t motor_error2=MOTOR_FORWARD(&ST_motor_1);
	EN_motor_error_t motor_error1=MOTOR_BACKWARD(&ST_motor_2);
	
	if(motor_error1 != MOTOR_OK || motor_error2 != MOTOR_OK)
	{
		ret_val=CAR_NOK;
	}
	else
	{
		// do nothing
	}
	return ret_val;
}


/************************************************************************
*description : used to stop the car
*input       : this function take two pointers to motor structure
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_stop(void)
{
	EN_car_error_t ret_val=CAR_OK;
	EN_motor_error_t motor_error1=MOTOR_STOP(&ST_motor_1);
	EN_motor_error_t motor_error2=MOTOR_STOP(&ST_motor_2);
	
	if(motor_error1 != MOTOR_OK || motor_error2 != MOTOR_OK)
	{
		ret_val=CAR_NOK;
	}
	else
	{
		// do nothing
	}
	return ret_val;
}