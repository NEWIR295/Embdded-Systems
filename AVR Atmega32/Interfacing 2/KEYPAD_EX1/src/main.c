/*
 * main.c
 *
 *  Created on: Sep 27, 2024
 *      Author: Mohamed Newir
 *
 */
#include "../Keypad_Driver/keypad.h"
#include "../GPIO/gpio.h"

int main(void){

	GPIO_setupPinDirection(PORTC_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN2_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTC_ID,PIN3_ID,PIN_OUTPUT);

	while(1){
		uint8 key= KEYPAD_getPressedKey();
		if(key >= 0 && key <=9){
			GPIO_writePort(PORTC_ID,key);
		}
	}
	return 0;
}
