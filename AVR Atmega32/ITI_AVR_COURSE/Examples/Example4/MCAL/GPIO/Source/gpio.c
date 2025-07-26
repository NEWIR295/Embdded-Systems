/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: gpio.c
 *      Description:
 *      			Function implementations To handle AVR ATmega32 GPIO Registers
 */

/* standard library for AVR ATmega32 REG/PINs definitions*/
#include <avr/io.h>
/* used macros to handle REG/PINS operations */
#include "../../Macros/macros.h"

/* gpio header file */
#include "../Include/gpio.h"

/*
 * function used to setup certain pin direction in a certain port
 */
void GPIO_setupPinDirection(uint8 portNum, uint8 pinNum, GPIO_PinDirectionType direction){

	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			direction == PIN_OUTPUT ? SET_BIT(DDRA, pinNum) : CLEAR_BIT(DDRA, pinNum) ;
			break;
		case PORTB_ID:
			direction == PIN_OUTPUT ? SET_BIT(DDRB, pinNum) : CLEAR_BIT(DDRB, pinNum) ;
			break;
		case PORTC_ID:
			direction == PIN_OUTPUT ? SET_BIT(DDRC, pinNum) : CLEAR_BIT(DDRC, pinNum) ;
			break;
		case PORTD_ID:
			direction == PIN_OUTPUT ? SET_BIT(DDRD, pinNum) : CLEAR_BIT(DDRD, pinNum) ;
			break;
		}
	}
}

/*
 * function used to set on/off certain pin in certain port
 */
void GPIO_writePin(uint8 portNum, uint8 pinNum, Logical_Value value){

	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			High == value? SET_BIT(PORTA, pinNum) : CLEAR_BIT(PORTA, pinNum);
			break;
		case PORTB_ID:
			High == value? SET_BIT(PORTB, pinNum) : CLEAR_BIT(PORTB, pinNum);
			break;
		case PORTC_ID:
			High == value? SET_BIT(PORTC, pinNum) : CLEAR_BIT(PORTC, pinNum);
			break;
		case PORTD_ID:
			High == value? SET_BIT(PORTD, pinNum) : CLEAR_BIT(PORTD, pinNum);
			break;
		}
	}
}

/*
 * function used to toggle a certain pin in a certain port
 */
void GPIO_togglePin(uint8 portNum, uint8 pinNum){

	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			TOGGLE_BIT(PORTA, pinNum);
			break;
		case PORTB_ID:
			TOGGLE_BIT(PORTB, pinNum);
			break;
		case PORTC_ID:
			TOGGLE_BIT(PORTC, pinNum);
			break;
		case PORTD_ID:
			TOGGLE_BIT(PORTD, pinNum);
			break;
		}
	}
}

/*
 * function used to read a certain pin in a certain port
 */
Logical_Value GPIO_readPin(uint8 portNum, uint8 pinNum){

	if(portNum >= NUM_OF_PORTS || pinNum >= NUM_OF_PINS_PER_PORT){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			return BIT_IS_SET(PINA, pinNum) ? High : LOW;

		case PORTB_ID:
			return BIT_IS_SET(PINB, pinNum) ? High : LOW;

		case PORTC_ID:
			return BIT_IS_SET(PINC, pinNum) ? High : LOW;

		case PORTD_ID:
			return BIT_IS_SET(PIND, pinNum) ? High : LOW;
		}
	}
	return LOW;
}

/*
 * function used to setup certain port direction
 */
void GPIO_setupPortDirection(uint8 portNum, GPIO_PortDirectionType direction){

	if(portNum >= NUM_OF_PORTS){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*
 * function used to write entire port
 */
void GPIO_writePort(uint8 portNum, uint8 value){

	if(portNum >= NUM_OF_PORTS){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*
 * function read value of entire port
 */
uint8 GPIO_readPort(uint8 portNum){

	if(portNum >= NUM_OF_PORTS){
		/* do nothing */
	}
	else{
		switch(portNum){
		case PORTA_ID:
			return PINA;

		case PORTB_ID:
			return PINB;

		case PORTC_ID:
			return PINC;

		case PORTD_ID:
			return PIND;
		}
	}
	return LOW;
}

/*
 * function write a mask on a port
 */
void GPIO_writePortMasked(uint8 portNum, uint8 value, uint8 mask){

	if(portNum >= NUM_OF_PORTS)
	{
		/* do nothing */
	}
	else
	{
		uint8 currentValue = GPIO_readPort(portNum);
		uint8 newValue = (currentValue & ~mask) | (value & mask);
		GPIO_writePort(portNum, newValue);
	}
}
