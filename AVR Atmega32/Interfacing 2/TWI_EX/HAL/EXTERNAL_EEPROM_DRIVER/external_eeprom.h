/*
 * 		File Name: external_eeprom.h
 *
 *  	Created on: Oct 30, 2024
 *      Author: Mohamed Newir
 *      File Description: External EEPROM Header File
 */

#ifndef HAL_EXTERNAL_EEPROM_DRIVER_EXTERNAL_EEPROM_H_
#define HAL_EXTERNAL_EEPROM_DRIVER_EXTERNAL_EEPROM_H_

/* user defined data types library*/
#include "../../MCAL/GPIO_Driver/macros/std_types.h"

/* constant definitions */
#define ERROR   0
#define SUCCESS 1

/* Function Prototypes */

/* function write one 1 byte in specified address in EEPROM using TWI */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);

/* function read one 1 byte in specified address in EEPROM using TWI */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);



#endif /* HAL_EXTERNAL_EEPROM_DRIVER_EXTERNAL_EEPROM_H_ */
