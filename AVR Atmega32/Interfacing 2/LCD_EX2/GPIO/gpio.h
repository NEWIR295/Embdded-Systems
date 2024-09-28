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

/* PORT ID*/
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

/* PIN ID */
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

/*
 * Description:
 * setup the direction of the required pin  either input or output
 * check if the input port and pin ID isn't defined
 * if the pin direction is output the  pin will be output
 * if the pin direction is input the  pin will be input
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);

/*
 * Description:
 * write the value on required pin
 * check if the input port and pin ID isn't defined
 * if the pin is output the value will be written either LOW or HIGH
 * if the pin is input it will either activate/deactivate internal
 *  pull-up register
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*
 * Description:
 * Read the value on required pin and return its value
 * check if the input port and pin ID isn't defined it will return 0
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*
 * Description:
 * setup the direction of the required port  either input or output
 * check if the input port ID isn't defined
 * if the port direction is output the entire pins will be output
 * if the port direction is input the entire pins will be input
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);


/*
 * Description:
 * write the value on required port
 * check if the input port ID isn't defined
 * if the pin is output the value will be written
 * if the pin is input it will either activate/deactivate internal
 *  pull-up register
 */
void GPIO_writePort(uint8 port_num, uint8 value);


/*
 * Description:
 * Read the value on required port and return its value
 * check if the input port ID isn't defined it will return 0
 */
uint8 GPIO_readPort(uint8 port_num);

#endif /* GPIO_GPIO_H_ */
