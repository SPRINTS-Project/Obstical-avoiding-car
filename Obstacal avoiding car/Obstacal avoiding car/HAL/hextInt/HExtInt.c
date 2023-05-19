/*
 * HExtInt.c
 *
 *  Created on: Apr 5, 2023
 *      Author: hp
 */

#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
//#include "../../MCAL/ExtInt/EXTINT_Interface.h"
#include "../../MCAL/dio/dio.h"
#include "HExtInt.h"
#include "hextInt_cfg.h"


ptr_func cbf = NULL;

enu_HExtIntError_t HExtInt_enInit(en_int_type_t enExtint, en_sns_ctrl_t snsCtrl)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;
	#if HEXTINT_TYPE  == HEXTINT_INT0
	(void) DIO_init(INT_0_PIN, STD_INPUT);
	(void) DIO_writePIN(INT_0_PIN, STD_LOW);
	
	#elif HEXTINT_TYPE  == HEXTINT_INT1
	(void) DIO_init(INT_1_PIN, STD_INPUT);
	(void) DIO_writePIN(INT_1_PIN, STD_LOW);	
	#endif
	
	vidExtInt_init(enExtint , snsCtrl );

	return errorStatus;

}

enu_HExtIntError_t HExtInt_enCBFInt0(ptr_func pFunc)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (pFunc != NULL)
	{
		MEXTINT_vidCallBackFuncInt0(pFunc);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}


	return errorStatus;

}

enu_HExtIntError_t HExtInt_enCBFInt1(ptr_func pFunc)
{
	enu_HExtIntError_t errorStatus = HEXTINT_OK;

	if (pFunc != NULL)
	{
		MEXTINT_vidCallBackFuncInt1(pFunc);
	}
	else
	{
		errorStatus = HEXTINT_NOK;
	}


	return errorStatus;
}

void HExtInt0_enIntDisable(void)
{
	MEXTINT_vidDisableInterrupt();
}

void HExtInt0_enIntEnable(void)
{
	 MEXTINT_vidEnableInterrupt();
}

