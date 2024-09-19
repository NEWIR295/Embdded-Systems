/*
 * main.c
 *
 *  Created on: Sep 19, 2024
 *      Author: Mohamed Newir
 *      Project Description: Stopwatch with Dual Mode (Increment and Countdown)
 *     						 Using ATmega32 and Seven-Segment Display.
 *
 */

/*system frequency*/

#include "macros.h"
#include "interrupts.h"
#include "gpio.h"
#include "sevenSegment.h"
#include "buttons.h"

/* container contain the array of time */
unsigned int time[SEVEN_SEGMENT_NUMBERS] = {ZERO};

extern volatile unsigned char interrupt0flag; /* reset flag */
extern volatile unsigned char resumePauseFlag;
/* ISR FUNCTIONS */


/* main function*/
int main(void) {
	/* HW initialization functions*/
	GPIO_init();
	interrupt_init();

	/* application code */
	while(1){

		/* continuous 7 segment update */
		time[0] = seconds%TEN;
		time[1] = seconds/TEN;
		time[2] = minutes%TEN;
		time[3] = minutes/TEN;
		time[4] = hours%TEN;
		time[5] = hours/TEN;

		/* reset interrupt */
		if(!interrupt0flag){
			/* in case of reset */
			milliseconds = ZERO;
			seconds = ZERO;
			minutes = ZERO;
			hours = ZERO;
			/* when reset start in count up mode */
			countUP_DOWN = ONE;
			/* in case count up open red led */
			PORTD = (PORTD&0xcf) | (0x10&0x30);
			/*stop buzzer */
			PORTD &=~ (ONE<<PD0);
			interrupt0flag = ONE;
		}

		/* in case of stop watch is set to pause */
		if(!resumePauseFlag){

			buttons();
		}
	}
	return 0;
}
