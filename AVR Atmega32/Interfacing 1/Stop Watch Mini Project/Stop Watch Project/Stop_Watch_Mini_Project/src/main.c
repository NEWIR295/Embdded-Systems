/*
 * main.c
 *
 *  Created on: Sep 14, 2024
 *      Author: Mohamed Newir
 *      Project Description: Stopwatch with Dual Mode (Increment and Countdown)
 *     		      Using ATmega32 and Seven-Segment Display.
 *
 */

/*system frequency*/
#define F_CPU 16000000UL

/*std libraries*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include  <util/delay.h>

/* constant definitions */
#define zero 0
#define one 1
#define five 5
#define seven 7
#define ten 10
#define  sevenSegmentNumbers 6
#define displayDelay 1
#define  depouncingDelay 10
#define maxHours 99
#define maxSeconds 59
#define maxMinutes 59
#define maxMillis 1000
#define timerCompareValue 250

/*Global variables*/
/* flags */
unsigned char interrupt0flag = one; /* reset flag */
unsigned char resumePauseFlag = one; /* pause/resume flag*/
unsigned char countUP_DOWN = one; /* count up/down flag*/

/* time variables */
unsigned int milliseconds = zero;
unsigned char seconds = zero;
unsigned char minuites = zero;
unsigned char hours = zero;

/* container contain the array of time */
unsigned int time[sevenSegmentNumbers] = {zero};

/* to activate chosen 7 segment */
unsigned char activate7segment = zero;

/*  Six multiplexed seven-segment displays initialization */
/* display timer in the 7 segment */
void multi7sergment(unsigned char currentTime,unsigned char activate7segment){
	/* write current time */
	PORTA = (PORTA & 0xC0) | ((1<<(five-activate7segment))&0x3f);
	PORTC = (PORTC & 0xf0) | (currentTime & 0x0f);
	/* diplay time in the specfic 7 segment */
	_delay_us(displayDelay);
	PORTA = (PORTA & 0xC0) | (0x00&0x3f);
}

/* ISR FUNCTIONS */

/* timer1 compare mode ISR */
ISR(TIMER1_COMPA_vect){
	/* continuous display of timer data on 7 segment */
	multi7sergment(time[activate7segment],activate7segment);
	activate7segment++;
	if (sevenSegmentNumbers == activate7segment){
		activate7segment = zero;
	}
	/*in case of timer not paused */
	if(resumePauseFlag){
		/* update stop watch every 1 s*/
		milliseconds++;
		/*in case of count up  countUP_DOWN = 1*/
		if(countUP_DOWN)
		{
			/*stop buzzer*/
			PORTD &=~ (one<<PD0);
			if(milliseconds >= maxMillis)
			{
				seconds++;
				milliseconds = zero;
				if(seconds > maxSeconds)
				{
					minuites++;
					seconds = zero;
					if(minuites > maxMinutes)
					{
						hours++;
						minuites = zero;
						if(hours > maxHours)
						{
							hours = zero;
						}
					}
				}
			}
		}
		else{
			/*in case of count down  countUP_DOWN = 0*/
			if(milliseconds >= maxMillis){
				milliseconds = zero;
				if(seconds == zero){
					if(minuites == zero){
						if(hours == zero){
							/*run buzzer*/
							PORTD |= (one<<PD0);
						}
						else{
							hours--;
							minuites = maxMinutes;
							seconds = maxSeconds;
						}
					}
					else{
						minuites--;
						seconds = maxSeconds;
					}
				}
				else{
					seconds--;
				}
			}
		}
	}
}

/* INT0 ISR */
ISR(INT0_vect){
	/* force stop watch reset */
	interrupt0flag = zero;
}

/* INT1 ISR */
ISR(INT1_vect){
	/* force stop watch to pause */
	resumePauseFlag = zero;
}

/* INT2 ISR */
ISR(INT2_vect){
	/* force stop watch to resume */
	resumePauseFlag = one;
}

/*timer 1 Compare mode initialization*/
void timer1init(void){
	/*
	 * WGM12 to enable CTC
	 * CS11 & CS10 to choose pre-scaler = 64
	 */
	TCCR1B = (one<<WGM12) | (one<<CS11) | (one<<CS10);
	//TCNT1 = 0;
	/*  compare every 250 tick / every 1 ms */
	OCR1A = timerCompareValue;
	/*enable timer 1 */
	TIMSK |= (one<<OCIE1A) ;
}

/* int 0 init */
void int0_init(void){
	/* int 0 work with falling edge*/
	MCUCR |= (one<<ISC01);
	/* int 0 enable */
	GICR |= (one<<INT0);
}

/* int 1 init */
void int1_init(void){
	/* int 1  work with  rising edge */
	MCUCR |= (one<<ISC11) | (one<<ISC10);
	/* int 1 enable */
	GICR |=(one<<INT1);
}

/* int 2 init */
void int2_init(void){
	/* int 2 work with falling edge */
	MCUCSR &=~(one<<ISC2);
	/* int 2 enable */
	GICR |= (one<<INT2);
}

/*  interrupt initialization */
void interrupt_init(void){
	SREG |= (one<<seven);
	timer1init();
	int1_init();
	int0_init();
	int2_init();
}

/*  GPIO initialization */
void GPIO_init(void){
	DDRD |= (one<<PD0) | (one<<PD4) | (one<<PD5);
	PORTD = (PORTD&0xcf) | (0x10&0x30);
	/* set pin 3  @ port d as input*/
	DDRD &=~ (one<<PD3); /* note that pd3 as external pullup */
	/* set pin 2  @ port d as input*/
	DDRD &=~ (one<<PD2);
	/* set pd2 as internal pullup*/
	PORTD |= (one<<PD2);
	/* set 1st 4 pins in portc as output for 7 segment decoder */
	DDRC = 0x0f;
	/*init 7 segment with zeros*/
	PORTC = (PORTC & 0xf0) | ( 0x00 & 0x0f);
	/*set 6 multiplixed 7 segments*/
	DDRA = 0x3f;
	/* allow 7 segment to init with zeros*/
	PORTA = 0x3f;
	/*set port b as inputs for push buttons*/
	DDRB = 0x00;
	/* activate portb for internal pullup for push buttons*/
	PORTB = 0xff;
}

/* main function*/
int main(void) {
	/* HW initialization functions*/
	GPIO_init();
	interrupt_init();
	/* local variabkes for push Buttons*/
	/* to change the state of the stop watch from counting up to down and vise-versa */
	unsigned char lastToggleButtonState = zero;
	unsigned char toggleButtonState = zero;

	/*seconds increment*/
	unsigned char lastSecIncButtonState = zero;
	unsigned char SecIncButtonState = zero;

	/*seconds decrement*/
	unsigned char lastSecDecButtonState = zero;
	unsigned char SecDecButtonState = zero;

	/*minutes increment*/
	unsigned char lastMinIncButtonState = zero;
	unsigned char MinIncButtonState = zero;

	/*minutes decrement*/
	unsigned char lastMinDecButtonState = zero;
	unsigned char MinDecButtonState = zero;

	/*hours increment*/
	unsigned char lastHoursDecButtonState = zero;
	unsigned char HoursDecButtonState = zero;

	/*hours decrement*/
	unsigned char lastHoursIncButtonState = zero;
	unsigned char HoursIncButtonState = zero;

	/* application code */
	while(1){

		/* continuous 7 segment update */
		time[0] = seconds%ten;
		time[1] = seconds/ten;
		time[2] = minuites%ten;
		time[3] = minuites/ten;
		time[4] = hours%ten;
		time[5] = hours/ten;

		/* reset interrupt */
		if(!interrupt0flag){
			/* in case of reset */
			milliseconds = zero;
			seconds = zero;
			minuites = zero;
			hours = zero;
			/* when reset start in count up mode */
			countUP_DOWN = one;
			/* in case count up open red led */
			PORTD = (PORTD&0xcf) | (0x10&0x30);
			/*stop buzzer */
			PORTD &=~ (1<<PD0);
			interrupt0flag = one;
		}

		/* in case of stop watch is set to pause */
		if(!resumePauseFlag){
			/* reset milliseconds */
			milliseconds = zero;
			/* in case pause flag is set */
			/* in case toggle button pushed */
			toggleButtonState = (PINB & (one<<PB7));
			/* in case seconds inc/dec button pushed */
			SecIncButtonState = (PINB & (one<<PB6));
			SecDecButtonState = (PINB & (one<<PB5));
			/* in case minutes inc/dec button pushed */
			MinDecButtonState = (PINB & (one<<PB3));
			MinIncButtonState = (PINB & (one<<PB4));
			/* in case hours inc/dec button pushed */
			HoursDecButtonState =(PINB & (one<<PB0)) ;
			HoursIncButtonState =(PINB & (one<<PB1)) ;

			if((toggleButtonState == zero) && (lastToggleButtonState != zero))
			{
				countUP_DOWN = !countUP_DOWN;
				if(countUP_DOWN){
					/*in case of count up  countUP_DOWN = 1*/
					/*stop buzzer */
					PORTD &=~ (one<<PD0);
					/* in case count up open red led */
					PORTD = (PORTD&0xcf) | (0x10&0x30);
				}
				else{
					/*in case of count down  countUP_DOWN = 0*/
					/* in case count down open yellow led */
					PORTD = (PORTD&0xcf) | (0x20&0x30);
				}
			}
			lastToggleButtonState = toggleButtonState;
			_delay_ms(depouncingDelay);

			/* seconds decrement*/
			if((SecDecButtonState == zero) && (lastSecDecButtonState != zero)){
				if(seconds>zero){
					seconds--;
				}
			}
			lastSecDecButtonState = SecDecButtonState;
			_delay_ms(depouncingDelay);

			/* seconds increments*/
			if((SecIncButtonState == zero) && (lastSecIncButtonState != zero)){
				seconds++;
				if(seconds >maxSeconds){
					/* reset seconds */
					minuites++;
					seconds = zero;
					if(minuites>maxMinutes){
						/* reset minutes */
						hours++;
						minuites = zero;
						if(hours>maxHours){
							/* reset stop watch */
							hours =zero;
						}
					}
				}
			}
			lastSecIncButtonState = SecIncButtonState;
			_delay_ms(depouncingDelay);

			/* minutes decrement */
			if((MinDecButtonState == zero) && (lastMinDecButtonState != zero)){
				if(minuites>zero){
					minuites--;
				}

			}
			lastMinDecButtonState = MinDecButtonState;
			_delay_ms(depouncingDelay);

			/* minutes increment */
			if((MinIncButtonState == zero) && (lastMinIncButtonState != zero)){
				minuites++;
				/* reset minutes */
				if(minuites >maxMinutes){
					hours++;
					minuites = zero;
					/* reset stop watch */
					if(hours > maxHours){
						hours = zero;
					}
				}
			}
			lastMinIncButtonState = MinIncButtonState;
			_delay_ms(depouncingDelay);

			/* hours decrement */
			if((HoursDecButtonState == zero) && (lastHoursDecButtonState != zero)){
				if(hours>zero){
					hours--;
				}
			}
			lastHoursDecButtonState = HoursDecButtonState;
			_delay_ms(depouncingDelay);

			/* hours increment */
			if((HoursIncButtonState == zero) && (lastHoursIncButtonState != zero)){
				hours++;
				/* reset stop watch */
				if(hours > maxHours){
					hours = zero;
					seconds = zero;
					minuites = zero;
				}
			}
			lastHoursIncButtonState = HoursIncButtonState;
			_delay_ms(depouncingDelay);
		}

	}
	return 0;
}
