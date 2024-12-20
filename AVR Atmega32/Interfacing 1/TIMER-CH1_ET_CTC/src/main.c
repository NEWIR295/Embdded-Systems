/*
 * main.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Mohamed Newir
 *      Description: control lrd by timer0 in ctc mode
 */
/*std libraries*/
#include <avr/io.h>
#include <avr/interrupt.h>
/*system frequency*/
#define F_CPU 16000000
/*global variables*/
unsigned char tickG = 0;
unsigned char num = 0;
unsigned char compValue = 250;
unsigned char nCompPerSec= 250;
unsigned int numbers[10] = {0x7e,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};
/*ISR function*/
ISR(TIMER0_COMP_vect){
	tickG++;
	if(tickG == nCompPerSec){
		tickG = 0;
		if(num == 9){
			num = 0;
		}
		else{
			num++;
		}
		PORTA = (PORTA & 0x01) | (numbers[num] & 0xfe);
	}
}
/*timer 0 init*/
void timer0compMode(void){
	TCCR0 = (1<<FOC0) | (1<<WGM01) | (1<<CS02);
	TCNT0 = 0;
	OCR0 = compValue;
	TIMSK |= (1<<OCIE0);
	SREG |= (1<<7);
}
/*main function*/
int main(void){
	/*application initialization*/
	/*set port a as output*/
	DDRA = 0xfe;
	/*set port a to start with zero*/
	//PORTA = 0x7e;
	PORTA = (PORTA & 0x01) | (0x7e & 0xfe);/*save pin A0 from any undesired change*/
	/*enable 7 segment*/
	DDRC |=(1<<PC6);
	PORTC |= (1<<PC6);
	timer0compMode();
	while(1){

	}
	return 0;
}
