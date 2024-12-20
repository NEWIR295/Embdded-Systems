/*
 * main.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Mohamed Newir
 *      project description: control led using push button
 */
/*define system frequency*/
#define F_CPU 1000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	/*set pin 0 in port b as input */
	DDRB &=~(1<<0);
	PORTB |=(1<<0); /*activate internal pull up*/
	/*set pin 0 in port c as output*/
	DDRC |=(1<<0);
	/*set pin 0 in port c high*/
	PORTC |=(1<<0);/*negative logic*/
	int buttonState = 0;
	int lastState = 0;
	while(1){
		buttonState = PINB &(1<<0);
		if(buttonState == 0 && lastState != 0){
			PORTC ^=(1<<0);
		}
		lastState = buttonState;
		_delay_ms(100);
	}
	return 1;
}


