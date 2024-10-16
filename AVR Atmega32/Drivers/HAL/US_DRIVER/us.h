/*
 * 		File Name: us.h
 *
 * 		Created on: Oct 11, 2024
 *      Author: Mohamed Newir
 *      DEscription: Ultra-sonic Sensor Header file
 */

#ifndef HAL_US_DRIVER_US_H_
#define HAL_US_DRIVER_US_H_

/* User defined Data Types */
#include "../../MCAL/GPIO_Driver/macros/std_types.h"

/* Ultra-sonic Sensor Pin/Port ID */
#define TRIGGER_PORT_ID PORTD_ID
#define TRIGGER_PIN_ID PIN7_ID

/* Function Prototypes */

/*
 * 	Initialize the ICU driver as required.
 *	Set up the ICU callback function.
 *	Set the direction for the trigger pin as output through
 *	the GPIO driver.
 */
void Ultrasonic_init(void);

/*
 * Send the trigger pulse to the ultrasonic sensor.
 */
void Ultrasonic_Trigger(void);

/*
 * Send the trigger pulse by using the Ultrasonic_Trigger function.
 *Start the measurement process via the ICU driver.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * This is the callback function called by the ICU driver.
 * It calculates the high time (pulse time) generated by
 * the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* HAL_US_DRIVER_US_H_ */








