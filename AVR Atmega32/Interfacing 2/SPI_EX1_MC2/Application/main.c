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

/* LED Positive Logic configuration */
#define LED_ON             HIGH
#define LED_OFF            LOW

int main(void)
{
	uint8 data_received;

	/* Initialize the SPI driver as Slave */
	SPI_initSlave();

	GPIO_setupPinDirection(PORTC_ID,PIN3_ID,PIN_OUTPUT); /* Configure PC3 as output pin */
	GPIO_writePin(PORTC_ID,PIN3_ID,LED_OFF); /* Turn OFF the LED */

    while(1)
    {
    	/*
    	 * Receive button status from the MC1 using SPI,
    	 * and send SPI_DEFAULT_DATA_VALUE as no need to send data to other device.
    	 */
		data_received = SPI_sendReceive(SPI_DEFAULT_VALUE);

		if(data_received == BUTTON_PRESSED)
		{
			GPIO_writePin(PORTC_ID,PIN3_ID,LED_ON); /* Turn ON the LED */
		}
		else
		{
			GPIO_writePin(PORTC_ID,PIN3_ID,LED_OFF); /* Turn OFF the LED */
		}
    }
}
