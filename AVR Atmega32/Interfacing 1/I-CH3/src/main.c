/*
 * main.c
 *
 *  Created on: Aug 17, 2024
 *      Author: Mohamed Newir
 *      project description: controlling 7-segment using 2 pusg buttons
 */
/*system frequency*/
#define F_CPU 16000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>
/*main function*/
int main(void){
	/*application initialization*/
	/*set pin 2 & 3 in port d as input for push buttons*/
	DDRD &= ~(1<<PD2) & ~(1<<PD3);
	/*activate internal AVR pull up resistor */
	/*
	PORTD |= (1<<PD2) | (1<<PD3);
	 */
	/*set port a as output*/
	DDRA = 0xfe;
	/*set port a to start with zero*/
	//PORTA = 0x7e;
	PORTA = (PORTA & 0x01) | (0x7e & 0xfe);/*save pin A0 from any undesired change*/
	/*enable 7 segment*/
	DDRC |=(1<<PC6);
	PORTC |= (1<<PC6);
	int button1state = 0;
	int button2state = 0;
	int lastButton1state = 0;
	int lastButton2state = 0;
	int num = 0;
	unsigned int numbers[10] = {0x7e,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};
	while(1){
		/*application code*/
		/*read button value*/
		button1state = PIND&(1<<PD2);
		button2state = PIND&(1<<PD3);
		/*increment the counter*/
		if(button1state == 0 && lastButton1state != 0){
			if(num<9){
				num++;
				/*save pin A0 from any undesired change*/
				PORTA = (PORTA & 0x01) | (numbers[num] & 0xfe);
			}
		}
		lastButton1state = button1state;
		/*decrement the counter*/
		if(button2state == 0 && lastButton2state != 0){
			if(num>0){
				num--;
				/*save pin A0 from any undesired change*/
				PORTA = (PORTA & 0x01) | (numbers[num] & 0xfe);
			}
		}
		lastButton2state = button2state;
		/*solve Denouncing effect*/
		_delay_ms(30);
	}
	return 1;
}
