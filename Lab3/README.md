# Lab 3

##PART 1
*1. PB0 and PB1 each connect to an LED. PB0's LED is initially on, PB1 is initially off. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off 
PB1's LED and turns on PB0's LED.*

*2. Buttons are connected to PA0 and PA1. Output for PORTC is initially binary value 7. Pressing PA0 increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.*

*3. A household has a digital combination deadbolt lock system on the doorway. The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1. Any other sequence fails to unlock. Pressing a button from inside the house (PA7) locks the door (PB0=0). For debugging purposes, give each state a number, and always write the current state to PORTC (consider using the enum state variable). Be sure to check that only one button is pressed at a time.* 

*4. Extend the above door so that it can also be locked by entering the earlier code.*

*5. Extend the above door to require the 4-button sequence #-X-Y-X rather than the earlier 2-button sequence. To avoid excessive states, store the correct button sequence in an array, and use a looping SM.*

##PART 2
*1. Create a synchSM to blink three LEDs connected to PB0, PB1, and PB2 in sequence, 1 second each. Implement that synchSM in C as described in Section 4.7 of the ‘Programming Embedded Systems’ zyBook. In addition to demoing your program, you will need to show that your code adheres entirely to the method with no variations.*

*2. Create a simple light game that requires pressing a button on PA0 while the middle of three LEDs on PB0, PB1, and PB2 is lit. The LEDs light for 300 ms each in sequence. When the button is pressed, the currently lit LED stays lit. Pressing the button again restarts the game.*
