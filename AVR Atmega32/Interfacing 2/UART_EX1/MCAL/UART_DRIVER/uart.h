/*
 * 		File Name: uart.h
 *
 *  	Created on: Oct 12, 2024
 *      Author: Mohamed Newir
 *      Description: Uart header File
 */

#ifndef MCAL_UART_DRIVER_UART_H_
#define MCAL_UART_DRIVER_UART_H_

/* User Defined Data Types */
#include "../GPIO_Driver/macros/std_types.h"

/* Function Prototypes */

/* function initialize uart peripheral with user Baud Rate */
void UART_init(uint32 baud_rate);

/* function responsible for sending 1 byte to to another device */
void UART_sendByte(const uint8 data);

/* function responsible for receiving 1 byte to to another device */
uint8 UART_receiveByte(void);

/* function responsible for sending String to to another device */
void UART_sendString(const uint8 *str);

/* function responsible for receiving String to to another device */
void UART_receiveString(uint8 *str);

#endif /* MCAL_UART_DRIVER_UART_H_ */
