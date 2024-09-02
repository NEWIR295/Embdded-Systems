/*
 * main.c
 *
 *  Created on: Aug 19, 2024
 *      Author: Mohamed Newir
 *      Project Description: control led by external interrupt
 */
/*system frequency*/
#define F_CPU 1000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*ISR function*/
ISR(INT0_vect){
	PORTC ^=(1<<PC0);
}
/*INT0 init*/
void int0_init(void){
	DDRD &=~(1<<PD2);
	MCUCR |= (1<<ISC01) | (1<<ISC00);
	GICR |=(1<<INT0);
	SREG |=(1<<7);
}
int main(void){
	int0_init();
	/*led setup*/
	DDRC |=(1<<PC0);
	PORTC |=(1<<PC0);
	while(1){

	}
	return 0;
}
