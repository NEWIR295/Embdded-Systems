/*
 * 		File Name: main.c
 *
 * 		Created on: Oct 5, 2024
 *      Author: Mohamed Newir
 *      Description: Update LCD16x2 with Potentiometer value
 */
/* system internal frequency */
#define F_CPU 16000000
/* used libraries */
#include "../LCD_DRIVER/lcd.h"
#include "../ADC_DRIVER/adc.h"

/* main function */
int main(void){
	uint16 potValue;
	LCD_init();
	ADC_init();
	LCD_displayString("ADC value = ");
	while(1){
		potValue = ADC_readChannel(0);
		LCD_moveCursor(0,12);

		if(potValue >=1000){
			LCD_integerToString(potValue);
		}
		else{
			LCD_integerToString(potValue);
			LCD_displayString(" ");
		}
	}
	return 0;
}

