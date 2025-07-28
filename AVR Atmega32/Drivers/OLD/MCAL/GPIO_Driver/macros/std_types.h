/*
 * 	    File Name: std_types.h
 *
 *  	Created on: Sep 26, 2024
 *      Author: Mohamed Newir
 *      Description: User defined types to deal with AVR ATmega32
 *
 */

#ifndef MACROS_STD_TYPES_H_
#define MACROS_STD_TYPES_H_

/* LOGIC STATE DEFINITIONS */

/* low state definition */
#ifndef LOW
#define LOW (0u)
#endif

/* high state definition */
#ifndef HIGH
#define HIGH (1u)
#endif

/* boolean values*/

/* TRUE value */
#ifndef TRUE
#define TRUE  (1u)
#endif

/* FALSE value */
#ifndef FALSE
#define FALSE (0u)
#endif

/* null pointer definition*/
#ifndef NULL_PTR
#define NULL_PTR ((void*)0)
#endif

/* boolean data type*/
typedef unsigned char boolean;

/* DT for 1 byte */
typedef unsigned char uint8;
typedef signed char sint8;

/* DT for 2 bytes */
typedef unsigned short uint16;
typedef signed short sint16;

/* DT for 4 bytes */
typedef unsigned long uint32;
typedef signed long sint32;

/* DT for 8 bytes */
typedef unsigned long long uint64;
typedef signed long long sint64;

/* DT for float 4 bytes */
typedef float float32;

/* DT for float 8 bytes */
typedef double float64;

#endif /* MACROS_STD_TYPES_H_ */
