/*
 *      File Name: main.c
 *
 *      Created on: Jul 17, 2025
 *      Author: newir529
 */
#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL

int main (void){
	int i;
	DDRB |= 0x07;
	PORTB &=~ 0x07;

	DDRC &= ~(1 << PC0) & ~(1 << PC1);
	PORTC |= (1 << PC0) | (1 << PC1);
	unsigned int button1 = 0;
	unsigned int button2 = 0;
	unsigned int lastButton1 = 0;
	unsigned int lastButton2 = 0;

	while(1){
		button1 = (PINC & (1 << PC0));
		button2 = (PINC & (1 << PC1));

		if(button1 == 0 && lastButton1 != 0){
			for(i = 0; i < 3; i++ ){
				PORTB |= (1 << i);
				_delay_ms(500);
			}
			PORTB = 0;
		}
		lastButton1 = button1;

		if(button2 == 0 && lastButton2 != 0){
			for(i = 2; i >= 0; i-- ){
				PORTB |= (1 << i);
				_delay_ms(500);
				if(i == 0) break;
			}
			PORTB = 0;
		}
		lastButton2 = button2;
	}
	return 0;
}
