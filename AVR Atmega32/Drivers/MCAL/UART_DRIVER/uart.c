/*
 * 		File Name: uart.c
 *
 *  	Created on: Oct 12, 2024
 *      Author: Mohamed Newir
 *      Description: Uart Source File
 */

/* used Libraries */
#include <avr/io.h>
#include "uart.h"
#include "../GPIO_Driver/macros/macros.h"

/* function initialize uart peripheral with user Baud Rate */
void UART_init(uint32 baud_rate){

	/* store the value of UBRR register */
	uint16 ubrr_value = 0;

	/* for double speed in asynchronous mode */
	UCSRA = (1<<U2X);

	/* enable receiver and transmitter registers */
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/* enable even parity
	 * choose 2 bits stop bit
	 * choose 8 bit character size
	 */
	/*
	UCSRC = (1<<URSEL) | (1<<UPM1) | (1<<USBS) | (1<<UCSZ1) | (1<<UCSZ0);
	*/

	/*
	 * enable 8 bit mode only
	 */
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);

	/* setup user desired baud rate */
	ubrr_value = (uint16)(((F_CPU/(baud_rate * 8UL)))-1);
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/* function responsible for sending 1 byte to to another device */
void UART_sendByte(const uint8 data){

	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;
}

/* function responsible for receiving 1 byte to to another device */
uint8 UART_receiveByte(void){

	while(bit_is_clear(UCSRA,RXC));
	if( bit_is_clear(UCSRA,FE) && bit_is_clear(UCSRA,PE) ){
		return UDR;
	}
	return 0;
}

/* function responsible for sending String to to another device */
void UART_sendString(const uint8 *str){

	uint8 i = 0;
	while( *(str+i) != '\0'){
		UART_sendByte( *(str+i) );
		i++;
	}
}

/* function responsible for receiving String to to another device */
void UART_receiveString(uint8 *str){

	uint8 i =0;
	str[i] = UART_receiveByte();
	while( *(str + i) != '#'){
		i++;
		*(str+i) = UART_receiveByte();
	}
	*(str+i) ='\0';
}
