/*
 * AUTHOR		: Bassel Yasser
 * FILE			: HLCD_Configure.h
 * DATE			: Apr 16, 2023
 * DESCRIPTION	: Pin Configuration For LCD
 */

/**************************************************************************************************
 * 											File Guard
 *************************************************************************************************/
#ifndef HAL_HLCD_HLCD_CONFIGURE_H_
#define HAL_HLCD_HLCD_CONFIGURE_H_

 /**************************************************************************************************
  * 											Macros
  *************************************************************************************************/
/*
 * Choosing LCD mode:
 *
 * 		HLCD_4_BIT_MODE  for 4 bit mode
 * 		HLCD_8_BIT_MODE  for 8 bit mode
 */
#define HLCD_MODE		HLCD_4_BIT_MODE
/*************************************************************************************************/

#define LCD_RS_PORT_PIN		portc,pin7
#define LCD_RW_PORT_PIN		portd,pin0
#define LCD_EN_PORT_PIN		portd,pin1
/*************************************************************************************************/



/*
 * Mode Selection
 */
#if HLCD_MODE == HLCD_4_BIT_MODE

#define DATA_PIN_NUMBER		4

#elif HLCD_MODE == HLCD_8_BIT_MODE

#define DATA_PIN_NUMBER		8


#endif
/*************************************************************************************************/


 /**************************************************************************************************
  * 									User Defined Data types
  *************************************************************************************************/
typedef struct
{
	en_dioPortsType en_dataPort;
	en_dioPinsType en_dataPin;

}st_lcdDataPin_t;


#endif /* HAL_HLCD_HLCD_CONFIGURE_H_ */


/**************************************************************************************************
 * 											END
 *************************************************************************************************/
