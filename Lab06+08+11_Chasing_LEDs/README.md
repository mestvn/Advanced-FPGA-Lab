# Lab 6,8,11: Chasing LEDs, with Potentiometer, with Mous

DEMO Lab 6 (Switches): https://youtube.com/shorts/8zASkPSO5p0?feature=share
DEMO Lab 8 (Potentiometer): https://youtube.com/shorts/aSvMhWtHJ9k?feature=share
DEMO Lab 11 (Mouse): https://youtube.com/shorts/rr_uVjQlV2Y?feature=share

## C++ Application Lab 6:
Most of source code was provided - only had to create the application file. Consists of incrementing and decrementing for loops that have a smaller sleep period depending on the speed. UART transmission only occurs when the speed is changed. Speed changes according to switches.

## C++ Application Lab 8:
Most of the code is unchanged except for the addition of xADC and a potentiometer which controls the speed instead of switches. The initial switch still resets the LED to LED0.

## C++ Application Lab 11:
Most of code is unchanged again, except for addition of Ps2 and Seven Segment cores and a wireless mouse for easier function. Left Click pauses and resumes the LED chasing. Right click enables and disables the speed to change according to the mouse's horizontal (x direction) movement. Pause status and speed are displayed on the seven segment displays.

## HDL and Drivers:
Source code from Professor Eddin: https://github.com/aseddin/ece_4305/tree/main/M8%20to%20M%2013%20-%20Sampler%20System