/*
 * sevenSegment.c
 *
 *  Created on: Sep 19, 2024
 *      Author: Mohamed Newir
 */

#include "sevenSegment.h"
/*  Six multiplexed seven-segment displays initialization */
/* display timer in the 7 segment */
void multi7sergment(unsigned char currentTime,unsigned char activate7segment_){
	/* write current time */
	PORTA = (PORTA & 0xC0) | ((1<<(FIVE-activate7segment_))&0x3f);
	PORTC = (PORTC & 0xf0) | (currentTime & 0x0f);
	/* diplay time in the specfic 7 segment */
	_delay_us(displayDelay);
	PORTA = (PORTA & 0xC0) | (0x00&0x3f);
}
