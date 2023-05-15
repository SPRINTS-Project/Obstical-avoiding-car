/*
 * motor.c
 *
 * Created: 4/14/2023 5:35:05 PM
 *  Author: basel
 */ 
/*including sections*/
#include "motor.h"

/* APIs impelementation*/
EN_motor_error_t MOTOR_INIT(const ST_motor_t* motor)
{
	if((DIO_init(motor->port,motor->pin_num1,STD_OUTPUT)==DIO_E_OK) && (DIO_init(motor->port,motor->pin_num2,STD_OUTPUT)==DIO_E_OK ))
	{
		return MOTOR_OK;
	}
	else
	{
		return MOTOR_NOK;
	}
}
EN_motor_error_t MOTOR_FORWARD(const ST_motor_t* motor)
{
	if(DIO_writePIN(motor->port,motor->pin_num1,STD_HIGH)==DIO_E_OK && DIO_writePIN(motor->port,motor->pin_num2,STD_LOW)==DIO_E_OK)
	{   
		return MOTOR_OK;
	}
	else
	{
		return MOTOR_NOK;
	}
}
EN_motor_error_t MOTOR_BACKWARD(const ST_motor_t* motor)
{
	if(DIO_writePIN(motor->port,motor->pin_num1,STD_LOW)==DIO_E_OK && DIO_writePIN(motor->port,motor->pin_num2,STD_HIGH)==DIO_E_OK)
	{    
		return MOTOR_OK;
	}
	else
	{
		return MOTOR_NOK;
	}
}
EN_motor_error_t MOTOR_STOP(const ST_motor_t* motor)
{
	if(DIO_writePIN(motor->port,motor->pin_num1,STD_LOW)==DIO_E_OK && DIO_writePIN(motor->port,motor->pin_num2,STD_LOW)==DIO_E_OK)
	{   
		return MOTOR_OK;
	}
	else
	{
		return MOTOR_NOK;
	}
}
