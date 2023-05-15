/*
 * keypad_and_LCD_intergration.c
 *
 * Created: 4/22/2023 3:16:32 PM
 *  Author: basel
 */ 
/*#include"keypad.h"
#include"../lcd/lcd.h"
 st_lcdConfigType st_gs_lcdConfig;
 st_keypadConfigType st_gs_keypadConfig;
int main()
{
	st_gs_lcdConfig.u8_mode = LCD_4_BIT_MODE;
	st_gs_lcdConfig.u8_d4Pin[0] = porta;
	st_gs_lcdConfig.u8_d4Pin[1] = pin0;
	st_gs_lcdConfig.u8_d5Pin[0] = porta;
	st_gs_lcdConfig.u8_d5Pin[1] = pin1;
	st_gs_lcdConfig.u8_d6Pin[0] = porta;
	st_gs_lcdConfig.u8_d6Pin[1] = pin2;
	st_gs_lcdConfig.u8_d7Pin[0] = porta;
	st_gs_lcdConfig.u8_d7Pin[1] = pin3;
	st_gs_lcdConfig.u8_RSpin[0]=porta;
	st_gs_lcdConfig.u8_RSpin[1]=pin4;
	st_gs_lcdConfig.u8_RWpin[0]=porta;
	st_gs_lcdConfig.u8_RWpin[1]=pin5;
	st_gs_lcdConfig.u8_Epin[0]=porta;
	st_gs_lcdConfig.u8_Epin[1]=pin6;
	LCD_init(&st_gs_lcdConfig);

	
	
		st_gs_keypadConfig.u8_col1Pin[0] = portc;
		st_gs_keypadConfig.u8_col1Pin[1] = pin3;
		st_gs_keypadConfig.u8_col2Pin[0] = portc;
		st_gs_keypadConfig.u8_col2Pin[1] = pin4;
		st_gs_keypadConfig.u8_col3Pin[0] = portc;
		st_gs_keypadConfig.u8_col3Pin[1] = pin5;
		st_gs_keypadConfig.u8_col4Pin[0] = portc;
		st_gs_keypadConfig.u8_col4Pin[1] = pin6;
		st_gs_keypadConfig.u8_row1Pin[0] = portc;
		st_gs_keypadConfig.u8_row1Pin[1] = pin0 ;
		st_gs_keypadConfig.u8_row2Pin[0] = portc;
		st_gs_keypadConfig.u8_row2Pin[1] = pin1 ;
		st_gs_keypadConfig.u8_row3Pin[0] = portc;
		st_gs_keypadConfig.u8_row3Pin[1] = pin2 ;
	KEYPAD_init(&st_gs_keypadConfig);
	uint8_t value;
	
	
	
	while(1)
	{	KEYPAD_read(&value);
		if(value !='N')
		{
			LCD_char(&st_gs_lcdConfig,value);
		}
		
		
	}
}*/