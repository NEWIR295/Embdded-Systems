/*
 * 		File Name: motor.h
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: Motor Driver Header file
 */

#ifndef MOTOR_H_
#define MOTOR_H_

/* user defined data types library */
#include "../macros/std_types.h"

/* motor driver pin/port ID */
#define MOTOR_DRIVER_PORT_ID PORTB_ID
#define IN1_PIN PIN0_ID
#define IN2_PIN PIN1_ID

/* defined enum data type for motor state */
typedef enum {CW,CCW,STOP} motorState;

/*
 * Initializes the DC motor by setting the direction for the motor pins and stopping the
 * motor at the beginning.
 */
void DcMotor_Init(void);

/*
 * Controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
 * on the input duty cycle.
 */
void DcMotor_Rotate(motorState state, uint8 speed);

#endif /* MOTOR_H_ */
