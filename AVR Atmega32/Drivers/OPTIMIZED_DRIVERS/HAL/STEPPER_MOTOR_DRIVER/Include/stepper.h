/*
 *      Author: Mohamed Newir
 *      Created on: Aug 31, 2025
 *      File name: stepper.h
 *      Description:
 *                  uni-polar stepper motor driver implementation
 *      Note: it should be 4 consecutive bits to work right with our mask
 */


#ifndef HAL_STEPPER_MOTOR_DRIVER_INCLUDE_STEPPER_H_
#define HAL_STEPPER_MOTOR_DRIVER_INCLUDE_STEPPER_H_

#include "../../../MCAL/Macros/std_types.h"

#define MAX_STEPS_PER_REV 200
#define STEP_ANGLE 1.8

/* stepper motor state declaration */
typedef enum{
	STEPPER_CW, STEPPER_CCW, STEPPER_STOP
}STEPPER_STATE;

/* stepper motor mode declaration */
typedef enum{
	FULL_STEP = 4, HALF_STEP = 8
}STEPPER_MODE;

/* stepper motor data type declaration */
typedef struct{
	uint8 portNum;
	uint8 mask;
	uint16 delay; /* best practice to be 100 mills */
	STEPPER_MODE mode;
	bool ULN2003A_used; /* in case we use ULN2003 chip */
}Stepper_t;

/* initialize stepper motor pins */
void STEPPER_init(const Stepper_t* stepper);

/* stepper motor start action in steps  */
void STEPPER_move_steps(const Stepper_t* stepper, STEPPER_STATE state, uint16 steps);

/* stepper motor start action in degrees */
void STEPPER_move_angle(const Stepper_t* stepper, STEPPER_STATE state, uint16 degree);


#endif /* HAL_STEPPER_MOTOR_DRIVER_INCLUDE_STEPPER_H_ */
