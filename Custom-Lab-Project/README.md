# Custom Lab Project
###Components
- 3 ATMEGA 1284 Microcontrollers
- 1 8x8 RG LED MATRIX
- 1 4 Digit 7-segment Display
- 1 2-axis Joystick by Parallax
- 4 74HC595 Shift Registers
- 1 16x2 LCD Display
- 1 8ohm 1 Watt Speaker
- 1 16 Button Keypad
- 2 Breadboards

Project consisted of a Mini Arcade with 4 games: Dance Dance Revolution, Tunnel Runner, Simon Says and Snake.

###Dance Dance Revolution
- Takes input from the 2 axis joystick and compares if the direciton of the joystick matches the arrow on the LED matrix. If the input is correct, the next symbol is shown. If the input is wrong, the player loses the game. The sensitivity is a couple milliseconds so the input is read quickly.

###Tunnel Runner
- The player is placed at the bottom of LED matrix and has control of the runner and must use the joystick to move left and right to get through the wall that is coming towards the user. If the user gets hit by the wall, the game is over. There is no end to the game so the player can play for as long as he/she would like. To begin the game the first button is pressed. To reset the game, the second button is pressed. To return to the main menu, the asterisk is pressed on the keypad.

###Simon Says
- A memory game that with the help of the 4 digit 7 segment display, aids the user on the pattern that must be inputted with the keypad. For example, the user will begin with a single pattern. After every turn that the user inputs the correct pattern, an extra symbol is added to the end of the old pattern. For example, turn 1 is 1, 2, 3, 4. On turn 2, the pattern becomes 1, 2, 3, 4, 2. The pattern is hardcoded into the microcontroller and consists of 20 symbols. After those 20 symbols, the 8 ohm speaker will sound a high pitched note that indicates the player has won. 

###Snake
- The player begins by pressing the button and the snake begins moving. The joystick is then isolated depending on which axis it is moving along. For example, if the player is move horizontally, it is only allowed move vertically on the next move and vice versa. The snake, however, does not grow when a bit is ate. After every 5 bits eaten, the player speeds up so cocentration must increase so the player does not run into the walls. The second button resets the game is the user wants to start over again. The asterisk on the keypad brings the user back to the main menu of the arcade. 
