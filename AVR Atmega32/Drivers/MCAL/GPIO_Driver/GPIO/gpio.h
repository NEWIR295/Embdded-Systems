/*
 * 		File Name: gpio.h
 *
 *      Created on: Sep 26, 2024
 *      Author: Mohamed Newir
 *      Description: header file for Avr Atmega32 GPIO
 */



#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

/* user defined data types library */
#include "../macros/std_types.h"

/* Register ID definitions */
#define NUM_OF_PORTS 4
#define NUM_OF_PINS_PER_PORT 8

#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

/* GPIO Type Declaration */

/* set either pin is input or output */
typedef enum{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

/* set either port is input or output */
typedef enum{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/* GPIO function prototype */

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);
void GPIO_writePort(uint8 port_num, uint8 value);
uint8 GPIO_readPort(uint8 port_num);


#endif /* GPIO_GPIO_H_ */