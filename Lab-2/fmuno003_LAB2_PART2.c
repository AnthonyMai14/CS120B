/*	Kent Arroyo			karro001@ucr.edu
*	Francisco Munoz		fmuno003@ucr.edu
* Lab Section: 022
* Assignment: Lab# 2 Exercise 2
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>
enum States {Start, INIT, INC, DEC, WAIT, RESET}state;
void Tick();

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;
	while(1)
	{
		Tick();
	}
}

//Tick function written by Kent
//Fransisco helped with some of the transitions logic
void Tick(){
	switch(state){ //Transitions
		case Start:
		{
			PORTC = 0x00;
			state = INIT;
			break;
		}
		
		case INIT:
		if((~PINA & 0x03) == 0x01)
		{
			state = INC; break;
		}
		else if((~PINA & 0x03) == 0x02)
		{
			state = DEC; break;
		}
		else if((~PINA & 0x03) == 0x03)
		{
			state = RESET; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case INC:
		state = WAIT;
		break;
		
		case DEC:
		state = WAIT;
		break;
		
		case WAIT:
		if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02))
		{
			state = WAIT; break;
		}
		else
		{
			state = INIT; break;
		}
		
		case RESET:
		if(((~PINA & 0x03) == 0x01) || ((~PINA & 0x03) == 0x02))
		{
			state = RESET; break;
		}
		else
		{
			state = INIT; break;
		}
		
		default:
		break;
	}
	switch(state){ //State actions
		case Start:
		break;
		
		case INIT:
		break;
		
		case INC:
		{
			if(PORTC >= 0x09)
			{
				PORTC = 0x09; break;
			}
			else
			{
				PORTC = PORTC + 0x01; break;
			}
		}
		
		case DEC:
		{
			if(PORTC <= 0x00)
			{
				PORTC = 0x00; break;
			}
			else
			{
				PORTC = PORTC - 0x01; break;
			}
		}
		
		case WAIT:
		break;
		
		case RESET:
		{
			PORTC = 0x00; break;
		}
	}
}