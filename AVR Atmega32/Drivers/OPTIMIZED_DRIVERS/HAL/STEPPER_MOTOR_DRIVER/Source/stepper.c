/*
 *      Author: Mohamed Newir
 *      Created on: Aug 31, 2025
 *      File name: stepper.c
 *      Description:
 *                  uni-polar stepper motor driver implementation
 */

#include "../../../MCAL/GPIO/Include/gpio.h"
#include "../Include/stepper.h"
#include <util/delay.h>

static uint8 STEPPER_fullStepSequence[4] = {12, 6, 3, 9};
static uint8 STEPPER_halfStepSequence[8] = {12, 4, 6, 2, 3, 1, 9, 8};

/* initialize stepper motor pins */
void STEPPER_init(const Stepper_t* stepper){
	GPIO_setupPortDirectionMasked(stepper -> portNum, stepper -> mask, stepper -> mask);
	/* ensure stepper is stopped */
	if(stepper -> ULN2003A_used == False){
		GPIO_writePortMasked(stepper -> portNum, 0x00, stepper -> mask);
	}
	else{
		GPIO_writePortMasked(stepper -> portNum, stepper -> mask, stepper -> mask);
	}
}

/* stepper motor start action  */
void STEPPER_move_steps(const Stepper_t* stepper, STEPPER_STATE state, uint16 steps){
	uint8 i;
	sint8 j; /* signed to prevent over flow in case < 0 */
	switch(stepper -> mode){
	case FULL_STEP:
		if(state == STEPPER_CW){
			for(i = 0; i < steps; i++){
				for(j = 0; j < FULL_STEP; j++){
					if(stepper -> ULN2003A_used == False){
						GPIO_writePortMasked(stepper -> portNum, STEPPER_fullStepSequence[j], stepper -> mask);
					}
					else{
						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_fullStepSequence[j], stepper -> mask);
					}
					_delay_ms(stepper -> delay);
				}
			}
		}
		else if(state == STEPPER_CCW){
			for(i = 0; i < steps; i++){
				for(j = FULL_STEP - 1; j >= 0; j--){
					if(stepper -> ULN2003A_used == False){
						GPIO_writePortMasked(stepper -> portNum, STEPPER_fullStepSequence[j], stepper -> mask);
					}
					else{
						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_fullStepSequence[j], stepper -> mask);
					}
					_delay_ms(stepper -> delay);
				}
			}
		}
		break;

	case HALF_STEP:
		if(state == STEPPER_CW){
			for(i = 0; i < steps; i++){
				for(j = 0; j < HALF_STEP; j++){
					if(stepper -> ULN2003A_used == False){
						GPIO_writePortMasked(stepper -> portNum, STEPPER_halfStepSequence[j], stepper -> mask);
					}
					else{
						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_halfStepSequence[j], stepper -> mask);
					}
					_delay_ms(stepper -> delay);
				}
			}
		}
		else if(state == STEPPER_CCW){
			for(i = 0; i < steps; i++){
				for(j = HALF_STEP - 1; j >= 0; j--){
					if(stepper -> ULN2003A_used == False){
						GPIO_writePortMasked(stepper -> portNum, STEPPER_halfStepSequence[j], stepper -> mask);
					}
					else{
						GPIO_writePortMasked(stepper -> portNum, ~STEPPER_halfStepSequence[j], stepper -> mask);
					}
					_delay_ms(stepper -> delay);
				}
			}
		}
		break;
	}
}

/* stepper motor start action in degrees */
void STEPPER_move_angle(const Stepper_t* stepper, STEPPER_STATE state, uint16 degree){

	uint16 steps;
	if(stepper -> mode == FULL_STEP){
		steps = (degree / 360.0) * (MAX_STEPS_PER_REV);
	}
	else if(stepper -> mode == HALF_STEP){
		/* *2 to double resolution from 200 to 400 */
		steps = (degree / 360.0) * (MAX_STEPS_PER_REV * 2);
	}
	STEPPER_move_steps(stepper, state, steps);
}
