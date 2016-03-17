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

unsigned char QUIT;
unsigned char j = 0x00;
unsigned char Y1 = 0x00;
unsigned char y2 = 0x00;
unsigned short TR_TEMP = 0;
unsigned char TR_LOSE = 0x00;
unsigned char TRLINES_period = 0;
unsigned char TRuser_period = 0;
unsigned char gameSelector = 0x03;

unsigned char arrow;
unsigned char arrows_LOSE = 0x00;
unsigned char k = 0x00;
unsigned char QUIT = 0x00;
unsigned short arrows_TEMP = 0;
unsigned char checker = 0;
unsigned char chances = 0x03;
unsigned short arrows_period = 0;
unsigned char arrows_inputP = 0;
unsigned char arrowsPeriod = 0;

unsigned short snakeJoystick = 0;	
unsigned short joystick = 0;
unsigned short body = 0;
unsigned char SNAKE_QUIT = 0x00;
unsigned char SNAKE_LOSE = 0x00;
unsigned short SNAKE_TEMP = 0;
unsigned char l = 0x00;
unsigned char SNEK_SIZE = 0;
unsigned short body_period = 600;
unsigned char bitA = 0x00;
unsigned char bitB = 0x00;
unsigned char movement = 0x01;

unsigned short SandM_period = 0;

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

void InitADC()
{
	ADMUX=(1<<REFS0);   //set seventh bit of ADMUX to 1 so reference voltage is 5v
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //rescalar div factor =128
}
void convert(){
	ADCSRA |=(1<<ADSC);//start ADC conversion
	while ( !(ADCSRA & (1<<ADIF)));//wait till ADC conversion
	
}
typedef struct LINE
{
	unsigned char start_x;
	unsigned char off_y1;
	unsigned char off_y2;
}LINE;

LINE CurrLine;
LINE L_3F;
LINE L_9F;
LINE L_CF;
LINE L_E7;
LINE L_F3;
LINE L_F9;
LINE L_FC;
typedef struct SNEK
{
	signed char x;
	signed char y;
}SNEK;
SNEK Snek_head;

void LINE_init()
{
	L_3F.start_x = 0;
	L_3F.off_y2 = 7;
	L_3F.off_y1 = 6;
	
	L_9F.start_x = 0;
	L_9F.off_y2 = 6;
	L_9F.off_y1 = 5;
	
	L_CF.start_x = 0;
	L_CF.off_y2 = 5;
	L_CF.off_y1 = 4;
	
	L_E7.start_x = 0;
	L_E7.off_y2 = 4;
	L_E7.off_y1 = 3;
	
	L_F3.start_x = 0;
	L_F3.off_y2 = 3;
	L_F3.off_y1 = 2;
	
	L_F9.start_x = 0;
	L_F9.off_y2 = 2;
	L_F9.off_y1 = 1;
	
	L_FC.start_x = 0;
	L_FC.off_y2 = 1;
	L_FC.off_y1 = 0;
}
void SetLINE(LINE s)
{
	CurrLine.start_x = s.start_x;
	CurrLine.off_y2 = s.off_y2;
	CurrLine.off_y1 = s.off_y1;
	return;
}
LINE Generate_RanLINE()
{
	unsigned char ran = rand() % 7;
	if(ran == 0)
	{return L_3F;}
	
	else if(ran == 1)
	{return L_9F;}
	
	else if(ran == 2)
	{return L_CF;}
	
	else if(ran == 3)
	{return L_E7;}
	
	else if(ran == 4)
	{return L_F3;}
	
	else if (ran == 5)
	{return L_F9;}
	
	else
	{return L_FC;}
}
char Generate_RanARROW()
{
	unsigned char ran = rand() % 4;
	if(ran == 0)
	{
		Up_arrow();
		return 0x00;
	}
	else if(ran == 1)
	{
		Right_arrow();
		return 0x01;
	}
	else if(ran == 2)
	{
		Down_arrow();
		return 0x02;
	}
	else
	{
		Left_arrow();
		return 0x03;
	}
}
char generateXPosition()
{
	unsigned char randomNum = 0x03;
	while(randomNum == 3)
	{
		randomNum = rand() % 8;
	}
	return randomNum;
}
char generateYposition()
{
	unsigned char randomNum = 0x03;
	while(randomNum == 3)
	{
		randomNum = rand() % 8;
	}
	return randomNum;
}
void Generate_RanSnack()
{
	unsigned char match = 1;
	while(match == 1)
	{
		bitA = generateXPosition();
		bitB = generateYposition();
		if(bitA != Snek_head.x && bitB != Snek_head.y)
		{
			match = 0;
		}
		else
		{
			match = 1;
		}
	}
	return;
}

void TUNRUN_LINES();
enum TRLINES_States {TRL_START, TRL_WAIT, TRL_PLAY, TRL_PAUSE, TRL_CHECK} Lines_state;
void TunRun_Input();
enum TRI_States{TRI_START, TRI_CHECK, TRI_SET, TRI_WAIT} TRI_state;
void TunRun_JoyStk();
enum TRJ_States{TRJ_START, TRJ_WAIT, TRJ_PLAY, TRJ_PAUSE}TRJ_state;
void TunRun_ChkLoss();
enum TRC_States{TRC_START, TRC_WAIT, TRC_PLAY, TRC_PAUSE}TRC_state;

void DDR_arrows();
enum Arrows_States {ARROWS_START, ARROWS_WAIT, ARROWS_PLAY, ARROWS_PAUSE}Arrows_state;
void DDR_Input();
enum DDRI_States{DDR_START, DDR_CHECK, DDR_SET, DDR_WAIT} DDRI_state;
void DDR_JoyStk();
enum DDRJ_states{DDRJ_START, DDRJ_WAIT, DDRJ_PLAY, DDRJ_PAUSE}DDRJ_state;
void DDR_ChkLoss();
enum DDRC_States{DDRC_START, DDRC_WAIT, DDRC_PLAY, DDRC_PAUSE}DDRC_state;

void Snake_Input();
enum SnakeStates{SNAKE_START, SNAKE_WAIT, SNAKE_CHECK, SNAKE_SET} snakeState;
void SnakeBody();
enum Snake_States{BODY_START, BODY_WAIT, BODY_PLAY, BODY_PAUSE, BODY_CHECK} bodyState;
void Snake_JoyStk();
enum SnakeJ_States{SJ_START, SJ_WAIT, SJ_PLAY, SJ_PAUSE} SJ_STATE;
void Snake_Movement();
enum SnakeM_States{SM_Start, SM_WAIT, SM_CHECK, SM_PAUSE} moveState;
	
void MasterTick();
enum M_STATES{M_START, M_WAIT, M_TRANSMIT, M_PAUSE}m_state;
void SlaveTick();
enum S_STATES{S_START, S_RECEIVE}s_state;

int main(void)
{
		DDRA = 0xF0; PORTA = 0x0F;
		DDRB = 0x00;  PORTB = 0xFF;
		DDRC = 0xFF; PORTC = 0x00;
		DDRD = 0xFF; PORTD = 0x00;
		gameSelector = 0xFF;
		LINE_init();
	    TimerSet(1);
	    TimerOn();
	    srand(0);
	    InitADC();
		initUSART(1);
		
    while (1) 
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
			if(TRLINES_period >= 9)
			{	       
				TRLINES_period = 0;
			}
			if(TRuser_period >= 80)
			{
				TunRun_ChkLoss();
				TunRun_JoyStk();
				TUNRUN_LINES();
				TunRun_Input();
				TRuser_period = 0;
			}
				displayMatrix();
				++TRLINES_period;
				++TRuser_period;
		}
		if(gameSelector == 0x04)
		{
			if(arrows_period >= 750)
			{
				DDR_arrows();
				if((arrow == 0) || (arrow == 2))
				{
					ADMUX = 0x40;
				}
				else
				{
					ADMUX = 0x41;
				}
				arrows_period = 0;
			}
			if(arrows_inputP >= 20)
			{
				DDR_Input();
				DDR_JoyStk();
				arrows_inputP = 0;
			}
			if(arrowsPeriod >= 250)
			{
				DDR_ChkLoss();
				arrowsPeriod = 0;
			}
			displayMatrix();
			++arrows_inputP;
			++arrows_period;
			++arrowsPeriod;
		}
		if(gameSelector == 0x03)
		{
			if(snakeJoystick > 30)
			{
				Snake_JoyStk();
				Snake_Input();
				snakeJoystick = 0;
			}
			if(body > body_period)
			{
				SnakeBody();
				Snake_Movement();
				body = 0;
			}
			++snakeJoystick;
			++joystick;
			++body;
			displayMatrix();
		}
		while(!TimerFlag);
		TimerFlag = 0;
    }
}

void SlaveTick()
{
	switch(s_state) // transitions
	{
		case S_START:
		s_state = S_RECEIVE;
		break;
		
		case S_RECEIVE:
		s_state = S_RECEIVE;
		break;
		
		default:
		break;
	}
	
	switch(s_state) //state actions
	{
		case S_START:
		break;
		
		case S_RECEIVE:
		gameSelector = receiveData(0);
		break;
		
		default:
		break;
	}
}
// void MasterTick()
// {
// 	switch(m_state) //transitions
// 	{
// 		case M_START:
// 			m_state = M_WAIT;
// 			break;
// 		
// 		case M_WAIT:
// 			if((~PINB & 0x04) == 0x04)
// 			{
// 				m_state = M_TRANSMIT;
// 				break;
// 			}
// 			else
// 			{
// 				m_state = M_WAIT;
// 				break;
// 			}
// 		
// 		case M_TRANSMIT:
// 			m_state = M_PAUSE;
// 			break;
// 		
// 		case M_PAUSE:
// 			if((~PINB & 0x04) != 0x00)
// 			{
// 				m_state = M_PAUSE;
// 				break;
// 			}
// 			else
// 			{
// 				m_state = M_WAIT;
// 				break;
// 			}
// 		
// 		default:
// 		break;
// 	}
// 	switch(m_state) //state actions
// 	{
// 		case M_START:
// 			break;
// 		
// 		case M_WAIT:
// 			break;
// 		
// 		case M_TRANSMIT:
// 			gameSelector = 0xFF;
// 			sendData(gameSelector , 0);
// 			break;
// 		
// 		default:
// 			break;
// 	}
// }

void TUNRUN_LINES()
{
	switch(Lines_state) //transitions
	{
		case TRL_START:
		Lines_state = TRL_WAIT;
		break;
		case TRL_WAIT:
		if((~PINB & 0x01) == 0x00)
		{
			Lines_state = TRL_WAIT; break;
		}
		else
		{
			Lines_state = TRL_PLAY; break;
		}
		
		case TRL_PLAY:
		if(QUIT == 1 || TR_LOSE == 1)
		{
			Lines_state = TRL_PAUSE; break;
		}
		else
		{
			Lines_state = TRL_CHECK; break;
		}
		
		case TRL_CHECK:
		if(TR_LOSE == 1)
		{
			Lines_state = TRL_PAUSE; break;
		}
		else
		{
			Lines_state = TRL_PLAY; break;
		}
		
		case TRL_PAUSE:
		{
			if((~PINB & 0x01) == 0)
			{
				Lines_state = TRL_WAIT; break;
			}
			else
			{
				Lines_state = TRL_PAUSE; break;
			}
		}
		
		default:
		break;
	}
	
	switch(Lines_state) //state actions
	{
		case TRL_START:
		break;
		
		case TRL_WAIT:
		clearLED();
		SetLINE(L_E7);
		for(unsigned char a = 0; a < 8; ++a)
		{
			turnOnLED(CurrLine.start_x, a);
		}
		turnOffLED(CurrLine.start_x, CurrLine.off_y1);
		turnOffLED(CurrLine.start_x, CurrLine.off_y2);
		Y1 = 3;
		y2 = 4;
		turnOnLED(7, Y1);
		turnOnLED(7, y2);
		break;
		
		case TRL_PLAY:
		for(unsigned char a = 0; a < 8; ++a)
		{
			if(CurrLine.start_x > 0)
			{
				turnOffLED(CurrLine.start_x - 1, a);
			}
			else if(CurrLine.start_x == 0)
			{
				turnOffLED(7,a);
			}
			turnOnLED(CurrLine.start_x, a);
		}
		turnOffLED(CurrLine.start_x, CurrLine.off_y1);
		turnOffLED(CurrLine.start_x, CurrLine.off_y2);
		break;
		
		case TRL_CHECK:
		++CurrLine.start_x;
		if(CurrLine.start_x > 7)
		{
			SetLINE(Generate_RanLINE());
		}
		break;
		
		case TRL_PAUSE:
		break;
		
		default:
		break;
	}
}
void TunRun_Input()
{
	switch(TRI_state) //state transitions
	{
		case TRI_START:
		TRI_state = TRI_WAIT; break;
		
		case TRI_WAIT:
		{
			if((~PINB & 0x02) == 0x00)
			{
				TRI_state = TRI_WAIT; break;
			}
			else
			{
				TRI_state = TRI_CHECK; break;
			}
		}
		
		case TRI_CHECK:
		{
			if((~PINB & 0x02) == 0x00)
			{
				TRI_state = TRI_WAIT; break;
			}
			else if(j <= 10)
			{
				TRI_state = TRI_CHECK; break;
			}
			else if(j > 10)
			{
				j = 0;
				TRI_state = TRI_SET; break;
			}
		}
		
		case TRI_SET:
		{
			if((~PINB & 0x02) == 0x00)
			{
				TRI_state = TRI_WAIT;
				QUIT = 0x00;
				break;
			}
			else
			{
				TRI_state = TRI_SET; break;
			}
		}
		
		default:
		break;
	}
	
	switch(TRI_state) //state actions
	{
		case TRI_START:
		break;
		
		case TRI_WAIT:
		QUIT = 0;
		break;
		
		case TRI_CHECK:
		++j;
		break;
		
		case TRI_SET:
		QUIT = 1;
		break;
		
		default:
		break;
	}
}
void TunRun_JoyStk()
{
	
	switch(TRJ_state) //transitions
	{
		case TRJ_START:
		TRJ_state = TRJ_WAIT; break;
		
		case TRJ_WAIT:
		if((~PINB & 0x01) == 0x00)
		{
			TRJ_state = TRJ_WAIT; break;
		}
		else
		{
			TRJ_state = TRJ_PLAY; break;
		}
		
		case TRJ_PLAY:
		if(QUIT == 1 || TR_LOSE == 1)
		{
			TRJ_state = TRJ_PAUSE; break;
		}
		else
		{
			TRJ_state = TRJ_PLAY; break;
		}
		
		case TRJ_PAUSE:
		if((~PINB & 0x01) == 0x00)
		{
			TRJ_state = TRJ_WAIT; break;
		}
		else
		{
			TRJ_state = TRJ_PAUSE; break;
		}
		
		default:
		break;
	}
	
	switch(TRJ_state) //state actions
	{
		case TRJ_START:
		break;
		
		case TRJ_WAIT:
		break;
		
		case TRJ_PLAY:
		convert();
		TR_TEMP = ADC;
		if(TR_TEMP > 600)
		{
			if(Y1 <= 0);
			
			else
			{
				turnOffLED(7, Y1);
				turnOffLED(7, y2);
				--Y1;
				--y2;
			}
		}
		else if(TR_TEMP < 350)
		{
			if(y2 >= 7);
			
			else
			{
				turnOffLED(7, Y1);
				turnOffLED(7, y2);
				++Y1;
				++y2;
			}
			
		}
		turnOnLED(7, Y1);
		turnOnLED(7, y2);
		break;
		
		case TRJ_PAUSE:
		break;
		
		default:
		break;
		
		
	}
}
void TunRun_ChkLoss()
{
	switch(TRC_state) // transitions
	{
		case TRC_START:
		TRC_state = TRC_WAIT; break;
		
		case TRC_WAIT:
		if((~PINB & 0x01) == 0x00)
		{
			TRC_state = TRC_WAIT; break;
		}
		else
		{
			TRC_state = TRC_PLAY; break;
		}
		
		case TRC_PLAY:
		if(QUIT == 1 || TR_LOSE == 1)
		{
			TRC_state = TRC_PAUSE;
			Lines_state = TRL_PAUSE;
			TRJ_state = TRJ_PAUSE;
			break;
		}
		else
		{
			TRC_state = TRC_PLAY; break;
		}
		
		case TRC_PAUSE:
		if((~PINB & 0x01) == 0x00)
		{
			TRC_state = TRC_WAIT; break;
			
		}
		else
		{
			TRC_state = TRC_PAUSE; break;
		}
		
		default:
		break;
	}
	
	switch(TRC_state) //state actions
	{
		case TRC_START:
		break;
		
		case TRC_WAIT:
		TR_LOSE = 0;
		break;
		
		case TRC_PLAY:
		if(CurrLine.start_x == 7)
		{
			if(Y1 != CurrLine.off_y1 || y2 != CurrLine.off_y2)
			{
				TR_LOSE = 1;
			}
		}
		break;
		
		case TRC_PAUSE:
		break;
		
		default:
		break;
		
	}
}

void DDR_arrows()
{
	switch(Arrows_state) //transitions
	{
		case ARROWS_START:
		{
			Arrows_state = ARROWS_WAIT;
			break;
		}
		case ARROWS_WAIT:
		{
			if((~PINB & 0x01) == 0x00)
			{
				Arrows_state = ARROWS_WAIT; 
				break;
			}
			else
			{
				Arrows_state = ARROWS_PLAY; 
				break;
			}			
		}
		case ARROWS_PLAY:
		{
			if(QUIT == 1 || arrows_LOSE == 1)
			{
				Arrows_state = ARROWS_PAUSE;
				break;
			}
			else
			{
				Arrows_state = ARROWS_PLAY;
				break;
			}			
		}
		case ARROWS_PAUSE:
		{
			if((~PINB & 0x01) == 0x00)
			{
				Arrows_state = ARROWS_WAIT; 
				break;
			}
			else
			{
				Arrows_state = ARROWS_PAUSE; 
				break;
			}			
		}
		default:
			break;
	}
	switch(Arrows_state) //state actions
	{
		case ARROWS_START:
			break;
		case ARROWS_WAIT:
		{
			clearLED();
			break;		
		}
		case ARROWS_PLAY:
		{
			clearLED();
			arrow = Generate_RanARROW();
			break;			
		}
		case ARROWS_PAUSE:
			break;
		default:
			break;
	}
}
void DDR_Input()
{
	switch(DDRI_state) //state transitions
	{
		case DDR_START:
		{
			DDRI_state = DDR_WAIT;
			break;
		}
		case DDR_WAIT:
		{
			if((~PINB & 0x02) == 0x00)
			{
				DDRI_state = DDR_WAIT; 
				break;
			}
			else
			{
				DDRI_state = DDR_CHECK; 
				break;
			}
		}
		case DDR_CHECK:
		{
			if((~PINB & 0x02) == 0x00)
			{
				DDRI_state = DDR_WAIT; 
				break;
			}
			else if(k <= 10)
			{
				DDRI_state = DDR_CHECK; 
				break;
			}
			else if(k > 10)
			{
				k = 0;
				DDRI_state = DDR_SET; 
				break;
			}
		}
		
		case DDR_SET:
		{
			if((~PINB & 0x02) == 0x00)
			{
				DDRI_state = DDR_WAIT;
				QUIT = 0x00;
				break;
			}
			else
			{
				DDRI_state = DDR_SET; 
				break;
			}
		}
		default:
			break;
	}
	switch(DDRI_state) //state actions
	{
		case DDR_START:
			break;
		
		case DDR_WAIT:
		{
			QUIT = 0;
			break;			
		}
		case DDR_CHECK:
		{
			++k;
			break;			
		}
		case DDR_SET:
		{
			QUIT = 1;
			break;			
		}
		default:
			break;
	}
}
void DDR_JoyStk()
{
	switch(DDRJ_state) //transitions
	{
		case DDRJ_START:
		{
			DDRJ_state = DDRJ_WAIT;
			break;			
		}
		case DDRJ_WAIT:
		{
			if((~PINB & 0x01) == 0x00)
			{
				DDRJ_state = DDRJ_WAIT; 
				break;
			}
			else
			{
				DDRJ_state = DDRJ_PLAY; 
				break;
			}			
		}
		case DDRJ_PLAY:
		{
			if(QUIT == 1 || arrows_LOSE == 1)
			{
				DDRJ_state = DDRJ_PAUSE; 
				break;
			}
			else
			{
				DDRJ_state = DDRJ_PLAY; 
				break;
			}			
		}
		case DDRJ_PAUSE:
		{
			if((~PINB & 0x01) == 0x00)
			{
				DDRJ_state = DDRJ_WAIT;
				break;
			}
			else
			{
				DDRJ_state = DDRJ_PAUSE;
				break;
			}			
		}
		default:
			break;
	}
	switch(DDRJ_state) //state actions
	{
		case DDRJ_START:
			break;
		case DDRJ_WAIT:
			break;
		case DDRJ_PLAY:
		{
			if(arrow == 0 || arrow == 2)
			{
				convert();
				arrows_TEMP = ADC;
				if(arrows_TEMP > 600)
				{checker = 0;}
				else if(arrows_TEMP < 350)
				{checker = 2;}
			}
			else
			{
				convert();
				arrows_TEMP = ADC;
				if(arrows_TEMP > 600)
				{checker = 1;}
				else if(arrows_TEMP < 350)
				{checker = 3;}
			}	
			break;		
		}
		case DDRJ_PAUSE:
			break;
		default:
			break;
	}
}
void DDR_ChkLoss()
{
	switch(DDRC_state) // transitions
	{
		case DDRC_START:
		{
			DDRC_state = DDRC_WAIT;
			break;			
		}
		case DDRC_WAIT:
		{
			if((~PINB & 0x01) == 0x00)
			{
				DDRC_state = DDRC_WAIT; 
				break;
			}
			else
			{
				DDRC_state = DDRC_PLAY; 
				break;
			}
		}
		case DDRC_PLAY:
		{
			if(QUIT == 1 || arrows_LOSE == 1 || chances == 0)
			{
				arrows_LOSE = 1;
				DDRC_state = DDRC_PAUSE;
				Arrows_state = ARROWS_PAUSE;
				DDRJ_state = DDRJ_PAUSE;
				break;
			}
			else
			{
				DDRC_state = DDRC_PLAY; break;
			}
		}
		case DDRC_PAUSE:
		{
			if((~PINB & 0x01) == 0x00)
			{
				DDRC_state = DDRC_WAIT; 
				break;
				
			}
			else
			{
				DDRC_state = DDRC_PAUSE; 
				break;
			}
		}
		default:
			break;
	}
	switch(DDRC_state) //state actions
	{
		case DDRC_START:
			break;
		case DDRC_WAIT:
		{
			arrows_LOSE = 0;
			chances = 3;
			break;
		}
		case DDRC_PLAY:
		{
			if(checker == arrow)
			{
				++chances;
				arrows_period = 750;
				if(chances >= 3)
				{
					chances = 3;
				}
			}
			else
			{
				--chances;
			}
			break;
		}
		case DDRC_PAUSE:
			break;
		default:
			break;
	}
}

void Snake_Input()
{
	switch(snakeState)
	{
		case SNAKE_START:
		{
			snakeState = SNAKE_WAIT;
			break;
		}
		case SNAKE_WAIT:
		{
			if((~PINB & 0x02) == 0x00)
			{
				snakeState = SNAKE_WAIT;
				break;
			}
			else
			{
				snakeState = SNAKE_CHECK;
				break;
			}
		}
		case SNAKE_CHECK:
		{
			if((~PINB & 0x02) == 0x00)
			{
				snakeState = SNAKE_WAIT;
				break;
			}
			else if (l <= 10)
			{
				snakeState = SNAKE_CHECK;
				break;
			}
			else if(l > 10)
			{
				l = 0;
				bodyState = BODY_PAUSE;
				SJ_STATE = SJ_PAUSE;
				moveState = SM_PAUSE;
				snakeState = SNAKE_SET;
				break;
			}
		}
		case SNAKE_SET:
		{
			if((~PINB & 0x02) == 0x00)
			{
				snakeState = SNAKE_WAIT;
				SNAKE_QUIT = 0x00;
				break;
			}
			else
			{
				snakeState = SNAKE_SET;
				break;
			}
		}
		default:
		break;
	}
	switch(snakeState)
	{
		case SNAKE_START:
		break;
		case SNAKE_WAIT:
		{
			SNAKE_QUIT = 0;
			break;
		}
		case SNAKE_CHECK:
		{
			++l;
			break;
		}
		case SNAKE_SET:
		{
			SNAKE_QUIT = 1;
			break;
		}
		default:
		break;
	}
}
void SnakeBody()
{
	switch(bodyState)
	{
		case BODY_START:
		{
			bodyState = BODY_WAIT;
			break;
		}
		case BODY_WAIT:
		{
			if((~PINB & 0x01) == 0x01)
			{
				Generate_RanSnack();
				turnOnLED(bitA,bitB);
				bodyState = BODY_PLAY;
				break;
			}
			else
			{
				bodyState = BODY_WAIT;
				break;
			}
		}
		case BODY_PLAY:
		{
			if((SNAKE_QUIT == 1) || (SNAKE_LOSE == 1))
			{
				bodyState = BODY_PAUSE;
				break;
			}
			else
			{
				bodyState = BODY_CHECK;
				break;
			}
		}
		case BODY_CHECK:
		{
			if(SNAKE_LOSE == 1)
			{
				bodyState = BODY_PAUSE;
				break;
			}
			else
			{
				bodyState = BODY_PLAY;
				break;
			}
		}
		case BODY_PAUSE:
		{
			if((~PINB & 0x01) == 0x00)
			{
				bodyState = BODY_WAIT;
				break;
			}
			else
			{
				bodyState = BODY_PAUSE;
				break;
			}
		}
		default:
		break;
	}
	switch(bodyState)
	{
		case BODY_START:
		break;
		case BODY_WAIT:
		{
			clearLED();
			Snek_head.x = 6;
			Snek_head.y = 4;
			turnOnLED(Snek_head.x,Snek_head.y);
			movement = 0x01;
			body_period = 500;
			break;
		}
		case BODY_PLAY:
		{
			turnOffLED(Snek_head.x,Snek_head.y);
			if(movement == 1)
			{
				--Snek_head.x;
			}
			else if(movement == 3)
			{
				++Snek_head.x;
			}
			else if(movement == 4)
			{
				--Snek_head.y;
			}
			else
			{
				++Snek_head.y;
			}
			turnOnLED(Snek_head.x,Snek_head.y);
			break;
		}
		case BODY_CHECK:
		{
			if((bitA == Snek_head.x) && (bitB == Snek_head.y))
			{
				Generate_RanSnack();
				turnOnLED(bitA,bitB);
				++SNEK_SIZE;
				if(SNEK_SIZE == 5)
				{
					SNEK_SIZE = 0;
					if(body_period > 300)
					{
						body_period -= 150;
					}
					else if (body_period <= 100)
					{
						body_period -= 10;
					}
					else if (body_period <= 300)
					{
						body_period -=50;
					}
					
				}
				break;
			}
			break;
		}
		case BODY_PAUSE:
		break;
		default:
		break;
	}
}
void Snake_JoyStk()
{
	switch(SJ_STATE) //transitions
	{
		case SJ_START:
		SJ_STATE = SJ_WAIT; break;
		
		case SJ_WAIT:
		if((~PINB & 0x01) == 0x00)
		{
			SJ_STATE = SJ_WAIT; break;
		}
		else
		{
			SJ_STATE = SJ_PLAY; break;
		}
		
		case SJ_PLAY:
		if(SNAKE_QUIT == 1 || SNAKE_LOSE == 1)
		{
			SJ_STATE = SJ_PAUSE; break;
		}
		else
		{
			SJ_STATE = SJ_PLAY; break;
		}
		
		case SJ_PAUSE:
		if((~PINB & 0x01) == 0x00)
		{
			SJ_STATE = SJ_WAIT; break;
		}
		else
		{
			SJ_STATE = SJ_PAUSE; break;
		}
		
		default:
		break;
	}
	
	switch(SJ_STATE) //state actions
	{
		case SJ_START:
		break;
		
		case SJ_WAIT:
		break;
		
		case SJ_PLAY:
		{
			if(movement == 0x01 || movement == 0x03)
			{
				ADMUX = 0x40; //enable left & right
				convert();
				SNAKE_TEMP = ADC;
				if(SNAKE_TEMP > 600)
				{
					movement = 0x04;
				}
				else if(SNAKE_TEMP < 350)
				{
					movement = 0x02;
				}
				break;
			}
			
			else
			{
				ADMUX = 0x41; //enable up & down
				convert();
				SNAKE_TEMP = ADC;
				if(SNAKE_TEMP > 600)
				{
					movement = 0x03;
				}
				else if(SNAKE_TEMP < 350)
				{
					movement = 0x01;
				}
				break;
			}
			
			case SJ_PAUSE:
			break;
			
			default:
			break;
			
			
		}
	}
}
void Snake_Movement()
{
	switch(moveState)
	{
		case SM_Start:
		{
			moveState = SM_WAIT;
			break;
		}
		
		case SM_WAIT:
		{
			if((~PINB & 0x01) == 0x00)
			{
				moveState = SM_WAIT;
				break;
			}
			else
			{
				moveState = SM_CHECK;
				break;
			}
		}
		case SM_CHECK:
		{
			if(SNAKE_QUIT == 1 || SNAKE_LOSE == 1)
			{
				bodyState = BODY_PAUSE;
				SJ_STATE = SJ_PAUSE;
				moveState = SM_PAUSE;
				break;
			}
			else
			{
				moveState = SM_CHECK;
				break;
			}
		}
		case SM_PAUSE:
		{
			if((~PINB & 0x01) == 0x00)
			{
				moveState = SM_WAIT;
				break;
			}
			else
			{
				moveState = SM_PAUSE;
				break;
			}
		}
		default:
		break;
	}
	switch(moveState)
	{
		case SM_Start:
		break;
		case SM_WAIT:
		{
			SNAKE_LOSE = 0;
			break;
		}
		case SM_CHECK:
		{
			if((Snek_head.x < 0) || (Snek_head.x > 7))
			{
				SNAKE_LOSE = 1; break;
			}
			else if((Snek_head.y < 0) || (Snek_head.y > 7))
			{
				SNAKE_LOSE = 1; break;
			}
			else if (SNEK_SIZE >= 5)
			{
				SNAKE_LOSE = 1; break;
			}
		}
		case SM_PAUSE:
		break;
		default:
		break;
	}
}