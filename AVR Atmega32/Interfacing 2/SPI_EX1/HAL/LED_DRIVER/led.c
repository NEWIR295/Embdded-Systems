/*
 * 		File Name: led.c
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: LED Driver Source File
 */
/* used libraries */
#include "../../MCAL/GPIO_Driver/GPIO/gpio.h"
#include "led.h"
/*
 * Initializes all Leds (red, green, blue) pins direction.
 * Turn off all the Leds
 */
void LEDS_init(void){

	/* SETUP LEDs  Direction as Output */
	GPIO_setupPinDirection(RED_LED_PORT,RED_LED_pin,PIN_OUTPUT);
	GPIO_setupPinDirection(GREEN_LED_PORT,GREEN_LED_pin,PIN_OUTPUT);
	GPIO_setupPinDirection(BLUE_LED_PORT,BLUE_LED_pin,PIN_OUTPUT);

	/* Turn off All pins on Startup*/
#if(LED_MODE == POSITIVE_LOGIC)

	GPIO_writePin(RED_LED_PORT,RED_LED_pin,LOW);
	GPIO_writePin(GREEN_LED_PORT,GREEN_LED_pin,LOW);
	GPIO_writePin(BLUE_LED_PORT,BLUE_LED_pin,LOW);

#elif(LED_MODE == NEGATIVE_LOGIC)

	GPIO_writePin(RED_LED_PORT,RED_LED_pin,HIGH);
	GPIO_writePin(GREEN_LED_PORT,GREEN_LED_pin,HIGH);
	GPIO_writePin(BLUE_LED_PORT,BLUE_LED_pin,HIGH);

#endif

}
/*
 * Turns on the specified LED.
 */
void LED_on(uint8 id){

#if(LED_MODE == POSITIVE_LOGIC)

	switch(id){
	case RED_LED_ID:
		GPIO_writePin(RED_LED_PORT,RED_LED_pin,HIGH);
		break;
	case BLUE_LED_ID:
		GPIO_writePin(BLUE_LED_PORT,BLUE_LED_pin,HIGH);
		break;
	case GREEN_LED_ID:
		GPIO_writePin(GREEN_LED_PORT,GREEN_LED_pin,HIGH);
		break;
	}


#elif(LED_MODE == NEGATIVE_LOGIC)

	switch(id){
	case RED_LED_ID:
		GPIO_writePin(RED_LED_PORT,RED_LED_pin,LOW);
		break;
	case BLUE_LED_ID:
		GPIO_writePin(BLUE_LED_PORT,BLUE_LED_pin,LOW);
		break;
	case GREEN_LED_ID:
		GPIO_writePin(GREEN_LED_PORT,GREEN_LED_pin,LOW);
		break;
	}

#endif

}

/*
 * Turns off the specified LED.
 */
void LED_off(uint8 id){


#if(LED_MODE == POSITIVE_LOGIC)

	switch(id){
	case RED_LED_ID:
		GPIO_writePin(RED_LED_PORT,RED_LED_pin,LOW);
		break;
	case BLUE_LED_ID:
		GPIO_writePin(BLUE_LED_PORT,BLUE_LED_pin,LOW);
		break;
	case GREEN_LED_ID:
		GPIO_writePin(GREEN_LED_PORT,GREEN_LED_pin,LOW);
		break;
	}


#elif(LED_MODE == NEGATIVE_LOGIC)

	switch(id){
	case RED_LED_ID:
		GPIO_writePin(RED_LED_PORT,RED_LED_pin,HIGH);
		break;
	case BLUE_LED_ID:
		GPIO_writePin(BLUE_LED_PORT,BLUE_LED_pin,HIGH);
		break;
	case GREEN_LED_ID:
		GPIO_writePin(GREEN_LED_PORT,GREEN_LED_pin,HIGH);
		break;
	}

#endif

}
