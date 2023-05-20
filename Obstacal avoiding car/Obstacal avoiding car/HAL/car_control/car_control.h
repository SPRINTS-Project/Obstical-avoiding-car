#ifndef _CAR_CONTRO_H_
#define _CAR_CONTRO_H_
/*including sections*/
#include "../motor/motor.h"

/*typedefs*/

typedef enum EN_car_error_t
{
	CAR_OK = 0,
	CAR_NOK = 0x0B,
}EN_car_error_t;
/*APIs prototypes*/
/************************************************************************
*description : used to initialize the two motor as output 
*input       : void
*return      : MOTOR_OK, MOTOR_NOK                                                             
************************************************************************/
EN_car_error_t CAR_init(void);


/************************************************************************
*description : used to move the car forward by specific speed
*input       : void
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_forward(void);


/************************************************************************
*description : used to reverse the car to the right
*input       : void
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_reverse_right(void);



/************************************************************************
*description : used to reverse the car to the left
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_reverse_left(void);



/************************************************************************
*description : used to move the car backward by specific speed
*input       : this function take two pointers to motor structure and speed of the car
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_backword(void);



/************************************************************************
*description : used to stop the car
*input       : this function take two pointers to motor structure
*return      : MOTOR_OK, MOTOR_NOK
************************************************************************/
EN_car_error_t CAR_stop(void);

#endif