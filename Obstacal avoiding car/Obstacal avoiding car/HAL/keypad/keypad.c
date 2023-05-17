/*
 * keypad.c
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 




#include "keypad.h"
#include "../../MCAL/dio/dio.h"
#define F_CPU 8000000U
#include<util/delay.h>
static uint8_t keypad[4][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'},{'*','0','#'}};
extern st_keypadConfigType st_gs_keypadConfig;
u8_en_keypadErrorsType KEYPAD_init (st_keypadConfigType* st_config)
{
	u8_en_keypadErrorsType ret_val=KEYPAD_E_OK;
	if(st_config==(void*)0)
	{
		ret_val=KEYPAD_E_NOT_OK;
	}
	else
	{
		DIO_init(st_config->u8_row1Pin[0],st_config->u8_row1Pin[1],STD_INPUT);
		DIO_init(st_config->u8_row2Pin[0],st_config->u8_row2Pin[1],STD_INPUT);
		DIO_init(st_config->u8_row3Pin[0],st_config->u8_row3Pin[1],STD_INPUT);
		DIO_writePIN(st_config->u8_row1Pin[0],st_config->u8_row1Pin[1],STD_HIGH);
		DIO_writePIN(st_config->u8_row2Pin[0],st_config->u8_row2Pin[1],STD_HIGH);
		DIO_writePIN(st_config->u8_row3Pin[0],st_config->u8_row3Pin[1],STD_HIGH);
		
		DIO_init(st_config->u8_col1Pin[0],st_config->u8_col1Pin[1],STD_OUTPUT);
		DIO_init(st_config->u8_col2Pin[0],st_config->u8_col2Pin[1],STD_OUTPUT);
		DIO_init(st_config->u8_col3Pin[0],st_config->u8_col3Pin[1],STD_OUTPUT);
		DIO_init(st_config->u8_col4Pin[0],st_config->u8_col4Pin[1],STD_OUTPUT);
	}
	return ret_val;
}

u8_en_keypadErrorsType KEYPAD_read (uint8_t * u8_data)
{   u8_en_keypadErrorsType ret_val=KEYPAD_E_OK;
	uint8_t value,flag=0;
	DIO_writePIN(st_gs_keypadConfig.u8_col1Pin[0],st_gs_keypadConfig.u8_col1Pin[1],STD_HIGH);
	DIO_writePIN(st_gs_keypadConfig.u8_col2Pin[0],st_gs_keypadConfig.u8_col2Pin[1],STD_HIGH);
	DIO_writePIN(st_gs_keypadConfig.u8_col3Pin[0],st_gs_keypadConfig.u8_col3Pin[1],STD_HIGH);
	DIO_writePIN(st_gs_keypadConfig.u8_col4Pin[0],st_gs_keypadConfig.u8_col4Pin[1],STD_HIGH);
	uint8_t i,j;
	for(i=0;i<4;i++)
	{
		DIO_writePIN(st_gs_keypadConfig.u8_col1Pin[0],st_gs_keypadConfig.u8_col1Pin[1]+i,STD_LOW);
		for(j=0;j<3;j++)
		{
			DIO_readPIN(st_gs_keypadConfig.u8_row1Pin[0],st_gs_keypadConfig.u8_row1Pin[1]+j,&value);
			if(value==0)
			{  
				 while(value==0)
				 {
					 DIO_readPIN(st_gs_keypadConfig.u8_row1Pin[0],st_gs_keypadConfig.u8_row1Pin[1]+j,&value);
				 }
				*u8_data=keypad[i][j];
				flag=1;
				
				break;
			}
			
		}
		DIO_writePIN(st_gs_keypadConfig.u8_col1Pin[0],st_gs_keypadConfig.u8_col1Pin[1]+i,STD_HIGH);
	}
	
	
	
	if(flag==1)
	{   
		
		return ret_val;
	}
	else
	{
		*u8_data='N';
		return ret_val;
	}
	
}