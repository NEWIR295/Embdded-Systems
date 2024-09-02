/*
 * main.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Mohamed Newir
 *      Project description: on/off 3 leds in sequence
 */
/*define system frequency*/
#define F_CPU 16000000
/*std libraries*/
#include <avr/io.h>
#include<util/delay.h>

int main(void){
	DDRC |=0x07; /*set pin 0,1,2 as output*/
	PORTC &= 0xf8; /*set pin 0,1,2 to low*/
	while(1){
		PORTC =  0x01;
		_delay_ms(500);
		PORTC =  0x02;
		_delay_ms(500);
		PORTC = 0x04;
		_delay_ms(500);
	}
	return 1;
}
