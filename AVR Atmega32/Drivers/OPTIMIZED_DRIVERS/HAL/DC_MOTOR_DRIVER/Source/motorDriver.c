/*
 *      Author: Mohamed Newir
 *      Created on: Aug 31, 2025
 *      File name: motorDriver.c
 *      Description:
 *      		L298/L293 motor driver implementation
 */

#include "../Include/motorDriver.h"

#include "../../../MCAL/GPIO/Include/gpio.h"
#include "../../../MCAL/Timers_Driver/Include/Timer0.h"
#include "../../../MCAL/Timers_Driver/Include/Timer1.h"
#include "../../../MCAL/Timers_Driver/Include/Timer2.h"

/* Generalize function to initialize motor pins */
static void MOTOR_DRIVER_init(const MotorDriver_t* motor){

	GPIO_setupPinDirection(motor -> portNum, motor -> IN1_pinNum, PIN_OUTPUT);
	GPIO_setupPinDirection(motor -> portNum, motor -> IN2_pinNum, PIN_OUTPUT);

	/* ensure that motor is off at start */
	GPIO_writePin(motor -> portNum, motor -> IN1_pinNum, LOW);
	GPIO_writePin(motor -> portNum, motor -> IN2_pinNum, LOW);
}

/* Initialize motor in case timer 0/2 */
void MOTOR_DRIVER_init02(const MotorDriver_t* motor){

	MOTOR_DRIVER_init(motor);

	switch(motor -> timer){
	case TIMER0:
		TIMER0_FAST_PWM_init(NON_INVERTING_MODE, motor -> motor_prescaler);
		TIMER0_FAST_PWM_set_dutyCycle(0);
		break;

	case TIMER2:
		TIMER2_FAST_PWM_init(NON_INVERTING_MODE, motor -> motor_prescaler);
		TIMER2_FAST_PWM_set_dutyCycle(0);
		break;
	}
}

/* Initialize motor pins in case timer 1 */
void MOTOR_DRIVER_init1(const MotorDriver_t* motor1, const MotorDriver_t* motor2){

	MOTOR_DRIVER_init(motor1);
	MOTOR_DRIVER_init(motor2);

	TIMER1_FAST_PWM_init(NON_INVERTING_MODE, NON_INVERTING_MODE, PRESCALER_64, TIMER1_TOP);
	TIMER1_FAST_PWM_set_dutyCycle_A(0);
	TIMER1_FAST_PWM_set_dutyCycle_B(0);
}

/* set motor speed*/
void MOTOR_DRIVER_setSpeed(const MotorDriver_t* motor, MOTOR_STATE state, uint8 speed){

	uint16 dutyCycle = 0;

	/* range check */
	/* as range of speed is from 0 to 100 % */
	if(speed > 100) speed = 100;

	if(motor -> timer == TIMER1A || motor -> timer == TIMER1B){
		dutyCycle = ((uint16)(( (uint32) speed * TIMER1_TOP ) / 100));
	}
	else{
		dutyCycle = ((uint16)(( (uint32) speed * 255 ) / 100));
	}

	switch(motor -> timer){
	case TIMER0:
		TIMER0_FAST_PWM_set_dutyCycle((uint8)dutyCycle);
		break;

	case TIMER1A:
		TIMER1_FAST_PWM_set_dutyCycle_A(dutyCycle);
		break;

	case TIMER1B:
		TIMER1_FAST_PWM_set_dutyCycle_B(dutyCycle);
		break;

	case TIMER2:
		TIMER2_FAST_PWM_set_dutyCycle((uint8)dutyCycle);
		break;
	}

	switch(state){
	case CW:
		GPIO_writePin(motor -> portNum, motor -> IN1_pinNum, HIGH);
		GPIO_writePin(motor -> portNum, motor -> IN2_pinNum, LOW);
		break;

	case CCW:
		GPIO_writePin(motor -> portNum, motor -> IN1_pinNum, LOW);
		GPIO_writePin(motor -> portNum, motor -> IN2_pinNum, HIGH);
		break;

	case STOP:
		GPIO_writePin(motor -> portNum, motor -> IN1_pinNum, LOW);
		GPIO_writePin(motor -> portNum, motor -> IN2_pinNum, LOW);
		break;

	case BRAKE:
		GPIO_writePin(motor -> portNum, motor -> IN1_pinNum, HIGH);
		GPIO_writePin(motor -> portNum, motor -> IN2_pinNum, HIGH);
		break;
	}
}
