/*
 *		 main.c
 *
 *  	Created on: Oct 5, 2024
 *      Author: Mohamed Newir
 */


#include "../ADC_DRIVER/adc.h"
#include "../LCD_DRIVER/lcd.h"

int main(void)
{
	uint16 res_value;
	LCD_init(); /* initialize LCD driver */
	ADC_init(); /* initialize ADC driver */

	/* Display this string "ADC Value = " only once on LCD at the first row */

	LCD_displayString("ADC value = ");
	LCD_displayStringRowColumn(1,0," so sad ");
    while(1)
    {
    	/* Read ADC channel 0 where the potentiometer is connected */
		res_value = ADC_readChannel(0);

		/* Display the ADC digital value every time at same position */
		LCD_moveCursor(0,12);
		if(res_value >= 1000)
		{
			LCD_integerToString(res_value);
		}
		else
		{
			LCD_integerToString(res_value);
			/* In case the digital value is three or two or one digits print space in the next digit place */
			LCD_displayChar(' ');
		}
    }
}
