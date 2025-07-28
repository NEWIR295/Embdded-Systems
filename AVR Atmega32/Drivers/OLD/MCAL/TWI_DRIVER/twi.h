/*
 * 		File Name: twi.h
 *
 *  	Created on: Oct 29, 2024
 *      Author: Mohamed Newir
 *      Description: Two Wire Interface Driver Header File
 */

#ifndef MCAL_TWI_DRIVER_TWI_H_
#define MCAL_TWI_DRIVER_TWI_H_

/* user defined data types*/
#include "../GPIO_Driver/macros/std_types.h"

/* Constant Definitions */
#define TWI_START			0x08 /* confirm start is sent*/
#define TWI_REP_START		0x10 /* confirm repeated start is sent */
#define TWI_MT_SLA_W_ACK	0x18 /* confirm master sent salve address and in write mode */
#define TWI_MT_SLA_R_ACK 	0x40 /* confirm master sent salve address and in read mode */
#define TWI_MT_DATA_ACK     0x28 /* confirm master sent Data and acknowledgment received from slave  */
#define TWI_MR_DATA_ACK		0x50 /* confirm master receive Data and acknowledgment sent by slave */
#define TWI_MR_DATA_NACK 	0x58 /* confirm master sent Data and no acknowledgment sent by slave */

/* Function Prototypes */

/* function initialize I2C in master */
void TWI_init(void);

/* function sent start bit */
void TWI_start(void);

/* function sent stop bit */
void TWI_stop(void);

/* function write byte */
void TWI_writeByte(uint8 data);

/* function read byte with acknowledgment */
uint8 TWI_readByteWithACK(void);

/* function read byte with no acknowledgment */
uint8 TWI_readByteWithNACK(void);

/* function get I2C status */
uint8 TWI_getStatus(void);

#endif /* MCAL_TWI_DRIVER_TWI_H_ */
