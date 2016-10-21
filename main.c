/********************************************************************************
 * The MIT License
 *
 * Copyright (c) 2016 shydyl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int time=0;
volatile unsigned int i=0;

int main( void )
{
	extern volatile unsigned int time;
	int beep_flag=0;
	
	DDRB=0x23;
	DDRC=0xFF;
	/*DDRB3 connect to the photoresistance*/
	/*DDRC1,2,3 connet to three LEDs*/
	/*INT0 connect to the echo of the Ultrasonic distance measurement*/
	/*DDRB2 connect to the trig of the Ultrasonic distance measurement*/
	PORTB=0x00;
	PORTC=0x00;
	TCCR1B=0x03;
	TIMSK1=1;
	EICRA=0x02;
	EIMSK=1;
	sei();
	while (1){
		/*no light*/
		if (((PINB&0x04)==0x04))
		{
			PORTC=0xF8;
		/*light*/
		}else{
			if (time<=200){
				PORTC|=0x01;
				/*sound*/
				if (beep_flag==1){
					PORTB|=0x01;
				}
				PORTC&=~0x06;
			}else if(time>=200&&time<=350){
				PORTC|=0x02;
				PORTC&=~0x05;
			}else{
				PORTC|=0x04;
				PORTC&=~0x03;
			}

		}
		/*sounding time*/
		if (i>=4){
			beep_flag=0;
			PORTB&=~0x01;
		}
		/*time reach 1 hour*/
		if (i>=7200){
			i=0;
			beep_flag=1;
		}

	}
}

ISR(INT0_vect)
{
	extern volatile unsigned int time;
	time=TCNT1;
}

ISR(TIMER1_OVF_vect)
{
	extern volatile unsigned int i;
	PORTB|=0x02;
	_delay_us(20);
	PORTB &=~(0x02);
	i+=1;
}