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
#include "../HAL/pwm/pwm.h"
#include "../HAL/car_control/car_control.h"
#include <avr/io.h>
#include "app.h"
#include <util/delay.h>


#define MOTOR_TURN_RIGHT			0
#define MOTOR_TURN_LEFT				1
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
uint8_t u8KeyRead, flag1 = 0, flag2 = 0, flag3 = 0 , flag4 = 0 , flag5 = 0;
uint8_t u8_g_OneSecTicks = 0;
static uint8_t u8_gs_rotate_counter = 1;
uint8_t u8_g_dirStateCounter = MOTOR_TURN_RIGHT;
en_motorSel_t en_motorSel = EN_MOTOR_IDLE;
en_start_states_t en_start_state = EN_UPDATE_DIR;
en_Dist_states_t en_Dist_states = OBSTACLE_IDLE;


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



/************************************************************************************************/
/*									Function Implementation										*/
/************************************************************************************************/
void APP_vidInit(void)
{
    HULTRASONIC_vidInit();
	HULTRASONIC_vidInterruptEnable();
	(void) HLCD_vidInit();
	(void) KEYPAD_init(&st_gs_keypadConfig);
	(void) HExtInt_enInit(INT_0, RISE_EDGE);
	(void) TIMER_Manager_init (&st_timer1Config);
	(void) PWM_init();
	(void) CAR_init();
	
	HULTRASONIC_vidCBF_TIM(HULTRASONIC_vidTimerCBF);
	HULTRASONIC_vidCBF_INT(HULTRASONIC_vidSigCalc);
	(void) HExtInt_enCBFInt0(BUTTON_vidChangeDir);
	
/*	sei();*/
	//DDRA = 0xFF;
}

void APP_vidStart(void)
{
 	//if (en_motorSel == EN_MOTOR_IDLE)
 	//{
		(void) KEYPAD_read(&u8KeyRead);
		
		if (u8KeyRead != 'N')
		{
			switch(u8KeyRead)
			{
				case '1' : {
					en_motorSel = EN_MOTOR_START;
					break;
				}
				case '2' : {
					en_motorSel = EN_MOTOR_STOP;
					flag2 = 0;
					break;
				}
				default :
				{
					//en_motorSel = EN_MOTOR_IDLE;
					break;
				}
			}
		}
	//}
	if (en_motorSel == EN_MOTOR_START)
	 { 				
		if (en_start_state == EN_UPDATE_DIR)
		{
			HLCD_ClrDisplay();
			HLCD_gotoXY(0,0);
			HLCD_WriteString( (uint8_t*) "Set Def. Rot.");
			APP_updateDirection();
			en_start_state = UPDATE_OBISTICAL_STATE;
		}
		else if (en_start_state == UPDATE_OBISTICAL_STATE )
		{
		  global_f64Dist = HULTRASONIC_u8Read();
		  _delay_ms(15);
		  
			if		(global_f64Dist > 70.0 )							{ en_Dist_states = NO_OBISTICALS;  }		
			else if (global_f64Dist > 30.0 && global_f64Dist <= 70.0)	{ en_Dist_states = OBISTICAL_70_30; }	
			else if (global_f64Dist >= 20.0 && global_f64Dist <= 30)	{ en_Dist_states = OBISTICAL_30_20;}	
			else if (global_f64Dist < 20.0)								{ en_Dist_states = OBISTICAL_LESS_20;}	
			else{  /* do nothing */ }	
				
			}	else { /*do nothing*/}
				
		if (en_Dist_states == NO_OBISTICALS)
		{
			if(global_f64Dist>99.0)
			{
				global_f64Dist = 99.0;
			}
				HLCD_gotoXY(1,0);
				HLCD_WriteString((uint8_t*)"Dist: ");
				HLCD_WriteInt( (Uint32_t)  global_f64Dist);
				HLCD_WriteString((uint8_t*)" cm");
				
				/* Motor move forward with duty cycle 30% for 5 sec */
				u8_g_OneSecTicks = 0;
				TIMER_Manager_start (&st_timer1Config);
				
				while(u8_g_OneSecTicks <= 5 && flag4 == 0)
				{
					HLCD_gotoXY(0,0);
					HLCD_WriteString((uint8_t*)"Speed:30% ");
					HLCD_WriteString((uint8_t*)"Dir:F");
					PWM_start(30,20,FORWARD);
				}
				flag4=1;
				(void) TIMER_Manager_stop (st_timer1Config.u8_timerNum);
				/* Motor move forward with duty cycle 50%  */
				HLCD_gotoXY(0,0);
				HLCD_WriteString((uint8_t*)"Speed:50% ");
				HLCD_WriteString((uint8_t*)"Dir:F");
				PWM_start(50,20,FORWARD);
				
		}
		else if (en_Dist_states == OBISTICAL_70_30)
		{
				flag4=0;
				HLCD_gotoXY(1,0);
				HLCD_WriteString((uint8_t*)"Dist: ");
				HLCD_WriteInt( (Uint32_t)  global_f64Dist);
				HLCD_WriteString((uint8_t*)" cm");
				
				HLCD_gotoXY(0,0);
				HLCD_WriteString((uint8_t*)"Speed:30% ");
				HLCD_WriteString((uint8_t*)"Dir:F");
				/* Motor move forward with duty cycle 30% */		
				PWM_start(30,20,FORWARD);
		}
		else if (en_Dist_states == OBISTICAL_30_20)
		{
			flag4=0;
			PWM_stop();
				HLCD_gotoXY(1,0);
				HLCD_WriteString((uint8_t*)"Dist: ");
				HLCD_WriteInt( (Uint32_t)  global_f64Dist);
				HLCD_WriteString((uint8_t*)" cm");
				
				HLCD_gotoXY(0,0);
				HLCD_WriteString((uint8_t*)"Speed:0%");
				HLCD_WriteString((uint8_t*)"Dir:S");
				/* Motor Stop Implementation  */
				CAR_stop();
				//_delay_ms(500);
				HLCD_gotoXY(0,0);
				HLCD_WriteString((uint8_t*)"Speed:100%");
				HLCD_WriteString((uint8_t*)"Dir:R");
				u8_g_OneSecTicks = 0;
				TIMER_Manager_start(&st_timer1Config);
				while (global_f64Dist <= 30.0)
				{
					/* rotate depend on u8_g_dirStateCounter  */
					if (u8_g_OneSecTicks <= 4)
					{
						if (u8_g_dirStateCounter == MOTOR_TURN_LEFT)
						{
							CAR_reverse_left();
							//_delay_ms(1000);
							//u8_gs_rotate_counter++;
						}
						else if (u8_g_dirStateCounter == MOTOR_TURN_RIGHT)
						{
							CAR_reverse_right();
							//_delay_ms(1000);
							//u8_gs_rotate_counter++;
						}
						else
						{
							// do nothing
						}
						/*u8_gs_rotate_counter++;*/
					}
					else{
						en_motorSel = EN_MOTOR_STOP_V2;
						break;
					}
					(void) KEYPAD_read(&u8KeyRead);
					if (u8KeyRead == '2')
					{
						en_motorSel = EN_MOTOR_STOP;
						flag2 = 0;
						break;
					}
					global_f64Dist = HULTRASONIC_u8Read();
					HLCD_gotoXY(1,0);
					HLCD_WriteString((uint8_t*)"Dist: ");
					HLCD_WriteInt( (Uint32_t)  global_f64Dist);
					HLCD_WriteString((uint8_t*)" cm");
					if (global_f64Dist <= 20.0) break;
				}

		}
		else if (en_Dist_states == OBISTICAL_LESS_20)
		{
			flag4=0;
				HLCD_gotoXY(1,0);
				HLCD_WriteString((uint8_t*)"Dist: ");
				HLCD_WriteInt( (Uint32_t)  global_f64Dist);
				HLCD_WriteString((uint8_t*)" cm");
				
				HLCD_gotoXY(0,0);
				HLCD_WriteString((uint8_t*)"Speed:0% ");
				HLCD_WriteString((uint8_t*)"Dir:S");
				/*  Motor Stop Implementation  */
				CAR_stop();
				//_delay_ms(500);
				HLCD_gotoXY(0,0);
				HLCD_WriteString((uint8_t*)"Speed:30% ");
				HLCD_WriteString((uint8_t*)"Dir:b");
				while (global_f64Dist <= 20.0)
				{
					/* Motor move backward with duty cycle 30%  */
					PWM_start(30,20,BACKWARD);
					global_f64Dist = HULTRASONIC_u8Read();
					HLCD_gotoXY(1,0);
					HLCD_WriteString((uint8_t*)"Dist: ");
					HLCD_WriteInt( (Uint32_t)  global_f64Dist);
					HLCD_WriteString((uint8_t*)" cm");	
					(void) KEYPAD_read(&u8KeyRead);
					if (u8KeyRead == '2')
					{
						en_motorSel = EN_MOTOR_STOP;
						flag2 = 0;
						break;
					}					
				}
		}
	 } 
	else if (en_motorSel == EN_MOTOR_STOP)
	  {
		  if (flag2 == 0){HLCD_ClrDisplay();  flag1 = 0; flag2 = 1; flag3 = 0; }		  
		  //HLCD_ClrDisplay();
		  HLCD_gotoXY(0,0);
		  HLCD_WriteString( (uint8_t*) "Motor Stopped"); 
		  CAR_stop();
		  PWM_stop();  
	  }
	  else if (en_motorSel == EN_MOTOR_STOP_V2)
	  {
		  
		  HLCD_ClrDisplay();
		  HLCD_gotoXY(0,0);
		  HLCD_WriteString( (uint8_t*) "Motor Stopped");
		  CAR_stop();
		  _delay_ms(2000);
		  HLCD_ClrDisplay();
		  HLCD_gotoXY(0,0);
		  HLCD_WriteString( (uint8_t*) "Trying again in");
		  HLCD_gotoXY(1,0);
		  HLCD_WriteString( (uint8_t*) "1 sec");
		  _delay_ms(1000);
		  u8_gs_rotate_counter=0;
		  en_motorSel = EN_MOTOR_START;
	  }
	  else 
	  {
		  if (flag1 == 0) {HLCD_ClrDisplay();  flag1 = 1; flag2 = 0; flag3 = 0; }
		  HLCD_gotoXY(0,0);
		  HLCD_WriteString( (uint8_t*) "MOTOR in IDLE");  
	  }
}


/************************************************************************************************/
/*									Static Function Implementation                				*/
/************************************************************************************************/

void BUTTON_vidChangeDir(void)
{
	u8_g_dirStateCounter ^= 1 ;
}


void TIMER1_callBackFunc(void)
{
	u8_g_OneSecTicks++;
	TIMER_Manager_reset(&st_timer1Config);
}

void APP_updateDirection(void)
{
	HULTRASONIC_vidInterruptDisable();
	u8_g_OneSecTicks = 0;
	TIMER_Manager_start (&st_timer1Config);
	HExtInt0_enIntEnable();
	while(u8_g_OneSecTicks <= 2)
	{
		if (u8_g_dirStateCounter == MOTOR_TURN_LEFT)
		{
			HLCD_gotoXY(1,4);
			HLCD_vidWriteChar(' ');
			HLCD_gotoXY(1,0);
			HLCD_WriteString((uint8_t*)"Left");
		}
		else if(u8_g_dirStateCounter == MOTOR_TURN_RIGHT){
			HLCD_gotoXY(1,0);
			HLCD_WriteString((uint8_t*)"Right");
		}
		else {
			/* do nothing  */
		}
	}
	//while(u8_g_OneSecTicks <= 7);
	HLCD_ClrDisplay();
	(void) TIMER_Manager_stop (st_timer1Config.u8_timerNum);
	HExtInt0_enIntDisable();
	HULTRASONIC_vidInterruptEnable();
	HLCD_gotoXY(0,0);
	HLCD_WriteString((uint8_t*)"Motor starts in");
	HLCD_gotoXY(1,0);
	HLCD_WriteString((uint8_t*)"2 Sec.");
	_delay_ms(2000);
	HLCD_ClrDisplay();
}
/************************************************************************************************/
/*									END                 										*/
/************************************************************************************************/