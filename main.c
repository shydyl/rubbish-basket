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
	PORTB=0x00;
	PORTC=0x00;
	TCCR1B=0x03;
	TIMSK1=1;
	EICRA=0x02;
	EIMSK=1;
	sei();
	while (1){
		if (((PINB&0x04)==0x04))
		{
			PORTC=0xF8;
		}else{
			if (time<=200){
				PORTC|=0x01;
				if (beep_flag==1)/*sound*/
				{
					PORTB|=0x01;
				}
				PORTC&=~0x06;
			}else if(time>=200&&time<=350)
			{
				PORTC|=0x02;
				PORTC&=~0x05;
			}else{
				PORTC|=0x04;
				PORTC&=~0x03;
			}

		}
		if (i>=2)/*sounding time*/
		{
			beep_flag=0;
			PORTB&=~0x01;
		}
		if (i>=10)/*time reach 1 hour*/
		{
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