/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Configure.c
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Pin Configuration For LCD
 */


/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include "../../MCAL/dio/dio_types.h"
#include "HLCD_Interface.h"
#include "HLCD_Configure.h"



/**************************************************************************************************
 * 											User Defined Pins
 *************************************************************************************************/
#if HLCD_MODE == HLCD_4_BIT_MODE


st_lcdDataPin_t dataPin[4] = {
		{portd,pin4},
		{portd,pin5},
		{portd,pin6},
		{portd,pin7}
};

#elif HLCD_MODE == HLCD_8_BIT_MODE

st_lcdDataPin_t dataPin[8] = {
		{portc,pin0},
		{portc,pin1},
		{portc,pin2},
		{portc,pin3},
		{portc,pin4},
		{portc,pin5},
		{portc,pin6},
		{portc,pin7}
};


#endif

/**************************************************************************************************
 * 											END
 *************************************************************************************************/
