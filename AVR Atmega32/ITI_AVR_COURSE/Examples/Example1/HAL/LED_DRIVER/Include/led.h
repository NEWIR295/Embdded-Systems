/*
 *      Author: Mohamed Newir
 *      Created on: Jul 26, 2025
 *      File name: led.h
 *      Description:
 *      			Function declaration for LED driver
 */


#ifndef HAL_LED_DRIVER_INCLUDE_LED_H_
#define HAL_LED_DRIVER_INCLUDE_LED_H_

/* GPIO driver for ATmega32 */
#include "../../../MCAL/GPIO/Include/gpio.h"
/* user defined data types for AVR ATmega32  */
#include "../../../MCAL/Macros/std_types.h"

/* LED port ID definition */
#define LED_PORT_ID PORTA_ID

/* LED logic definition */
#define	NEGATIVE_LOGIC 0
#define POSITIVE_LOGIC 1

/* Configure LED connections */
#define CONFIG POSITIVE_LOGIC

/* Delay needed for every blink */
#define BLINK_MS_DELAY 100

#define NUM_OF_BLINKS 3

/* LED id declaration */
typedef enum{
	LED1_ID, LED2_ID, LED3_ID, LED4_ID, LED5_ID, LED6_ID, LED7_ID, LED8_ID
}LED_ID;

/* Function to initialize a certain led in a certain pin */
void LED_init(LED_ID led_id);

/* Function to set a certain led in a certain pin on */
void LED_on(LED_ID led_id);

/* Function to set a certain led in a certain pin off */
void LED_off(LED_ID led_id);

/* Function to blink a certain led in a certain pin */
void LED_blink(LED_ID led_id);

/* Function to toggle a certain led in a certain pin */
void LED_toggle(LED_ID led_id);

#endif /* HAL_LED_DRIVER_INCLUDE_LED_H_ */
