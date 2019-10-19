/*
 * Prak2_arch.c
 *
 * Created: 16.10.2019 10:41:25
 * Author : bh8332s
 */ 

#include <avr/io.h>
#define F_CPU 1000UL
#include <util/delay.h>

/*
int main(void)
{
    DDRB |= (1 << PB0);	//PB0 als Ausgang setzten -> 1
	
	while(1){
		PORTB ^= (1 << PB0); //PB0 als LED an/aus schalten xor - m�glich ganzen Byte in PORTB zu schreiben? (PORTB = 0bxxxxxxxx)
		_delay_ms(200);
	}
	return 0;
}*/

/*
Ablauf: -> unelegant
PB2 	PB1 	PB0
0		0		1
0		1		0
1		0		0
0		1		0
_______
0		0		1
...

Ablauf:	-> mittelelegant
PB2		PB1		PB0
0		0		0
0		0		1
0		1		1

*/

void unelegant(){
		PORTB ^= (1 << PB0);		//			0	0	1
		_delay_ms(200);
		PORTB ^= (1 << PB1) | (1 << PB0);//		0	1	0
		_delay_ms(200);
		PORTB ^= (1 << PB2) | (1 << PB1);//		1 	0	0
		_delay_ms(200);
		PORTB ^= (1 << PB2) | (1 << PB1);//		0	1	0
		_delay_ms(200);
		PORTB ^= (1 << PB1);			//		0	0	0
}

void mittelelegant(){
	static bool flag = true;
	PORTB = 0x00;
	if(flag)	//PB0 soll leuchten, PB1, PB2 nicht
		PORTB ^= (1 << PB0);
	else		//PB2 sol leuchten, PB1, PB0 nicht
		PORTB ^= (1 << PB2);
	_delay_ms(200);
	PORTB = 0x00;
	PORTB  |= (1 << PB1);
	_delay_ms(200);
}

int main(void)
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);	//PB0 als Ausgang setzten -> 1
	
	while(1){						//PORTB		0	0	0
		//unelegant();
		mittelelegant();
	}
	return 0;
}