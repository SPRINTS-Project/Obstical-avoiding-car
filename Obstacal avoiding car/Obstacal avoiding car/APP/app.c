/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#define F_CPU 8000000UL
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "../HAL/button/button.h"
#include "../HAL/keypad/keypad.h"
#include "../HAL/lcd/lcd.h"
#include "../HAL/motor/motor.h"
//#include "../HAL/timer_manager/timer_manager.h"
#include "../HAL/Ultrasonic/ultrasonic.h"
#include "app.h"
#include <util/delay.h>

/************************************************************************************************/
/*									extern functions											*/
/************************************************************************************************/
extern void HULTRASONIC_vidTimerCBF(void);
extern void HULTRASONIC_vidSigCalc(void);

/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/
float64_t global_f64Dist;



/*
// Buttons configuration structure
const st_btnConfigType st_gc_btn_config[]={
	{portd,pin3,Button_Start},
	{portd,pin2,0x01}
};

// Motors configuration structure
const ST_motor_t st_gc_motorConfig[]={
	{
		porta,pin3,pin4
	},
	{
		porta,pin0,pin1
	}
};
*/


/************************************************************************************************/
/*									Function Implementation										*/
/************************************************************************************************/
void APP_vidInit(void)
{
    HULTRASONIC_vidInit();
    HULTRASONIC_vidCBF_TIM(HULTRASONIC_vidTimerCBF);
	HULTRASONIC_vidCBF_INT(HULTRASONIC_vidSigCalc);
}

void APP_vidStart(void)
{
    global_f64Dist = HULTRASONIC_u8Read();
	_delay_ms(15);
}
/************************************************************************************************/
/*									END                 										*/
/************************************************************************************************/