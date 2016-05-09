# Lab 5
*1. Connect LEDs to PB0, PB1, PB2, and PB3. In one state machine (Three LEDs), output to a shared variable (threeLEDs) the following behavior: set only bit 0 to 1, then only bit 1, then only bit 2 in sequence for 1 second each. In a second state machine (Blinking LED), output to a shared variable (bilnkingLED) the following behavior: set bit 3 to 1 for 1 second, then 0 for 1 second. In a third state machine (Combine LEDs), combine both shared variables and output to the PORTB. Note: only one SM is writing to outputs. Do this for the rest of the quarter.*

*2. Modify the above example so the three LEDs light for 300 ms, while PB3's LED still blinks 1 second on and 1 second off.*

*3. Start with the previous exercise's implementation. Connect your speaker's red wire to PB4 and black wire to ground. Add a third task that toggles PB4 on for 2 ms and off for 2 ms as long as a switch on PA2 is in the on position.*

*4. Extend the previous exercise to allow a user to adjust the sound frequency up or down using buttons connected to PA0 (up) and PA1 (down). Using our 1 ms timer abstraction, the fastest you'll be able to pulse is 1 ms on and 1 ms off, meaning 500 Hz. You'll probably want to introduce another synchSM that polls the buttons and sets a global variable storing the current frequency that in turn is read by the frequency generator task.*

*5. Buttons are connected to PA0 and PA1. Output PORTB drives a bank of 4 LEDs. Pressing PA0 increments a binary number displayed on the bank of LEDs (stopping at 9). Pressing PA1 decrements the binary number (stopping at 0). If both buttons are depressed (even if not initially simultaneously), the display resets to 0. If a button is held, then the display continues to increment (or decrement) at a rate of once per second. However, if the button is held for 3 seconds, the incrementing/decrementing occurs once per 400 ms. Use synchronous state machines captured in C.*
