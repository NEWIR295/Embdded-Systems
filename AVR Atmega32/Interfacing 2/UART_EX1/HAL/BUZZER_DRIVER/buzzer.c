/*
 * 		File Name: buzzer.c
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: Buzzer Driver Source File
 */
/* used libraries */
#include "../../MCAL/GPIO_Driver/GPIO/gpio.h"
#include "buzzer.h"

/*
 * Initializes the buzzer pin direction and turn off the buzzer
 */
void Buzzer_init(void){

	/* set buzzer pin direction to be output */
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);

}

/*
 * Activates the buzzer.
 */
void Buzzer_on(void){

	/* activate buzzer */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,HIGH);

}

/*
 * Deactivates the buzzer.
 */
void Buzzer_off(void){

	/* deactivate buzzer */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOW);

}
