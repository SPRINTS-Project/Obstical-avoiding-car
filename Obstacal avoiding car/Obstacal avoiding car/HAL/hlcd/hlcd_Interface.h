/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Interface.h
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Function Prototypes
 */

/**************************************************************************************************
 * 											File Guard
 *************************************************************************************************/
#ifndef HAL_HLCD_HLCD_INTERFACE_H_
#define HAL_HLCD_HLCD_INTERFACE_H_

/**************************************************************************************************
 * 											Includes
 *************************************************************************************************/
#include "../../STD_LIBRARIES/STD_TYPES.h"

/**************************************************************************************************
 * 											Macros
 *************************************************************************************************/
#define HLCD_8_BIT_MODE				0
#define HLCD_4_BIT_MODE				1

typedef uint8_t u8_en_lcdErrorsType;

#define LCD_E_OK				((u8_en_lcdErrorsType)0x00)
#define LCD_E_NOT_OK			((u8_en_lcdErrorsType)0x08)
/**************************************************************************************************
 * 											functions prototype
 *************************************************************************************************/
/*
 * function		: HLCD_vidInit
 * description 	: func to set LCD initialization
 * input param 	: void
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_vidInit(void);

/*
 * function		: HLCD_vidWritecmd
 * description 	: func to configure some commands on lcd
 * input param 	:
 * 					u8commandCopy --> take lcd cmd instructions from instruction table <https://components101.com/sites/default/files/component_datasheet/16x2%20LCD%20Datasheet.pdf>
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_vidWritecmd(uint8_t u8commandCopy);



/*
 * function		: HLCD_vidWriteChar
 * description 	: func to write char on lcd
 * input param 	: u8CharCopy -> take ascii code of char   or   char address on CGROM
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_vidWriteChar(uint8_t u8CharCopy);


/*
 * function		: HLCD_ClrDisplay
 * description 	: func to clear anything on lcd
 * input param 	: void
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_ClrDisplay(void);


/*
 * function		: HLCD_ShiftLeft
 * description 	: func to shift the lcd display from right to left
 * input param 	: void
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_ShiftLeft(void);


/*
 * function		: HLCD_gotoXY
 * description 	: func to determine position which char print at this position on lcd  ### NOTE : (2rows x 16coloms)
 * input param 	:
 * 				  row -> take row number 0 or 1
 * 				  pos -> take colom number from 0 ~ 16
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_gotoXY(uint8_t row, uint8_t pos);


/*
 * function		: HLCD_WriteString
 * description 	: func to write string on lcd
 * input param 	: str --> which take string as argument
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_WriteString(uint8_t* str);



/*
 * function		: HLCD_WriteInt
 * description 	: func to write integer number on lcd
 * input param 	: number --> which take number as argument
 * return		: u8_en_lcdErrorsType
 * */
u8_en_lcdErrorsType HLCD_WriteInt(Uint32_t number);



/*
 * function		: HLCD_WriteArabic
 * description 	: func to write Arabic string on lcd
 * input param 	: u8ArCharCopy --> which take string as argument
 * return		: void
 * */
void HLCD_WriteArabic(uint8_t u8ArCharCopy);




/*
 * function		: HLCD_vidCreatCustomChar
 * description 	: func to store new patterm on CGRAM
 * input param 	:
 * 				  pu8custom  -> take pointer to array which having LCD Custom Character Generated data ### take only 8 characters
 * 				  u8Location -> determine location on CGRAM [0 ~ 8]
 * return		: void
 * */
void HLCD_vidCreatCustomChar(uint8_t* pu8custom, uint8_t u8Location);



#endif /* HAL_HLCD_HLCD_INTERFACE_H_ */


/**************************************************************************************************
 * 											END
 *************************************************************************************************/
