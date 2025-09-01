/*
 *      Author: Mohamed Newir
 *      Created on: Aug 5, 2025
 *      File name: Timer0.c
 *      Description:
 *                  Function implementation to handle AVR ATmega32 Timer 0
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../GPIO/Include/gpio.h"
#include "../../Macros/macros.h"
#include "../../EXT_INTERTUPT_DRIVER/Include/EXT_interrupt.h"
#include "../Include/Timer0.h"

/* pointer to function callback for OF interrupt */
void (*TIMER0_OF_cb)(void) = NULL_PTR;
void (*TIMER0_CTC_cb)(void) = NULL_PTR;

/* select timer0 clock static function prototype */
static void TIMER0_clockSelect(CLOCK_SELECT clock);

/* initialize TIMER0 overflow mode with specific characteristics */
void TIMER0_OF_init(CLOCK_SELECT clock){

	TCNT0 = TIMER0_PRELOAD;

	SET_BIT(TCCR0, FOC0);
	CLEAR_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);

	TIMER0_clockSelect(clock);

#if (TIMER0_OF_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, TOIE0);
	EXT_interrupt_GIE_state(ENABLE);
#else
	/* in case interrupt isn't enabled we will work with pooling */
	while(! ( TIFR & ( 1<<TOV0 ) ));
	TIFR |= ( 1<<TOV0 );
	TCCR0 = 0;
#endif

}

/* initialize TIMER0 CTC mode with specific characteristics */
void TIMER0_CTC_init(TIMER0_CTC_MODE_SELECT ctc, CLOCK_SELECT clock, uint8 compValue){
	TCNT0 = 0;
	OCR0 = compValue; /* compare value */
	SET_BIT(TCCR0, FOC0);
	/* choose CTC mode */
	SET_BIT(TCCR0, WGM01);
	CLEAR_BIT(TCCR0, WGM00);

	switch(ctc){
	case OC0_CTC_NORMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;

	case TOGGLE_OC0:
		CLEAR_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		break;

	case CLEAR_OC0:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		break;

	case SET_OC0:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		break;
	}

	TIMER0_clockSelect(clock);

#if (TIMER0_CTC_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, OCIE0);
	EXT_interrupt_GIE_state(ENABLE);
#else
	/* in case interrupt isn't enabled we will work with pooling */
	while(! ( TIFR & ( 1<<OCF0 ) ));
	TIFR |= ( 1<<OCF0 );
	TCCR0 = 0;
#endif

}

/* initialize TIMER0 PWM mode with specific characteristics */
void TIMER0_FAST_PWM_init(FAST_PWM_MODE_SELECT mode, CLOCK_SELECT clock){
	TCNT0 = 0;
	OCR0 = 0; /* initialize OCRO output with 0 */
	CLEAR_BIT(TCCR0, FOC0);
	/* choose CTC mode */
	SET_BIT(TCCR0, WGM01);
	SET_BIT(TCCR0, WGM00);
	switch(mode){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		break;

	case RESERVED:
		CLEAR_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		break;

	case NON_INVERTING_MODE:
		SET_BIT(TCCR0, COM01);
		CLEAR_BIT(TCCR0, COM00);
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		break;

	case INVERTING_MODE:
		SET_BIT(TCCR0, COM01);
		SET_BIT(TCCR0, COM00);
		GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
		break;
	}

	TIMER0_clockSelect(clock);

}

/* set duty cycle with specific duty cycle value */
void TIMER0_FAST_PWM_set_dutyCycle(uint8 dutyCycle){
	OCR0 = dutyCycle;
}

void TIMER0_clockSelect(CLOCK_SELECT clock){
	switch(clock){
	case NO_CLOCK:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case NO_PRESCALER:
		CLEAR_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;

	case PRESCALER_8:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case PRESCALER_64:
		CLEAR_BIT(TCCR0, CS02);
		SET_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;


	case PRESCALER_256:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		CLEAR_BIT(TCCR0, CS00);
		break;

	case PRESCALER_1024:
		SET_BIT(TCCR0, CS02);
		CLEAR_BIT(TCCR0, CS01);
		SET_BIT(TCCR0, CS00);
		break;
	}
}

/* set timer0 callback in case of overflow interrupt */
void TIMER0_OF_set_cb(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER0_OF_cb = cb;
}

/* set timer0 callback in case of CTC interrupt */
void TIMER0_CTC_set_cb(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER0_CTC_cb = cb;
}

ISR(TIMER0_COMP_vect){

#if(TIMER0_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER0_CTC_cb != NULL_PTR) TIMER0_CTC_cb();

}

ISR(TIMER0_OVF_vect){

#if(TIMER0_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER0_OF_cb != NULL_PTR) TIMER0_OF_cb();
}
