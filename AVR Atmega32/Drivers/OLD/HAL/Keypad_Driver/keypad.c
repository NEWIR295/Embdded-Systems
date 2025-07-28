/*
 * 		file name: keypad.c
 *
 * 	    Created on: Sep 27, 2024
 *      Author: Mohamed Newir
 *      Description: source file for keypad driver
 */

/* GPIO driver LIB */
#include "../GPIO/gpio.h"
/* keypad header file */
#include "keypad.h"
/* delay lib */
#include <util/delay.h>

/* static function prototype to adjust key number either 4*4 or 4*3*/
#if(KEYPAD_COL_NUM == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);

#elif(KEYPAD_COL_NUM == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);

#endif

uint8 KEYPAD_getPressedKey(void){

	uint8 col,row;

	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID+2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID+3,PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+2,PIN_INPUT);

#if(KEYPAD_COL_NUM == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+3,PIN_INPUT);
#endif

	while(1){

		for(row = 0;row<KEYPAD_ROW_NUM;row++){

			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID+row,PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID+row,KEYPAD_BUTTON_PRESSED);
			for(col = 0;col<KEYPAD_COL_NUM;col++){

				if((GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col)) == KEYPAD_BUTTON_PRESSED){
#if(KEYPAD_COL_NUM == 3)
					return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_COL_NUM) + col +1);
#elif(KEYPAD_COL_NUM == 4)
					return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_COL_NUM) + col +1);
#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROWS_PIN_ID+row,PIN_INPUT);
			_delay_ms(10);
		}
	}

}

#if(KEYPAD_COL_NUM == 3)

static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number){

	uint8 keypadButton = 0;

	switch(button_number){
	case 10:
		keypadButton = '*';
		break;
	case 11:
		keypadButton = 0;
		break;
	case 12:
		keypadButton = '#';
		break;
	default:
		keypadButton = button_number;
		break;
	}
	return keypadButton;
}

#elif(KEYPAD_COL_NUM == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number){

	uint8 keypadButton = 0;

	switch(button_number){
	case 1:
		keypadButton = 7;
		break;
	case 2:
		keypadButton = 8;
		break;
	case 3:
		keypadButton = 9;
		break;
	case 4:
		keypadButton = '%';
		break;
	case 5:
		keypadButton = 4;
		break;
	case 6:
		keypadButton = 5;
		break;
	case 7:
		keypadButton = 6;
		break;
	case 8:
		keypadButton = '*';
		break;
	case 9:
		keypadButton = 1;
		break;
	case 10:
		keypadButton = 2;
		break;
	case 11:
		keypadButton = 3;
		break;
	case 12:
		keypadButton = '-';
		break;
	case 13:
		keypadButton = 13;
		break;
	case 14:
		keypadButton = 0;
		break;
	case 15:
		keypadButton = '=';
		break;
	case 16:
		keypadButton = '+';
		break;
	default:
		keypadButton = button_number;
		break;
	}
	return keypadButton;
}

#endif
