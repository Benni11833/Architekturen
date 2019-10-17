/*
 * Prak2_arch.c
 *
 * Created: 16.10.2019 10:41:25
 * Author : bh8332s
 */ 

#include <avr/io.h>
#define F_CPU 1000UL
#include <util/delay.h>

int main(void)
{
    DDRB |= (1 << PB0);	//PB0 als Ausgang setzten -> 1
	
	while(1){
		PORTB ^= (1 << PB0); //PB0 als LED an/aus schalten xor - möglich ganzen Byte in PORTB zu schreiben? (PORTB = 0bxxxxxxxx)
		_delay_ms(200);
	}
	return 0;
}

