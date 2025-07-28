/*
 *      Author: Mohamed Newir
 *      Created on: Jul 27, 2025
 *      File name: buzzer.h
 *      Description:
 *      			Buzzer driver delaration
 */


#ifndef HAL_BUZZER_DRIVER_INCLUDE_BUZZER_H_
#define HAL_BUZZER_DRIVER_INCLUDE_BUZZER_H_

/* user defined data types library */
#include "../../../MCAL/Macros/std_types.h"

/* Buzzer state declaration */
typedef enum{
	BUZZER_OFF, BUZZER_ON
}BUZZER_STATE;

typedef enum{
	ACTIVE, PASSIVE
}BUZZER_TYPE;

/* Buzzer data type declaration */
typedef struct{
	uint8 portNum;
	uint8 pinNum;
	BUZZER_TYPE type;
}Buzzer_t;

/* Function initialize buzzer */
void BUZZER_init(const Buzzer_t *buzzer);

/* Function control active buzzer state  */
void BUZZER_activeCtrl(const Buzzer_t *buzzer, BUZZER_STATE state);

/* Function control passive buzzer state  */
void BUZZER_passiveCtrl(const Buzzer_t *buzzer, BUZZER_STATE state, uint8 freq);


#endif /* HAL_BUZZER_DRIVER_INCLUDE_BUZZER_H_ */
