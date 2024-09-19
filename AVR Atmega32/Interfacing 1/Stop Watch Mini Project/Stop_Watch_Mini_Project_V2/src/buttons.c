/*
 * buttons.c
 *  Created on: Sep 19, 2024
 *      Author: Mohamed Newir
 */

#include "buttons.h"

/* global static variabkes for push Buttons*/
/* to change the state of the stop watch from counting up to down and vise-versa */
static unsigned char lastToggleButtonState = ZERO;

static unsigned char toggleButtonState = ZERO;

/*seconds increment*/
static unsigned char lastSecIncButtonState = ZERO;
static unsigned char SecIncButtonState = ZERO;

/*seconds decrement*/
static unsigned char lastSecDecButtonState = ZERO;
static unsigned char SecDecButtonState = ZERO;

/*minutes increment*/
static unsigned char lastMinIncButtonState = ZERO;
static unsigned char MinIncButtonState = ZERO;

/*minutes decrement*/
static unsigned char lastMinDecButtonState = ZERO;
static unsigned char MinDecButtonState = ZERO;

/*hours increment*/
static unsigned char lastHoursDecButtonState = ZERO;
static unsigned char HoursDecButtonState = ZERO;

/*hours decrement*/
static unsigned char lastHoursIncButtonState = ZERO;
static unsigned char HoursIncButtonState = ZERO;

void buttons(void){
	/* reset milliseconds */
	milliseconds = ZERO;
	if((toggleButtonState == ZERO) && (lastToggleButtonState != ZERO))
	{
		countUP_DOWN = !countUP_DOWN;
		if(countUP_DOWN){
			/*in case of count up  countUP_DOWN = 1*/
			/*stop buzzer */
			PORTD &=~ (ONE<<PD0);
			/* in case count up open red led */
			PORTD = (PORTD&0xcf) | (0x10&0x30);
		}
		else{
			/*in case of count down  countUP_DOWN = 0*/
			/* in case count down open yellow led */
			PORTD = (PORTD&0xcf) | (0x20&0x30);
		}
	}
	lastToggleButtonState = toggleButtonState;
	_delay_ms(DEPOUNCING_DELAY);

	/* seconds decrement*/
	if((SecDecButtonState == ZERO) && (lastSecDecButtonState != ZERO)){
		if(seconds>ZERO){
			seconds--;
		}
	}
	lastSecDecButtonState = SecDecButtonState;
	_delay_ms(DEPOUNCING_DELAY);

	/* seconds increments*/
	if((SecIncButtonState == ZERO) && (lastSecIncButtonState != ZERO)){
		seconds++;
		if(seconds >MAX_SECONDS){
			/* reset seconds */
			minutes++;
			seconds = ZERO;
			if(minutes>MAX_MINUTES){
				/* reset minutes */
				hours++;
				minutes = ZERO;
				if(hours>MAX_HOURS){
					/* reset stop watch */
					hours =ZERO;
				}
			}
		}
	}
	lastSecIncButtonState = SecIncButtonState;
	_delay_ms(DEPOUNCING_DELAY);

	/* minutes decrement */
	if((MinDecButtonState == ZERO) && (lastMinDecButtonState != ZERO)){
		if(minutes>ZERO){
			minutes--;
		}

	}
	lastMinDecButtonState = MinDecButtonState;
	_delay_ms(DEPOUNCING_DELAY);

	/* minutes increment */
	if((MinIncButtonState == ZERO) && (lastMinIncButtonState != ZERO)){
		minutes++;
		/* reset minutes */
		if(minutes >MAX_MINUTES){
			hours++;
			minutes = ZERO;
			/* reset stop watch */
			if(hours > MAX_HOURS){
				hours = ZERO;
			}
		}
	}
	lastMinIncButtonState = MinIncButtonState;
	_delay_ms(DEPOUNCING_DELAY);

	/* hours decrement */
	if((HoursDecButtonState == ZERO) && (lastHoursDecButtonState != ZERO)){
		if(hours>ZERO){
			hours--;
		}
	}
	lastHoursDecButtonState = HoursDecButtonState;
	_delay_ms(DEPOUNCING_DELAY);

	/* hours increment */
	if((HoursIncButtonState == ZERO) && (lastHoursIncButtonState != ZERO)){
		hours++;
		/* reset stop watch */
		if(hours > MAX_HOURS){
			hours = ZERO;
			seconds = ZERO;
			minutes = ZERO;
		}
	}
	lastHoursIncButtonState = HoursIncButtonState;
	_delay_ms(DEPOUNCING_DELAY);
}

