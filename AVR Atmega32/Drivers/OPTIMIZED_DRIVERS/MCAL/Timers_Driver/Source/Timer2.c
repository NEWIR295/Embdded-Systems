/*
 *      Author: Mohamed Newir
 *      Created on: Aug 5, 2025
 *      File name: Timer2.c
 *      Description:
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../GPIO/Include/gpio.h"
#include "../../Macros/macros.h"
#include "../../EXT_INTERTUPT_DRIVER/Include/EXT_interrupt.h"
#include "../Include/Timer2.h"

/* pointer to function callback for OF interrupt */
void (*TIMER2_OF_cb)(void) = NULL_PTR;
void (*TIMER2_CTC_cb)(void) = NULL_PTR;

/* select TIMER2 clock static function prototype */
static void TIMER2_clockSelect(CLOCK_SELECT clock);

/* initialize TIMER2 overflow mode with specific characteristics */
void TIMER2_OF_init(CLOCK_SELECT clock){

	TCNT2 = TIMER2_PRELOAD;

	SET_BIT(TCCR2, FOC2);
	CLEAR_BIT(TCCR2, WGM21);
	CLEAR_BIT(TCCR2, WGM20);

	TIMER2_clockSelect(clock);

#if (TIMER2_OF_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, TOIE2);
	EXT_interrupt_GIE_state(ENABLE);
#else
	/* in case interrupt isn't enabled we will work with pooling */
	while(! ( TIFR & ( 1<<TOV2 ) ));
	TIFR |= ( 1<<TOV2 );
	TCCR2 = 0;
#endif

}

/* initialize TIMER2 CTC mode with specific characteristics */
void TIMER2_CTC_init(TIMER2_CTC_MODE_SELECT ctc, CLOCK_SELECT clock, uint8 compValue){
	TCNT2 = 0;
	OCR2 = compValue; /* compare value */
	SET_BIT(TCCR2, FOC2);
	/* choose CTC mode */
	SET_BIT(TCCR2, WGM21);
	CLEAR_BIT(TCCR2, WGM20);

	switch(ctc){
	case OC2_CTC_NORMAL:
		CLEAR_BIT(TCCR2, COM21);
		CLEAR_BIT(TCCR2, COM20);
		break;

	case TOGGLE_OC2:
		CLEAR_BIT(TCCR2, COM21);
		SET_BIT(TCCR2, COM20);
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		break;

	case CLEAR_OC2:
		SET_BIT(TCCR2, COM21);
		CLEAR_BIT(TCCR2, COM20);
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		break;

	case SET_OC2:
		SET_BIT(TCCR2, COM21);
		SET_BIT(TCCR2, COM20);
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		break;
	}

	TIMER2_clockSelect(clock);

#if (TIMER2_CTC_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE2);
	EXT_interrupt_GIE_state(ENABLE);
#else
	/* in case interrupt isn't enabled we will work with pooling */
	while(! ( TIFR & ( 1<<OCF2 ) ));
	TIFR |= ( 1<<OCF2 );
	TCCR2 = 0;
#endif

}

/* initialize TIMER2 PWM mode with specific characteristics */
void TIMER2_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, CLOCK_SELECT clock){
	TCNT2 = 0;
	OCR2 = 0; /* initialize OCRO output with 0 */
	CLEAR_BIT(TCCR2, FOC2);
	/* choose CTC mode */
	SET_BIT(TCCR2, WGM21);
	SET_BIT(TCCR2, WGM20);
	switch(mode){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR2, COM21);
		CLEAR_BIT(TCCR2, COM20);
		break;

	case RESERVED:
		CLEAR_BIT(TCCR2, COM21);
		SET_BIT(TCCR2, COM20);
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		break;

	case NON_INVERTING_MODE:
		SET_BIT(TCCR2, COM21);
		CLEAR_BIT(TCCR2, COM20);
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		break;

	case INVERTING_MODE:
		SET_BIT(TCCR2, COM21);
		SET_BIT(TCCR2, COM20);
		GPIO_setupPinDirection(PORTD_ID, PIN7_ID, PIN_OUTPUT);
		break;
	}

	TIMER2_clockSelect(clock);

}

/* set duty cycle with specific duty cycle value */
void TIMER2_FAST_PWM_set_dutyCycle(uint8 dutyCycle){
	OCR2 = dutyCycle;
}

void TIMER2_clockSelect(CLOCK_SELECT clock){
	switch(clock){
	case NO_CLOCK:
		CLEAR_BIT(TCCR2, CS22);
		CLEAR_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS20);
		break;

	case NO_PRESCALER:
		CLEAR_BIT(TCCR2, CS22);
		CLEAR_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS20);
		break;

	case PRESCALER_8:
		CLEAR_BIT(TCCR2, CS22);
		SET_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS20);
		break;

	case PRESCALER_32:
		CLEAR_BIT(TCCR2, CS22);
		SET_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS20);
		break;


	case PRESCALER_64:
		SET_BIT(TCCR2, CS22);
		CLEAR_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS20);
		break;

	case PRESCALER_128:
		SET_BIT(TCCR2, CS22);
		CLEAR_BIT(TCCR2, CS21);
		SET_BIT(TCCR2, CS20);
		break;

	case PRESCALER_256:
		SET_BIT(TCCR2, CS22);
		SET_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS20);
		break;

	case PRESCALER_1024:
		SET_BIT(TCCR2, CS22);
		SET_BIT(TCCR2, CS21);
		CLEAR_BIT(TCCR2, CS20);
		break;
	}
}

/* set TIMER2 callback in case of overflow interrupt */
void TIMER2_OF_set_cb(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER2_OF_cb = cb;
}

/* set TIMER2 callback in case of CTC interrupt */
void TIMER2_CTC_set_cb(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER2_CTC_cb = cb;
}

ISR(TIMER2_COMP_vect){

#if(TIMER2_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER2_CTC_cb != NULL_PTR) TIMER2_CTC_cb();

}

ISR(TIMER2_OVF_vect){

#if(TIMER2_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER2_OF_cb != NULL_PTR) TIMER2_OF_cb();
}
