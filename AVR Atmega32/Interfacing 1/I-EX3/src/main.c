/*
 * main.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Mohamed Newir
 *      project description: control two leds using push buttons
 */
/*define system frequency*/
#define F_CPU 1000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	/*set pin 0,1 in port c as input*/
	DDRB &=~(1<<0);
	DDRB &=~(1<<1);
	/*set pin 0,1 in port c as output*/
	DDRC |=(1<<0);
	DDRC |=(1<<1);
	/*set pin 0,1 in port c as pull down*/
	PORTC |=(1<<0);
	PORTC |=(1<<1);
	while(1){
		if(PINB&(1<<0)){
			PORTC &=~(1<<0); /*set led 0 on*/
		}
		else{
			PORTC |=(1<<0); /*set led 0 off*/
		}
		if(PINB &(1<<1)){
			PORTC &=~(1<<1); /*set led 1 on*/
		}
		else{
			PORTC |=(1<<1); /*set led 1 off*/
		}
	}
	return 1;
}



