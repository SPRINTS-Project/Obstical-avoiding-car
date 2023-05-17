/*
 * STD_TYPES.h
 *
 * Created: 4/5/2023 
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/**********************************  section 1: Includes ********************************************************/

/**********************************  section 2: Macro Declarations ***********************************************/

#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

// #ifndef HIGH
// #define HIGH        (1u)
// #endif
// 
// #ifndef LOW
// #define LOW         (0u)
// #endif


#ifndef NULL
#define NULL    ((void*)0)
#endif



/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/
#if 0        
typedef signed char           sint8_t;          /*        -128 .. +127            */
typedef signed short          sint16_t;         /*      -32768 .. +32767          */
typedef unsigned long long    uint64_t;         /*       0..18446744073709551615  */
typedef signed long long      sint64_t;
#endif

typedef unsigned char			uint8_t;		 /*           0 .. 255             */
typedef unsigned short int      Uint16_t;		/*           0 .. 65535           */
typedef unsigned long int       Uint32_t;		/*           0 .. 4294967295      */
typedef signed long int			sint32_t;		/* -2147483648 .. +2147483647     */
typedef float					float32_t;
typedef double					float64_t;


typedef enum{
	E_NOT_OK = 0,     
	E_OK         
}Std_ReturnType;
/**********************************  section 5: Function Declarations ********************************************/



#endif /* STD_TYPES_H_ */