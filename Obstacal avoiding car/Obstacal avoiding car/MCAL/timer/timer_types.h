/*
 * timer_types.h
 *
 * Created: 4/21/2023 12:27:22 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef TIMER_TYPES_H_
#define TIMER_TYPES_H_

//#include <stdint.h>
#include "../../STD_LIBRARIES/std_types.h"
#include "../../STD_LIBRARIES/bit_math.h"


typedef  void (*timerCallBack) (void);



typedef uint8_t u8_en_timerErrorsType;

#define  TIMER_E_OK				((u8_en_timerErrorsType)0x00)
#define  TIMER_E_NOT_OK			((u8_en_timerErrorsType)0x03)

typedef uint8_t u8_en_timerInterruptFeature;

#define  TIMER_INTERRUPT_FEATURE_ENABLE				((u8_en_timerInterruptFeature)0x01)
#define  TIMER_INTERRUPT_FEATURE_DISABLE			((u8_en_timerInterruptFeature)0x00)

typedef uint8_t u8_en_timerPrescalerType;

#define TIMER_NO_CLOCK							((u8_en_timerPrescalerType)0x00)
#define TIMER_F_CPU_CLOCK						((u8_en_timerPrescalerType)0x01)
#define TIMER_F_CPU_8							((u8_en_timerPrescalerType)0x02)
#define TIMER_F_CPU_32							((u8_en_timerPrescalerType)0x03)
#define TIMER_F_CPU_64							((u8_en_timerPrescalerType)0x04)
#define TIMER_F_CPU_128							((u8_en_timerPrescalerType)0x05)
#define TIMER_F_CPU_256							((u8_en_timerPrescalerType)0x06)
#define TIMER_F_CPU_1024						((u8_en_timerPrescalerType)0x07)
#define TIMER_EXTERNAL_CLK_FALLING_EDGE			((u8_en_timerPrescalerType)0x08)
#define TIMER_EXTERNAL_CLK_RISING_EDGE			((u8_en_timerPrescalerType)0x09)
#define TIMER_INVALID_CLOCK						((u8_en_timerPrescalerType)0x0a)




typedef uint8_t u8_en_timerNumberType;

#define TIMER_0						((u8_en_timerNumberType)0x00)
#define TIMER_1						((u8_en_timerNumberType)0x01)
#define TIMER_2						((u8_en_timerNumberType)0x02)
#define TIMER_INVALID_NUM			((u8_en_timerNumberType)0x03)


typedef struct
{
	u8_en_timerNumberType u8_timerNum;			/* @ref u8_en_timerNumberType*/
	u8_en_timerPrescalerType u8_timerClock;		/* @ref u8_en_timerPrescalerType*/
	Uint16_t u16_timer_InitialValue;			/* the pre-loaded value on Timer/Counter Register*/
	u8_en_timerInterruptFeature u8_timer_ovf_int_enable;	/*timer interrupt mask-ability*/
	timerCallBack callBackFunction;  /*pointer to function that take void and return nothing(void) ,should loaded with call-back function's address*/
}st_timerConfigType;


#endif	/*	TIMER_TYPES_H	*/