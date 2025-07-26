/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: main.c
 *      Description:
 *      		   Simple Application to blink a LED
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include "../HAL/LED_DRIVER/Include/led.h"
#include "../HAL/PUSHBUTTON_DRIVER/Include/pushbutton.h"

int main(void){


	LED_init(LED2_ID);


	while(1){
		LED_blink(LED2_ID);
	}
	return 0;
}
