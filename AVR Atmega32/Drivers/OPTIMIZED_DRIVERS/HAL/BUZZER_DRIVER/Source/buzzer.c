/*
 *      Author: Mohamed Newir
 *      Created on: Jul 27, 2025
 *      File name: buzzer.c
 *      Description:
 *      			buzzer driver implementation
 */

#include "../../../MCAL/GPIO/Include/gpio.h"
#include "../Include/buzzer.h"

/* Function initialize buzzer */
void BUZZER_init(const Buzzer_t *buzzer){
	GPIO_setupPinDirection(buzzer->portNum, buzzer->pinNum, PIN_OUTPUT);
	GPIO_writePin(buzzer->portNum, buzzer->pinNum,LOW);
}

/* Function control buzzer state  */
void BUZZER_activeCtrl(const Buzzer_t *buzzer, BUZZER_STATE state){
	GPIO_writePin(buzzer->portNum, buzzer->pinNum,state);
}

/* Function control passive buzzer state  */
void BUZZER_passiveCtrl(const Buzzer_t *buzzer, BUZZER_STATE state, uint8 freq){

}
