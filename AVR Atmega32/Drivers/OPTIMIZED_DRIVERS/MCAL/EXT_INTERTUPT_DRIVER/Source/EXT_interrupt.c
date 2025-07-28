/*
 *      Author: Mohamed Newir
 *      Created on: Jul 26, 2025
 *      File name: EXT_interrupt.c
 *      Description:
 *      			Function implementation to handle AVR ATmega32 Interrupts
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../GPIO/Include/gpio.h"
#include "../../Macros/macros.h"
#include "../Include/EXT_interrupt.h"

/* pointer to function callback for external interrupts */
void (*EXT_int0_cb)(void) = NULL_PTR;
void (*EXT_int1_cb)(void) = NULL_PTR;
void (*EXT_int2_cb)(void) = NULL_PTR;

/* Enable/Disable GIE bit in SREG register */
void EXT_interrupt_GIE_state(INT_STATE state){
	state == DISABLE? CLEAR_BIT(SREG, SREG_I) : SET_BIT(SREG, SREG_I);
}

/* initialize interrupt 0 */
void EXT_INT0_init(INT_STATE state, INT_CONTROL ctrl){

	//GPIO_setupPinDirection(PORTD_ID, PIN2_ID, PIN_INPUT);

	switch(ctrl){

	case LOW_LEVEL:
		CLEAR_BIT(MCUCR, ISC01);
		CLEAR_BIT(MCUCR, ISC00);
		break;

	case ANY_CHANGE:
		CLEAR_BIT(MCUCR, ISC01);
		SET_BIT(MCUCR, ISC00);
		break;

	case FALLING_EDGE:
		SET_BIT(MCUCR, ISC01);
		CLEAR_BIT(MCUCR, ISC00);
		break;

	case RISING_EDGE:
		SET_BIT(MCUCR, ISC01);
		SET_BIT(MCUCR, ISC00);
		break;
	}

	switch(state){

	case DISABLE:
		CLEAR_BIT(GICR, INT0);
		break;

	case ENABLE:
		SET_BIT(GICR, INT0);
		break;
	}

	EXT_interrupt_GIE_state(ENABLE);
}

/* initialize interrupt 1 */
void EXT_INT1_init(INT_STATE state, INT_CONTROL ctrl){

	//GPIO_setupPinDirection(PORTD_ID, PIN3_ID, PIN_INPUT);

	switch(ctrl){

	case LOW_LEVEL:
		CLEAR_BIT(MCUCR, ISC11);
		CLEAR_BIT(MCUCR, ISC10);
		break;

	case ANY_CHANGE:
		CLEAR_BIT(MCUCR, ISC11);
		SET_BIT(MCUCR, ISC10);
		break;

	case FALLING_EDGE:
		SET_BIT(MCUCR, ISC11);
		CLEAR_BIT(MCUCR, ISC10);
		break;

	case RISING_EDGE:
		SET_BIT(MCUCR, ISC11);
		SET_BIT(MCUCR, ISC10);
		break;
	}

	switch(state){

	case DISABLE:
		CLEAR_BIT(GICR, INT1);
		break;

	case ENABLE:
		SET_BIT(GICR, INT1);
		break;
	}

	EXT_interrupt_GIE_state(ENABLE);
}

/* initialize interrupt 2 */
void EXT_INT2_init(INT_STATE state, INT_CONTROL ctrl){

	//GPIO_setupPinDirection(PORTB_ID, PIN2_ID, PIN_INPUT);

	switch(ctrl){

	case FALLING_EDGE:
		CLEAR_BIT(MCUCSR, ISC2);
		break;

	case RISING_EDGE:
		SET_BIT(MCUCSR, ISC2);
		break;
	}

	switch(state){

	case DISABLE:
		CLEAR_BIT(GICR, INT2);
		break;

	case ENABLE:
		SET_BIT(GICR, INT2);
		break;
	}

	EXT_interrupt_GIE_state(ENABLE);
}

/* function set callback function to call in interrup0 ISR  */
void EXT_int0_set_cb( void (*cb)(void) ){
	if(cb != NULL_PTR) EXT_int0_cb = cb;
}

/* function set callback function to call in interrup1 ISR  */
void EXT_int1_set_cb( void (*cb)(void) ){
	if(cb != NULL_PTR) EXT_int1_cb = cb;
}

/* function set callback function to call in interrup2 ISR  */
void EXT_int2_set_cb( void (*cb)(void) ){
	if(cb != NULL_PTR) EXT_int2_cb = cb;
}

/* ISR for external interrupts  */
ISR(INT0_vect){

#if(ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	EXT_int0_cb();
}

ISR(INT1_vect){

#if(ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	EXT_int1_cb();
}

ISR(INT2_vect){

#if(ALLOW_NESTING_INTERRUPT == True)
	EXT_interrupt_GIE_state(ENABLE);
#endif

	EXT_int2_cb();
}



