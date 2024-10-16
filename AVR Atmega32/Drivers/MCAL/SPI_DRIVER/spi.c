/*
 * 		File Name: spi.c
 *
 *  	Created on: Oct 16, 2024
 *      Author: Mohamed Newir
 *      Description: SPI Driver Source File
 */

/* used libraries */
#include <avr/io.h>
#include "../GPIO_Driver/GPIO/gpio.h"
#include "../GPIO_Driver/macros/macros.h"
#include "spi.h"

/* SPI master initialization */
void SPI_initMaster(void){

	/* set spi pin direction */
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);

	/* enable spi and master */
	SPCR = (1<<SPE) | (1<<MSTR) ;
	SPSR &=~(1<<SPI2X);
}

/* SPI slave initialization */
void SPI_initSlave(void){

	/* set spi pin direction */
	GPIO_setupPinDirection(PORTB_ID,PIN4_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_INPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN6_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_INPUT);

	/* enable spi and slave */
	SPCR = (1<<SPE) ;
	SPSR &=~(1<<SPI2X);
}

/*
 * SPI function send and receive data at the same time
 */
uint8 SPI_sendReceive(uint8 data){

	/* send data to another device */
	SPDR = data;

	/* wait until data sent successfully */
	while(BIT_IS_CLEAR(SPSR,SPIF));

	/* return data received */
	return SPDR;

}

/*
 * send String to another device using SPI
 */
void SPI_sendString(const uint8 *str){

	/* counter variable */
	uint8 i = 0;

	/* dummy variable */
	uint8 dataReceived = 0;

	while( *(str + i ) != '\0'){
		dataReceived = SPI_sendReceive( *(str + i) );
		i++;
	}
}

/*
 * Receive String from another device using SPI
 */
void SPI_ReceiveString(uint8 *str){

	/* counter variable */
	uint8 i = 0;

	/* dummy variable */
	str[i] = SPI_sendReceive(SPI_DEFAULT_VALUE) ;

	while( *(str + i ) != '#'){
		i++;
		str[i] = SPI_sendReceive( SPI_DEFAULT_VALUE );
	}
	str[i] = '\0';
}

