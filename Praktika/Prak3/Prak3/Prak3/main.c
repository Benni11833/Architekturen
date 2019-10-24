/*
 * Prak3.c
 *
 * Created: 23.10.2019 10:40:13
 * Author : bh8332s
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

void init(){
	DDRB |= (1 << PB0) | (1 << PB1);
	DDRD = 0;	//DDRD als Eingang
	PORTD = 0xff;	//PullUps auf PORTD einschalten
}

int Taster1_pressed(){
	if(PIND != (PIND ^ (1 << PD2)))
		return 1;
	else
		return 0;
}

int Taster2_pressed(){
	if(PIND != (PIND ^ (1 << PD1)))
		return 1;
	else
		return 0;
}

int main(void)
{
	init();
	
    while (1) 
    {
		if(Taster1_pressed())
			PORTB |= (1 << PB0);
		else if(Taster2_pressed())
			PORTB |= (1 << PB1);
		else
			PORTB = 0;
    }
}

