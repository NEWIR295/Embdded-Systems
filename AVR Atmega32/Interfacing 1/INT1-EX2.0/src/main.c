/*
 * main.c
 *
 *  Created on: Aug 19, 2024
 *      Author: Mohamed Newir
 *      project description: control 3 leds using external interrupt
 */
/*system frequency*/
#define F_CPU 16000000UL
/*std libraries*/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*global var*/
unsigned char interruptFlag = 0;

/*ISR INT1 function*/
ISR(INT1_vect){
    interruptFlag = 1;
}

/*INT1 initialization function*/
void int1_init(void){
    DDRD &= ~(1<<PD3);  // Set PD3 as input for INT1
    MCUCR |= (1<<ISC11) | (1<<ISC10);  // Trigger INT1 on rising edge
    GICR |= (1<<INT1);  // Enable INT1
    SREG |= (1<<7);  // Enable global interrupts
}

int main(void){
    int1_init();  // Initialize INT1
    DDRC |= (1<<PC0) | (1<<PC1) | (1<<PC2);  // Set PC0, PC1, and PC2 as output for LEDs
    PORTC = (PORTC & 0xf8) | (0x00);  // Initialize PORTC to turn off all LEDs
    int i;
    while(1){
        if(interruptFlag == 0){
            PORTC = (PORTC & 0xf8) | 0x01;  // Turn on LED 1
            _delay_ms(500);
            PORTC = (PORTC & 0xf8) | 0x02;  // Turn on LED 2
            _delay_ms(500);
            PORTC = (PORTC & 0xf8) | 0x04;  // Turn on LED 3
            _delay_ms(500);
        }
        else if(interruptFlag == 1){
            for(i = 0; i < 5; i++){
                PORTC = (PORTC & 0xf8) | 0x07;  // Turn on all LEDs
                _delay_ms(500);
                PORTC = (PORTC & 0xf8) | 0x00;  // Turn off all LEDs
                _delay_ms(500);
            }
            interruptFlag = 0;  // Reset interrupt flag
        }
    }
    return 1;
}
