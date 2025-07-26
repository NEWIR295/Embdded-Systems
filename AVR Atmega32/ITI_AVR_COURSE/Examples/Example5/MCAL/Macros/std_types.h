/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: std_types.h
 *      Description:
 *      			common data types used when interfacing with AVR
 *      			Microcontroller
 */


#ifndef MCAL_MACROS_STD_TYPES_H_
#define MCAL_MACROS_STD_TYPES_H_

/* NULL pointer definition */
#ifndef NULL_Ptr
#define NULL_PTR ((void*)0)
#endif
/*
 * False value definition
 */
#ifndef False
#define False (0u)
#endif

/*
 * True value definition
 */
#ifndef True
#define True (1u)
#endif

/*
 * boolean data type definition
 */
typedef unsigned char bool;

/* Logical value declaration */
typedef enum{
	LOW = (0u), High = (1u)
}Logical_Value;

/*
 * Standard data types definitions
 */

/*
 * 1 byte data types
 */
typedef unsigned char uint8;
typedef signed char sint8;

/*
 * 2 bytes data types
 */
typedef unsigned short uint16;
typedef signed short sint16;

/*
 * 4 bytes data types
 */
typedef unsigned long uint32;
typedef signed long sint32;

/*
 * 8 bytes data types
 */
typedef unsigned long long uint64;
typedef signed long long sint64;

/*
 * 4 bytes float data type
 */
typedef float float32;

/*
 * 8 bytes float data type
 */
typedef double float64;


#endif /* MCAL_MACROS_STD_TYPES_H_ */
