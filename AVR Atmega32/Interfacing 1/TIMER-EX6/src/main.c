/*
 * main.c
 *
 *  Created on: Sep 6, 2024
 *      Author: Mohamed Newir
 *      project Description: control led brightness using fastPWM
 */
/*system frequency*/
#define F_CPU 8000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>
/*timer fast pwm function*/
void timer0_init(unsigned int pwm){
	TCCR0 = (1<<WGM01)|(1<<WGM00)|(1<<COM01)|(1<<CS01);
	TCNT0 = 0;
	OCR0 = pwm;
}
/*main function*/
int main (void){
	DDRB |=(1<<PB3);
	unsigned int pwm;
	while(1){
		for(pwm = 0;pwm<256;pwm++){
			timer0_init(pwm);
			_delay_ms(100);
		}
		_delay_ms(100);
		for(;pwm>=0;pwm--){
			timer0_init(pwm);
			_delay_ms(100);
		}
	}
	return 0;
}

