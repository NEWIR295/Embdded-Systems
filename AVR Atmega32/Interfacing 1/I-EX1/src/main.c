/*
 * main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Mohamed Newir
 *      challenge1: control LED using Push Buttom
 */
/*AVR STD Libraries*/
#include <avr/io.h>
#include <util/delay.h>

/*main function*/
int main(void){
	/*initialization of pin direction*/
	DDRC |=(1<<1);
	DDRD &=~(1<<2);
	PORTC &= ~(1<<1);
	int buttonState = 0;
	int lastState = 0;
	while(1){
		buttonState = PIND&(1<<2);
		if(buttonState == 0 && lastState !=0){
			PORTC ^= (1<<1);
		}
		lastState = buttonState;
		_delay_ms(100);
	}
	return 0;
}
