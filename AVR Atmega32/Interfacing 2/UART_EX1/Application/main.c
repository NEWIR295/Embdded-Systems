/*
 * 		main.c
 *
 * 		Created on: Oct 12, 2024
 *      Author: Mohamed Newir
 *      Description: Test Uart Driver
 */

/* system internal frequency */
#define F_CPU 16000000UL

/* used Libraries */
#include "../MCAL/UART_DRIVER/uart.h"

int main(void){

	/* Application Initialization */
	uint8 data;
	uint8 str[20];
	UART_init(9600);

	while(1){
		/* Application Code */
		/*
		data = UART_receiveByte();
		UART_sendByte(data);
		*/
		UART_receiveString(str);
		UART_sendString(str);

	}
	return 0;
}
