/*
 * 		File Name: ldr_sensor.c
 *
 *  	Created on: Oct 7, 2024
 *      Author: Mohamed Newir
 *      Description: LDR Sensor Driver Source File
 */
/* used libraries*/
#include "../ADC_DRIVER/adc.h"
#include "../GPIO/gpio.h"
#include "ldr_sensor.h"

/* Reads the LDR sensor value and returns the light intensity. */
uint16 LDR_getLightIntensity(void){

	uint16 channelReading = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);
	uint16 LDR_value = (uint16)(( (uint32) channelReading * LDR_SENSOR_MAX_LIGHT_INTENSITY * ADC_REF_VOLT_VALUE)/(LDR_SENSOR_MAX_VOLT_VALUE * ADC_MAX_VALUE));
	return LDR_value;
}
