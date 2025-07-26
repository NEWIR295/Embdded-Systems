/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: main.c
 *      Description:
 *      		   Simple Application control 8 LEDs using 2 Pushbuttons
 *      		   one pushbutton only open even LEDs and the other for odd LEDs
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "../HAL/LED_DRIVER/Include/led.h"
#include "../HAL/PUSHBUTTON_DRIVER/Include/pushbutton.h"

int main(void){
	uint8 i;

	PushButton_t button1 = {PIN0_ID, PORTD_ID, INTERNAL_PULLUP};
	PushButton_t button2 = {PIN1_ID, PORTD_ID, INTERNAL_PULLUP};

	PUSHBUTTON_init(&button1);
	PUSHBUTTON_init(&button2);

	for(i = 0; i<NUM_OF_LEDS; i++){
		LED_init(i);
	}

	PUSHBUTTON_CONDITION button1State = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION lastButton1State = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION button2State = BUTTON_RELEASED;
	PUSHBUTTON_CONDITION lastButton2State = BUTTON_RELEASED;

	while(1){
		button1State = PUSHBUTTON_buttonPressed(&button1);
		button2State = PUSHBUTTON_buttonPressed(&button2);

		if(button1State == BUTTON_PRESSED && lastButton1State != BUTTON_PRESSED){

			for(i = 0; i < NUM_OF_LEDS; i++){
				if(i%2 == 0){
					LED_on(i);
				}
				else{
					LED_off(i);
				}
			}
		}
		lastButton1State = button1State;

		if(button2State == BUTTON_RELEASED && lastButton2State != BUTTON_RELEASED){
			for(i = 0; i < NUM_OF_LEDS; i++){
				if(i%2 != 0){
					LED_on(i);
				}
				else{
					LED_off(i);
				}
			}
		}
		lastButton2State = button2State;

	}
	return 0;
}

