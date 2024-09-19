/*
 * interrupts.c
 *
 *  Created on: Sep 19, 2024
 *      Author: Mohamed Newir
 */
#include "interrupts.h"


volatile unsigned int milliseconds = ZERO;
volatile unsigned char seconds = ZERO;
volatile unsigned char minutes = ZERO;
volatile unsigned char hours = ZERO;

volatile unsigned char interrupt0flag = ONE; /* reset flag */
volatile unsigned char resumePauseFlag = ONE; /* pause/resume flag*/
volatile unsigned char countUP_DOWN = ONE; /* count up/down flag*/

/* to activate chosen 7 segment */
unsigned char activate7segment = ZERO;

/*increment function*/
void increment (void){
	/*stop buzzer*/
	PORTD &=~ (ONE<<PD0);
	seconds++;
	if(seconds > MAX_SECONDS)
	{
		minutes++;
		seconds = ZERO;
		if(minutes > MAX_MINUTES)
		{
			hours++;
			minutes = ZERO;
			if(hours > MAX_HOURS)
			{
				hours = ZERO;
			}
		}
	}
}
/*decrement function*/
void decrement(void){
	/*in case of count down  countUP_DOWN = 0*/
	if(seconds == ZERO){
		if(minutes == ZERO){
			if(hours == ZERO){
				/*run buzzer*/
				PORTD |= (ONE<<PD0);
			}
			else{
				hours--;
				minutes = MAX_MINUTES;
				seconds = MAX_SECONDS;
			}
		}
		else{
			minutes--;
			seconds = MAX_SECONDS;
		}
	}
	else{
		seconds--;
	}

}
/* ISR FUNCTIONS */

/* timer1 compare mode ISR */
ISR(TIMER1_COMPA_vect){
	/* continuous display of timer data on 7 segment */
	multi7sergment(time[activate7segment],activate7segment);
	activate7segment++;
	if (SEVEN_SEGMENT_NUMBERS == activate7segment){
		activate7segment = ZERO;
	}
	/*in case of timer not paused */
	if(resumePauseFlag){
		/* update stop watch every 1 s*/
		milliseconds++;

		if(milliseconds >= MAX_MILLIS)
		{
			milliseconds = ZERO;
			/*in case of count up  countUP_DOWN = 1*/
			if(countUP_DOWN){
				increment();
			}
			else{
				decrement();
			}
		}
	}
}
/* INT0 ISR */
ISR(INT0_vect){
	/* force stop watch reset */
	interrupt0flag = ZERO;
}

/* INT1 ISR */
ISR(INT1_vect){
	/* force stop watch to pause */
	resumePauseFlag = ZERO;
}

/* INT2 ISR */
ISR(INT2_vect){
	/* force stop watch to resume */
	resumePauseFlag = ONE;
}

/*timer 1 Compare mode initialization*/
void timer1init(void){
	/*
	 * WGM12 to enable CTC
	 * CS11 & CS10 to choose pre-scaler = 64
	 */
	TCCR1B = (ONE<<WGM12) | (ONE<<CS11) | (ONE<<CS10);
	//TCNT1 = 0;
	/*  compare every 250 tick / every 1 ms */
	OCR1A = TIMER_COMPARE_VALUE;
	/*enable timer 1 */
	TIMSK |= (ONE<<OCIE1A) ;
}

/* int 0 init */
void int0_init(void){
	/* int 0 work with falling edge*/
	MCUCR |= (ONE<<ISC01);
	/* int 0 enable */
	GICR |= (ONE<<INT0);
}

/* int 1 init */
void int1_init(void){
	/* int 1  work with  rising edge */
	MCUCR |= (ONE<<ISC11) | (ONE<<ISC10);
	/* int 1 enable */
	GICR |=(ONE<<INT1);
}

/* int 2 init */
void int2_init(void){
	/* int 2 work with falling edge */
	MCUCSR &=~(ONE<<ISC2);
	/* int 2 enable */
	GICR |= (ONE<<INT2);
}

/*  interrupt initialization */
void interrupt_init(void){
	SREG |= (ONE<<SEVEN);
	timer1init();
	int1_init();
	int0_init();
	int2_init();
}
