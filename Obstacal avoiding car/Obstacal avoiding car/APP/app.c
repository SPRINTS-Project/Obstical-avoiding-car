/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#define F_CPU 8000000UL
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "../HAL/button/button.h"
#include "../HAL/keypad/keypad.h"
#include "../HAL/hlcd/hlcd_Interface.h"
#include "../HAL/motor/motor.h"
//#include "../HAL/timer_manager/timer_manager.h"
#include "../HAL/Ultrasonic/ultrasonic.h"
#include <avr/io.h>
#include "app.h"
#include <util/delay.h>

/************************************************************************************************/
/*									extern functions											*/
/************************************************************************************************/
extern void HULTRASONIC_vidTimerCBF(void);
extern void HULTRASONIC_vidSigCalc(void);

/*extern st_lcdConfigType st_lcdConfig;*/
/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/
float64_t global_f64Dist;
uint8_t u8KeyRead;


st_keypadConfigType st_gs_keypadConfig = {
	.u8_row1Pin[0] = portc,
	.u8_row1Pin[1] = pin0,
	
	.u8_row2Pin[0] = portc,
	.u8_row2Pin[1] = pin1,
	
	.u8_row3Pin[0] = portc,
	.u8_row3Pin[1] = pin2,
	
	.u8_col1Pin[0] = portc,
	.u8_col1Pin[1] = pin3,
	
	.u8_col2Pin[0] = portc,
	.u8_col2Pin[1] = pin4,
	
	.u8_col3Pin[0] = portc,
	.u8_col3Pin[1] = pin5,
	
	.u8_col4Pin[0] = portc,
	.u8_col4Pin[1] = pin6
};

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
	(void) HLCD_vidInit();
		DDRA = 0xFF;
	PORTA =  KEYPAD_init(&st_gs_keypadConfig);
	

}

void APP_vidStart(void)
{
	   global_f64Dist = HULTRASONIC_u8Read();
 	_delay_ms(15);
	
	(void) KEYPAD_read(&u8KeyRead);
	
 	HLCD_gotoXY(0,0);
 	HLCD_WriteInt((Uint32_t) global_f64Dist);
	 
	 if (u8KeyRead != 'N')
	 {
		 HLCD_gotoXY(1,0);
		 HLCD_vidWriteChar(u8KeyRead);
		 _delay_ms(15);
	 }

 	
	
	/*LCD_WriteInt( (Uint32_t) global_f64Dist );*/
	

	
}
/************************************************************************************************/
/*									END                 										*/
/************************************************************************************************/