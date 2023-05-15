/*
 * bit_math.h
 *
 * Created: 4/5/2023 
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_
/**********************************  section 1: Includes ********************************************************/
#include "std_types.h"
/**********************************  section 2: Macro Declarations ***********************************************/
#ifndef BIT_MASK
/*mask 1-bit (LSB)*/
#define BIT_MASK  (uint8_t)0x01
#endif

/*mask 8-bit_reg*/
#define U8_BIT_REG_MASK           ((uint8_t)0xFF)
#define U16_BIT_REG_MASK          ((uint16_t)0xFFFF)

#define  FLAG_IS_SET	    (uint8_t)1
#define  U8_ZERO_INITIALIZE (uint8_t)0

/**********************************  section 3: Macro Like Function Declarations *************************** *****/

/*set a certain bit in a 8-bit register*/
#ifndef SET_BIT
#define SET_BIT(REG,BIT_POSN)    (REG |=  (BIT_MASK << BIT_POSN))
#endif

#ifndef CLEAR_BIT
/*reset a certain bit in a 8-bit register*/
#define CLEAR_BIT(REG,BIT_POSN)  (REG &= ~(BIT_MASK << BIT_POSN))
#endif

#ifndef TOGGLE_BIT
/*toggle a certain bit in a 8-bit register*/
#define TOGGLE_BIT(REG,BIT_POS)  (REG ^=  (BIT_MASK << BIT_POS) )
#endif

#ifndef READ_BIT
/*read a certain bit in a 8-bit register*/
//#define READ_BIT(REG,BIT_POS)    ((REG >> BIT_POS) & (BIT_MASK) )
#define READ_BIT(REG,BIT_POS)    ((REG & (BIT_MASK<<BIT_POS)) >> BIT_POS)
#endif

#ifndef  CLEAR_REG
#define CLEAR_REG(REG)		(REG = ((uint8_t)0x00))
#endif



/**********************************  section 4: Data Type Declarations  ******************************************/

/**********************************  section 5: Function Declarations ********************************************/
#endif /* BIT_MATH_H_ */