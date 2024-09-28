/*
 * main.c
 *
 *  Created on: Sep 27, 2024
 *      Author: Mohamed Newir
 *
 */
/* adjust system frequency */
#define F_CPU 16000000UL

/* used libraries */
#include "../Keypad_Driver/keypad.h"
#include "../GPIO/gpio.h"

int main(void){

	/* numbers container */
	uint8 numbers[10] = {0x7e,0x0c,0xb6,0x9e,0xcc,0xda,0xfa,0x0e,0xfe,0xde};

	/* initialize 7 segment pins */
	GPIO_setupPinDirection(PORTA_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN2_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN3_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN7_ID,PIN_OUTPUT);

	/* enable 7 segment */
	GPIO_setupPinDirection(PORTC_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_writePin(PORTC_ID,PIN6_ID,HIGH);

	/* initialize 7 segment with 0 */
	GPIO_writePort(PORTA_ID,numbers[0]);

	uint8 count;
	while(1){

		/* get pressed button */
		uint8 key= KEYPAD_getPressedKey();

		/* validate key data*/
		if((key >= 0) && (key <=9)){
				/* write on the entire port the pressed key */
					GPIO_writePort(PORTA_ID,numbers[key]);
		}
	}
	return 0;
}
