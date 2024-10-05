/*
 * adc.h
 *
 *  Created on: Sep 28, 2024
 *      Author: ma479
 */

#ifndef ADC_H_
#define ADC_H_

#include "../macros/std_types.h"

#define ADC_REF_VOLT_VALUE 5
#define ADC_MAX_VALUE 1023

/* function prototypes */

/* function responsible to init ADC */
void ADC_init(void);
/* function responsible to read ADC channel */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
