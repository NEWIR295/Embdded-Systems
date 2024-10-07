/*
 * gpio.c
 *
 *  Created on: Sep 19, 2024
 *      Author: Mohamed Newir
 */

#include "gpio.h"
/*  GPIO initialization */
void GPIO_init(void){
	DDRD |= (ONE<<PD0) | (ONE<<PD4) | (ONE<<PD5);
	PORTD = (PORTD&0xcf) | (0x10&0x30);
	/* set pin 3  @ port d as input*/
	DDRD &=~ (ONE<<PD3); /* note that pd3 as external pullup */
	/* set pin 2  @ port d as input*/
	DDRD &=~ (ONE<<PD2);
	/* set pd2 as internal pullup*/
	PORTD |= (ONE<<PD2);
	/* set 1st 4 pins in portc as output for 7 segment decoder */
	DDRC = 0x0f;
	/*init 7 segment with zeros*/
	PORTC = (PORTC & 0xf0) | ( 0x00 & 0x0f);
	/*set 6 multiplixed 7 segments*/
	DDRA = 0x3f;
	/* allow 7 segment to init with zeros*/
	PORTA = 0x3f;
	/*set port b as inputs for push buttons*/
	DDRB = 0x00;
	/* activate portb for internal pullup for push buttons*/
	PORTB = 0xff;
}
