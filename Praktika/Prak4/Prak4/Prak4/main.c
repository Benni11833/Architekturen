/*
 * Prak4.c
 *
 * Created: 06.11.2019 10:53:30
 * Author : bh8332s
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t system_clock = 0;

ISR(TIMER0_OVF_vect){
	
	system_clock++;
	
	TCNT0 = 255;
}

void setUp(){
	cli();
	TCCR0 &= 0b11111000;				// Lösche Bits 0-2 (Timer stopped)
	TCCR0 |= ((1<<CS02) | (1<<CS00));	// CS00 und CS02 setzen: Teiler 1024
	TCNT0 = 255;
	TIMSK |= (1<<TOIE0);				// Interrupt maskieren
	
	DDRB |= ((1 << 0) | (1 << 1));
	
	sei();
}

void waitUntil(uint32_t ms){
	while(system_clock < ms)
		;
}

void waitFor(uint32_t ms){
	uint32_t start_clock = system_clock;
	while(system_clock < start_clock + ms)
		;
}

int main(void)
{
	setUp();
	
	waitUntil(500);
	PORTB ^= (1 << 1);
	
	while(1){
		waitFor(400);
		PORTB ^= (1 << 0);
	}
}

