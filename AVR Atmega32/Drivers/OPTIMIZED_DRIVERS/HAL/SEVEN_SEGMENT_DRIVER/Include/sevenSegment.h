/*
 *      Author: Mohamed Newir
 *      Created on: Jul 27, 2025
 *      File name: sevenSegment.h
 *      Description:
 *      			Seven Segment driver declaration
 */


#ifndef HAL_SEVEN_SEGMENT_DRIVER_INCLUDE_SEVENSEGMENT_H_
#define HAL_SEVEN_SEGMENT_DRIVER_INCLUDE_SEVENSEGMENT_H_

/* user defined data types for AVR ATmega32  */
#include "../../../MCAL/Macros/std_types.h"

/* seven segment type declaration */
typedef enum{
	ANODE, CATHODE
}SEVEN_SEGMENT_TYPE;

/* seven segment data type declaration*/
typedef struct{
	uint8 portNum;
	uint8 mask; /* used for pin connection for example if it was without decoder it could be 0xff
				   and if with it it could be for example 0xf0, ox0f */
	bool decoderExist;
	SEVEN_SEGMENT_TYPE type;
}SevenSegment_t;

/* seven segment initialization function */
void SEVEN_SEGMENT_init(const SevenSegment_t* sevenSegment);

/* seven segment show value function */
void SEVEN_SEGMENT_show(const SevenSegment_t* sevenSegment, uint8 value);

#endif /* HAL_SEVEN_SEGMENT_DRIVER_INCLUDE_SEVENSEGMENT_H_ */
