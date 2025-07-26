/*
 *      Author: Mohamed Newir
 *      Created on: Jul 26, 2025
 *      File name: pushbutton.c
 *      Description:
 *               	Pushbutton function implementation
 *
 */

#include "../Include/pushbutton.h"

/* Function initialize a certain pin in a certain port */
void PUSHBUTTON_init(const PushButton_t *button){
	GPIO_setupPinDirection(button->portNum, button->pinNum, PIN_INPUT);
	if(button->config == INTERNAL_PULLUP){
		GPIO_writePin(button->portNum, button->pinNum, High);
	}
}

/* Function Check if button is pressed */
PUSHBUTTON_CONDITION PUSHBUTTON_buttonPressed(const PushButton_t *button){
	if(button -> config == PULLDOWN){
		return GPIO_readPin(button->portNum, button->pinNum) == High? BUTTON_PRESSED : BUTTON_RELEASED;
	}
	else{
		return GPIO_readPin(button->portNum, button->pinNum) == LOW? BUTTON_PRESSED : BUTTON_RELEASED;
	}
}
