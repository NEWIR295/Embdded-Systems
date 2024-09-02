/*
 * main.c
 *
 *  Created on: Aug 31, 2024
 *      Author: Mohamed Newir
 *      project description: control dc motor using L293 CHIP , using push button in pull-down mode for dir control
 */
/*system frequency*/
#define F_CPU 1000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>

/*main function*/
int main(void){
	DDRA &=~ (1<<PA0) & (1<<PA1) & (1<<PA2);
	DDRC |= (1<<PC0) | (1<<PC1);
	PORTC = (PORTC&0xfc) | (0x00&0x03);
	char button1State = 0;
	char button1LastState = 0;
	char button2State = 0;
	char button2LastState = 0;
	char button3State = 0;
	char button3LastState = 0;
	while(1){
		button1State = PINA&(1<<PA0);
		button2State = PINA&(1<<PA1);
		button3State = PINA&(1<<PA2);
		if(button1State == 1 && button1LastState !=0){
			/*motor rotate anti-clock wise*/
			PORTC = (PORTC&0xfc) | (0x02&0x03);
		}
		else if(button2State == 1 && button2LastState !=0){
			/*motor rotate anti-clock wise*/
			PORTC = (PORTC&0xfc) | (0x01&0x03);
		}
		else if(button3State == 1 && button3LastState !=0){
			/*stop motor*/
			PORTC = (PORTC&0xfc) | (0x00&0x03);
		}
		button1LastState = button1State;
		button2LastState = button2State;
		button3LastState = button3State;
		_delay_ms(30);
	}
	return 0;
}
