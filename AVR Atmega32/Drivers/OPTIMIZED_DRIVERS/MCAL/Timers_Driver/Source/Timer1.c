/*
 *      Author: Mohamed Newir
 *      Created on: Aug 5, 2025
 *      File name: Timer1.c
 *      Description:
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../GPIO/Include/gpio.h"
#include "../../Macros/macros.h"
#include "../../EXT_INTERTUPT_DRIVER/Include/EXT_interrupt.h"
#include "../Include/Timer1.h"
/* pointer to function callback for OF interrupt */
void (*TIMER1_OF_cb)(void) = NULL_PTR;

/* pointer to function callback for CTC interrupt */
void (*TIMER1_CTC_cb_A)(void) = NULL_PTR;
void (*TIMER1_CTC_cb_B)(void) = NULL_PTR;

/* select TIMER1 clock static function prototype */
static void TIMER1_clockSelect(CLOCK_SELECT clock);

/* initialize TIMER1 overflow mode with specific characteristics */
void TIMER1_OF_init(CLOCK_SELECT clock){

	TCNT1 = TIMER1_PRELOAD;

	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);

	/* choose OF mode */
	CLEAR_BIT(TCCR1A, WGM10);
	CLEAR_BIT(TCCR1A, WGM11);
	CLEAR_BIT(TCCR1B, WGM12);
	CLEAR_BIT(TCCR1B, WGM13);

	TIMER1_clockSelect(clock);

#if (TIMER1_OF_INTERRUPT_ENABLE == True)
	SET_BIT(TIMSK, TOIE1);
	EXT_interrupt_GIE_state(ENABLE);
#else
	/* in case interrupt isn't enabled we will work with pooling */
	while(! ( TIFR & ( 1<<TOV1 ) ));
	TIFR |= ( 1<<TOV1 );
	TCCR1A = 0;
	TCCR1B = 0;
#endif

}

/* initialize TIMER1 CTC mode with specific characteristics */
void TIMER1_CTC_init(TIMER1_CTC_MODE_SELECT ctc_OC1A, TIMER1_CTC_MODE_SELECT ctc_OC1B,
		CLOCK_SELECT clock, uint16 compValueA, uint16 compValueB){
	TCNT1 = 0;
	OCR1A = compValueA; /* compare value */
	OCR1B = compValueB; /* compare value */
	SET_BIT(TCCR1A, FOC1A);
	SET_BIT(TCCR1A, FOC1B);

	/* choose CTC mode */
	CLEAR_BIT(TCCR1A, WGM10);
	CLEAR_BIT(TCCR1A, WGM11);
	SET_BIT(TCCR1B, WGM12);
	CLEAR_BIT(TCCR1B, WGM13);

	switch(ctc_OC1A){
	case OC1_CTC_NORMAL:
		CLEAR_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		break;

	case TOGGLE_OC1:
		CLEAR_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOW);
		break;

	case CLEAR_OC1:
		SET_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOW);
		break;

	case SET_OC1:
		SET_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOW);
		break;
	}

	switch(ctc_OC1B){
	case OC1_CTC_NORMAL:
		CLEAR_BIT(TCCR1A, COM1B1);
		CLEAR_BIT(TCCR1A, COM1B0);
		break;

	case TOGGLE_OC1:
		CLEAR_BIT(TCCR1A, COM1B1);
		SET_BIT(TCCR1A, COM1B0);
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOW);
		break;

	case CLEAR_OC1:
		SET_BIT(TCCR1A, COM1B1);
		CLEAR_BIT(TCCR1A, COM1B0);
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOW);
		break;

	case SET_OC1:
		SET_BIT(TCCR1A, COM1B1);
		SET_BIT(TCCR1A, COM1B0);
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOW);
		break;
	}

	TIMER1_clockSelect(clock);

#if (TIMER1_CTC_INTERRUPT_ENABLE_A == True)
	SET_BIT(TIMSK, OCIE1A);
	EXT_interrupt_GIE_state(ENABLE);
#endif

#if (TIMER1_CTC_INTERRUPT_ENABLE_B == True)
	SET_BIT(TIMSK, OCIE1B);
	EXT_interrupt_GIE_state(ENABLE);
#endif

}

uint8 TIMER1_CTC_poll_A(void) {
	if (TIFR & (1<<OCF1A)) {
		TIFR |= (1<<OCF1A);
		if (TIMER1_CTC_cb_A != NULL_PTR) TIMER1_CTC_cb_A();
		return True;
	}
	return False;
}

uint8 TIMER1_CTC_poll_B(void) {
	if (TIFR & (1<<OCF1B)) {
		TIFR |= (1<<OCF1B);
		if (TIMER1_CTC_cb_B != NULL_PTR) TIMER1_CTC_cb_B();
		return True;
	}
	return False;
}

/* initialize TIMER1 PWM mode with specific characteristics */
void TIMER1_FAST_PWM_init(FAST_PWM_MODE_SELECT mode_A, FAST_PWM_MODE_SELECT mode_B,
		CLOCK_SELECT clock, uint16 top){

	TCNT1 = 0;
	OCR1A = 0; /* initialize OCR1A output with 0 */
	OCR1B = 0; /* initialize OCR1B output with 0 */

	ICR1 = top; /*
	 	 	 	 	 frequency = f_cpu/((1+top)*N)
	 */

	CLEAR_BIT(TCCR1A, FOC1A);
	CLEAR_BIT(TCCR1A, FOC1B);

	/* choose fast PWM mode */
	SET_BIT(TCCR1B, WGM13);
	SET_BIT(TCCR1B, WGM12);
	SET_BIT(TCCR1A, WGM11);
	CLEAR_BIT(TCCR1A, WGM10);

	switch(mode_A){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		break;

	case RESERVED:
		CLEAR_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOW);
		break;

	case NON_INVERTING_MODE:
		SET_BIT(TCCR1A, COM1A1);
		CLEAR_BIT(TCCR1A, COM1A0);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOW);
		break;

	case INVERTING_MODE:
		SET_BIT(TCCR1A, COM1A1);
		SET_BIT(TCCR1A, COM1A0);
		GPIO_setupPinDirection(PORTD_ID, PIN5_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN5_ID, LOW);
		break;
	}

	switch(mode_B){
	case FAST_PWM_NORMAL:
		CLEAR_BIT(TCCR1A, COM1B1);
		CLEAR_BIT(TCCR1A, COM1B0);
		break;

	case RESERVED:
		CLEAR_BIT(TCCR1A, COM1B1);
		SET_BIT(TCCR1A, COM1B0);
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOW);
		break;

	case NON_INVERTING_MODE:
		SET_BIT(TCCR1A, COM1B1);
		CLEAR_BIT(TCCR1A, COM1B0);
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOW);
		break;

	case INVERTING_MODE:
		SET_BIT(TCCR1A, COM1B1);
		SET_BIT(TCCR1A, COM1B0);
		GPIO_setupPinDirection(PORTD_ID, PIN4_ID, PIN_OUTPUT);
		GPIO_writePin(PORTD_ID, PIN4_ID, LOW);
		break;
	}

	TIMER1_clockSelect(clock);

}

/* set duty cycle with specific duty cycle value */
void TIMER1_FAST_PWM_set_dutyCycle_A(uint16 dutyCycle){
	OCR1A = dutyCycle;
}

/* set duty cycle with specific duty cycle value */
void TIMER1_FAST_PWM_set_dutyCycle_B(uint16 dutyCycle){
	OCR1B = dutyCycle;
}

void TIMER1_clockSelect(CLOCK_SELECT clock){
	switch(clock){
	case NO_CLOCK:
		CLEAR_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
		break;

	case NO_PRESCALER:
		CLEAR_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS10);
		break;

	case PRESCALER_8:
		CLEAR_BIT(TCCR1B, CS12);
		SET_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
		break;

	case PRESCALER_64:
		CLEAR_BIT(TCCR1B, CS12);
		SET_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS10);
		break;


	case PRESCALER_256:
		SET_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		CLEAR_BIT(TCCR1B, CS10);
		break;

	case PRESCALER_1024:
		SET_BIT(TCCR1B, CS12);
		CLEAR_BIT(TCCR1B, CS11);
		SET_BIT(TCCR1B, CS10);
		break;
	}
}


/* set TIMER1 callback in case of CTC interrupt */
void TIMER1_CTC_set_cb_A(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER1_CTC_cb_A = cb;
}

/* set TIMER1 callback in case of CTC interrupt */
void TIMER1_CTC_set_cb_B(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER1_CTC_cb_B = cb;
}

void TIMER1_OF_set_cb(void (*cb)(void)){
	if( cb != NULL_PTR ) TIMER1_OF_cb = cb;
}

ISR(TIMER1_COMPA_vect){

#if(TIMER1_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER1_CTC_cb_A != NULL_PTR) TIMER1_CTC_cb_A();

}

ISR(TIMER1_COMPB_vect){

#if(TIMER1_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER1_CTC_cb_B != NULL_PTR) TIMER1_CTC_cb_B();

}

ISR(TIMER1_OVF_vect){

#if(TIMER1_ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	if(TIMER1_OF_cb != NULL_PTR) TIMER1_OF_cb();
}
