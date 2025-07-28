/*
 * 		File Name: spi.h
 *
 *  	Created on: Oct 16, 2024
 *      Author: Mohamed Newir
 *      Description: SPI Driver Header File
 */

#ifndef MCAL_SPI_DRIVER_SPI_H_
#define MCAL_SPI_DRIVER_SPI_H_

/* user defined data types*/
#include "../GPIO_Driver/macros/std_types.h"

/* SPI default value */
#define SPI_DEFAULT_VALUE 0xFF

/* Function Prototypes */

/* SPI master initialization */
void SPI_initMaster(void);

/* SPI slave initialization */
void SPI_initSlave(void);

/*
 * SPI function send and receive data at the same time
 */
uint8 SPI_sendReceive(uint8 data);

/*
 * send String to another device using SPI
 */
void SPI_sendString(const uint8 *str);

/*
 * Receive String from another device using SPI
 */
void SPI_ReceiveString(uint8 *str);

#endif /* MCAL_SPI_DRIVER_SPI_H_ */
