/*
 * main.c
 *
 *  Created on: Aug 16, 2024
 *      Author: Mohamed Newir
 *      project description: control buzzer
 */
/*system frequency*/
#define F_CPU 16000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	/*pins setup*/
	DDRD &=~(1<<PD3);/*set pin 3 at port d as input*/
	DDRC &=~(1<<PC5);/*set pin 5 at port c as output*/
	PORTC &=~(1<<PC5);/*init pin5 in port c to low*/
	while(1){
		/*main application*/
		if(!(PIND&(1<<3))){
			PORTC |=(1<<PC5);
		}
		else{
			PORTC &=~(1<<PC5);
		}
		_delay_ms(30);
	}
	return 1;
}
