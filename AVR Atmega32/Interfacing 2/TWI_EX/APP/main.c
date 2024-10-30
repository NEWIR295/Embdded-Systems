/*
 *		File Name: main.c
 *
 *  	Created on: Oct 29, 2024
 *      Author: Mohamed Newir
 *      Description: Test EEPROM Driver read/write
 */

/* used libraries */
#include "../MCAL/GPIO_Driver/GPIO/gpio.h"
#include "../MCAL/TWI_DRIVER/twi.h"
#include "../HAL/EXTERNAL_EEPROM_DRIVER/external_eeprom.h"
#include <util/delay.h>

int main (void){

	uint8 test = 0;
	/* Application Initialization */
	TWI_init();
	GPIO_setupPortDirection(PORTD_ID,PORT_OUTPUT);
	GPIO_writePort(PORTD_ID,0x00);
	EEPROM_writeByte(0x0311,0x0f);
	_delay_ms(10);
	EEPROM_readByte(0x0311,&test);
	while(1){

		/* Application Code */
		GPIO_writePort(PORTD_ID,test);
	}

	return 0;
}
