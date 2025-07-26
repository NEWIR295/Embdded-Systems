/*
 *      Author: Mohamed Newir
 *      Created on: Jul 26, 2025
 *      File name: pushbutton.h
 *      Description:
 *      			Pushbutton function declaration
 */


#ifndef HAL_PUSHBUTTON_DRIVER_INCLUDE_PUSHBUTTON_H_
#define HAL_PUSHBUTTON_DRIVER_INCLUDE_PUSHBUTTON_H_

/* GPIO driver for ATmega32 */
#include "../../../MCAL/GPIO/Include/gpio.h"
/* user defined data types for AVR ATmega32  */
#include "../../../MCAL/Macros/std_types.h"

/* Pushbutton configuration declaration  */
typedef enum{
	INTERNAL_PULLUP, EXTERNAL_PULLUP, PULLDOWN
}PushButton_CONFIG;

/* Pushbutton data type declaration*/
typedef struct {
	uint8 pinNum;
	uint8 portNum;
	PushButton_CONFIG config;
}PushButton_t;

/* Button condition data type declaration  */
typedef enum{
	BUTTON_RELEASED, BUTTON_PRESSED
}PUSHBUTTON_CONDITION;

/* Function initialize a certain pin in a certain port */
void PUSHBUTTON_init(const PushButton_t *button);

/* Function Check if button is pressed */
PUSHBUTTON_CONDITION PUSHBUTTON_buttonPressed(const PushButton_t *button);

#endif /* HAL_PUSHBUTTON_DRIVER_INCLUDE_PUSHBUTTON_H_ */
