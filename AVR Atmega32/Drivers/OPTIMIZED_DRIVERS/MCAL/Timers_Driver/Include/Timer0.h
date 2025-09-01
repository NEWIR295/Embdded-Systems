/*
 *      Author: Mohamed Newir
 *      Created on: Aug 5, 2025
 *      File name: Timer0.h
 *      Description:
 *                  Function declaration to handle AVR ATmega32 Timer 0
 *
 */


#ifndef MCAL_TIMERS_DRIVER_INCLUDE_TIMER0_H_
#define MCAL_TIMERS_DRIVER_INCLUDE_TIMER0_H_

#include "../../Macros/std_types.h"
#include "Timers_config.h"

#define TIMER0_CTC_INTERRUPT_ENABLE True
#define TIMER0_OF_INTERRUPT_ENABLE True
#define TIMER0_ALLOW_NESTING_INTERRUPT False

#define TIMER0_PRELOAD 0

/* CTC MODE SELECT */
typedef enum{
	OC0_CTC_NORMAL, /* OCO disconnected */
	TOGGLE_OC0, CLEAR_OC0, SET_OC0
}TIMER0_CTC_MODE_SELECT;


/* initialize TIMER0 overflow mode with specific characteristics */
void TIMER0_OF_init(CLOCK_SELECT clock);

/* initialize TIMER0 CTC mode with specific characteristics */
void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT ctc, CLOCK_SELECT clock, uint8 compValue);

/* initialize TIMER0 PWM mode with specific characteristics */
void TIMER0_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, CLOCK_SELECT clock);

/* set duty cycle with specific duty cycle value */
void TIMER0_FAST_PWM_set_dutyCycle(uint8 dutyCycle);

/* set timer0 callback in case of overflow interrupt */
void TIMER0_OF_set_cb(void (*cb)(void));

/* set timer0 callback in case of CTC interrupt */
void TIMER0_CTC_set_cb(void (*cb)(void));

#endif /* MCAL_TIMERS_DRIVER_INCLUDE_TIMER0_H_ */
