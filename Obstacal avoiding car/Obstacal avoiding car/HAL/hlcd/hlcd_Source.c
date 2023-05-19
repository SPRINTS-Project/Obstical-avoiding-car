/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Source.c
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Function Implementation
 * 					- void HLCD_vidInit(void)
 * 					- void HLCD_vidWritecmd(uint8_t u8commandCopy)
 * 					- void HLCD_vidWriteChar(uint8_t u8CharCopy)
 * 					- void HLCD_ClrDisplay(void)
 * 					- void HLCD_ShiftLeft(void)
 * 					- void HLCD_gotoXY(uint8_t row, uint8_t pos)
 * 					- void HLCD_WriteString(uint8_t* str)
 * 					- void HLCD_WriteInt(Uint32_t number)
 * 					- void HLCD_WriteArabic(uint8_t u8ArCharCopy)
 * 					- void HLCD_vidCreatCustomChar(uint8_t* pu8custom, uint8_t u8Location)
 */

/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include <util/delay.h>
#include <stdlib.h>
//#include "../../Common/std_types.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "../../MCAL/dio/dio.h"
#include "HLCD_Interface.h"
#include "HLCD_Configure.h"

/**************************************************************************************************
 * 										Macros
 *************************************************************************************************/

#define HLCD_CLEAR_DISPLAY					0x01
#define HLCD_CURSOR_HOME					0x02
#define HLCD_ENTRY_MODE_CURSOR_INCREMENT	0x06
#define HLCD_DISPLAY_ON_CURSOR_ON_NO_BLINK	0x0E
#define HLCD_DISPLAY_ON_CURSOR_OFF_NO_BLINK	0x0C
#define HLCD_4_BIT_MODE_SELECTION			0x28
#define HLCD_8_BIT_MODE_SELECTION			0x38
#define HLCD_DISPLAY_SHIFT_LEFT				0x18
#define HLCD_DISPLAY_SHIFT_RIGHT			0x1C
#define LCD_SET_CGRAM_ADDR_CMD				0x40

#define INDEX		10
/**************************************************************************************************
 * 										Global Variables
 *************************************************************************************************/
#if HLCD_MODE == HLCD_4_BIT_MODE

extern st_lcdDataPin_t dataPin[4];

#elif HLCD_MODE == HLCD_8_BIT_MODE

extern st_lcdDataPin_t dataPin[8];


#endif


/**************************************************************************************************
 * 						functions implementation
 *************************************************************************************************/
/*
 * function		: HLCD_vidInit
 * description 	: func to set LCD initialization
 * input param 	: void
 * return		: u8_en_lcdErrorsType
 **/
u8_en_lcdErrorsType HLCD_vidInit(void)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |= DIO_init(dataPin[i].en_dataPort,dataPin[i].en_dataPin,STD_OUTPUT);
	}

	errorStatus |= DIO_init(LCD_RS_PORT_PIN,STD_OUTPUT);
	errorStatus |= DIO_init(LCD_RW_PORT_PIN,STD_OUTPUT);
	errorStatus |= DIO_init(LCD_EN_PORT_PIN,STD_OUTPUT);

	_delay_ms(40);

	errorStatus |= HLCD_vidWritecmd(HLCD_CURSOR_HOME);
	_delay_ms(1);
#if HLCD_MODE == HLCD_4_BIT_MODE

	errorStatus |= HLCD_vidWritecmd(HLCD_4_BIT_MODE_SELECTION);
	_delay_ms(1);

#elif HLCD_MODE == HLCD_8_BIT_MODE
	errorStatus |= HLCD_vidWritecmd(HLCD_8_BIT_MODE_SELECTION);
	_delay_ms(1);
#endif
	errorStatus |= HLCD_vidWritecmd(HLCD_CLEAR_DISPLAY);
	_delay_ms(4);

	errorStatus |= HLCD_vidWritecmd(HLCD_ENTRY_MODE_CURSOR_INCREMENT);
	_delay_ms(1);

	errorStatus |= HLCD_vidWritecmd(HLCD_DISPLAY_ON_CURSOR_OFF_NO_BLINK);
	_delay_ms(1);
	
	return errorStatus;
}



/*
 * function		: HLCD_vidWritecmd
 * description 	: func to configure some commands on lcd
 * input param 	:
 * 					u8commandCopy --> take lcd cmd instructions from instruction table <https://components101.com/sites/default/files/component_datasheet/16x2%20LCD%20Datasheet.pdf>
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_vidWritecmd(uint8_t u8commandCopy)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	errorStatus |= DIO_writePIN(LCD_RW_PORT_PIN, STD_LOW); // WRITE
	errorStatus |= DIO_writePIN(LCD_RS_PORT_PIN, STD_LOW); // CMD

#if HLCD_MODE == HLCD_4_BIT_MODE

	uint8_t loc_u8DataReg = 0;
	loc_u8DataReg = (u8commandCopy & 0xF0);
	loc_u8DataReg >>= 4;

	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |= DIO_writePIN(dataPin[i].en_dataPort,dataPin[i].en_dataPin , ((loc_u8DataReg >> i)&1) );
	}

	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_HIGH); //ENABLE STD_HIGH
	_delay_ms(1);
	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_LOW); //ENABLE STD_LOW

	_delay_us(200);

	loc_u8DataReg = (u8commandCopy & 0x0F);

	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |= DIO_writePIN(dataPin[i].en_dataPort,dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}
	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_HIGH); //ENABLE STD_HIGH
	_delay_ms(1);
	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_LOW); //ENABLE STD_LOW
	_delay_ms(2);

#elif HLCD_MODE == HLCD_8_BIT_MODE
	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |= DIO_writePIN(dataPin[i].en_dataPort,dataPin[i].en_dataPin, ((u8commandCopy >> i)&1) );
	}

	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_HIGH); //ENABLE STD_HIGH
	_delay_ms(2);
	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_LOW); //ENABLE STD_LOW
	_delay_ms(2);
#endif

return errorStatus;
}



/*
 * function		: HLCD_vidWriteChar
 * description 	: func to write char on lcd
 * input param 	: u8CharCopy -> take ascii code of char   or   char address on CGROM
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_vidWriteChar(uint8_t u8CharCopy)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	errorStatus |= DIO_writePIN(LCD_RW_PORT_PIN, STD_LOW); // WRITE
	errorStatus |= DIO_writePIN(LCD_RS_PORT_PIN, STD_HIGH); // DATA

#if HLCD_MODE == HLCD_4_BIT_MODE

	uint8_t loc_u8DataReg = 0;
	loc_u8DataReg = (u8CharCopy & 0xF0);
	loc_u8DataReg >>= 4;

	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |= DIO_writePIN(dataPin[i].en_dataPort,dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}

	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_HIGH); //ENABLE STD_HIGH
	_delay_ms(1);
	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_LOW); //ENABLE STD_LOW

	_delay_us(200);

	loc_u8DataReg = (u8CharCopy & 0x0F);

	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |= DIO_writePIN(dataPin[i].en_dataPort,dataPin[i].en_dataPin, ((loc_u8DataReg >> i)&1) );
	}

	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_HIGH); //ENABLE STD_HIGH
	_delay_ms(1);
	errorStatus |=  DIO_writePIN(LCD_EN_PORT_PIN, STD_LOW); //ENABLE STD_LOW
	_delay_ms(2);


#elif HLCD_MODE == HLCD_8_BIT_MODE
	for (uint8_t i = 0; i < DATA_PIN_NUMBER; i++)
	{
		errorStatus |=  DIO_writePIN(dataPin[i].en_dataPort,dataPin[i].en_dataPin, ((u8CharCopy >> i)&1) );
	}

	errorStatus |=  DIO_writePIN(LCD_EN_PORT_PIN, STD_HIGH); //ENABLE STD_HIGH
	_delay_ms(2);
	errorStatus |= DIO_writePIN(LCD_EN_PORT_PIN, STD_LOW); //ENABLE STD_LOW
#endif
	return errorStatus;

}


/*
 * function		: HLCD_ClrDisplay
 * description 	: func to clear anything on lcd
 * input param 	: void
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_ClrDisplay(void)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	errorStatus |= HLCD_vidWritecmd(HLCD_CLEAR_DISPLAY);
	_delay_ms(4);
	errorStatus |= HLCD_vidWritecmd(HLCD_CURSOR_HOME);
	_delay_ms(4);
	return errorStatus;

}



/*
 * function		: HLCD_ShiftLeft
 * description 	: func to shift the lcd display from right to left
 * input param 	: void
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_ShiftLeft(void)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	errorStatus = HLCD_vidWritecmd(HLCD_DISPLAY_SHIFT_LEFT);
	_delay_ms(1);
	return errorStatus;

}



/*
 * function		: HLCD_gotoXY
 * description 	: func to determine position which char print at this position on lcd  ### NOTE : (2rows x 16coloms)
 * input param 	:
 * 				  row -> take row number 0 or 1
 * 				  pos -> take colom number from 0 ~ 16
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_gotoXY(uint8_t row, uint8_t pos)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	if (row==0 && pos < 16)
	{
		errorStatus |= HLCD_vidWritecmd((pos & 0x0F)| 0x80);
	}
	else if (row==1 && pos < 16)
	{
		errorStatus |= HLCD_vidWritecmd((pos & 0x0F)| 0xC0);
	}
	else
	{
		errorStatus |= LCD_E_NOT_OK;
	}
	return errorStatus;
}




/*
 * function		: HLCD_WriteString
 * description 	: func to write string on lcd
 * input param 	: str --> which take string as argument
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_WriteString(uint8_t* str)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	Uint16_t count = 0;
	uint8_t string = str[count];
	while(string)
	{
		errorStatus |= HLCD_vidWriteChar(string);
		string = str[++count];
	}
	return errorStatus;
}



/*
 * function		: HLCD_WriteInt
 * description 	: func to write integer number on lcd
 * input param 	: number --> which take number as argument
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_WriteInt(Uint32_t number)
{
	u8_en_lcdErrorsType errorStatus = LCD_E_OK;
	uint8_t STR[INDEX];
	itoa(number, STR, 10);
	errorStatus |= HLCD_WriteString(STR);
	return errorStatus;
}


/*
 * function		: HLCD_WriteArabic
 * description 	: func to write Arabic string on lcd
 * input param 	: u8ArCharCopy --> which take string as argument
 * return		: void
 * */
void HLCD_WriteArabic(uint8_t u8ArCharCopy)
{
	HLCD_vidWritecmd(0x04);
	HLCD_vidWriteChar(u8ArCharCopy);
}



/*
 * function		: HLCD_vidCreatCustomChar
 * description 	: func to store new patterm on CGRAM
 * input param 	:
 * 				  pu8custom  -> take pointer to array which having LCD Custom Character Generated data ### take only 8 characters
 * 				  u8Location -> determine location on CGRAM [0 ~ 8]
 * return		: void
 * */
void HLCD_vidCreatCustomChar(uint8_t* pu8custom, uint8_t u8Location)
{
	if (u8Location < 8)  // CGRAM only store 8 characters
	{
		HLCD_vidWritecmd(LCD_SET_CGRAM_ADDR_CMD + (u8Location*8));
		_delay_ms(1);
		for (uint8_t i = 0; i < 8 ; i++)
		{
			HLCD_vidWriteChar(pu8custom[i]);
		}
	}
}
/**************************************************************************************************
* 											END
*************************************************************************************************/



