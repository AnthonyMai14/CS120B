# Lab 1

*1. Garage open at night-- A garage door sensor connects to PA0 (1 means door open), and a light sensor connects to PA1 (1 means light is sensed). Write a program that illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night. In this laboratory exercise, we will not actually use sensors or LEDS; just use the simulator and set inputs to 0 and 1 as needed and observe the output.*

*2. Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of a four-space parking lot. Write a program that outputs in binary on port C the number of available spaces (Hint: declare a variable "unsigned char cntavail"; you can assign a number to a port as follows: PORTC = cntavail;).*

*3. Extend the program in Exercise 2 to still write the available spaces number, but only to PC3…PC0, and to set PC7 to 1 if the lot is full.*

*4. Count the number of 1s on ports A and B and output that number on port C.*

*5. A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.  (The example below shows the display for a fuel level of 3).  In this laboratory exercise, we will not actually use LEDS; just use the simulator and set inputs to 0 and 1 as needed and observe the output.*

*6. In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is 1 if a driver is seated, and PA6 is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.*
