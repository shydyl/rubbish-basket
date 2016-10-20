Download:all
	avrdude -p m328p -c arduino -D -P COM4 -U flash:w:test.hex:i -v

all:hex

hex:elf
	avr-objcopy test.elf -O ihex test.hex

elf:
	avr-gcc -mmcu=atmega328p -Wall -Wextra -O2 test.c -o test.elf