/*
 * 		File Name: led.h
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: LED Driver Header File
 */

#ifndef LED_H_
#define LED_H_


/* user defined data types library */
#include "../macros/std_types.h"

/* LED Connection Logic */
#define POSITIVE_LOGIC TRUE
#define NEGATIVE_LOGIC FALSE

#define LED_MODE POSITIVE_LOGIC

/* Red LED port/pin ID */
#define RED_LED_PORT PORTB_ID
#define RED_LED_pin  PIN5_ID
#define RED_LED_ID 0

/* Green LED port/pin ID */
#define GREEN_LED_PORT PORTB_ID
#define GREEN_LED_pin  PIN6_ID
#define GREEN_LED_ID 1

/* Blue LED port/pin ID */
#define BLUE_LED_PORT PORTB_ID
#define BLUE_LED_pin PIN7_ID
#define BLUE_LED_ID 2

/* Function Prototype */

/*
 * Initializes all Leds (red, green, blue) pins direction.
 * Turn off all the Leds
 */
void LEDS_init(void);

/*
 * Turns on the specified LED.
 */
void LED_on(uint8 id);

/*
 * Turns off the specified LED.
 */
void LED_off(uint8 id);

#endif /* LED_H_ */
