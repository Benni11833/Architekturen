/*
 * Prak4.c
 *
 * Created: 06.11.2019 10:53:30
 * Author : bh8332s
 */ 

#include <avr/io.h>

void setUp(){
	TCCR0 |= ((1 << CS02) | (1 << CS00));
	DDRB |= (1 << 0);
}

void waitUntil(int32_t ms){
	while(TCNT0 < ms)
		;
}

void waitFor(int32_t ms){
	if(TCNT0 + ms > 255){
		ms = (TCNT0 + ms) % 255;
	}
	while(TCNT0 < ms)
		;
}

int main(void)
{
	setUp();
	
	while(1){
		waitFor(200);
		PORTB ^= (1 << 0);
		TCNT0 = 0;
	}
}

