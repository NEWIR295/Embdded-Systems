/*
 * main.c
 *
 *  Created on: Aug 8, 2024
 *      Author: Mohamed Newir
 *      AVR USBASP CONNECTION TEST WITH VM RUNNING WINDOWS10 IN UBUNTU LINUX MACHINE
 *      كهارب الفرح هههه
 */
//#define F_CPU 12000000
#include <avr/io.h>
#include <util/delay.h>
void main(void){
	DDRD = 0xff;
	while(1){
		PORTD = 0b01010101;
		_delay_ms(500);
		PORTD = 0b10101010;
		_delay_ms(500);
	}
}
