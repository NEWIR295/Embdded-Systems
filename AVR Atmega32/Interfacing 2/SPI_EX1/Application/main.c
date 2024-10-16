/*
 * 		main.c
 *
 * 		Created on: Oct 16, 2024
 *      Author: Mohamed Newir
 *      Description: Test spi Driver
 */

/* system internal frequency */
#define F_CPU 1000000UL

/* used Libraries */
#include "../MCAL/SPI_DRIVER/spi.h"
#include "../MCAL/GPIO_Driver/GPIO/gpio.h"

/* Push button pull-down configuration */
#define BUTTON_PRESSED     HIGH
#define BUTTON_RELEASED    LOW

int main(void)
{
	/* Initialize the SPI driver as Master */
	SPI_initMaster();

	/* Configure PA0 as input pin */
	GPIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_INPUT);

    while(1)
    {
    	/* Check the push button status, and send to MC2 using SPI */
		if(GPIO_readPin(PORTA_ID,PIN0_ID) == BUTTON_PRESSED)
		{
			/* Send the button state, and no need to receive data from the other device */
			SPI_sendReceive(BUTTON_PRESSED);
		}
		else
		{
			/* Send the button state, and no need to receive data from the other device */
			SPI_sendReceive(BUTTON_RELEASED);
		}
    }
}
