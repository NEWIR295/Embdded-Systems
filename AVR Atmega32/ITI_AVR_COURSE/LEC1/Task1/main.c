/*
 * main.c
 *
 *  Created on: Jul 16, 2025
 *      Author: newir529
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void) {

    DDRB |= (1 << PB0); // Set PB0 as output
    //DDRB &=~(1<<PB1); // set pb1 as input
    while (1) {
        PORTB ^= (1 << PB0); // Toggle PB0
        _delay_ms(500); // Delay for 500ms
    }
    return 0;
}
