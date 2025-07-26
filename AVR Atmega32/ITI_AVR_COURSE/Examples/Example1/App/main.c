/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: main.c
 *      Description:
 *      		   Simple Application open/close LED
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "../HAL/LED_DRIVER/Include/led.h"
#include "../HAL/PUSHBUTTON_DRIVER/Include/pushbutton.h"

int main(void){

	PushButton_t button = {PIN0_ID, PORTA_ID, INTERNAL_PULLUP};
	PUSHBUTTON_init(&button);
	LED_init(LED2_ID);

	PUSHBUTTON_CONDITION buttonState = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION lastButtonState = BUTTON_RELEASED;

	while(1){
		buttonState = PUSHBUTTON_buttonPressed(&button);
		if(buttonState == BUTTON_PRESSED && lastButtonState != BUTTON_PRESSED){
			LED_toggle(LED2_ID);
		}
		lastButtonState = buttonState;
	}
	return 0;
}
