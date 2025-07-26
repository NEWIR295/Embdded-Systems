/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: main.c
 *      Description:
 *      		   Simple Application control 3 LEDs using external interrupts
 *      		   Connected to 3 pushbuttons
 */

#define F_CPU 8000000UL
#include "../HAL/LED_DRIVER/Include/led.h"
#include "../HAL/PUSHBUTTON_DRIVER/Include/pushbutton.h"
#include "../MCAL/EXT_INTERTUPT_DRIVER/Include/EXT_interrupt.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void int0CB(void){
	LED_toggle(LED1_ID);
}

void int1CB(void){
	LED_toggle(LED2_ID);
}

void int2CB(void){
	LED_toggle(LED3_ID);
}

int main(void){

	PushButton_t button1 = {PIN2_ID, PORTD_ID, INTERNAL_PULLUP};
	PushButton_t button2 = {PIN3_ID, PORTD_ID, INTERNAL_PULLUP};
	PushButton_t button3 = {PIN2_ID, PORTB_ID, INTERNAL_PULLUP};

	PUSHBUTTON_init(&button1);
	PUSHBUTTON_init(&button2);
	PUSHBUTTON_init(&button3);

	EXT_INTERRUPT(INT0,ENABLE,RISING_EDGE);
	EXT_INTERRUPT(INT1,ENABLE,RISING_EDGE);
	EXT_INTERRUPT(INT2,ENABLE,FALLING_EDGE);

	EXT_int0_set_cb(int0CB);
	EXT_int1_set_cb(int1CB);
	EXT_int2_set_cb(int2CB);

	LED_init(LED1_ID);
	LED_init(LED2_ID);
	LED_init(LED3_ID);

	while(1){
	}

	return 0;
}

