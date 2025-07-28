/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: gpio.h
 *      Description:
 *      			Function declarations To handle AVR ATmega32 GPIO Registers
 */


#ifndef MCAL_GPIO_INCLUDE_GPIO_H_
#define MCAL_GPIO_INCLUDE_GPIO_H_

/* user defined data types for AVR ATmega32  */
#include "../../Macros/std_types.h"

/* define number of ports and pins in AVR ATmega32 GPIO registers*/
#define NUM_OF_PINS_PER_PORT 8
#define NUM_OF_PORTS 4

/* define port ID */
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

/* Define pins ID */
#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7

/* Pin direction declaration */
typedef enum{
	PIN_INPUT, PIN_OUTPUT
}GPIO_PinDirectionType;

/* Port direction declaration */
typedef enum{
	PORT_INPUT, PORT_OUTPUT = 0xff
}GPIO_PortDirectionType;

/* GPIO functions prototypes */

/*
 * function used to setup certain pin direction in a certain port
 */
void GPIO_setupPinDirection(uint8 portNum, uint8 pinNum, GPIO_PinDirectionType direction);

/*
 * function used to set on/off certain pin in certain port
 */
void GPIO_writePin(uint8 portNum, uint8 pinNum, Logical_Value value);

/*
 * function used to read a certain pin in a certain port
 */
Logical_Value GPIO_readPin(uint8 portNum, uint8 pinNum);

/*
 * function used to toggle a certain pin in a certain port
 */
void GPIO_togglePin(uint8 portNum, uint8 pinNum);

/*
 * function used to setup certain port direction
 */
void GPIO_setupPortDirection(uint8 portNum, GPIO_PortDirectionType direction);

/*
 * function used to write entire port
 */
void GPIO_writePort(uint8 portNum, uint8 value);

/*
 * function read value of entire port
 */
uint8 GPIO_readPort(uint8 portNum);

/*
 * function write a mask on a port
 */
void GPIO_writePortMasked(uint8 portNum, uint8 value, uint8 mask);

/*
 * Function sets the direction of specific pins in a port using a mask
 */
void GPIO_setupPortDirectionMasked(uint8 portNum, uint8 direction, uint8 mask);

#endif /* MCAL_GPIO_INCLUDE_GPIO_H_ */
