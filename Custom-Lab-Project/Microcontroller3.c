/*	Kent Arroyo			karro001@ucr.edu
 *	Francisco Munoz		fmuno003@ucr.edu
 *	Lab Section: 022
 *	Assignment: Custom Lab Project
 *  I acknowledge all content contained herein, excluding template or example code, is my own original work.
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
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
#include </Users/munoz/Desktop/header files/LEDMATRIX.c>
#include </Users/munoz/Desktop/header files/Arrows.c>
#include </Users/munoz/Desktop/header files/usart.h>

double Snek[115] = {E5, E5, B4, C5, D5, C5, B4, A4, A4, C5, E5, D5, C5, B4, B4, C5, D5, E5, C5, A4, A4, 0,
	D5, F5, A5, G5, F5, E5, C5, E5, D5, C5, B4, B4, C5, D5, E5, C5, A4, A4, 0,
	E4, C4, D4, B3, C4, A3, G_3, B3, E4, C4, D4, B3, C4, E4, A4, A4, G_4,
	E5, B4, C5, D5, C5, B4, A4, A4, C5, E5, D5, C5, B4, B4, C5, D5, E5, C5, A5, A5, 0,
	D5, F5, A5, G5, F5, E5, C5, E5, D5, C5, B4, B4, C5, D5, E5, C5, A4, A4, 0,
E4, C4, D4, B3, C4, A3, G_3, B3, E4, C4, D4, B3, C4, E4, A4, A4, G_4}; // tempo = 140 beats per minute
char SnekTime[115] = {2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 3, 1, 2, 1, 1, 3,
	1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2,
	2, 8, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 3, 1, 2, 1, 1,
	3, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 2,
2, 2, 8};
double Menu[110] = {0, C_5, B4, C_5, F_4, 0, D5, C_5, D5, C_5, B4, 0, D5, C_5, D5, F_4, 0, B4, A4, B4, A4, G_4, B4, 0, C_5,
	B4, C_5, F_4, 0, D5, C_5, D5, C_5, B4, 0, D5, C_5, D5, F_4, 0, B4, A4, B4, A4, G_4, B4, 0, C_5, B4,
	C_5, F_4, 0, D5, C_5, D5, C_5, B4, 0, D5, C_5, D5, F_4, 0, B4, A4, B4, A4, G_4, B4, 0, C_5, B4, C_5,
	F_4, 0, D5, C_5, D5, C_5, B4, 0, D5, C_5, D5, F_4, 0, B4, A4, B4, A4, G_4, B4, A4, G_4, A4, B4, A4, B4,
C_5, B4, A4, G_4, F_4, D5, C_5, C_5, D5, C_5, B4, C_5}; // tempo = 120 beats per minute
char MenuTime[110] = {6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 4, 6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 2, 2, 6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 4,
	6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 2, 2, 6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 4, 6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 2, 2, 6,
1, 1, 4, 4, 6, 1, 1, 2, 2, 4, 6, 1, 1, 4, 4, 6, 1, 1, 2, 2, 2, 2, 6, 1, 1, 6, 1, 1, 2, 2, 2, 2, 4, 4, 8, 1, 1, 1, 1, 16};
double TunRun[77] = {C5, C5, C5, D4, C5, 0, C5, D4, C5, D4, C5, B4, B4, B4, C4, B4, 0, B4, C4, B4, C4, B4,
	C5, C5, C5, D4, C5, 0, C5, D4, C5, D4, C5, B4, B4, B4, C4, B4, 0, B4, C4, B4, C4, B4,
	C5, C5, C5, D4, C5, 0, C5, D4, C5, D4, C5, B4, B4, B4, C4, B4, 0, B4, C4, B4, C4, B4,
C5, C5, C5, D4, C5, 0, C5, D4, C5, D4, C5}; // tempo = 300 beats per minute
char TunTunTime[77] = {2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2,
	1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2,
1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2};
double DDR[303] = {F5, E5, D_5, E5, D_5, D5, D_5, D5, C_5, D5, C_5, C5, B4, D_4, D4, D_4, D4, C_4, F_4, F4, E4, F4,
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
char DDRTime[304] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 14, 2, 8, 6, 2, 14, 2, 8, 6, 2, 14, 2, 8, 6, 2, 14, 2, 8, 6,
	4, 4, 4, 2, 4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 8, 4, 4, 4, 2, 4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 4, 2, 2, 4, 1, 1, 1, 1,
	4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4,
	4, 4, 4, 4, 4, 4, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 16, 16, 4, 12, 4,
	12, 32, 4, 12, 8, 8, 60, 1, 1, 1, 1, 16, 16, 16, 10, 6, 4, 4, 4, 2, 4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 8, 4, 4, 4, 2,
	4, 4, 2, 2, 2, 2, 2, 8, 8, 8, 4, 2, 2, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 4,
	1, 1, 1, 1, 4, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 4, 4, 4, 4, 4, 4, 4, 4, 16, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 16, 16, 4, 12, 4, 12, 32, 4, 12, 8, 8, 60, 1, 1, 1, 1, 16, 16, 16, 10, 6};

unsigned char receiveData(unsigned char port)
{
	unsigned char temp1 = 2;
	while(1)
	{
		if(USART_HasReceived(port))
		{
			temp1 = USART_Receive(port);
			return temp1;
		}
	}
}

unsigned char gameSelector = 0xFF;
unsigned char SandM_period;

unsigned short count = 0;
unsigned short cnt = 0;

enum TR_STATES{TR_START, TR_PLAY}tr_state;
unsigned short TR_bpm = 80; //CONVERT BPM and set it equal to it
unsigned short TR_count = 0;
unsigned short TR_cnt = 0;
void TunRunBGM()
{
	switch(tr_state) //transitions
	{
		case TR_START:
			TR_cnt = 0;
			TR_count = 0;
			tr_state = TR_PLAY;
			break;
			
		case TR_PLAY:
			tr_state = TR_PLAY;
			break;
		
		default:
			break;
	}
	
	switch(tr_state) //state actions
	{
		case TR_START:
			break;
			
		case TR_PLAY:
			if(TunTunTime[TR_cnt] > TR_count)
			{
				set_PWM(TunRun[TR_cnt]);
				++TR_count;
				break;
			}
			else
			{
				TR_count = 0;
				++TR_cnt;
				if(TR_cnt >= 77)
				{
					TR_cnt = 0;
				}
				break;
			}
	}
}

enum Snek_STATES{SNEK_START, SNEK_PLAY}snek_state;
unsigned short Snek_bpm = 100; //convert bpm and set it equal
unsigned short Snek_count = 0;
unsigned short Snek_cnt = 0;
void SNEK_BGM()
{
	switch(snek_state) //transitions
	{
		case SNEK_START:
		Snek_cnt = 0;
		Snek_count = 0;
		snek_state = SNEK_PLAY;
		break;
		
		case SNEK_PLAY:
		snek_state = SNEK_PLAY;
		break;
		
		default:
		break;
	}
	
	switch(snek_state) //state actions
	{
		case SNEK_START:
		break;
		
		case SNEK_PLAY:
		if(SnekTime[Snek_cnt] > Snek_count)
		{
			set_PWM(Snek[Snek_cnt]);
			++Snek_count;
			break;
		}
		else
		{
			Snek_count = 0;
			++Snek_cnt;
			if(Snek_cnt >= 115)
			{
				Snek_cnt = 0;
			}
			break;
		}
	}
}

enum DDR_STATES{DDR_START, DDR_PLAY}ddr_state;
unsigned short DDR_bpm = 100; //convert bpm
unsigned short DDR_count = 0;
unsigned short DDR_cnt = 0;
void DDR_BGM()
{
	switch(ddr_state) //transitions
	{
		case DDR_START:
		DDR_cnt = 0;
		DDR_count = 0;
		ddr_state = DDR_PLAY;
		break;
		
		case DDR_PLAY:
		ddr_state = DDR_PLAY;
		break;
		
		default:
		break;
	}
	
	switch(ddr_state) //state actions
	{
		case DDR_START:
		break;
		
		case DDR_PLAY:
		if(DDRTime[DDR_cnt] > DDR_count)
		{
			set_PWM(DDR[DDR_cnt]);
			++DDR_count;
			break;
		}
		else
		{
			DDR_count = 0;
			++DDR_cnt;
			if(DDR_cnt >= 303)
			{
				DDR_cnt = 0;
			}
			break;
		}
	}
}

enum MENU_STATES{MENU_START, MENU_PLAY}menu_state;
unsigned short MENU_bpm = 80; //convert bpm
unsigned short MENU_count = 0;
unsigned short MENU_cnt = 0;
void MENU_BGM()
{
	switch(menu_state) //transitions
	{
		case MENU_START:
		MENU_cnt = 0;
		MENU_count = 0;
		menu_state = MENU_PLAY;
		break;
		
		case MENU_PLAY:
		menu_state = MENU_PLAY;
		break;
		
		default:
		break;
	}
	
	switch(menu_state) //state actions
	{
		case MENU_START:
		break;
		
		case MENU_PLAY:
		if(MenuTime[MENU_cnt] > MENU_count)
		{
			set_PWM(Menu[MENU_cnt]);
			++MENU_count;
			break;
		}
		else
		{
			MENU_count = 0;
			++MENU_cnt;
			if(MENU_cnt >= 110)
			{
				MENU_cnt = 0;
			}
			break;
		}
	}
}
int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	TimerSet(1);
	TimerOn();
	PWM_on();
	initUSART(1);
	gameSelector = 0xFF;
	unsigned short Tr_period = 0;
	unsigned short Snek_period = 0;
	unsigned short DDR_period = 0;
	unsigned short Menu_period = 0;
	
	while(1)
	{
		if(SandM_period >= 10)
		{
			if(USART_HasReceived(1)){
				gameSelector = receiveData(1);
			}
			SandM_period = 0;
		}
		++SandM_period;
		
		if(gameSelector == 0x02)
		{
			if(Tr_period >= TR_bpm)
			{
				TunRunBGM();
				Tr_period = 0;
			}
			++Tr_period;
			
		}
		
		else if(gameSelector == 0x03)
		{
			if(Snek_period >= Snek_bpm)
			{
				SNEK_BGM();
				Snek_period = 0;
			}
			++Snek_period;
		}
		
		else if(gameSelector == 0x04)
		{
			if(DDR_period >= DDR_bpm)
			{
				DDR_BGM();
				DDR_period = 0;
			}
			++DDR_period;
		}
		
		else if(gameSelector == 0xFF)
		{
			if(Menu_period >= MENU_bpm)
			{
				MENU_BGM();
				Menu_period = 0;
			}
			++Menu_period;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
}