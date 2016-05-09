# Lab 7

*1. Modify the keypad code to be in an SM task. Then, modify the keypad SM to utilize the simple task scheduler format (refer to PES Chp 7). All code from here on out should use the task scheduler.*

*2. Use the LCD code, along with a button and/or time delay to display the message "CS120B is Legend... wait for it DARY!" The string will not fit on the display all at once, so you will need to come up with some way to paginate or scroll the text.*

*3. Combine the functionality of the keypad and LCD so when keypad is pressed and released, the character of the button pressed is displayed on the LCD, and stays displayed until a different button press occurs (May be accomplished with two tasks: LCD interface & modified test harness).*

*4. Notice that you can visually see the LCD refresh each character (display a lengthy string then update to a different lengthy string). Design a system where a single character is updated in the displayed string rather than the entire string itself. Use the functions provided in “io.c”.*

*An example behavior would be to initially display a lengthy string, such as “Congratulations!”. The first keypad button pressed changes the first character ‘C’ to the button pressed. The second keypad press changes the second character to the second button pressed, etc. No refresh should be observable during the character update.*
