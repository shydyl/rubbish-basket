#Makefile for XCH's intelligent rubbish basket
#Create by Yeonji 2016/10/20

PORT=COM4

TARGET=avr
MMCU=atmega328p
OPTION=-Wall -Wextra

AR=avr-ar
AS=avr-as
CC=avr-gcc
CCAR=avr-gcc-ar
CFLAGS=-O2 -mmcu=$(MMCU) $(OPTION)
LD=avr-ld
NM=avr-nm
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
RAMLIB=avr-ranlib
SIZEOF=avr-size

Download:all
	avrdude -p m328p -c arduino -D -P $(PORT) -U flash:w:main.hex:i -v

all:test.hex

test.hex:test.elf
	avr-objcopy main.elf -O ihex main.hex

test.elf:
	$(CC) $(CFLAGS) main.c -o main.elf
