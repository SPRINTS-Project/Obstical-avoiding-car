#ifndef APP_APP_H_
#define APP_APP_H_

#include <avr/interrupt.h>
typedef enum
{
	EN_MOTOR_START = 0,
	EN_MOTOR_STOP,
	EN_MOTOR_STOP_V2,
	EN_MOTOR_IDLE
	
	}en_motorSel_t;

typedef enum
{
	EN_UPDATE_DIR = 0,
	UPDATE_OBISTICAL_STATE

	}en_start_states_t;
	
	typedef enum 
	{
		OBSTACLE_IDLE = 0,
		NO_OBISTICALS ,
		OBISTICAL_70_30,
		OBISTICAL_30_20,
		OBISTICAL_LESS_20
		
		}en_Dist_states_t;

/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

void APP_vidInit(void);
void APP_vidStart(void);



#endif /*APP_APP_H_*/


/************************************************************************************************/
/*									END                     									*/
/************************************************************************************************/