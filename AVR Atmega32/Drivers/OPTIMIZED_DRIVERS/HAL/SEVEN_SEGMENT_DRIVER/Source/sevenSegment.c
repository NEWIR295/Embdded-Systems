/*
 *      Author: Mohamed Newir
 *      Created on: Jul 27, 2025
 *      File name: sevenSegment.c
 *      Description:
 *      			Seven Segment driver implementation
 */

/* GPIO driver for ATmega32 */
#include "../../../MCAL/GPIO/Include/gpio.h"
#include "../Include/sevenSegment.h"

/* global array variable hold numbers in case there is no decoder */
const uint8 g_numbers[10] = {0x7e,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};

/* seven segment initialization function */
void SEVEN_SEGMENT_init(const SevenSegment_t* sevenSegment){

	GPIO_setupPortDirectionMasked(sevenSegment->portNum, PORT_OUTPUT, sevenSegment->mask);

	if(sevenSegment->decoderExist){

		/* in decoder it doesen't matter the type of the 7 segment we either use 7447 for cathode or 7448 for anode */
		/* initialize seven segment with zero*/
		GPIO_writePortMasked(sevenSegment->portNum, 0, sevenSegment->mask);
	}
	else{
		/* In case there is no decoder */
		if(sevenSegment->type == CATHODE){

			/* initialize seven segment with zero*/
			GPIO_writePort(sevenSegment->portNum, g_numbers[0]);
		}
		else{

			/* in case it's Anode*/
			/* initialize seven segment with zero*/
			GPIO_writePort(sevenSegment->portNum, ~g_numbers[0]);
		}
	}
}

/* seven segment show value function */
void SEVEN_SEGMENT_show(const SevenSegment_t* sevenSegment, uint8 value){

	if(value > 9) return; /* check input value where we only accept from 0 -> 9  */

	if(sevenSegment->decoderExist){
		/* in decoder it doesen't matter the type of the 7 segment we either use 7447 for cathode or 7448 for anode */
		GPIO_writePortMasked(sevenSegment->portNum, value, sevenSegment->mask);
	}
	else{
		/* In case there is no decoder */
		if(sevenSegment->type == CATHODE){
			GPIO_writePortMasked(sevenSegment->portNum, g_numbers[value], sevenSegment->mask);
		}
		else{
			/* in case it's Anode*/
			GPIO_writePortMasked(sevenSegment->portNum, ~g_numbers[value], sevenSegment->mask);
		}
	}
}
