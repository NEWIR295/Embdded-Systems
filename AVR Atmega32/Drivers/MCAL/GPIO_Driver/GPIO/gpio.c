/*
 * 		File Name: gpio.c
 *
 *      Created on: Sep 26, 2024
 *      Author: Mohamed Newir
 *      Description: source file define for Avr Atmega32 GPIO
 */
#include "gpio.h"

/* user defined macros*/
#include "../macros/macros.h"

/* avr std library*/
#include "avr/io.h"


/*
 * Description:
 * setup the direction of the required pin  either input or output
 * check if the input port and pin ID isn't defined
 * if the pin direction is output the  pin will be output
 * if the pin direction is input the  pin will be input
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction) {
	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/*do nothing*/
	} else {
		switch (port_num) {
		case PORTA_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRA, pin_num);
			} else {
				CLEAR_BIT(DDRA, pin_num);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRB, pin_num);
			} else {
				CLEAR_BIT(DDRB, pin_num);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRC, pin_num);
			} else {
				CLEAR_BIT(DDRC, pin_num);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT) {
				SET_BIT(DDRD, pin_num);
			} else {
				CLEAR_BIT(DDRD, pin_num);
			}
			break;
		}
	}
}

/*
 * Description:
 * write the value on required pin
 * check if the input port and pin ID isn't defined
 * if the pin is output the value will be written either LOW or HIGH
 * if the pin is input it will either activate/deactivate internal
 *  pull-up register
 */
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

/*
 * Description:
 * Read the value on required pin and return its value
 * check if the input port and pin ID isn't defined it will return 0
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num) {

	if ((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS)) {
		/* do nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			return BIT_IS_SET(PINA, pin_num) ? HIGH : LOW;
			break;
		case PORTB_ID:
			return BIT_IS_SET(PINB, pin_num) ? HIGH : LOW;
			break;
		case PORTC_ID:
			return BIT_IS_SET(PINC, pin_num) ? HIGH : LOW;
			break;
		case PORTD_ID:
			return BIT_IS_SET(PIND, pin_num) ? HIGH : LOW;
			break;
		}
/*
		switch(port_num)
				{
				case PORTA_ID:
					if(BIT_IS_SET(PINA,pin_num))
					{
						return HIGH;
					}
					else
					{
						return LOW;
					}
					break;
				case PORTB_ID:
					if(BIT_IS_SET(PINB,pin_num))
					{
						return HIGH;
					}
					else
					{
						return LOW;
					}
					break;
				case PORTC_ID:
					if(BIT_IS_SET(PINC,pin_num))
					{
						return HIGH;
					}
					else
					{
						return LOW;
					}
					break;
				case PORTD_ID:
					if(BIT_IS_SET(PIND,pin_num))
					{
						return HIGH;
					}
					else
					{
						return  LOW;
					}
					break;
				}*/

	}

	return 0;
}

/*
 * Description:
 * setup the direction of the required port  either input or output
 * check if the input port ID isn't defined
 * if the port direction is output the entire pins will be output
 * if the port direction is input the entire pins will be input
 */
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

/*
 * Description:
 * write the value on required port
 * check if the input port ID isn't defined
 * if the pin is output the value will be written
 * if the pin is input it will either activate/deactivate internal
 *  pull-up register
 */
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

/*
 * Description:
 * Read the value in required port and return its value
 * check if the input port ID isn't defined, it will return 0
 */
uint8 GPIO_readPort(uint8 port_num) {
	if ((port_num >= NUM_OF_PORTS)) {
		/* do nothing */
	} else {
		switch (port_num) {
		case PORTA_ID:
			return PINA;
			break;
		case PORTB_ID:
			return PINB;
			break;
		case PORTC_ID:
			return PINC;
			break;
		case PORTD_ID:
			return PIND;
			break;
		}
	}
	return 0;
}
