/*
 * 		File Name: buzzer.h
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: Buzzer Driver Header File
 */

#ifndef BUZZER_H_
#define BUZZER_H_

/* user defined data types library */
#include "../../MCAL/GPIO_Driver/GPIO/gpio.h"

/* Buzzer Port/Pin ID */
#define BUZZER_PORT_ID PORTC_ID
#define BUZZER_PIN_ID PIN5_ID

/* Function Prototypes*/

/*
 * Initializes the buzzer pin direction and turn off the buzzer
 */
void Buzzer_init(void);

/*
 * Activates the buzzer.
 */
void Buzzer_on(void);

/*
 * Deactivates the buzzer.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
