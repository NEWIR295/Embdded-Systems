/*
 *		File Name: adc.c
 *
 *  	Created on: Sep 28, 2024
 *      Author: Mohamed Newir
 *      Description: ADC Driver source File
 */

/* used libraries */
#include <avr/io.h>
#include "adc.h"
#include "../macros/macros.h"

/* function responsible to init ADC */
void ADC_init(void){
	/* CHOOSe 2.56v as reference voltage */
	ADMUX = (1<<REFS1) | (1<<REFS0) ;
	/* ADEN -> enable ADC
	 * ADPS0:2 choose ADC clock
	 * we choose here 128  as our pre-scaler
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}
/* function responsible to read ADC channel */
uint16 ADC_readChannel(uint8 channel_num){

	ADMUX = (ADMUX&0xE0) | (channel_num & 0x07) ;
	SET_BIT(ADCSRA,ADSC);
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}