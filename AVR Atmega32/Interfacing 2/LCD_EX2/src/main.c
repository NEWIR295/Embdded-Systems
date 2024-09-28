/*
 * 		File name: main.c
 *
 *  	Created on: Sep 27, 2024
 *      Author: Mohamed Newir
 *		Description: control LCD with Atmega32 mc
 */

/* used libraries */
#include "../LCD_DRIVER/lcd.h"
#include <util/delay.h>

int main(void){

	/* Application initialization */
	LCD_init(); /* initialize LCD */

	LCD_displayString("Hi, I am Newir");
	LCD_displayStringRowColumn(1,0,"I am R&D Eng");



	_delay_ms(4000);
	LCD_clearScreen();

	LCD_displayString("I am sad");
	LCD_moveCursor(1,4);
	LCD_displayString("jan");
	LCD_moveCursor(1,8);
	LCD_integerToString(90);
	while(1){



	}

	return 0;
}
