/*
 * 		File Name: motor.c
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: Motor Driver Source file
 */
/* used libraries */
#include "../GPIO/gpio.h"
#include "../PWM_DRIVER/pwm.h"
#include "motor.h"
/*
 * Initializes the DC motor by setting the direction for the motor pins and stopping the
 * motor at the beginning.
 */
void DcMotor_Init(void){

	/* Set IN1/2 as Output Pins*/
	GPIO_setupPinDirection(MOTOR_DRIVER_PORT_ID,IN1_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_DRIVER_PORT_ID,IN2_PIN,PIN_OUTPUT);

	/* Stop motor at Start */
	GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN1_PIN,LOW);
	GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN2_PIN,LOW);

}

/*
 * Controls the motor's state (Clockwise/Anti-Clockwise/Stop) and adjusts the speed based
 * on the input duty cycle.
 */
void DcMotor_Rotate(motorState state, uint8 speed){

	uint8 pwm = (uint8) (( (uint32) speed * 255) / 100);
	switch(state){
	case CW:
		GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN1_PIN,HIGH);
		GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN2_PIN,LOW);
		PWM_Timer0_Start(pwm);
		break;
	case CCW:
		GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN1_PIN,LOW);
		GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN2_PIN,HIGH);
		PWM_Timer0_Start(pwm);
		break;
	case STOP:
		GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN1_PIN,LOW);
		GPIO_writePin(MOTOR_DRIVER_PORT_ID,IN2_PIN,LOW);
		PWM_Timer0_Start(0);
		break;
	}

}
