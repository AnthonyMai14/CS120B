/*	
 *  Kent Arroyo			karro001@ucr.edu
 *	Francisco Munoz		fmuno003@ucr.edu
 *	Lab Section: 022
 *	Assignment: Custom Lab Project
 *  I acknowledge all content contained herein, excluding template or example code, is my own original work.
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include </Users/munoz/Desktop/header files/io.h>
#include </Users/munoz/Desktop/header files/io.c>
#include </Users/munoz/Desktop/header files/bit.h>
#include </Users/munoz/Desktop/header files/timer.h>
#include </Users/munoz/Desktop/header files/notes.c>
#include </Users/munoz/Desktop/header files/PWM.c>
#include </Users/munoz/Desktop/header files/keypad.h>
#include </Users/munoz/Desktop/header files/SHIFT.c>
#include </Users/munoz/Desktop/header files/usart.h>

unsigned char hasSent = 0x00;


char * message = "Welcome to Mini Arcade!! Please choose the following game! "; //59
char * message2 = "1. Simon Says    2. Tunnel Runner  3. SNEK   4.Dance Dance Revolution   "; //72
unsigned char display[16];
unsigned char display2[16];
double pattern[14] = {C3, E3, G3, C3, B3, C3, C3, E3, G3, C3, G3, B3, C3, B3};
char buttons[14] = {'1', '2', '3', '1', '4', '1', '1', '2', '3', '1', '3', '4', '1', '4'};
char hex[14] = {0x06, 0x5B, 0x4F, 0x06, 0x66, 0x06, 0x06, 0x5B, 0x4F, 0x06, 0x4F, 0x66, 0x06, 0x66};
double danceRev[303] = {F5, E5, D_5, E5, D_5, D5, D_5, D5, C_5, D5, C_5, C5, B4, D_4, D4, D_4, D4, C_4, F_4, F4, E4, F4,
	F4, E4, D_4, E4, D_4, D4, D_4, D4, C_4, D4, C_4, B4, 0, B4, 0, C5, B4, 0, B4, 0, A_4, B4, 0, B4, 0, C5,
	B4, 0, B4, 0, C_5, D_5, C_5, D_5, E5, F_5, E5, D_5, C_5, B4, C_5, D_5,
	A4, C_5, E5, C_5, D_5, C_5, D_5, E5, F_5, E5, D_5, C_5, B4, C_5, D_5, C_5, B4, A4, E5, E5, C_5, 0,
	D4, C_4, B3, D4, 0, E4, D4, B3, E4, 0, F_4, E4, C_4, F_4, 0, E5, C_5, E5, F5, D4, C_4, B3, 0, E4,
	D4, B3, E4, 0, F_4, E4, C_4, F_4, E4, C_4, D4, C_4, F_4, E4, 0, B4, C5, A4, B4, C5, A4, G_4, F_4,
	C4, C_4, D4, D_4, E4, D_4, D4, C_4, C4, B3, A3, G3, F_3, F3, E3, F3, 0, B4, C5, A4, B4, C5, A4,
	C5, B4, F_5, 0, A4, 0, C_5, D_5, 0, C_5, A5, E5, B5, B4, D_5, F_5, A_5, B5, F_5, A5, C_6, A5, D_5, C_5,
	D_5, E5, F_5, E5, D_5, C_5, B4, C_5, D_5, A4, C_5, E5, C_5, D_5, C_5, D_5, E5, F_5, E5, D_5, C_5, B4, C_5,
	D_5, C_5, B4, A4, E5, E5, C_5, 0, D4, C_4, B3, D4, 0, E4, D4, B3, E4, 0, F_4, E4, C_4, F_4, 0, E5, C_5, E5,
	F5, D4, C_4, B3, 0, E4, D4, B3, E4, 0, F_4, E4, C_4, F_4, E4, C_4, D4, C_4, F_4, E4, 0, B4, C5, A4, B4, C5,
	A4, G_4, F_4, C4, C_4, D4, D_4, E4, D_4, D4, C_4, C4, B3, A3, G3, F_3, F3, E3, F3, 0, B4, C5, A4, B4, C5, A4,
C5, B4, F_5, 0, A4, 0, C_5, D_5, 0, C_5, A5, E5, B5, B4, D_5, F_5, A_5, B5, F_5, A5, C_6, A5}; // tempo = 184 beats per minute
char danceTime[304] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 14, 2, 8, 6, 2, 14, 2, 8, 6, 2, 14, 2, 8, 6, 2, 14, 2, 8, 6,
	4, 4, 4, 2, 4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 8, 4, 4, 4, 2, 4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 4, 2, 2, 4, 1, 1, 1, 1,
	4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4,
	4, 4, 4, 4, 4, 4, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 16, 16, 4, 12, 4,
	12, 32, 4, 12, 8, 8, 60, 1, 1, 1, 1, 16, 16, 16, 10, 6, 4, 4, 4, 2, 4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 8, 4, 4, 4, 2,
	4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 4, 2, 2, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 4,
	1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 16, 16, 4, 12, 4, 12, 32, 4, 12, 8, 8, 60, 1, 1, 1, 1, 16, 16, 16, 10, 6};
unsigned char a = 0x00;
unsigned char b = 0x00;
unsigned char c = 0x00;
unsigned char d = 0x00;
unsigned char tmp = 0x00;
unsigned char KeyTemp = 0x00;
unsigned char key = 0x00;
unsigned char shift = 0x00;
unsigned char gameStart = 0;
unsigned char cnt = 0x00;
unsigned char cnt2 = 0x00;
unsigned char gameSelector = 0x07;
unsigned char musicPeriod = 0;
unsigned short cont = 0;
unsigned short count = 0;
unsigned short mainPeriod = 0;
unsigned short simonPeriod = 0;
unsigned short SandM_period = 0;

void sendData(unsigned char x , unsigned char port)
{
	unsigned char hasSent = 0;
	while(!hasSent)
	{
		if(USART_IsSendReady(port))
		{
			USART_Send(x , port);
			hasSent = 1;
		}
	}
	return;
}

enum SS_State {SS_Start, SS_WAIT, SS_BEGIN, SS_DOWN, SS_PAUSE, SS_CHECK, SS_WRONG, SS_RELEASE, SS_UPDATE, SS_WIN}simonState;
void SimonSays_Tick()
{
	switch(simonState)
	{
		case SS_Start:
		{
			tmp = '\0';
			simonState = SS_WAIT;
			break;
		}
		case SS_WAIT:
		{
			if(tmp != '\0')
			{
				simonState = SS_BEGIN; break;
			}
			else
			{
				simonState = SS_WAIT; break;
			}
		}
		
		case SS_BEGIN:
		{
			if(a <= 10)
			{
				simonState = SS_BEGIN; break;
			}
			else if(a > 10)
			{
				++b;
				simonState = SS_DOWN;
				break;
			}
		}
		case SS_DOWN:
		{
			if(b > c)
			{
				b = 0x00;
				tmp = '\0';
				simonState = SS_PAUSE;
				break;
			}
			else
			{
				simonState = SS_BEGIN;
				break;
			}
		}
		case SS_PAUSE:
		{
			if(tmp == '\0')
			{
				simonState = SS_PAUSE; break;
			}
			else if(b == c)
			{
				b = 0x00;
				++c;
				simonState = SS_UPDATE; break;
			}
			else if(tmp != '\0')
			{
				simonState = SS_CHECK;
				break;
			}
		}
		
		case SS_CHECK:
		{
			if(tmp == buttons[b])
			{
				++b;
				simonState = SS_RELEASE; break;
			}
			else
			{
				simonState = SS_WRONG; break;
			}
		}
		
		case SS_WRONG:
		{
			if(a <= 14)
			{
				simonState = SS_WRONG; break;
			}
			else if(a > 14)
			{
				tmp = '\0';
				simonState = SS_WAIT; break;
			}
		}
		
		case SS_UPDATE:
		{
			if(c >= 14)
			{
				simonState = SS_WIN; break;
			}
			else if(c < 14)
			{
				simonState = SS_BEGIN; break;
			}
		}
		
		case SS_WIN:
		{
			if(a <= 14)
			{
				simonState = SS_WIN; break;
			}
			else if(a > 14)
			{
				tmp = '\0';
				simonState = SS_WAIT; break;
			}
		}
		case SS_RELEASE:
		{
			if(tmp != '\0')
			{
				simonState = SS_RELEASE;
				break;
			}
			else
			{
				tmp = '\0';
				simonState = SS_PAUSE;
				break;
			}
		}
		default:
		break;
	}
	switch(simonState) //state actions
	{
		case SS_Start:
		break;
		
		case SS_WAIT:
		{
			set_PWM(0);
			shift = hex[0];
			transmit_data1(shift);
			a = 0;
			b = 0;
			c = 0;
			tmp = GetKeypadKey();
			break;
		}
		
		case SS_BEGIN:
		{
			++a;
			set_PWM(pattern[b]);
			shift = hex[b];
			transmit_data1(shift);
			break;
		}
		
		case SS_DOWN:
		{
			set_PWM(0);
			shift = 0x00;
			transmit_data1(shift);
			a = 0x00;
			break;
		}
		
		case SS_PAUSE:
		tmp = GetKeypadKey();
		break;
		
		case SS_CHECK:
		break;
		
		case SS_WRONG:
		{
			set_PWM(D6);
			++a;
			b = 0;
			c = 0;
			
			break;
		}
		
		case SS_UPDATE:
		break;
		
		case SS_WIN:
		{
			set_PWM(C5);
			++a;
			shift = (~shift);
			transmit_data1(shift);
			break;
		}
		
		case SS_RELEASE:
		{
			tmp = GetKeypadKey();
			break;
		}
		default:
		break;
	}
}
enum States{OUT}state;
void Tick()
{
	switch(state) //transitions
	{
		case OUT:
		state = OUT; break;
		
		default:
		state = OUT; break;
	}
	switch(state) //state actions
	{
		case OUT:
		{
			for(int i = 0; i < 16; ++i)
			{
				
				display[i] = message[(cnt + i) % 59];
				display2[i] = message2[(cnt2 + i) % 72];
			}
			cnt = (cnt + 1) % 59;
			cnt2 = (cnt2 + 1) % 126;
			LCD_DisplayString(1, display);
			LCD_DisplayString2(17, display2);
			break;
		}
		
		default:
		break;
	}
	
}
enum MenuStates{Start, Wait} mState;
void menuInput()
{
	switch(mState)
	{
		case Start:
		{
			mState = Wait;
			break;
		}
		case Wait:
		{
			mState = Wait;
			break;
		}
		default:
		break;
	}
	switch(mState)
	{
		case Start:
		break;
		case Wait:
		{
			gameSelector = GetKeypadKey();
			switch(gameSelector)
			{
				case '\0': gameSelector = 0xFF; break;
				case 'A': gameSelector = 0xFF; break;
				case 'B': gameSelector = 0xFF; break;
				case 'C': gameSelector = 0xFF; break;
				case 'D': gameSelector = 0xFF; break;
				case '*': gameSelector = 0xFF; break;
				case '#': gameSelector = 0xFF; break;
				case '1' : gameSelector = 0x01; break;
				case '2' : gameSelector = 0x02; break;
				case '3' : gameSelector = 0x03; break;
				case '4' : gameSelector = 0x04; break;
				case '5' : gameSelector = 0x05; break;
				case '6' : gameSelector = 0x06; break;
				case '7' : gameSelector = 0x07; break;
				case '8' : gameSelector = 0x08; break;
				case '9' : gameSelector = 0x09; break;
				case '0' : gameSelector = 0x00; break;
			}
			break;
		}
	}
}
enum States_{Start_2, Wait_2, Play} musicState;
void Music_Tick()
{
	switch(musicState) // transitions
	{
		case Start_2:
		{
			musicState = Wait_2;
			break;
		}
		case Wait_2:
		{
			musicState = Play;
		}
		case Play:
		{
			musicState = Play;
		}
		default:
		break;
	}
	switch(musicState) // state actions
	{
		case Start_2:
		break;
		case Wait_2:
		{
			cont = 0;
			count = 0;
			break;
		}
		case Play:
		if(danceTime[cont] > count)
		{
			set_PWM(danceRev[cont]);
			++count;
			break;
		}
		else
		{
			count = 0;
			++cont;
			break;
		}
	}
}


enum M_STATES{M_START, M_WAIT, M_TRANSMIT}m_state;
void MasterTick()
{
	switch(m_state) //transitions
	{
		case M_START:
		KeyTemp = '\0';
		m_state = M_WAIT;
		break;
		
		case M_WAIT:
		if(KeyTemp != '\0')
		{
			m_state = M_TRANSMIT;
			break;
		}
		else
		{
			m_state = M_WAIT;
			break;
		}
		
		case M_TRANSMIT:
			KeyTemp = '\0';
			m_state = M_WAIT;
			break;
	
		
		default:
		break;
	}
	switch(m_state) //state actions
	{
		case M_START:
		KeyTemp = '\0';
		break;
		
		case M_WAIT:
		KeyTemp = GetKeypadKey();
		if(KeyTemp == '2')
		{
			gameSelector = 0x02;
		}
		else if(KeyTemp == '3')
		{
			gameSelector = 0x03;
		}
		else if(KeyTemp == '4')
		{
			gameSelector = 0x04;
		}
		else if(KeyTemp == '*')
		{
			gameSelector = 0xFF;
		}
		
		break;
		
		case M_TRANSMIT:
		sendData(gameSelector , 1);
		break;
		
		default:
		break;
	}
}


int main(void)
{
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;
	gameSelector = 0xFF;
	LCD_init();
	initUSART(1);
	TimerSet(1);
	TimerOn();
	
	while (1)
	{
		if(SandM_period >= 10)
		{
			MasterTick();
			SandM_period = 0;
		}
		// 		if(musicPeriod > 40)
		// 		{
		// 			if(gameSelector == 0xFF)
		// 			{
		// 				Music_Tick();
		// 			}
		// 			musicPeriod = 0;
		// 		}
		
		if(mainPeriod > 500)
		{
			if(gameSelector == 0xFF)
			{
				Tick();
				menuInput();
			}
			mainPeriod = 0;
		}
		
		if(simonPeriod > 40)
		{
			if(gameSelector == 7)
			{
				SimonSays_Tick();
			}
			simonPeriod = 0;
		}
		++SandM_period;
		++mainPeriod;
		++simonPeriod;
		/*		++musicPeriod;*/
		while(!TimerFlag);
		TimerFlag = 0;
	}
}

