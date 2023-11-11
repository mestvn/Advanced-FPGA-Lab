# Lab 7: Blinking LEDs

DEMO: https://youtube.com/shorts/ppcT2OD06Y8?feature=share

## HDL for 1 LED:
Created top_led.sv which takes a 16-bit input for millisecondss & consists of a modulo-1ms counter that triggers a modulo 1-milliseconds counter which then triggers a T flip-flop that controls an LED.

## Wrapping Circuit HDL for 4 LEDs:
Then, the wrapping circuit interfaces with the mmios and maps 4 rows of the 16-bit register map to 4 LED's. This circuit simply writes or resets the 4 "rows" or registers.

## C++ Drivers & Main Application:
Essentially defines the first 16-bits as bits to write. Takes in 16 switches as the milliseconds and LED0 blinks as that time. LED's 1-3 blink half the speed of the previous switch to create illusion of a binary counter.

## HDL and Drivers:
Source code from Professor Eddin: https://github.com/aseddin/ece_4305/tree/main/M8%20to%20M%2013%20-%20Sampler%20System
