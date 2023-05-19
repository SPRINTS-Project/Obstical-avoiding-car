/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#define F_CPU 8000000UL
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "../HAL/button/button.h"
#include "../HAL/keypad/keypad.h"
#include "../HAL/hlcd/hlcd_Interface.h"
#include "../HAL/hextInt/HExtInt.h"
#include "../HAL/motor/motor.h"
#include "../HAL/timer_manager/timer_manager.h"
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
/*									Static Function Prototype											*/
/************************************************************************************************/
void BUTTON_vidChangeDir(void);
void TIMER1_callBackFunc(void);
void APP_updateDirection(void);
/************************************************************************************************/
/*									Global variables											*/
/************************************************************************************************/
float64_t global_f64Dist;
uint8_t u8KeyRead, flag1 = 0, flag2 = 0, flag3 = 0;
uint8_t u8_g_OneSecTicks = 0;
uint8_t* g_u8_motorDir = "Right";
en_motorSel_t en_motorSel = EN_MOTOR_IDLE;


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


st_timerConfigType st_timer1Config = {
	.u8_timerNum = TIMER_1,
	.u8_timerClock = TIMER_F_CPU_1024,
	.u16_timer_InitialValue = 57724,
	.u8_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_ENABLE,
	.callBackFunction = TIMER1_callBackFunc
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
	(void) HLCD_vidInit();
	(void) KEYPAD_init(&st_gs_keypadConfig);
	(void) HExtInt_enInit(INT_0, RISE_EDGE);
	(void) TIMER_Manager_init (&st_timer1Config);
	
	HULTRASONIC_vidCBF_TIM(HULTRASONIC_vidTimerCBF);
	HULTRASONIC_vidCBF_INT(HULTRASONIC_vidSigCalc);
	(void) HExtInt_enCBFInt0(BUTTON_vidChangeDir);
	
	DDRA = 0xFF;
}

void APP_vidStart(void)
{
	(void) KEYPAD_read(&u8KeyRead);
	
	 if (u8KeyRead != 'N')
	 {
		 switch(u8KeyRead)
		 {
			 case '1' : {
				 en_motorSel = EN_MOTOR_START; HLCD_gotoXY(1,0); HLCD_vidWriteChar(u8KeyRead); 				 
				 break;
				 }	 
			 case '2' : {
				 en_motorSel = EN_MOTOR_STOP; HLCD_gotoXY(1,0); HLCD_vidWriteChar(u8KeyRead); 
				 break;
				 }
				 default :
				 {
					 en_motorSel = EN_MOTOR_IDLE;
					 break;
				 }
		 } 
	 }
	 
	  if (en_motorSel == EN_MOTOR_START)
	  {
		global_f64Dist = HULTRASONIC_u8Read();
		_delay_ms(15);
		if (flag3 == 0) {HLCD_ClrDisplay();  flag1 = 0; flag2 = 0; flag3 = 1; }		
		APP_updateDirection();
		
		
		
		
	  }
	  else if (en_motorSel == EN_MOTOR_STOP)
	  {
		  if (flag2 == 0){HLCD_ClrDisplay();  flag1 = 0; flag2 = 1; flag3 = 0; }		  
		  HLCD_gotoXY(0,0);
		  HLCD_WriteString( (uint8_t*) "Motor Stopped");   
	  }
	  else 
	  {
		  if (flag1 == 0) {HLCD_ClrDisplay();  flag1 = 1; flag2 = 0; flag3 = 0; }
		  HLCD_gotoXY(0,0);
		  HLCD_WriteString( (uint8_t*) "MOTOR in IDLE");  
	  }
	 

}


/************************************************************************************************/
/*									Static Function Implementation                										*/
/************************************************************************************************/

void BUTTON_vidChangeDir(void)
{
	static Uint16_t counter = 0, L_flag = 0;
	counter += 2;
	if (counter % 2 == 0) {HLCD_ClrDisplay();}
		
		if (L_flag == 0)
			{g_u8_motorDir = "Left"; L_flag = 1;}
		else if (L_flag == 1)
		{
			g_u8_motorDir = "Right"; L_flag = 0;
		}
	
}


void TIMER1_callBackFunc(void)
{
	u8_g_OneSecTicks++;
}

void APP_updateDirection(void)
{
	TIMER_Manager_start (&st_timer1Config);
	HExtInt0_enIntEnable();
// 	while(u8_g_OneSecTicks <= 5)
// 	{
// 		HLCD_gotoXY(0,0);
// 		HLCD_WriteString( (uint8_t*) "Set Def. Rot.");
// 		HLCD_gotoXY(1,0);
// 		HLCD_WriteString(g_u8_motorDir);
// 	}
	PORTA = u8_g_OneSecTicks;
	HLCD_ClrDisplay();
	(void) TIMER_Manager_stop (st_timer1Config.u8_timerNum);
	HExtInt0_enIntDisable();
	
}
/************************************************************************************************/
/*									END                 										*/
/************************************************************************************************/