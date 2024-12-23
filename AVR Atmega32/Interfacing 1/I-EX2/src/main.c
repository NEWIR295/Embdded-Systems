/*
 * main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Mohamed Newir
 *      challenge1: toggle led every 1 second
 */
/*AVR STD Libraries*/
#include <avr/io.h>
#include <util/delay.h>
/*main function*/
int main(void){
	/*initialization of pin direction*/
	DDRC |=(1<<2); /*set LED PIN 2 to be output*/
	PORTC &= ~(1<<2);/*ensure that led initially set to zero*/
	while(1){
		PORTC |=(1<<2); /*set pin 2 to HIGH*/
		_delay_ms(1000);
		PORTC &=~(1<<2); /*SET pin 2 to LOW*/
		_delay_ms(1000);
	}
	return 0;
}
