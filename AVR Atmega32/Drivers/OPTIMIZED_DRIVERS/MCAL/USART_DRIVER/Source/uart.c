/*
 *      Author: Mohamed Newir
 *      Created on: Aug 6, 2025
 *      File name: UART.c
 *      Description:
 *      			UART function implementation
 */

#include <avr/io.h>
#include "../../Macros/macros.h"
#include "../Include/uart.h"
/* UART initialization */
void UART_init(UART_t *uart){

	uint16 ubrrValue;
	uint8 uscrc = (1 << URSEL);
	/* check if i want double speed mode */
	if(uart -> ASYNC_DSM){
		UCSRA = (1 << U2X);
		ubrrValue = (uint16)((F_CPU/((8UL) * uart -> baudRate)) - 1);
	}
	else{
		UCSRA = 0x00; /* ensure that the whole register is cleared */
		ubrrValue = (uint16)((F_CPU/((16UL) * uart -> baudRate)) - 1);
	}

	UCSRB = (1 << RXEN) | (1 << TXEN);
	uscrc |= (1<<UCSZ1) | (1<<UCSZ0);
	uscrc &= ~((1<<UMSEL) | (1<<UCPOL));

	switch(uart ->mode){

	case DISABLED:
		uscrc &= ~((1<<UPM0) | (1<<UPM1));
		break;

	case EVEN_PARITY:
		uscrc &= ~(1<<UPM0);
		uscrc |= (1<<UPM1);
		break;

	case ODD_PARITY:
		uscrc |= (1<<UPM1) | (1<<UPM0);
		break;
	}

	switch(uart -> select){

	case ONE_BIT:
		uscrc &=~ (1<<USBS);
		break;

	case TWO_BIT:
		uscrc |= (1<<USBS);
		break;
	}

	UCSRC = uscrc;
	UBRRH = ubrrValue >> 8;
	UBRRL = ubrrValue;

}

/* UART receive byte */
bool UART_receiveByte(uint8 *data){

	while(BIT_IS_CLEAR(UCSRA, RXC));
	uint8 status = UCSRA; /* Capture status before reading UDR */
	uint8 byte = UDR;
	if(BIT_IS_SET(status, FE) || BIT_IS_SET(status, PE)){
		/* data should be initialized before it sent */
		*data = 0;
		return False;
	}
	*data = byte;
	return True;
}

/* UART send byte */
void UART_sendByte(const uint8 data){

	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR = data;

	/*
	 * while(BIT_IS_CLEAR(UCSRA, TXC));
	 * SET_BIT(UCSRA, TXC);
	 */

}

/* UART receive string */
void UART_receiveString(uint8 *str){
	uint8 i = 0;
	/* receive the first byte */
	if(!UART_receiveByte(str)){
		*(str) = '\0';
		return;
	}
	/* check the each byte if it's = # */
	while((*(str + i) != '#') && (i < MAX_STRING_LENGTH - 1 )){
		i++;
		if(!UART_receiveByte(str + i)){
			*(str + i) = '\0';
			return;
		}
	}
	/* after receiving the whole string with # replace # with
	 *  the null terminator
	 */
	*(str + i) = '\0';
}

/* UART send string */
void UART_sendString(const uint8 *str){
	uint8 i;

	for(i = 0; *(str + i) != '\0'; i++){
		UART_sendByte(*(str + i));
	}
	UART_sendByte('#');
}
