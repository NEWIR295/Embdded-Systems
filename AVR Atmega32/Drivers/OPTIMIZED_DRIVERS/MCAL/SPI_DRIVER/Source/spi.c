/*
 *      Author: Mohamed Newir
 *      Created on: Aug 6, 2025
 *      File name: spi.c
 *      Description:
 *      			SPI driver implementation
 */

#include <avr/io.h>
#include "../../GPIO/Include/gpio.h"
#include "../../Macros/macros.h"
#include "../Include/spi.h"
/* initialize SPI in master mode */
void SPI_masterInit(SPI_CLOCK_RATE clock){
	GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_OUTPUT); /* Set SS pin as output */
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_OUTPUT); /* Set MOSI pin as output */
	GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_INPUT); /* Set MISO pin as input */
	GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_OUTPUT); /* Set SCK pin as output */

	if(SPI_DOUBLE_SPEED_MODE == 0){

		switch(clock){
		case CLOCK_4:
			SPCR = (1<<SPE) | (1<<MSTR);
			SPSR &=~ (1<<SPI2X); /* test */
			break;

		case CLOCK_16:
			SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
			SPSR &=~ (1<<SPI2X); /* test */
			break;

		case CLOCK_64:
			SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1);
			SPSR &=~ (1<<SPI2X); /* test */
			break;

		case CLOCK_128:
			SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<SPR1);
			SPSR &=~ (1<<SPI2X); /* test */
			break;
		}
	}
	else{
		switch(clock){
		case CLOCK_2:
			SPCR = (1<<SPE) | (1<<MSTR);
			SPSR |= (1<<SPI2X); /* test */
			break;

		case CLOCK_8:
			SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0);
			SPSR |= (1<<SPI2X); /* test */
			break;

		case CLOCK_32:
			SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR1);
			SPSR |= (1<<SPI2X); /* test */
			break;

		case CLOCK_64:
			SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0) | (1<<SPR1);
			SPSR |= (1<<SPI2X); /* test */
			break;
		}
	}
}

/* initialize SPI in slave mode */
void SPI_slaveInit(void){
	GPIO_setupPinDirection(PORTB_ID, PIN4_ID, PIN_INPUT); /* Set SS pin as input */
	GPIO_setupPinDirection(PORTB_ID, PIN5_ID, PIN_INPUT); /* Set MOSI pin as input */
	GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT); /* Set MISO pin as output */
	GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_INPUT); /* Set SCK pin as input */

	SPCR = (1<<SPE); /* enable SPI and set it as slave*/

}

/* send receive byte in normal mode */
uint8 SPI_sendReceiveByte(uint8 data){

	SPDR = data;

	while(BIT_IS_CLEAR(SPSR, SPIF));

	return SPDR;
}

/*
 *  send receive byte in Daisy mode
 *  This forwards the previously received byte (in SPDR) to the next device.
 *  Useful for chaining shift-register-like devices.
*/
uint8 SPI_sendReceiveByteDaisy(){

	uint8 data= SPDR;
	SPDR = data;

	while(BIT_IS_CLEAR(SPSR, SPIF));

	return SPDR;
}

/* send send String in normal mode */
void SPI_sendString(uint8 *str){
	uint8 i = 0;
	while((str[i] != '\0') && (i < MAX_STRING_LENGTH - 1) ){
		SPI_sendReceiveByte(str[i]);
		i++;
	}
	SPI_sendReceiveByte('#');
}

/* send receive String in normal mode */
void SPI_receiveString(uint8 *str){
	uint8 i = 0;
	str[i] = SPI_sendReceiveByte(SPI_DEFAULT_VALUE);
	while(str[i] != '#'){
		i++;
		str[i] = SPI_sendReceiveByte(SPI_DEFAULT_VALUE);
	}
	str[i] = '\0';
}
