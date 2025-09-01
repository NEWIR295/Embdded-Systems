/*
 *      Author: Mohamed Newir
 *      Created on: Aug 6, 2025
 *      File name: spi.h
 *      Description:
 *      			SPI driver declaration
 */


#ifndef MCAL_SPI_DRIVER_INCLUDE_SPI_H_
#define MCAL_SPI_DRIVER_INCLUDE_SPI_H_

#include "../../Macros/std_types.h"

#define SPI_DEFAULT_VALUE 0xFF

#define MAX_STRING_LENGTH 50

/* set SPI speed mode */
#define SPI_DOUBLE_SPEED_MODE True

/* SPI clock rate data type declaration */
typedef enum{
	CLOCK_2 , CLOCK_4, CLOCK_8, CLOCK_16,
	CLOCK_32, CLOCK_64, CLOCK_128
}SPI_CLOCK_RATE;

/* initialize SPI in master mode */
void SPI_masterInit(SPI_CLOCK_RATE clock);

/* initialize SPI in slave mode */
void SPI_slaveInit(void);

/* send receive byte in normal mode */
uint8 SPI_sendReceiveByte(uint8 data);

/* send receive byte in Daisy mode */
uint8 SPI_sendReceiveByteDaisy(void);

/* send send String in normal mode */
void SPI_sendString(uint8 *str);

/* send receive String in normal mode */
void SPI_receiveString(uint8 *str);

#endif /* MCAL_SPI_DRIVER_INCLUDE_SPI_H_ */
