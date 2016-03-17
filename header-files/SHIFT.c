#ifndef SHIFT_H
#define SHIFT_H

#include <avr/io.h>
// Ensure DDRC is setup as output
void transmit_data1(unsigned char data) // controls 7seg & controls rows on LED matrix
{
	for(int i = 0; i < 8; ++i)
	{
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTC = 0x08;
		// set SER = next bit of data to be sent.
		PORTC |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTC |= 0x04;
	}
	// set RCLK = 1. Rising edge copies data from the �Shift� register to the
	// �Storage� register
	PORTC |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTC = 0x00;
}
void transmit_data2(unsigned char data) //controls red columns
{
    for(int i = 4; i >= 0; --i)
    {
        PORTA = 0x80;
        PORTA |= ((data << i) & 0x10);
        PORTA |= 0x40;
    }
    for(int i = 1; i <= 3; ++i)
    {
        PORTA = 0x80;
        PORTA |= ((data >> i) & 0x10);
        PORTA |= 0x40;
    }
    PORTA |= 0x20;
    PORTA = 0x00;
}

void transmit_data3(unsigned char data) //controls green columns
{
    for(int i = 4; i >= 0; --i)
    {
        PORTC = 0x80;
        PORTC |= ((data << i) & 0x10);
        PORTC |= 0x40;
    }
    for(int i = 1; i <= 3; ++i)
    {
        PORTC = 0x80;
        PORTC |= ((data >> i) & 0x10);
        PORTC |= 0x40;
    }
    PORTC |= 0x20;
    PORTC = 0x00;
}

#endif
