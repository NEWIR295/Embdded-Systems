/*
 * 	    File Name: macros.h
 *
 *  	Created on: Sep 26, 2024
 *      Author: Mohamed Newir
 *      Description: User defined macros to deal with AVR ATmega32 registers
 */

#ifndef MACROS_MACROS_H_
#define MACROS_MACROS_H_

/* Set a certain bit in the register */
#define SET_BIT(REG,BIT) ((REG)|=(1<<(BIT)))
/* Clear a certain bit in the register */
#define CLEAR_BIT(REG,BIT) ((REG)&=(~(1<<(BIT))))
/* Toggle a certain bit in the register */
#define TOGGLE_BIT(REG,BIT) ((REG)^=(1<<(BIT)))
/* Rotate right register value with certain numbers of rotates */
#define ROR(REG,NUM) ((REG) = ((REG)>>(NUM)) | ((REG)<<(8-(NUM)))
/* Rotate Left register value with certain numbers of rotates */
#define ROL(REG,NUM) ((REG) = ((REG)<<(NUM)) | ((REG)>>(8-(NUM)))
/* Check if a certain bit in the register is set */
#define BIT_IS_SIT(REG,BIT) ((REG)&(1<<BIT))
/* Check if a certain bit in the register is cleared */
#define BIT_IS_CLEAR(REG,BIT) (!((REG)&(1<<BIT)))

#endif /* MACROS_MACROS_H_ */
