/*
 *      Author: Mohamed Newir
 *      Created on: Aug 31, 2025
 *      File name: motorDriver.h
 *      Description:
 *      		L298/L293 motor driver declaration
 */


#ifndef HAL_DC_MOTOR_DRIVER_INCLUDE_MOTORDRIVER_H_
#define HAL_DC_MOTOR_DRIVER_INCLUDE_MOTORDRIVER_H_

#include "../../../MCAL/Macros/std_types.h"
#include "../../../MCAL/Timers_Driver/Include/Timers_config.h"

#define TIMER1_TOP 2499 /* 2499 -> in case 8mhz and pre-scaler = 64 */

/* timer used declaration */
typedef enum{
	TIMER0, TIMER1A, TIMER1B, TIMER2
}TIMER_NUM;

/* timer used declaration */
typedef enum{
	CW, CCW, STOP, BRAKE
}MOTOR_STATE;

/* motor driver data type declaration */
typedef struct{
	uint8 portNum;
	uint8 IN1_pinNum;
	uint8 IN2_pinNum;
	CLOCK_SELECT motor_prescaler;
	TIMER_NUM timer;
}MotorDriver_t;

/* Initialize motor pins in case timer 0/2 */
void MOTOR_DRIVER_init02(const MotorDriver_t* motor);

/* Initialize motor pins in case timer 1 */
void MOTOR_DRIVER_init1(const MotorDriver_t* motor1, const MotorDriver_t* motor2);

/* motors take speed as percentage from 0% -> 100% */
/* set motor speed */
void MOTOR_DRIVER_setSpeed(const MotorDriver_t* motor, MOTOR_STATE state, uint8 speed);

#endif /* HAL_DC_MOTOR_DRIVER_INCLUDE_MOTORDRIVER_H_ */
