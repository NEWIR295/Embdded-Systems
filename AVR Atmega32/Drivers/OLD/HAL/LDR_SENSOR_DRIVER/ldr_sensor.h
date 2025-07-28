/*
 * 		File Name: ldr_sensor.h
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: LDR Sensor Driver Header File
 */

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_

/* user defined data type */
#include "../macros/std_types.h"
/* LDR Sensor max volt */
#define LDR_SENSOR_MAX_VOLT_VALUE 2.56
/* LDR Sensor max light intensity */
#define LDR_SENSOR_MAX_LIGHT_INTENSITY 100
/* LDR Pin ID */
#define LDR_SENSOR_CHANNEL_ID PIN0_ID

/* Function Prototype */

/* Reads the LDR sensor value and returns the light intensity. */
uint16 LDR_getLightIntensity(void);

#endif /* LDR_SENSOR_H_ */
