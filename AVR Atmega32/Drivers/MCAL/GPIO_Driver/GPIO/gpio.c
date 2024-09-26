/*
 * 		File Name: gpio.c
 *
 *      Created on: Sep 26, 2024
 *      Author: Mohamed Newir
 *      Description: source file define for Avr Atmega32 GPIO
 */
#include "gpio.h"
#include "../macros/macros.h"
#include "avr/io.h"

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDirectionType direction) {
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/*do nothing*/
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA, PIN_OUTPUT);
			} else {
				CLEAR_BIT(DDRA, PIN_INPUT);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB, PIN_OUTPUT);
			} else {
				CLEAR_BIT(DDRB, PIN_INPUT);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC, PIN_OUTPUT);
			} else {
				CLEAR_BIT(DDRC, PIN_INPUT);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD, PIN_OUTPUT);
			} else {
				CLEAR_BIT(DDRD, PIN_INPUT);
			}
			break;
		}
	}
}
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value) {
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/* do nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (HIGH == value) {
				SET_BIT(PORTA, pin_num);
			} else {
				CLEAR_BIT(PORTA, pin_num);
			}
			break;
		case PORTB_ID:
			if (HIGH == value) {
				SET_BIT(PORTB, pin_num);
			} else {
				CLEAR_BIT(PORTB, pin_num);
			}
			break;
		case PORTC_ID:
			if (HIGH == value) {
				SET_BIT(PORTC, pin_num);
			} else {
				CLEAR_BIT(PORTC, pin_num);
			}
			break;
		case PORTD_ID:
			if (HIGH == value) {
				SET_BIT(PORTD, pin_num);
			} else {
				CLEAR_BIT(PORTD, pin_num);
			}
			break;
		}
	}
}
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {

	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/* do nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			return BIT_IS_SIT(PINA, pin_num);
			break;
		case PORTB_ID:
			return BIT_IS_SIT(PINB, pin_num);
			break;
		case PORTC_ID:
			return BIT_IS_SIT(PINC, pin_num);
			break;
		case PORTD_ID:
			return BIT_IS_SIT(PIND, pin_num);
			break;
		}
	}

	return 0;
}
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction) {
	if ((port_num >= NUM_OF_PORTS)) {
		/* do nothing */
	} else {
		switch (port_num) {
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
void GPIO_writePort(uint8 port_num, uint8 value) {
	if ((port_num >= NUM_OF_PORTS)) {
		/* DO NOTHING */
	} else {
		switch (port_num) {
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
uint8 GPIO_readPort(uint8 port_num) {
	if ((port_num >= NUM_OF_PORTS)) {
		/* do nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			return PINA;
			break;
		case PORTB_ID:
			return PINC;
			break;
		case PORTC_ID:
			return PINB;
			break;
		case PORTD_ID:
			return PIND;
			break;
		}
	}
	return 0;
}
