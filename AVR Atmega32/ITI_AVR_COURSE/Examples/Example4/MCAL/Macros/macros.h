/*
 *      Author: Mohamed Newir
 *      Created on: Jul 25, 2025
 *      File name: macros.h
 *      Description:
 *      			Define macros to handle register/bit operations
 */

#ifndef MCAL_MACROS_MACROS_H_
#define MCAL_MACROS_MACROS_H_

/*
 * used to set on a certain bit in a certain register
 */
#define SET_BIT(REG,BIT) ((REG) |= (1<<(BIT)))

/*
 * used to set off a certain bit in a certain register
 */
#define CLEAR_BIT(REG,BIT) ((REG) &=~ (1<<(BIT)))

/*
 * used to toggle a certain bit in a certain register
 */
#define TOGGLE_BIT(REG,BIT) ((REG) ^= (1<<(BIT)))

/*
 * Rotate right register value with certain number of rotates
 */
#define ROR(REG,NUM) (((REG) >> (num)) | ((REG) << (8-(NUM))))

/*
 * Rotate left register value with certain number of rotates
 */
#define ROL(REG,NUM) (((REG) << (NUM)) | ((REG) >> (8-(NUM))))

/*
 * Check a certain bit in a certain register is set
 */
#define BIT_IS_SET(REG,BIT) ((REG)&(1<<(BIT)))

/*
 * Check a certain bit in a certain register is cleared
 */
#define BIT_IS_CLEAR(REG,BIT) (!((REG) & (1<<BIT)))

/*
 *
 */
#define GET_BIT(REG,BIT) (((REG) & (1<<(BIT)) >> (BIT)))

#endif /* MCAL_MACROS_MACROS_H_ */
