# Lab 1

*1. Garage open at night-- A garage door sensor connects to PA0 (1 means door open), and a light sensor connects to PA1 (1 means light is sensed). Write a program that illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night. In this laboratory exercise, we will not actually use sensors or LEDS; just use the simulator and set inputs to 0 and 1 as needed and observe the output.*

*2. Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of a four-space parking lot. Write a program that outputs in binary on port C the number of available spaces (Hint: declare a variable "unsigned char cntavail"; you can assign a number to a port as follows: PORTC = cntavail;).*

*3. Extend the program in Exercise 2 to still write the available spaces number, but only to PC3…PC0, and to set PC7 to 1 if the lot is full.*

*4. Count the number of 1s on ports A and B and output that number on port C.*

*5. A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.  (The example below shows the display for a fuel level of 3).  In this laboratory exercise, we will not actually use LEDS; just use the simulator and set inputs to 0 and 1 as needed and observe the output.*

*6. In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is 1 if a driver is seated, and PA6 is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.*

*7. An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg. Can you also devise a way to inform the ride operator of the approximate weight using the remaining bits on D? (Interesting note: Disneyland recently redid their "It's a Small World" ride because the average passenger weight has increased over the years, causing more boats to get stuck on the bottom).*

*(Hint: Use two intermediate variables to keep track of weight, one of the actual value and another being the shifted weight. Binary shift right by one is the same as dividing by two and binary shift left by one is the same as multiplying by two.)*

*8.Read an 8-bit value on PA7..PA0 and write that value on PB3..PB0PC7..PC4. That is to say,  take the upper nibble of PINA and map it to the lower nibble of PORTB, likewise take the lower nibble of PINA and map it to the upper nibble of PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).*

*9. A car's passenger-seat weight sensor outputs a 9-bit value (ranging from 0 to 511) and connects to input PD7..PD0PB0 on the microcontroller. If the weight is equal to or above 70 pounds, the airbag should be enabled by setting PB1 to 1. If the weight is above 5 but below 70, the airbag should be disabled and an "Airbag disabled" icon should light by setting PB2 to 1. (Neither B1 nor B2 should be set if the weight is 5 or less, as there is no passenger).*
