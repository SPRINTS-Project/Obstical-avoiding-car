/************************************************************************************************/
/*									INCLUDES													*/
/************************************************************************************************/
#include <avr/interrupt.h>
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "EXTINT_Private.h"
#include "EXTINT_Interface.h"


/************************************************************************************************/
/*									USER_DEFINED TYPES											*/
/************************************************************************************************/
ptr_func callBackFuncInt0 = NULL;
ptr_func callBack = NULL;
ptr_func callBackFunc = NULL;

/************************************************************************************************/
/*									FUNCTION_IMPLEMENTATION										*/
/************************************************************************************************/

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidExtInt_init
 * description 	: func to write integer number on lcd
 * in[1]	 	: enExtint : Interrupt type [INT0, INT1. INT2]
 * in[2]		: snsCtrl  : Sense Control {ANY_LOGICAL, FALL_EDGE, RISE_EDGE}
 * return		: Uint8_t : return error Status  {E_INT_OK ,E_INT_NOK }
 * */
uint8_t vidExtInt_init(en_int_type_t enIntType, en_sns_ctrl_t enSensControl)
{
	uint8_t err_status = E_INT_OK;
	if(enIntType < INT_TYPE_INVALID && enSensControl < SENS_CONTROL_INVALID)
	{
		if (enIntType == INT_0)
		{
			switch (enSensControl)
			{
				case LOW_LEVEL 	: CLEAR_BIT(MCUCR_REG, ISC00); CLEAR_BIT(MCUCR_REG, ISC01); break;
				case ANY_LOGICAL: SET_BIT(MCUCR_REG, ISC00); CLEAR_BIT(MCUCR_REG, ISC01); break;
				case FALL_EDGE 	: CLEAR_BIT(MCUCR_REG, ISC00); SET_BIT(MCUCR_REG, ISC01); break;
				case RISE_EDGE 	: SET_BIT(MCUCR_REG, ISC00); SET_BIT(MCUCR_REG, ISC01); break;
				default : err_status = E_INT_NOK; break;
			}

// 			SET_BIT(GIFR_REG, INTF0);	// to clear flag for Interrupt 0
// 			SET_BIT(GICR_REG, INT0);
			
		}
		else if (enIntType == INT_1)
		{
			switch (enSensControl)
			{
				case LOW_LEVEL 	: CLEAR_BIT(MCUCR_REG, ISC10); CLEAR_BIT(MCUCR_REG, ISC11); break;
				case ANY_LOGICAL: SET_BIT(MCUCR_REG, ISC10); CLEAR_BIT(MCUCR_REG, ISC11); break;
				case FALL_EDGE 	: CLEAR_BIT(MCUCR_REG, ISC10); SET_BIT(MCUCR_REG, ISC11); break;
				case RISE_EDGE 	: SET_BIT(MCUCR_REG, ISC10); SET_BIT(MCUCR_REG, ISC11); break;
				default : err_status = E_INT_NOK; break;
			}
			SET_BIT(GICR_REG, INT1);
			SET_BIT(GIFR_REG, INTF1);	// to clear flag for Interrupt 1
		}
		else if (enIntType == INT_2)
		{
			switch (enSensControl)
			{
				case FALL_EDGE 	: CLEAR_BIT(MCUCSR_REG, ISC2);  break;
				case RISE_EDGE 	: SET_BIT(MCUCSR_REG, ISC2);  break;
				default : err_status = E_INT_NOK; break;
			}
// 			SET_BIT(GICR_REG, INT2);
// 			SET_BIT(GIFR_REG, INTF2);  // to clear flag for Interrupt 2
		}
	}
	else
	{
		err_status = E_INT_NOK;
	}

	/*SET_BIT(SREG_REG, I);*/ // enable global interrupt
//	CLEAR_BIT(SREG_REG, I);

	return err_status;
}



void MEXTINT_vidCallBackFuncInt0(ptr_func funcCopy)
{
	
	callBackFuncInt0 = funcCopy;
}

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidCallBackFunc
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
void MEXTINT_vidCallBackFunc(ptr_func funcCopy)
{
	callBack = funcCopy;

}


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: vidCallBackFuncInt1
 * description 	: Take pointer to function to be executed in ISR when it fires
 * input param 	: pointer to function
 * return		: void
 * */
void MEXTINT_vidCallBackFuncInt1(ptr_func funcCopy)
{
	callBackFunc = funcCopy;

}



/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidWaitFlag
 * description 	: it INT is disabled , this function pollying on flag
 * input param 	: void
 * return		: void
 * */
void MEXTINT_vidWaitFlag(void)
{
	while( !( READ_BIT(GIFR_REG, INTF0) ) );
}

/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidDisableInterrupt
 * description 	: Disable EXTINT
 * input param 	: void
 * return		: void
 * */
void MEXTINT_vidDisableInterrupt(void)
{
	CLEAR_BIT(GICR_REG, INT0);
}


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidEnableInterrupt
 * description 	: ENABLE extint
 * input param 	: void
 * return		: void
 * */
void MEXTINT_vidEnableInterrupt(void)
{
	SET_BIT(GIFR_REG, INTF0);
	SET_BIT(GICR_REG, INT0);
}

void MEXTINT2_vidDisableInterrupt(void)
{
	CLEAR_BIT(GICR_REG, INT2);
}


/*
 * Author		: Bassel Yasser Mahmoud
 * function		: MEXTINT_vidEnableInterrupt
 * description 	: ENABLE extint
 * input param 	: void
 * return		: void
 * */
void MEXTINT2_vidEnableInterrupt(void)
{
		SET_BIT(GICR_REG, INT2);
		SET_BIT(GIFR_REG, INTF2);
}

/************************************************************************************************/
/*									ISR															*/
/************************************************************************************************/
ISR(INT0_vect)
{
	callBackFuncInt0();
}

ISR(INT1_vect)
{
	callBackFunc();
}

ISR(INT2_vect)
{
	callBack();
}
/************************************************************************************************/
/*									END															*/
/************************************************************************************************/