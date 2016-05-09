/* Partner 1 Name & E-mail: Francisco Munoz		fmuno003@ucr.edu
* Partner 2 Name & E-mail: Kent Arroyo			karro001@ucr.edu
* Lab Section: 022
* Assignment: Lab #2 Exercise #1
* Exercise Description: 
*	A car has a fuel-level sensor that sets PA3-PA0 to a value between
*	0 and 15. A series of LEDs connected to PB5-PB0 should light to 
*	to graphically indicated the fuel level.
* 
* I acknowledge all content contained herein, excluding template or example
* code, is my own original work.
*/


#include <avr/io.h>

int main(void)
{
   
   DDRA = 0x00; PORTA = 0xFF;
   DDRC = 0xFF; PORTC = 0x00;
   
   unsigned char fuelLevel = 0x00;
   unsigned char sensor = 0x00;
   
   while(1)
   {
	   fuelLevel = PINA;
	   if((fuelLevel & 0x00) == 0x00)
	   {
		   sensor = 0x40;
	   }
	   if((fuelLevel & 0x01) == 0x01)
	   {
		   sensor = 0x60;
	   }
	   if((fuelLevel & 0x02) == 0x02)
	   {
		   sensor = 0x60;
	   }
	   if((fuelLevel & 0x03) == 0x03)
	   {
		   sensor = 0x70;
	   }
	   if((fuelLevel & 0x04) == 0x04)
	   {
		   sensor = 0x70;
	   }
	   if((fuelLevel & 0x05) == 0x05)
	   {
		   sensor = 0x38;
	   }
	   if((fuelLevel & 0x06) == 0x06)
	   {
		   sensor = 0x38;
	   }
	   if((fuelLevel & 0x07) == 0x07)
	   {
		   sensor = 0x3C;
	   }
	   if((fuelLevel & 0x08) == 0x08)
	   {
		   sensor = 0x3C;
	   }
	   if((fuelLevel & 0x09) == 0x09)
	   {
		   sensor = 0x3C;
	   }
	   if((fuelLevel & 0x0A) == 0x0A)
	   {
		   sensor = 0x3E;
	   }
	   if((fuelLevel & 0x0B) == 0x0B)
	   {
		   sensor = 0x3E;
	   }
	   if((fuelLevel & 0x0C) == 0x0C)
	   {
		   sensor = 0x3E;
	   }
	   if((fuelLevel & 0x0D) == 0x0D)
	   {
		   sensor = 0x3F;
	   }
	   if((fuelLevel & 0x0E) == 0x0E)
	   {
		   sensor = 0x3F;
	   }
	   if((fuelLevel & 0x0F) == 0x0F)
	   {
		   sensor = 0x3F;
	   }
	   PORTC = sensor;
	   sensor = 0x00;
	   fuelLevel = 0x00;
   }
}