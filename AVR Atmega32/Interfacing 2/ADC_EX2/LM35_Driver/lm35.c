/*
 *	File Name: lm35.c
 *
 * 	Created on: Oct 5, 2024
 *  Author: Mohamed Newir
 *  Description: Source file for LM35 Temperature Sensor
 */
#include "../GPIO/gpio.h"
#include "../ADC_DRIVER/adc.h"
#include "lm35.h"


/* Function get the reading of Temperature Sensor */
uint8 LM35_getReading(void){
	uint16 channelReading = ADC_readChannel(LM35_PIN_ID);
	uint8 temp =  (uint8)(((uint32)channelReading * LM35_MAX_TEMP * ADC_REF_VOLT_VALUE)/(LM35_MAX_VOLT * ADC_MAX_VALUE));
	return temp;
}
