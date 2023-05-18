/*
 * timer.c
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 

#include "timer.h"
#include "timer_private_reg.h"


/* Global pointers to function to hold the address of the call back function in the upper layers */
static timerCallBack sg_Timer0_callBackPtr = NULL;
static timerCallBack sg_Timer1_callBackPtr = NULL;
static timerCallBack sg_Timer2_callBackPtr = NULL;

ISR(TIMER0_OVF)
{
	if(sg_Timer0_callBackPtr != NULL)
	{
		// The timer0 overflow  occurred (must be cleared in software)
		CLEAR_BIT(TIFR,TOV0);
		//Call the Call Back function in the upper layer after the timer overflow
		(sg_Timer0_callBackPtr)();
	}
}

ISR(TIMER1_OVF)
{
	if(sg_Timer1_callBackPtr != NULL)
	{
		// The timer1 overflow  occurred (must be cleared in software)
		CLEAR_BIT(TIFR,TOV1);
		// Call the Call Back function in the upper layer after the timer overflow
		(sg_Timer1_callBackPtr)();
	}
}

// ISR(TIMER2_OVF)
// {
// 	if(sg_Timer2_callBackPtr != NULL)
// 	{
// 		//The timer2 overflow  occurred (must be cleared in software) 
// 		SET_BIT(TIFR,TOV2);
// 		//Call the Call Back function in the upper layer after the timer overflow
// 		(sg_Timer2_callBackPtr)();
// 	}
// }

u8_en_timerErrorsType TIMER_init (st_timerConfigType* st_config)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==st_config || st_config->u8_timerNum >= TIMER_INVALID_NUM || st_config->u8_timerClock >= TIMER_INVALID_CLOCK)
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		switch(st_config->u8_timerNum)
		{
			
			case TIMER_0:
				/*Clear registers of Timer0 before processing any of them*/
				CLEAR_REG(TCNT0);
				CLEAR_REG(TCCR0);
				CLEAR_REG(OCR0);
				/*Configure initial value in TCNT0 for Timer0 to start count from it*/
				TCNT0 = st_config->u16_timer_InitialValue & U8_BIT_REG_MASK;
				
				/*Configure the TIMER0 with normal  mode value and enable the interrupt for this mode if interrupt feature activated */
				
				/*Make FOC0 to be Active as it is overflow mode(for non-PWM mode)*/
				SET_BIT(TCCR0,FOC0);
				/*Normal Overflow mode*/
				CLEAR_BIT(TCCR0,WGM00);
				CLEAR_BIT(TCCR0,WGM01);
				/*Normal port operation, OC0 disconnected*/
				CLEAR_BIT(TCCR0,COM00);
				CLEAR_BIT(TCCR0,COM01);
				if(TIMER_INTERRUPT_FEATURE_ENABLE==st_config->u8_timer_ovf_int_enable)
				{
					/* Enable Timer0 overflow interrupt*/
					SET_BIT(TIMSK,TOIE0);
				}
				else
				{
					// DO NOTHING
				}
				
				break;
			
			case TIMER_1:
				/*Clear registers of Timer1 before processing any of them*/
				CLEAR_REG(TCNT1L);
				CLEAR_REG(TCNT1H);
				CLEAR_REG(TCCR1A);
				CLEAR_REG(TCCR1B);
				CLEAR_REG(OCR1AH);
				CLEAR_REG(OCR1AL);
				/*Configure initial value in TCNT1(high&low) for Timer0 to start count from it*/
				TCNT1 = st_config->u16_timer_InitialValue;
				
				#if 0
				TCNT1L =(st_config->u16_timer_InitialValue) & U8_BIT_REG_MASK;
				TCNT1H = (st_config->u16_timer_InitialValue >> 8) & U8_BIT_REG_MASK;*/
				#endif
				
				/*Configure the TIMER1 with normal  mode value and enable the interrupt for this mode if interrupt feature activated */
				/*Make FOC1A,FOC1B to be Active as it is overflow mode(for non-PWM mode)*/
				SET_BIT(TCCR1A,FOC1A);
				SET_BIT(TCCR1A,FOC1B);
				/*Normal Overflow mode*/
				CLEAR_BIT(TCCR1A,WGM10);
				CLEAR_BIT(TCCR1A,WGM11);
				CLEAR_BIT(TCCR1B,WGM12);
				CLEAR_BIT(TCCR1B,WGM13);
				/*Normal port operation, OC1A/OC1B disconnected.*/
				CLEAR_BIT(TCCR1A,COM1A0);
				CLEAR_BIT(TCCR1A,COM1A1);
				CLEAR_BIT(TCCR1A,COM1B0);
				CLEAR_BIT(TCCR1A,COM1B1);
				
				if(TIMER_INTERRUPT_FEATURE_ENABLE==st_config->u8_timer_ovf_int_enable)
				{
					/* Enable Timer1 overflow interrupt*/
					//TIMSK |= 1<<TOIE1;
					SET_BIT(TIMSK,TOIE1);
				}
				else
				{
					// DO NOTHING
				}
				
				
				break;
			
			case TIMER_2:
				/*Clear registers of Timer2 before processing any of them*/
				CLEAR_REG(TCNT2);
				CLEAR_REG(TCCR2);
				CLEAR_REG(OCR2);
				/*Configure initial value in TCNT for Timer2 to start count from it*/
				//TCNT2 = st_config->u16_timer_InitialValue & U8_BIT_REG_MASK;
				TCNT2 = 0;
				/*Configure the TIMER2 with normal  mode value and enable the interrupt for this mode if interrupt feature activated */
				/*Make FOC2 to be Active as it is overflow mode(for non-PWM mode)*/
				//SET_BIT(TCCR2,FOC2);
				/*Normal Overflow mode*/
				CLEAR_BIT(TCCR2,WGM20);
				CLEAR_BIT(TCCR2,WGM21);
				/*Normal port operation, OC2 disconnected*/
				CLEAR_BIT(TCCR2,COM20);
				CLEAR_BIT(TCCR2,COM21);
				if(TIMER_INTERRUPT_FEATURE_ENABLE==st_config->u8_timer_ovf_int_enable)
				{
					/* Enable Timer2 overflow interrupt*/
					SET_BIT(TIMSK,TOIE2);
				}
				else
				{
					// DO NOTHING
				}
				
				break;
			
			default:
				l_ret |= TIMER_E_NOT_OK;
				break;
		}
	}
	return l_ret;
}
u8_en_timerErrorsType TIMER_start (st_timerConfigType* st_config)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==st_config || st_config->u8_timerNum >= TIMER_INVALID_NUM || st_config->u8_timerClock >= TIMER_INVALID_CLOCK)
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		/*Configure the TIMER Pres-scaler value for Timer-x clock*/
		switch(st_config->u8_timerNum)
		{
			case TIMER_0:
				switch(st_config->u8_timerClock)
				{
					case TIMER_NO_CLOCK:
						CLEAR_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case TIMER_F_CPU_CLOCK:
						SET_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case TIMER_F_CPU_8:
						CLEAR_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case TIMER_F_CPU_64:
						SET_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						CLEAR_BIT(TCCR0,CS02);
						break;
					case TIMER_F_CPU_256:
						CLEAR_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);
						break;
					case TIMER_F_CPU_1024:
						SET_BIT(TCCR0,CS00);
						CLEAR_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);	
						break;
					case TIMER_EXTERNAL_CLK_FALLING_EDGE:
						CLEAR_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);
						break;
					case TIMER_EXTERNAL_CLK_RISING_EDGE:
						SET_BIT(TCCR0,CS00);
						SET_BIT(TCCR0,CS01);
						SET_BIT(TCCR0,CS02);
						break;
					default:
						l_ret = TIMER_E_NOT_OK;
						break;
				}
				break;
				
			case TIMER_1:
				switch(st_config->u8_timerClock)
				{
					case TIMER_NO_CLOCK:
						CLEAR_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case TIMER_F_CPU_CLOCK:
						SET_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case TIMER_F_CPU_8:
						CLEAR_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case TIMER_F_CPU_64:
						SET_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						CLEAR_BIT(TCCR1B,CS12);
						break;
					case TIMER_F_CPU_256:
						CLEAR_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);
						break;
					case TIMER_F_CPU_1024:
						SET_BIT(TCCR1B,CS10);
						CLEAR_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);	
						break;
					case TIMER_EXTERNAL_CLK_FALLING_EDGE:
						CLEAR_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);
						break;
					case TIMER_EXTERNAL_CLK_RISING_EDGE:
						SET_BIT(TCCR1B,CS10);
						SET_BIT(TCCR1B,CS11);
						SET_BIT(TCCR1B,CS12);
						break;
					default:
						l_ret = TIMER_E_NOT_OK;
						break;
				}			
				break;
				
			case TIMER_2:
				switch(st_config->u8_timerClock)
				{
					case TIMER_NO_CLOCK:
						CLEAR_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_CLOCK:
						SET_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_8:
						CLEAR_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_32:
						SET_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						CLEAR_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_64:
						CLEAR_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_128:
						SET_BIT(TCCR2,CS20);
						CLEAR_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_256:
						CLEAR_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);
						break;
					case TIMER_F_CPU_1024:
						SET_BIT(TCCR2,CS20);
						SET_BIT(TCCR2,CS21);
						SET_BIT(TCCR2,CS22);	
						break;
					default:
						l_ret = TIMER_E_NOT_OK;
						break;
				}
				break;
				
			default:
				l_ret |= TIMER_E_NOT_OK;
				break;
		}
	}
	return l_ret;
}
u8_en_timerErrorsType TIMER_stop (u8_en_timerNumberType u8_a_timerNum)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if( u8_a_timerNum >= TIMER_INVALID_NUM )
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		switch(u8_a_timerNum)
		{
			case TIMER_0:
				/*use no clock to halt timer0*/
				CLEAR_BIT(TCCR0,CS00);
				CLEAR_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
				break;
				
			case TIMER_1:
				/*use no clock to halt timer1*/
				CLEAR_BIT(TCCR1B,CS10);
				CLEAR_BIT(TCCR1B,CS11);
				CLEAR_BIT(TCCR1B,CS12);
				break;
				
			case TIMER_2:
				/*use no clock to halt timer2*/
				CLEAR_BIT(TCCR2,CS20);
				CLEAR_BIT(TCCR2,CS21);
				CLEAR_BIT(TCCR2,CS22);
				break;
				
			default:
				l_ret |= TIMER_E_NOT_OK;
				break;
		}
	}
	return l_ret;
}

u8_en_timerErrorsType TIMER_reset (st_timerConfigType* st_config)
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==st_config || st_config->u8_timerNum >= TIMER_INVALID_NUM || st_config->u8_timerClock >= TIMER_INVALID_CLOCK)
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		switch(st_config->u8_timerNum)
		{
			case TIMER_0:
				
				/*Configure initial value in TCNT1(high&low) for Timer0 to start count from it*/
				TCNT0 = st_config->u16_timer_InitialValue;
				break;
				
			case TIMER_1:
			
				/*Configure initial value in TCNT1(high&low) for Timer1 to start count from it*/
				TCNT1 = st_config->u16_timer_InitialValue;
				break;
				
			case TIMER_2:
				
				/*Configure initial value in TCNT1(high&low) for Timer2 to start count from it*/
				TCNT2 = st_config->u16_timer_InitialValue;
				break;
				
			default:
				l_ret |= TIMER_E_NOT_OK;
				break;
		}
	}
	return l_ret;
}
u8_en_timerErrorsType TIMER_setCallBack( void(*a_timerCallBack)(void), u8_en_timerNumberType u8_a_timerNum )
{
	u8_en_timerErrorsType l_ret = TIMER_E_OK;
	if(NULL==a_timerCallBack || u8_a_timerNum >= TIMER_INVALID_NUM )
	{
		l_ret = TIMER_E_NOT_OK;
	}
	else
	{
		switch(u8_a_timerNum)
		{
			case TIMER_0:
				/* load the address of the Call back function from upper layer in the global pointer to function */
				sg_Timer0_callBackPtr = a_timerCallBack;
				break;
			case TIMER_1:
				/* load the address of the Call back function from upper layer in the global pointer to function */
				sg_Timer1_callBackPtr = a_timerCallBack;
				break;
			case TIMER_2:
				/* load the address of the Call back function from upper layer in the global pointer to function */
				sg_Timer2_callBackPtr = a_timerCallBack;
				break;
			default:
				l_ret = TIMER_E_NOT_OK;
				break;
		}
	}
	return l_ret;
}




/********************************************************************************************
 * 								Edit by Bassel Yasser Mahmoud
*********************************************************************************************/
#include "timer2_Interface.h"

/*************************************************************************************************************
 * 								Macros
 ************************************************************************************************************/
#define PRESCALLER_CLR_MSK		(0b11111000)
#define PRESCALLER_OFFSET		CS00
#define F_CPU			8000000UL

#define STOPPED			0
#define RUNNING			1

#define OVF_TICKS		256UL
#define MAX_TIM_MS		5000UL
/*************************************************************************************************************
 * 								Global/Static Variables
 ************************************************************************************************************/
static enu_timerPrescalar_t global_prescaller;
static uint8_t global_timerStatus;
static uint8_t global_ovf = 1;
static Uint16_t preload = 0;
static cbf_t  globalCallFunc = NULL;


static Uint16_t prescaller_map[6] = {
		0,
		1,
		8,
		64,
		256,
		1024
};

/*************************************************************************************************************
 * 							Function Implementation
 ************************************************************************************************************/
enu_timerStatus_t enuTimer2_init (enu_timerMode_t enTimerMode)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	if(enTimerMode < TIMER_MODE_INVALID)
	{
		TCNT2 = 0;
		switch (enTimerMode)
		{
		case OVF_MODE 				: CLEAR_BIT(TCCR2, WGM01);CLEAR_BIT(TCCR2, WGM00); break;
		case PHASE_CORRECT_PWM_MODE : CLEAR_BIT(TCCR2, WGM01);SET_BIT(TCCR2, WGM00); break;
		case CTC_MODE 				: SET_BIT(TCCR2, WGM01);CLEAR_BIT(TCCR2, WGM00); break;
		case FAST_PWM_MODE 			: SET_BIT(TCCR2, WGM01);SET_BIT(TCCR2, WGM00); break;
		default 					: errorStatus = TIMER_NOK; break;
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}
	return errorStatus;
}


/*************************************************************************************************************/
enu_timerStatus_t u8Timer2_setPrescallar(enu_timerPrescalar_t Copy_enPrescal)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	uint8_t temp_reg;
	if(Copy_enPrescal < TIMER_PRESCALR_INVALID)
	{
		global_prescaller = Copy_enPrescal;
		if (global_timerStatus == RUNNING)
		{
			temp_reg = TCCR2;		 // read
			temp_reg &= PRESCALLER_CLR_MSK;  // mod
			temp_reg |=  global_prescaller << PRESCALLER_OFFSET; // mod
			TCCR2 |= temp_reg;		// write
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		errorStatus = TIMER_NOK;
	}


	return errorStatus;

}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_OvfIrqEnable(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	SET_BIT(TIFR, 6);
	SET_BIT(TIMSK, TOIE2);
//	SET_BIT(SREG_REG, 7);

	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_OvfIrqDisable(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	CLEAR_BIT(TIMSK, TOIE2);

	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_start(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	TCCR2 |=  global_prescaller << PRESCALLER_OFFSET;
	global_timerStatus  = RUNNING;

	return errorStatus;
}

/*************************************************************************************************************/
enu_timerStatus_t vidTimer2_stop(void)
{
	enu_timerStatus_t errorStatus = TIMER_OK;

	TCCR2 &=  PRESCALLER_CLR_MSK;
	global_timerStatus = STOPPED;

	return errorStatus;
}
/*************************************************************************************************************/
enu_timerStatus_t u8Timer2_setTime_ms(Uint32_t u32_time_ms)
{
	enu_timerStatus_t errorStatus = TIMER_OK;
	Uint32_t desired_ticks;
	float32_t tick_time_ms;
	if( u32_time_ms < MAX_TIM_MS )
	{
		tick_time_ms = (float32_t)prescaller_map[global_prescaller] / ((Uint32_t)F_CPU / 1000U)  ;
		desired_ticks = u32_time_ms / tick_time_ms;

		/* Compare ticks with OVF_ticks */
		if(desired_ticks == OVF_TICKS)
		{
			global_ovf = 1;
		}
		else if(desired_ticks < OVF_TICKS)
		{
			preload = OVF_TICKS - desired_ticks;
			TCNT2 = preload;
			global_ovf = 1;
		}
		else if(desired_ticks > OVF_TICKS)
		{
			global_ovf = (uint8_t)(desired_ticks / OVF_TICKS);
			preload = (Uint16_t)(OVF_TICKS - (desired_ticks % OVF_TICKS ));
			TCNT2 = preload;
			if (preload > 0U)
			{
				global_ovf++;
			}
		}
	}
		else
		{
			errorStatus = TIMER_NOK;
		}


		return errorStatus;
	}

/*************************************************************************************************************/
void vidTimer2_setcbf_OVF(cbf_t cbf)
{
	if (cbf != NULL)
	{
		globalCallFunc = cbf;
	}
	return;
}



void MTIMER_vidResetTCNT(void)
{
	TCNT2 = 0;
}
uint8_t MTIMER_u8GetTCNT(void)
{
	return TCNT2;
}


void MTIMER_vidEnableGlobalInterrupt(void)
{
	
	SET_BIT(SREG,7);
}
/*************************************************************************************************************
 * 							ISR Interrupt Handling
 ************************************************************************************************************/
ISR(TIMER2_OVF)
{
	static uint8_t counter = 0;
	counter++;
	if(counter == global_ovf)
	{
		if (globalCallFunc != NULL)
		{
			counter = 0;

			globalCallFunc();
//			TCNT2_REG = preload;
//			global_ovf = 0;
//			vidTimer1_stop();
		}
	}
}


/********************************************************************************************
 * 								END
*********************************************************************************************/