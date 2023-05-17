/*
 * EXTINT_Private.h
 *
 *  Created on: Apr 3, 2023
 *      Author: hp
 */

#ifndef MCAL_EXTINT_EXTINT_PRIVATE_H_
#define MCAL_EXTINT_EXTINT_PRIVATE_H_

#define MCUCR_REG	(*(volatile uint8_t*)(0x55))
#define MCUCSR_REG	(*(volatile uint8_t*)(0x54))
#define GICR_REG	(*(volatile uint8_t*)(0x5B))
#define GIFR_REG	(*(volatile uint8_t*)(0x5A))

#define SREG_REG 	(*(volatile uint8_t*)(0x5F)) // for global interrupt



/* MCUCR register bits*/
#define ISC00		0
#define ISC01		1
#define ISC10		2
#define ISC11		3
/* MCUCSR register bits*/
#define ISC2		6
/* GICR register bits*/
#define INT0		6
#define INT1		7
#define INT2		5
/* GIFR register bits*/
#define INTF0		6
#define INTF1		7
#define INTF2		5
/* SREG register bits*/
#define I			7

#endif /* 04_MCAL_EXTINT_EXTINT_PRIVATE_H_ */
