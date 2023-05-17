/*
 * timer_private_reg.h
 *
 * Created: 4/10/2023 3:40:44 PM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef TIMER_PRIVATE_REG_H_
#define TIMER_PRIVATE_REG_H_

#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"

/****************************************TIMER0_REGISTERS *************************************************/
/* TCNT0 – Timer/Counter Register*/
#ifndef TCNT0
#define TCNT0   (*(volatile uint8_t*)0x52)
#endif

#ifndef TCCR0
/*Timer/Counter Control Register*/
#define TCCR0   (*(volatile uint8_t*)0x53)
#endif
#ifndef TIMSK
/*TIMSK – Timer/Counter Interrupt Mask Register*/
#define TIMSK   (*(volatile uint8_t*)0x59)
#endif
#ifndef GIFR
/*GIFR – General Interrupt Flag Register*/
#define GIFR    (*(volatile uint8_t*)0x5A)
#endif
#ifndef TIFR
/*TIFR – Timer/Counter Interrupt Flag Register*/
#define TIFR    (*(volatile uint8_t*)0x58)
#endif
#ifndef OCR0
/*OCR0 – Output Compare Register*/
#define OCR0    (*(volatile uint8_t*)0x5C)
#endif

/*TCCR0-TIMER_0_CONTROL_REG_BITS*/
/*Bit 2:0 – CS02:0: Clock Select in TCCR0 REG */
#ifndef CS00
#define CS00  (0u)
#endif
#ifndef CS01
#define CS01  (1u)
#endif
#ifndef CS02
#define CS02  (2u)
#endif
/*Bit 5:4 – COM0[1:0]: Compare Match Output Mode in TCCR0 REG */
#ifndef COM00
#define COM00 (4u)
#endif
#ifndef COM01
#define COM01 (5u)
#endif
/*Bit 6, 3 – WGM0[1:0]: Waveform Generation Mode in TCCR0 REG */
#ifndef WGM00
#define WGM00 (6u)
#endif
#ifndef WGM01
#define WGM01 (3u)
#endif
/*Bit 7 – FOC0:Force Output Compare bit in TCCR0 REG*/
#ifndef FOC0
#define FOC0  (7u)
#endif


/*TIMSK-TIMER 0 INTERRUPT MASK REG BITS*/
/*Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable in TIMSK REG */
#ifndef TOIE0
#define TOIE0 (0u)
#endif
/*Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable in TIMSK REG*/
#ifndef OCIE0
#define OCIE0 (1u)
#endif

/*GIFR-TIMER 0 INTERRUPT FLAG REG BITS*/
/*Bit 0 – TOV0: Timer/Counter0 Overflow Flag in TIFR REG*/
#ifndef TOV0
#define TOV0  (0u)
#endif
/* Bit 1 – OCF0: Output Compare Flag 0 in TIFR REG*/
#ifndef OCF0
#define OCF0  (1u)
#endif

/****************************************TIMER1_REGISTERS *************************************************/

/* TCCR1A – Timer/Counter1 Control Register A*/
#ifndef TCCR1A
#define TCCR1A   (*(volatile uint8_t*)0x4F)
#endif
/*TCCR1B – Timer/Counter1 Control Register B*/
#ifndef TCCR1B
#define TCCR1B   (*(volatile uint8_t*)0x4E)
#endif

#ifndef TCNT1
#define TCNT1   (*(volatile Uint16_t*)0x4C)
#endif
/*TCNT1H  Timer/Counter1 – Counter Register High Byte*/
#ifndef TCNT1H
#define TCNT1H   (*(volatile uint8_t*)0x4D)
#endif
/*TCNT1L  Timer/Counter1 – Counter Register low Byte*/
#ifndef TCNT1L
#define TCNT1L   (*(volatile uint8_t*)0x4C)
#endif
/*OCR1AH Timer/Counter1 – Output Compare Register A High Byte */
#ifndef OCR1AH
#define OCR1AH   (*(volatile uint8_t*)0x4B)
#endif
/*OCR1AL Timer/Counter1 – Output Compare Register A Low Byte*/
#ifndef OCR1AL
#define OCR1AL   (*(volatile uint8_t*)0x4A)
#endif
/*OCR1BH Timer/Counter1 – Output Compare Register B High Byte*/
#ifndef OCR1BH
#define OCR1BH   (*(volatile uint8_t*)0x49)
#endif
/*OCR1BL Timer/Counter1 – Output Compare Register B Low Byte*/
#ifndef OCR1BL
#define OCR1BL   (*(volatile uint8_t*)0x48)
#endif


#ifndef SREG
/*OCR0 – Output Compare Register*/
#define SREG   (*(volatile uint8_t*)0x5F)
#endif



/*TCCR1A -TIMER_1_CONTROL_REG_A_BITS*/
/* Bit 7:6 – COM1A1:0: Compare Output Mode for Compare unit A in TCCR1A REG */
#ifndef COM1A0
#define COM1A0 (6u)
#endif
#ifndef COM1A1
#define COM1A1 (7u)
#endif
/* Bit 5:4 – COM1B1:0: Compare Output Mode for Compare unit B*/
#ifndef COM1B0
#define COM1B0 (4u)
#endif
#ifndef COM1B1
#define COM1B1 (5u)
#endif
/* Bit 3 – FOC1A: Force Output Compare for Compare unit A*/
#ifndef FOC1A
#define FOC1A (3u)
#endif
/*Bit 2 – FOC1B: Force Output Compare for Compare unit B*/
#ifndef FOC1B
#define FOC1B (2u)
#endif
/* Bit 1:0 – WGM11:0: Waveform Generation Mode*/
#ifndef WGM10
#define WGM10 (0u)
#endif
#ifndef WGM11
#define WGM11 (1u)
#endif

/*TCCR1B-TIMER_1_CONTROL_REG_B_BITS*/
/*Bit 7 – ICNC1: Input Capture Noise Canceler*/
#ifndef ICNC1
#define ICNC1 (7u)
#endif
/*Bit 6 – ICES1: Input Capture Edge Select*/
#ifndef ICES1
#define ICES1 (6u)
#endif
/*Bit 4:3 – WGM13:2: Waveform Generation Mode*/
#ifndef WGM12
#define WGM12 (4u)
#endif
#ifndef WGM13
#define WGM13 (3u)
#endif
/*Bit 2:0 – CS12:0: Clock Select*/
#ifndef CS12
#define CS12 (2u)
#endif
#ifndef CS11
#define CS11 (1u)
#endif
#ifndef CS10
#define CS10 (0u)
#endif

/*TIMSK-TIMER1 INTERRUPT MASK REG BITS*/

/*Bit 2 – TOIE1: Timer/Counter1, Overflow Interrupt Enable */
#ifndef TOIE1
#define TOIE1 (2u)
#endif
/*Bit 4 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable*/
#ifndef OCIE1A
#define OCIE1A (4u)
#endif
/*Bit 3 – OCIE1B: Timer/Counter1, Output Compare B Match Interrupt Enable*/
#ifndef OCIE1B
#define OCIE1B (3u)
#endif


/* TIFR – Timer/Counter1 Interrupt Flag Register bits*/

/*Bit 4 – OCF1A: Timer/Counter1, Output Compare A Match Flag*/
#ifndef OCF1A
#define OCF1A (4u)
#endif
/*Bit 3 – OCF1B: Timer/Counter1, Output Compare B Match Flag*/
#ifndef OCF1B
#define OCF1B (3u)
#endif
/* Bit 2 – TOV1: Timer/Counter1, Overflow Flag*/
#ifndef TOV1
#define TOV1 (2u)
#endif



/****************************************TIMER2_REGISTERS *************************************************/
/*TCCR2 – Timer/Counter Control Register*/
#ifndef TCCR2
#define TCCR2   (*(volatile uint8_t*)0x45)
#endif
/*TCNT2 – Timer/Counter Register*/
#ifndef TCNT2
#define TCNT2   (*(volatile uint8_t*)0x44)
#endif
/*OCR2 – Output Compare Register*/
#ifndef OCR2
#define OCR2   (*(volatile uint8_t*)0x43)
#endif


/*TCCR2 - TIMER_2_CONTROL_REG_BITS*/

/*Bit 7 – FOC2: Force Output Compare*/
#ifndef FOC2
#define FOC2 (7u)
#endif
/*Bit 6, 3 – WGM2[1:0]: Waveform Generation Mode*/
#ifndef WGM20
#define WGM20 (6u)
#endif
#ifndef WGM21
#define WGM21 (3u)
#endif
/*Bit 5:4 – COM2[1:0]: Compare Match Output Mode*/
#ifndef COM20
#define COM20 (4u)
#endif
#ifndef COM21
#define COM21 (5u)
#endif
/*Bit 2:0 – CS2[2:0]: Clock Select*/
#ifndef CS20
#define CS20 (2u)
#endif
#ifndef CS21
#define CS21 (1u)
#endif
#ifndef CS22
#define CS22 (0u)
#endif

/*TIMSK-TIMER 2 INTERRUPT MASK REG BITS*/

/*Bit 7 – OCIE2: Timer/Counter2 Output Compare Match Interrupt Enable*/
#ifndef OCIE2
#define OCIE2 (7u)
#endif
/* Bit 6 – TOIE2: Timer/Counter2 Overflow Interrupt Enable*/
#ifndef TOIE2
#define TOIE2 (6u)
#endif


/*TIFR – Timer/Counter Interrupt Flag Register bits */

/*Bit 7 – OCF2: Output Compare Flag 2*/
#ifndef OCF2
#define OCF2 (7u)
#endif
/* Bit 6 – TOV2: Timer/Counter2 Overflow Flag*/
#ifndef TOV2
#define TOV2 (6u)
#endif


#ifndef TIMER0_OVF
#define TIMER0_OVF __vector_11
#endif

#ifndef TIMER1_OVF
#define TIMER1_OVF __vector_9
#endif

#ifndef TIMER2_OVF
#define TIMER2_OVF __vector_5
#endif

#ifndef ISR
#define ISR(INT_VECT) void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)
#endif


#endif /* TIMER_PRIVATE_REG_H_ */