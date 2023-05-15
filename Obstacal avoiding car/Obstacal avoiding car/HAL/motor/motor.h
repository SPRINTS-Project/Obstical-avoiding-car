/*
 * motor.h
 *
 * Created: 4/14/2023 5:27:17 PM
 *  Author: basel
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
/*including sections*/
#include "../../MCAL/DIO/dio.h"

/*typedefs*/
typedef struct ST_motor_t
{   
	en_dioPortsType port;
	en_dioPinsType pin_num1;
	en_dioPinsType pin_num2;
}ST_motor_t;
typedef enum EN_motor_error_t 
{ 
	MOTOR_OK,
    MOTOR_NOK
}EN_motor_error_t;
	
#define NULL ((void*)0)	
/*************************************************************APIs prototypes*******************************************************************/



/************************************************************************
* description : this function used to init the motor as output
* input       : pointer to structure which have port and two pin number
* return      :MOTOR_OK or MOTR_NOK                                                                     
************************************************************************/
EN_motor_error_t MOTOR_INIT(const ST_motor_t* motor);


/************************************************************************
* description : this function used to move the motor forward
* input       : pointer to structure which have port and two pin number and speed of motor
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
EN_motor_error_t MOTOR_FORWARD(const ST_motor_t* motor);


/************************************************************************
* description : this function used to move the motor backward
* input       : pointer to structure which have port and two pin number and speed of motor
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
EN_motor_error_t MOTOR_BACKWARD(const ST_motor_t* motor);


/************************************************************************
* description : this function used to stop the motor
* input       : pointer to structure which have port and two pin number 
* return      :MOTOR_OK or MOTR_NOK
************************************************************************/
EN_motor_error_t MOTOR_STOP(const ST_motor_t* motor);





#endif /* MOTOR_H_ */