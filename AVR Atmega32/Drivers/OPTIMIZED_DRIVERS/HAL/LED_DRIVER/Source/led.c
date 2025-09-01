/*
 *      Author: Mohamed Newir
 *      Created on: Jul 26, 2025
 *      File name: led.c
 *      Description:
 *      			Function implementation for LED driver
 */

/* AVR delay library */
#include <util/delay.h>
#include "../Include/led.h"

/* Function to initialize a certain led in a certain pin */
void LED_init(LED_ID led_id){
	GPIO_setupPinDirection(LED_PORT_ID, led_id, PIN_OUTPUT);
#if(CONFIG == POSITIVE_LOGIC)
	GPIO_writePin(LED_PORT_ID, led_id, LOW);
#else
	GPIO_writePin(LED_PORT_ID, led_id, HIGH);
#endif
}

/* Function to set a certain led in a certain pin on */
void LED_on(LED_ID led_id){

#if(CONFIG == POSITIVE_LOGIC)
	GPIO_writePin(LED_PORT_ID, led_id, HIGH);
#else
	GPIO_writePin(LED_PORT_ID, led_id, LOW);
#endif
}

/* Function to set a certain led in a certain pin off */
void LED_off(LED_ID led_id){

#if(CONFIG == POSITIVE_LOGIC)
	GPIO_writePin(LED_PORT_ID, led_id, LOW);
#else
	GPIO_writePin(LED_PORT_ID, led_id, HIGH);
#endif
}

/* Function to blink a certain led in a certain pin */
void LED_blink(LED_ID led_id){
	uint8 i;
	for(i = 0; i < NUM_OF_BLINKS; i++){
		LED_toggle(led_id);
		_delay_ms(BLINK_MS_DELAY);
	}
}

/* Function to toggle a certain led in a certain pin */
void LED_toggle(LED_ID led_id){
	GPIO_togglePin(LED_PORT_ID, led_id);
}
