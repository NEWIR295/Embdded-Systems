/*
 *      Author: Mohamed Newir
 *      Created on: Jul 27, 2025
 *      File name: pir.c
 *      Description:
 *      			PIR sensor driver Implementation
 */

#include "../../../MCAL/GPIO/Include/gpio.h"
#include "../Include/pir.h"

/* function initialize PIR sensor */
void PIR_init(const PIR_t* pir){
	GPIO_setupPinDirection(pir->portNum, pir->pinNum, PIN_INPUT);
}

/* function read PIR sensor state */
uint8 PIR_state(const PIR_t* pir){
	return GPIO_readPin(pir->portNum, pir->pinNum);
}
