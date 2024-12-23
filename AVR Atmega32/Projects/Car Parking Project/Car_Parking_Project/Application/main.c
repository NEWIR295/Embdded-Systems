/*
 * 		File Name: main.c
 *
 *  	Created on: Oct 11, 2024
 *      Author: Mohamed Newir
 *      Description: Application Source File For Car Parking Alarm System
 */

/* System Internal Frequency */
#define F_CPU 16000000UL

/* Used Libraries */
#include <util/delay.h>
#include "../HAL/BUZZER_DRIVER/buzzer.h"
#include  "../HAL/LCD_DRIVER/lcd.h"
#include "../HAL/LED_DRIVER/led.h"
#include "../HAL/US_DRIVER/us.h"
#include "avr/io.h"

/* Main Function */
int main (void){

	/* Enable Global Interrupt */
	SREG |= (1<<7);

	/* Application Initialization */
	Ultrasonic_init();
	LCD_init();
	LEDS_init();
	Buzzer_init();


	/* clear screen @ start*/
	LCD_clearScreen();
	/* Show Reading on screen */
	LCD_displayStringRowColumn(0,0,"Distance = ");

	/* local variables definitions */
	uint16 US_distanceReading ;
	uint16 US_distanceReading_prevState = 0;

	while(1){

		/* Application Code */
		US_distanceReading = Ultrasonic_readDistance();

		if(US_distanceReading <= 5){

			/* show threat level */
			/* Flash LEDs */
			LED_on(RED_LED_ID);
			LED_on(GREEN_LED_ID);
			LED_on(BLUE_LED_ID);
			_delay_ms(500);
			LED_off(RED_LED_ID);
			LED_off(GREEN_LED_ID);
			LED_off(BLUE_LED_ID);

		}

		/* apply car parking conditions if the reading have changed */
		if(US_distanceReading != US_distanceReading_prevState){

			/* Show Reading on screen */
			LCD_moveCursor(0,11);
			if(US_distanceReading <10){
				LCD_integerToString(US_distanceReading);
				LCD_displayString(" ");
			}
			else{
				LCD_integerToString(US_distanceReading);
			}
			LCD_displayString(" cm");

			/* ensure stop section is cleared */
			if(US_distanceReading > 5){
				LCD_displayStringRowColumn(1,5,"       ");
			}

			/* apply threat/warnings for several car parking conditions */
			if(US_distanceReading <= 5){

				/* open buzzer */
				Buzzer_on();

				/* show alarm message */
				LCD_displayStringRowColumn(1,5,"STOP!!");

			}
			else if ( (US_distanceReading >= 6) &&  (US_distanceReading <= 10) ){

				/*ensure that buzzer is off */
				Buzzer_off();

				/* show threat level */
				/* open all LEDs */
				LED_on(RED_LED_ID);
				LED_on(GREEN_LED_ID);
				LED_on(BLUE_LED_ID);

			}
			else if ( (US_distanceReading >= 11) &&  (US_distanceReading <= 15) ){

				/*ensure that buzzer is off */
				Buzzer_off();

				/* show threat level */
				/* open led & green only */
				LED_on(RED_LED_ID);
				LED_on(GREEN_LED_ID);
				LED_off(BLUE_LED_ID);

			}
			else if ( (US_distanceReading >= 16) &&  (US_distanceReading <= 20) ){

				/*ensure that buzzer is off */
				Buzzer_off();

				/* show threat level */
				/* open led only */
				LED_on(RED_LED_ID);
				LED_off(GREEN_LED_ID);
				LED_off(BLUE_LED_ID);

			}
			else if ( US_distanceReading > 20 ){

				/*ensure that buzzer is off */
				Buzzer_off();

				/* show threat level */
				/* close all LEDs*/
				LED_off(RED_LED_ID);
				LED_off(GREEN_LED_ID);
				LED_off(BLUE_LED_ID);

			}
		}
		US_distanceReading_prevState = US_distanceReading;
	}
	return 0;
}
