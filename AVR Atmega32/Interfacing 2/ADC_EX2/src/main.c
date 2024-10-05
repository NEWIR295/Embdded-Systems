/*
 * 		File Name: main.c
 *
 * 		Created on: Oct 5, 2024
 *      Author: Mohamed Newir
 *      DEscription: Display LM35 Temperature Sensor Reading on LCD16x2
 */
/* internal frequency */
/*#define F_CPU 1000000*/
/* used libraries*/
#include "../ADC_DRIVER/adc.h"
#include "../LM35_Driver/lm35.h"
#include "../LCD_DRIVER/lcd.h"

/* main function */
int main(void){

	/* Application initialization */
	ADC_init();
	LCD_init();
	LCD_displayString("Temp =    C");

	uint8 temperature;
	while(1){
		/* Application */
		temperature = LM35_getReading();
		LCD_moveCursor(0,7);
		if(temperature >= 100){
			LCD_integerToString(temperature);
		}
		else{
			LCD_integerToString(temperature);
			LCD_displayString(" ");
		}
	}
	return 0;
}
