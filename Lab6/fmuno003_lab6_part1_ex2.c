/*	Kent Arroyo			karro001@ucr.edu
 *	Francisco Munoz		fmuno003@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab 6 ADC Part 1
 *  I acknowledge all content contained herein, excluding template or example code, is my own original work.
 */ 

#include <avr/io.h>

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	// in Free Running Mode, a new conversion will trigger
	// whenever the previous conversion completes.
}

unsigned short AD_convert = 0x00;
	
int main(void)
{	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	ADC_init();

    while(1)
    {
			AD_convert = ADC;
			PORTB =  (char)AD_convert;
			PORTD = (char)(AD_convert >> 8);
    }
}