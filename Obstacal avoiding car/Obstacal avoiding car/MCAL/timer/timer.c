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

ISR(TIMER2_OVF)
{
	if(sg_Timer2_callBackPtr != NULL)
	{
		//The timer2 overflow  occurred (must be cleared in software) 
		CLEAR_BIT(TIFR,TOV2);
		//Call the Call Back function in the upper layer after the timer overflow
		(sg_Timer2_callBackPtr)();
	}
}

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
				TCNT2 = st_config->u16_timer_InitialValue & U8_BIT_REG_MASK;
				/*Configure the TIMER2 with normal  mode value and enable the interrupt for this mode if interrupt feature activated */
				/*Make FOC2 to be Active as it is overflow mode(for non-PWM mode)*/
				SET_BIT(TCCR2,FOC2);
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

u8_en_timerErrorsType vidTimer2_OvfIrqEnable(void)
{
	u8_en_timerErrorsType errorStatus = TIMER_E_OK;

	SET_BIT(TIFR, 6);
	SET_BIT(TIMSK, TOIE2);
//	SET_BIT(SREG, 7);

	return errorStatus;
}

/*************************************************************************************************************/
u8_en_timerErrorsType vidTimer2_OvfIrqDisable(void)
{
	u8_en_timerErrorsType errorStatus = TIMER_E_OK;

	CLEAR_BIT(TIMSK, TOIE2);

	return errorStatus;
}

/*************************************************************************************************************/
void MTIMER_vidResetTCNT(void)
{
	TCNT2 = 0;
}


/*************************************************************************************************************/
uint8_t MTIMER_u8GetTCNT(void)
{
	return TCNT2;
}

/********************************************************************************************
 * 								END
*********************************************************************************************/