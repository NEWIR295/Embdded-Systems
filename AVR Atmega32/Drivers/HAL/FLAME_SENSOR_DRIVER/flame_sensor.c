/*
 * 		File Name: flame.c
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: Flame Sensor Driver Source File
 */
/* used libraries */
#include "../GPIO/gpio.h"
#include "flame_sensor.h"

/*
 * Initializes the flame sensor pin direction.
 */
void FlameSensor_init(void){

	/* set flame sensor pin direction to be output */
	GPIO_setupPinDirection(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_ID,PIN_INPUT);

}

/*
 * Reads the value from the flame sensor and returns it.
 */
uint8 FlameSensor_getValue(void){

	/* read flame sensor input */
	return GPIO_readPin(FLAME_SENSOR_PORT_ID,FLAME_SENSOR_PIN_ID);
}
