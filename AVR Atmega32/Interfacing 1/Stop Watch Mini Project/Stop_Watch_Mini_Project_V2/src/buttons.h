/*
 * buttons.h
 *
 *  Created on: Sep 19, 2024
 *      Author: ma479
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "macros.h"
#define DEPOUNCING_DELAY 50

extern volatile unsigned int milliseconds ;
extern volatile unsigned char seconds ;
extern volatile unsigned char minutes ;
extern volatile unsigned char hours ;

extern volatile unsigned char interrupt0flag  ; /* reset flag */
extern volatile unsigned char resumePauseFlag  ; /* pause/resume flag*/
extern volatile unsigned char countUP_DOWN  ; /* count up/down flag*/

void buttons(void);

#endif /* BUTTONS_H_ */
