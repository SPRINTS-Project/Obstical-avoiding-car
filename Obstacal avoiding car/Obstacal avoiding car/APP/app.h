#ifndef APP_APP_H_
#define APP_APP_H_

#include <avr/interrupt.h>
typedef enum
{
	EN_MOTOR_START = 0,
	EN_MOTOR_STOP,
	EN_MOTOR_IDLE
	
	}en_motorSel_t;

/************************************************************************************************/
/*									Function Prototypes     									*/
/************************************************************************************************/

void APP_vidInit(void);
void APP_vidStart(void);



#endif /*APP_APP_H_*/


/************************************************************************************************/
/*									END                     									*/
/************************************************************************************************/