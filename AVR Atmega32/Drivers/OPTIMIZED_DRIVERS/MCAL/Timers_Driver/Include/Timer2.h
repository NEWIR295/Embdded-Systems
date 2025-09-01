/*
 *      Author: Mohamed Newir
 *      Created on: Aug 5, 2025
 *      File name: Timer2.h
 *      Description:
 */


#ifndef MCAL_TIMERS_DRIVER_INCLUDE_TIMER2_H_
#define MCAL_TIMERS_DRIVER_INCLUDE_TIMER2_H_


#include "../../Macros/std_types.h"
#include "Timers_config.h"

#define TIMER2_CTC_INTERRUPT_ENABLE True
#define TIMER2_OF_INTERRUPT_ENABLE True
#define TIMER2_ALLOW_NESTING_INTERRUPT False

#define TIMER2_PRELOAD 0


/* CTC MODE SELECT */
typedef enum{
	OC2_CTC_NORMAL, /* OCO disconnected */
	TOGGLE_OC2, CLEAR_OC2, SET_OC2
}TIMER2_CTC_MODE_SELECT;


/* initialize TIMER2 overflow mode with specific characteristics */
void TIMER2_OF_init(CLOCK_SELECT clock);

/* initialize TIMER2 CTC mode with specific characteristics */
void TIMER2_CTC_init(TIMER2_CTC_MODE_SELECT ctc, CLOCK_SELECT clock, uint8 compValue);

/* initialize TIMER2 PWM mode with specific characteristics */
void TIMER2_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, CLOCK_SELECT clock);

/* set duty cycle with specific duty cycle value */
void TIMER2_FAST_PWM_set_dutyCycle(uint8 dutyCycle);

/* set TIMER2 callback in case of overflow interrupt */
void TIMER2_OF_set_cb(void (*cb)(void));

/* set TIMER2 callback in case of CTC interrupt */
void TIMER2_CTC_set_cb(void (*cb)(void));



#endif /* MCAL_TIMERS_DRIVER_INCLUDE_TIMER2_H_ */
