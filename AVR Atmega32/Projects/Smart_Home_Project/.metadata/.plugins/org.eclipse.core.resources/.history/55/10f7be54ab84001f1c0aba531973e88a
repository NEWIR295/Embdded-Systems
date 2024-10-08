/*
 * 		File Name: flame.h
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: Flame Sensor Driver Header File
 */

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

/* user defined data types library */
#include "../macros/std_types.h"

#define FIRE_DETECTED 0

/* Flame Sensor Port/Pin ID */
#define FLAME_SENSOR_PORT_ID PORTD_ID
#define FLAME_SENSOR_PIN_ID PIN2_ID

/* Function Prototypes*/

/*
 * Initializes the flame sensor pin direction.
 */
void FlameSensor_init(void);

/*
 * Reads the value from the flame sensor and returns it.
 */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
