/*
 * interrupts.h
 *
 *  Created on: Sep 19, 2024
 *      Author: Mohamed Newir
 */


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "macros.h"
#include "sevenSegment.h"
#define SEVEN 7
#define TIMER_COMPARE_VALUE 250

extern unsigned int time[SEVEN_SEGMENT_NUMBERS];
void interrupt_init(void);

#endif /* INTERRUPTS_H_ */
