/*
 *  File Name: lcd.c
 *
 *  Created on: Sep 28, 2024
 *  Author: Mohamed Newir
 *  Description: LCD driver source file
 */
#include "../GPIO/gpio.h"
#include "lcd.h"
#include <util/delay.h>

/*
 * function purpose is to initialize LCD: pin direction
 *  , setup lcd data mode 4-bits or 8-bits
 */
void LCD_init(void){

	GPIO_setupPinDirection(LCD_RS_PORT_ID,LCD_RS_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID,LCD_E_PIN_ID,PIN_OUTPUT);
	GPIO_setupPortDirection(LCD_DATA_PORT,PORT_OUTPUT);
	_delay_ms(20);
	LCD_sendCommand(LCD_TWO_LINES_8_BITS_MODE);
	LCD_sendCommand(LCD_CURSOR_OFF);
	LCD_sendCommand(LCD_CLEAR_COMMAND);

}

/*
 * function purpose is to send commands to LCD
 */
void LCD_sendCommand(uint8 command){

	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT,command);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOW);
	_delay_ms(1);
}

/*
 * function purpose is to display single char on LCD
 */
void LCD_displayChar(uint8 character){
	GPIO_writePin(LCD_RS_PORT_ID,LCD_RS_PIN_ID,HIGH);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT,character);
	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOW);
	_delay_ms(1);
}

/*
 * function purpose is to display strings on LCD
 */
void LCD_displayString(const uint8 *str){
	uint8 i = 0;
	while( *(str + i) != '\0' ){
		LCD_displayChar( *(str + i) );
		i++;
	}
}

/*
 * function purpose is to move cursor to specfic location
 * on screen
 */
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 LCD_memoryAddress;
	switch(row){
	case 0:
		LCD_memoryAddress = col ;
		break;
	case 1:
		LCD_memoryAddress = col +0x40 ;
			break;
	case 2:
		LCD_memoryAddress = col +0x10;
			break;
	case 3:
		LCD_memoryAddress = col +0x50;
			break;
	}
	LCD_sendCommand(LCD_memoryAddress | LCD_SET_CURSOR_LOCATION);
}

/*
 * function purpose is to display strings on LCD specific row/column
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8 *str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);
}

/*
 * function purpose is to display integers on screen
 */
void LCD_integerToString(uint8 data){

	uint8 buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

/*
 * function purpose is send command to clear screen
 */
void LCD_clearScreen(void){
	LCD_sendCommand(LCD_CLEAR_COMMAND);
}
