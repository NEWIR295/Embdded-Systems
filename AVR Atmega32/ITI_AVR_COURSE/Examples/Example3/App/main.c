/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: main.c
 *      Description:
 *      		   Simple Application control two LEDs using 2 Pushbuttons
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "../HAL/LED_DRIVER/Include/led.h"
#include "../HAL/PUSHBUTTON_DRIVER/Include/pushbutton.h"

int main(void){

	PushButton_t button1 = {PIN0_ID, PORTD_ID, INTERNAL_PULLUP};
	PushButton_t button2 = {PIN1_ID, PORTD_ID, INTERNAL_PULLUP};

	PUSHBUTTON_init(&button1);
	PUSHBUTTON_init(&button2);

	LED_init(LED1_ID);
	LED_init(LED2_ID);

	PUSHBUTTON_CONDITION button1State = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION lastButton1State = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION button2State = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION lastButton2State = BUTTON_RELEASED;

	while(1){
		button1State = PUSHBUTTON_buttonPressed(&button1);
		button2State = PUSHBUTTON_buttonPressed(&button2);

		if(button1State == BUTTON_PRESSED && lastButton1State != BUTTON_PRESSED){
			LED_on(LED1_ID);
		}
		else if(button1State == BUTTON_RELEASED && lastButton1State != BUTTON_RELEASED){
			LED_off(LED1_ID);
		}
		lastButton1State = button1State;

		if(button2State == BUTTON_PRESSED && lastButton2State != BUTTON_PRESSED){
			LED_on(LED2_ID);
		}
		else if(button2State == BUTTON_RELEASED && lastButton2State != BUTTON_RELEASED){
			LED_off(LED2_ID);
		}
		lastButton2State = button2State;

	}
	return 0;
}

