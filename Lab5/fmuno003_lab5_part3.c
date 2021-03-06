/*	Kent Arroyo			karro001@ucr.edu
 *	Francisco Munoz		fmuno003@ucr.edu
 *	Lab Section: 022
 *	Assignment: Lab 5 Part 1
 *  I acknowledge all content contained herein, excluding template or example code, is my own original work.
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn()
{
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff()
{
	TCCR1B = 0x00;
}
void TimerISR()
{
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect)
{
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0)
	{
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet(unsigned long M)
{
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}






void TickThree_LEDS();
void TickSpeaker();
void TickCOM();
enum Three_States {Start, LED_1, LED_2, LED_3} Three_state;
enum Speaker_States{SPEAK_Start, ON_SWITCH, OFF_SWITCH, WAIT} Speaker_state;
enum COMBINE_States{COM_Start, OUTPUT} Combine_State;
unsigned char Speaker = 0x00;
unsigned char Three = 0x00;
unsigned char temp = 0x00;
unsigned short count = 0x00;
unsigned short cnt = 0x00;
unsigned char button = 0x00;

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	Three_state = Start;
	Speaker_state = SPEAK_Start;
	Combine_State = COM_Start;
	cnt = 0;
	count = 0;
	
	TimerSet(1);
	TimerOn();
    while(1)
    {	
		TickThree_LEDS();
		TickSpeaker();
		TickCOM();
        while (!TimerFlag);
        TimerFlag = 0;
    }
}

void TickThree_LEDS()
{
	switch(Three_state) // Transitions
	{
		case Start:
		{
			Three_state = LED_1;
			break;
		}
		case LED_1:
		{
			if(cnt < 300)
			{
				Three_state = LED_1;
				++cnt;
			}
			else
			{
				Three_state = LED_2;
				cnt = 0;
			}
			break;
		}
		case LED_2:
		{
			if(cnt < 300)
			{
				Three_state = LED_2;
				++cnt;
			}
			else
			{
				Three_state = LED_3;
				cnt = 0;
			}
			break;
		}
		case LED_3:
		{
			if(cnt < 300)
			{
				Three_state = LED_3;
				++cnt;
			}
			else
			{
				Three_state = LED_1;
				cnt = 0;
			}
			break;
		}
		default:
			break;	
	}
	
	switch(Three_state) // State Actions
	{
		case Start:
			break;
		case LED_1:
		{
			Three = 0x01;
			break;
		}
		case LED_2:
		{
			Three = 0x02;
			break;
		}
		case LED_3:
		{
			Three = 0x04;
			break;
		}
		default:
			break;
	}
}
void TickSpeaker()
{
	switch(Speaker_state) // Transitions
	{
		case SPEAK_Start:
		{
			Speaker_state = WAIT;
			count = 0;
			break;
		}
		case ON_SWITCH:
		{
			if((count < 2) && ((~PINA & 0x04) == 0x04))
			{
				Speaker_state = ON_SWITCH;
				++count;
				break;
			}
			else if((~PINA & 0x04) == 0x04)
			{
				Speaker_state = OFF_SWITCH;
				count = 0;
				break;
			}
			else
			{
				Speaker_state = WAIT;
				break;
			}
		}
		case OFF_SWITCH:
		{
			if((count < 2) && ((~PINA & 0x04) == 0x04))
			{
				Speaker_state = OFF_SWITCH;
				++count;
				break;
			}
			else if((~PINA & 0x04) == 0x04)
			{
				Speaker_state = ON_SWITCH;
				count = 0;
				break;
			}
			else
			{
				Speaker_state = WAIT;
				break;
			}
		}
		case WAIT:
		{
			if((~PINA & 0x04) == 0x04)
			{
				Speaker_state = ON_SWITCH;
				break;
			}
			else
			{
				Speaker_state = WAIT;
				break;
			}
		}
		default:
			break;
	}
	switch(Speaker_state) // State Actions
	{
		case SPEAK_Start:
			break;
		case ON_SWITCH:
		{
			Speaker = 0x08;
			break;
		}
		case OFF_SWITCH:
		{
			Speaker = 0x00;
			break;
		}
		case WAIT:
		{
			Speaker = 0x00;
			count = 0x00;
			break;
		}
		default:
			break;
	}
}
void TickCOM()
{
	switch(Combine_State) // Transitions
	{
		case COM_Start:
		{
			Combine_State = OUTPUT;
			break;
		}
		case OUTPUT:
			break;
		default:
			break;
	}
	switch(Combine_State) // State Actions
	{
		case COM_Start:
			break;
		case OUTPUT:
		{
			temp = Speaker | Three;
			PORTB = temp;
			break;
		}
	}
}
