/*
 * 		File Name: twi.c
 *
 *  	Created on: Oct 29, 2024
 *      Author: Mohamed Newir
 *      Description: Two Wire Interface Driver Header File
 */

/* Used Libraries */
#include <avr/io.h>
#include "../GPIO_Driver/macros/macros.h"
#include "twi.h"

/* Function Prototypes */

/* function initialize I2C in master */
void TWI_init(void){

	TWBR = 0x02;  /* using 400.kps bit rate */
	TWSR = 0x00; /* using zero pre-scaler*/

	TWAR = 0b00000010; /* device address */
	TWCR = (1<<TWEN);

}

/* function sent start bit */
void TWI_start(void){

	/*
	 * send start bit
	 * enable TWI module
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT)); /* wait until start bit is sent successfully */
}

/* function sent stop bit */
void TWI_stop(void){

	/*
	 * Send stop bit
	 * enable TWI module
	 */
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

/* function write byte */
void TWI_writeByte(uint8 data){

	TWDR = data ; /* Send data */
	/*
	 * enable TWI module
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) ;
	while(BIT_IS_CLEAR(TWCR,TWINT)); /* wait until data is send successfully */
}

/* function read byte with acknowledgment */
uint8 TWI_readByteWithACK(void){

	/*
	 * enable TWI module
	 * enable send Acknowledgment after receiving data
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;
	while(BIT_IS_CLEAR(TWCR,TWINT)); /* wait until data is received */
	return TWDR; /* read data */
}

/* function read byte with no acknowledgment */
uint8 TWI_readByteWithNACK(void){

	/*
	 * enable TWI module
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(BIT_IS_CLEAR(TWCR,TWINT)); /* wait until data is received successfully */
	return TWDR; /* read data */
}

/* function get I2C status */
uint8 TWI_getStatus(void){

	uint8 status;
	status = TWSR & 0xF8; /* read only the last 5 bits in TWCR register to get TWI status*/
	return status; /* return status */
}
