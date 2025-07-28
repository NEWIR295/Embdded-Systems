/*
 * 		File Name: pwm.c
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: PWM Driver Source file
 */
/* used libraries */
#include <avr/io.h>
#include "../GPIO/gpio.h"

/*
 * Initializes Timer0 in PWM mode and sets the required duty cycle.
 * Prescaler: F_CPU/1024
 * Non-inverting mode
 * The function configures OC0 as the output pin.
*/
void PWM_Timer0_Start(uint8 duty_cycle){

	GPIO_setupPinDirection(PORTB_ID,PIN3_ID,PIN_OUTPUT);
	TCNT0 = 0;
	OCR0 = duty_cycle;
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS02) | (1<<CS00);


}
