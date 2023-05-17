/*
 * dio_types.h
 *
 * Created: 4/21/2023 3:50:54 AM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 


#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_

#include "../../STD_LIBRARIES/STD_TYPES.h"

#define DIO_MAX_PINS	8
#define DIO_MAX_PORTS	4

#define  DATA_DIRECTION_PORTA	DDRA
#define  DATA_DIRECTION_PORTB	DDRB
#define  DATA_DIRECTION_PORTC	DDRC
#define  DATA_DIRECTION_PORTD	DDRD


#define  WR_PORT_A					PORTA
#define  WR_PORT_B					PORTB
#define  WR_PORT_C					PORTC
#define  WR_PORT_D					PORTD




#define  RE_PORT_A					PINA
#define  RE_PORT_B					PINB
#define  RE_PORT_C					PINC
#define  RE_PORT_D					PIND

typedef enum en_dioPortsType
{
	porta, portb, portc, portd
} en_dioPortsType;
typedef enum en_dioPinsType
{
	pin0, pin1, pin2, pin3, pin4, pin5, pin6, pin7
} en_dioPinsType;


// DIO Level type ENUM
typedef uint8_t u8_en_dioLevelType;

#define STD_LOW					((u8_en_dioLevelType)0x00)
#define STD_HIGH				((u8_en_dioLevelType)0x01)


// DIO Errors ENUM
typedef uint8_t u8_en_dioErrors;

#define DIO_E_OK				((u8_en_dioErrors)0x00)
#define DIO_InvalidPin			((u8_en_dioErrors)0x01)
#define DIO_InvalidPort			((u8_en_dioErrors)0x02)


// DIO DIR type ENUM
typedef uint8_t u8_en_dioDirType;

#define STD_INPUT					((u8_en_dioDirType)0x00)
#define STD_OUTPUT					((u8_en_dioDirType)0x01)


#endif /* DIO_TYPES_H_ */