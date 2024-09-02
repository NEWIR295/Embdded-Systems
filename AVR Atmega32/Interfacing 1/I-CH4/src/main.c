/*
 * main.c
 *
 *  Created on: Aug 17, 2024
 *      Author: Mohamed Newir
 *      project description: control led using PIR sensor
 */
/*system frequency*/
#define F_CPU 1000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>
/*main function*/
int main (void){
	/*application initialization */
	/*set pin 0 in port c as input for PIR*/
	DDRC &=~(1<<PC0);
	/*set pin 0 in port b as output for led*/
	DDRB |= (1<<PB0);
	/*set led to low*/
	PORTB &=~(1<<PB0);
	while(1){
		/*application code*/
		if(PINC&(1<<PC0)){
			PORTB |= (1<<PC0);
		}
		else{
			PORTB &=~(1<<PC0);
		}
	}
	return 1;
}
