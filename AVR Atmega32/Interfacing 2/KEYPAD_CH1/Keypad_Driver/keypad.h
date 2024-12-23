/*
 *      File Name: keypad.h
 *
 *      Created on: Sep 27, 2024
 *      Author: Mohamed Newir
 *      Description: header file for Keypad deriver
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "../macros/std_types.h"

/* row/columns number for keypad */
#define KEYPAD_COL_NUM 4
#define KEYPAD_ROW_NUM 4

/* keypad port/pin configuration */

/* for ROWS */
#define KEYPAD_ROW_PORT_ID PORTB_ID
#define KEYPAD_FIRST_ROWS_PIN_ID PIN4_ID
/* for COLS*/
#define KEYPAD_COL_PORT_ID PORTD_ID
#define KEYPAD_FIRST_COL_PIN_ID PIN2_ID

/* keypad logic configuration */
#define KEYPAD_BUTTON_PRESSED LOW
#define KEYPAD_BUTTON_RELEASED HIGH

/* function prototype */

/* get the key which is pressed */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
