/*
 * lcd.c
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 



#include "lcd.h"
#include "stdlib.h"
#include <string.h>
#include "../../MCAL/dio/dio.h"
#define F_CPU 8000000U
#include<util/delay.h>
st_lcdConfigType st_gs_lcdConfig;
static uint8_t mode;
static void ENABLE(void);



u8_en_lcdErrorsType LCD_init (st_lcdConfigType* st_config)
{
	u8_en_lcdErrorsType ret_val=LCD_E_OK;
	ret_val |=DIO_init(st_config->u8_RSpin[0],st_config->u8_RSpin[1],STD_OUTPUT);
	ret_val |=DIO_init(st_config->u8_RWpin[0],st_config->u8_RWpin[1],STD_OUTPUT);
	ret_val |=DIO_init(st_config->u8_Epin[0],st_config->u8_Epin[1],STD_OUTPUT);
	switch(st_config->u8_mode)
	{
		case LCD_4_BIT_MODE	: 
		                        LCD_cmd(st_config,0x02);
		                        LCD_cmd(st_config,0x28);
		                        LCD_cmd(st_config,0x0C);
		                        LCD_cmd(st_config,0x06);
		                        LCD_cmd(st_config,0x01);
								ret_val |=DIO_init(st_config->u8_d4Pin[0],st_config->u8_d4Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d5Pin[0],st_config->u8_d5Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d6Pin[0],st_config->u8_d6Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d7Pin[0],st_config->u8_d7Pin[1],STD_OUTPUT);
								break;
								
	case LCD_8_BIT_MODE	: 
		                        LCD_cmd(st_config,0x38);
		                        LCD_cmd(st_config,0x0C);
		                        LCD_cmd(st_config,0x06);
		                        LCD_cmd(st_config,0x01);
		                        ret_val |=DIO_init(st_config->u8_d0Pin[0],st_config->u8_d0Pin[1],STD_OUTPUT);
		                        ret_val |=DIO_init(st_config->u8_d1Pin[0],st_config->u8_d1Pin[1],STD_OUTPUT);
		                        ret_val |=DIO_init(st_config->u8_d2Pin[0],st_config->u8_d2Pin[1],STD_OUTPUT);
		                        ret_val |=DIO_init(st_config->u8_d3Pin[0],st_config->u8_d3Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d4Pin[0],st_config->u8_d4Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d5Pin[0],st_config->u8_d5Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d6Pin[0],st_config->u8_d6Pin[1],STD_OUTPUT);
								ret_val |=DIO_init(st_config->u8_d7Pin[0],st_config->u8_d7Pin[1],STD_OUTPUT);
								break;
	default: ret_val=LCD_E_NOT_OK;
				break;
								
	}
	mode=st_config->u8_mode;
	
	/*st_gs_lcdConfig = st_config;*/
	memcpy(&st_gs_lcdConfig,st_config, strlen(st_config)+1);
	return ret_val;
}
u8_en_lcdErrorsType LCD_clear (void)
{

	u8_en_lcdErrorsType ret_val=LCD_E_OK;
	ret_val |=LCD_cmd(&st_gs_lcdConfig,0x01);
	return ret_val;

}
u8_en_lcdErrorsType LCD_setCursor (uint8_t u8_row,uint8_t u8_col)
{
	u8_en_lcdErrorsType ret_val=LCD_E_OK;
	switch(u8_row)
	{
		case 1 : LCD_cmd(&st_gs_lcdConfig,0x80+u8_col-1);break;
		case 2 :LCD_cmd(&st_gs_lcdConfig,0xc0+u8_col-1);break;	
		default:ret_val=LCD_E_NOT_OK;break;
	}

	return ret_val;

}
u8_en_lcdErrorsType LCD_writeString (uint8_t* u8_data)
{
	uint8_t i=0;
	u8_en_lcdErrorsType ret_val=LCD_E_OK;
	if(u8_data==(void*)0)
	{
		ret_val=LCD_E_NOT_OK;
	}

	else
	{
		while(u8_data[i] !='\0')
		{
			LCD_char(&st_gs_lcdConfig,u8_data[i]);
			i++;
			
		}
	}
	return ret_val;
	

}
u8_en_lcdErrorsType LCD_writeSpChar (u8_en_lcdSpCharType u8_SpChar)
{   u8_en_lcdErrorsType ret_val=LCD_E_OK;
	uint8_t sp_char[]= {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
	uint8_t i;
	LCD_cmd(&st_gs_lcdConfig,0x40+( u8_SpChar* 8));
	for(i=0;i<8;i++)
	{
		LCD_char(&st_gs_lcdConfig,sp_char[i]);
	}	
	
	LCD_cmd(&st_gs_lcdConfig,0xc0);
	LCD_char(&st_gs_lcdConfig,LCD_BELL);
	return ret_val;
}
u8_en_lcdErrorsType LCD_cmd(st_lcdConfigType* st_config,uint8_t cmd)
{   u8_en_lcdErrorsType ret_val=LCD_E_OK;
	DIO_writePIN(st_config->u8_Epin[0],st_config->u8_Epin[1],STD_LOW);
	DIO_writePIN(st_config->u8_RSpin[0],st_config->u8_RSpin[1],STD_LOW);
	DIO_writePIN(st_config->u8_RWpin[0],st_config->u8_RWpin[1],STD_LOW);
	if(mode==LCD_4_BIT_MODE)
	{
		
		DIO_writePIN(st_config->u8_d7Pin[0],st_config->u8_d7Pin[1],READ_BIT(cmd,7));
		DIO_writePIN(st_config->u8_d6Pin[0],st_config->u8_d6Pin[1],READ_BIT(cmd,6));
		DIO_writePIN(st_config->u8_d5Pin[0],st_config->u8_d5Pin[1],READ_BIT(cmd,5));
		DIO_writePIN(st_config->u8_d4Pin[0],st_config->u8_d4Pin[1],READ_BIT(cmd,4));
		ENABLE();
		_delay_ms(3);
	    DIO_writePIN(st_config->u8_d7Pin[0],st_config->u8_d7Pin[1],READ_BIT(cmd,3));
    	DIO_writePIN(st_config->u8_d6Pin[0],st_config->u8_d6Pin[1],READ_BIT(cmd,2));
    	DIO_writePIN(st_config->u8_d5Pin[0],st_config->u8_d5Pin[1],READ_BIT(cmd,1));
	    DIO_writePIN(st_config->u8_d4Pin[0],st_config->u8_d4Pin[1],READ_BIT(cmd,0));
		ENABLE();
		_delay_ms(3);
	}
	else if(mode==LCD_8_BIT_MODE)
	{
		
	}
	else
	{
		//do nothing
		ret_val=LCD_E_NOT_OK;
	}
	return ret_val;
}
  void LCD_char(st_lcdConfigType* st_config,uint8_t cmd)
{
	DIO_writePIN(st_config->u8_Epin[0],st_config->u8_Epin[1],STD_LOW);
	DIO_writePIN(st_config->u8_RSpin[0],st_config->u8_RSpin[1],STD_HIGH);
	DIO_writePIN(st_config->u8_RWpin[0],st_config->u8_RWpin[1],STD_LOW);
	if(mode==LCD_4_BIT_MODE)
	{
		
		DIO_writePIN(st_config->u8_d7Pin[0],st_config->u8_d7Pin[1],READ_BIT(cmd,7));
		DIO_writePIN(st_config->u8_d6Pin[0],st_config->u8_d6Pin[1],READ_BIT(cmd,6));
		DIO_writePIN(st_config->u8_d5Pin[0],st_config->u8_d5Pin[1],READ_BIT(cmd,5));
		DIO_writePIN(st_config->u8_d4Pin[0],st_config->u8_d4Pin[1],READ_BIT(cmd,4));
		ENABLE();
		_delay_ms(3);
		DIO_writePIN(st_config->u8_d7Pin[0],st_config->u8_d7Pin[1],READ_BIT(cmd,3));
		DIO_writePIN(st_config->u8_d6Pin[0],st_config->u8_d6Pin[1],READ_BIT(cmd,2));
		DIO_writePIN(st_config->u8_d5Pin[0],st_config->u8_d5Pin[1],READ_BIT(cmd,1));
		DIO_writePIN(st_config->u8_d4Pin[0],st_config->u8_d4Pin[1],READ_BIT(cmd,0));
		ENABLE();
		_delay_ms(3);
	}
	else if(mode==LCD_8_BIT_MODE)
	{
		
	}
	else
	{
		//do nothing
	}
}
void ENABLE(void)
{
	
	DIO_writePIN(st_gs_lcdConfig.u8_Epin[0],st_gs_lcdConfig.u8_Epin[1],STD_HIGH);
	_delay_us(1);
	DIO_writePIN(st_gs_lcdConfig.u8_Epin[0],st_gs_lcdConfig.u8_Epin[1],STD_LOW);
	//_delay_us(1);

}


#define INDEX  4
void LCD_WriteInt(Uint32_t number)
{
	uint8_t STR[INDEX];
	itoa(number, STR, 10);
	LCD_writeString(STR);
}