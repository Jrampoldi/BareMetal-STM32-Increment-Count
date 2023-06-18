# BareMetal-STM32-Increment-Count

Purpose behind program is to learn bare metal programming concepts 
using the stm32F103C8T6 MCU. Program utilizes GPIO usage, configuring
7 pins for output and 1 pin for input. Microcontroller will read button
state and increment a value from 0 - 9. A single 7 segment LED is used 
for output. Makefile responsible for compiling crt.s and main.c, linking with
linker.ld, converting .elf to .bin, and flashing .bin file to chip.
