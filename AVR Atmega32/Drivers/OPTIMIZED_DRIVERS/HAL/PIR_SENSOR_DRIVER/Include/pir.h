/*
 *      Author: Mohamed Newir
 *      Created on: Jul 27, 2025
 *      File name: pir.h
 *      Description:
 *      			PIR sensor driver declaration
 */


#ifndef HAL_PIR_SENSOR_DRIVER_INCLUDE_PIR_H_
#define HAL_PIR_SENSOR_DRIVER_INCLUDE_PIR_H_

/* user defined data types library */
#include "../../../MCAL/Macros/std_types.h"

/* PIR data type declaration */
typedef struct{
	uint8 portNum;
	uint8 pinNum;
}PIR_t;

/* function initialize PIR sensor */
void PIR_init(const PIR_t* pir);

/* function read PIR sensor state */
uint8 PIR_state(const PIR_t* pir);

#endif /* HAL_PIR_SENSOR_DRIVER_INCLUDE_PIR_H_ */
