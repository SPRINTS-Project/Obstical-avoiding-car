/*
 * lcd.h
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 


#ifndef LCD_H_
#define LCD_H_

//#include "../../MCAL/dio/dio.h"
#include "../../STD_LIBRARIES/bit_math.h"

typedef struct
{
	uint8_t u8_mode;
	uint8_t u8_d0Pin[2];
	uint8_t u8_d1Pin[2];
	uint8_t u8_d2Pin[2];
	uint8_t u8_d3Pin[2];
	uint8_t u8_d4Pin[2];
	uint8_t u8_d5Pin[2];
	uint8_t u8_d6Pin[2];
	uint8_t u8_d7Pin[2];
	
	uint8_t u8_RSpin[2];
	uint8_t u8_RWpin[2];
	uint8_t u8_Epin[2];
}st_lcdConfigType;


typedef uint8_t u8_en_lcdModeType;

#define LCD_4_BIT_MODE				((u8_en_lcdModeType)0x00)
#define LCD_8_BIT_MODE				((u8_en_lcdModeType)0x01)
#define LCD_INVALID_MODE			((u8_en_lcdModeType)0x02)


typedef uint8_t u8_en_lcdErrorsType;

#define LCD_E_OK				((u8_en_lcdErrorsType)0x00)
#define LCD_E_NOT_OK			((u8_en_lcdErrorsType)0x05)


typedef uint8_t u8_en_lcdSpCharType;


#define LCD_BELL					((u8_en_lcdSpCharType)0X03)



u8_en_lcdErrorsType LCD_init (st_lcdConfigType* st_config);
u8_en_lcdErrorsType LCD_cmd(st_lcdConfigType* st_config,uint8_t cmd);
 void LCD_char(st_lcdConfigType* st_config,uint8_t data);
u8_en_lcdErrorsType LCD_clear (void);
u8_en_lcdErrorsType LCD_setCursor (uint8_t u8_row,uint8_t u8_col);
u8_en_lcdErrorsType LCD_writeString (uint8_t* u8_data);
u8_en_lcdErrorsType LCD_writeSpChar (u8_en_lcdSpCharType u8_SpChar);
void LCD_WriteInt(Uint32_t number);
/*
void ENABLE(void);
*/
#endif /* KEYPAD_H	*/