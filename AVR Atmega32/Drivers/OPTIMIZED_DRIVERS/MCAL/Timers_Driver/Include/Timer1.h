/*
 *      Author: Mohamed Newir
 *      Created on: Aug 5, 2025
 *      File name: Timer1.h
 *      Description:
 */


#ifndef MCAL_TIMERS_DRIVER_INCLUDE_TIMER1_H_
#define MCAL_TIMERS_DRIVER_INCLUDE_TIMER1_H_

#include "../../Macros/std_types.h"
#include "Timers_config.h"
#define TIMER1_CTC_INTERRUPT_ENABLE_A True
#define TIMER1_CTC_INTERRUPT_ENABLE_B True
#define TIMER1_ALLOW_NESTING_INTERRUPT False
#define TIMER1_OF_INTERRUPT_ENABLE True

#define TIMER1_PRELOAD 0

/* CTC MODE SELECT */
typedef enum{
	OC1_CTC_NORMAL, /* OCO disconnected */
	TOGGLE_OC1, CLEAR_OC1, SET_OC1
}TIMER1_CTC_MODE_SELECT;

/* initialize TIMER1 overflow mode with specific characteristics */
void TIMER1_OF_init(CLOCK_SELECT clock);

/* initialize TIMER1 CTC mode with specific characteristics */
void TIMER1_CTC_init(TIMER1_CTC_MODE_SELECT ctc_OC1A, TIMER1_CTC_MODE_SELECT ctc_OC1B,
		CLOCK_SELECT clock, uint16 compValueA, uint16 compValueB);

/* initialize TIMER1 PWM mode with specific characteristics */
void TIMER1_FAST_PWM_init(FAST_PWM_MODE_SELECT mode_A, FAST_PWM_MODE_SELECT mode_B,
		CLOCK_SELECT clock, uint16 top);
/* set duty cycle with specific duty cycle value */
void TIMER1_FAST_PWM_set_dutyCycle_A(uint16 dutyCycle);
void TIMER1_FAST_PWM_set_dutyCycle_B(uint16 dutyCycle);

/* set TIMER1 callback in case of CTC interrupt */
void TIMER1_CTC_set_cb_A(void (*cb)(void));
void TIMER1_CTC_set_cb_B(void (*cb)(void));

/* For polling case */
uint8 TIMER1_CTC_poll_A(void);
uint8 TIMER1_CTC_poll_B(void);

/* set TIMER1 callback in case of OF interrupt */
void TIMER1_OF_set_cb(void (*cb)(void));

#endif /* MCAL_TIMERS_DRIVER_INCLUDE_TIMER1_H_ */
