/*
 * Prak2_arch.c
 *
 * Created: 16.10.2019 10:41:25
 * Author : bh8332s
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

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

void clearLEDs(){
	//PORTB ^= PORTB;			//		0	0	0
	PORTB &= (1 << PB0) & (1 << PB1) & (1 << PB2);
	//negieren = ~
}

void setRedLED(){
	PORTB ^= (1 << PB0);		//			0	0	1
	_delay_ms(200);
	clearLEDs();
}

void setYellowLED(){
	PORTB ^= (1 << PB1);//		0	1	0
	_delay_ms(200);
	clearLEDs();
}

void setGreenLED(){
	PORTB ^= (1 << PB2);//		1 	0	0
	_delay_ms(200);
	clearLEDs();
}

int main(void)
{
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);	//PB0 als Ausgang setzten -> 1
	int flag = 1;
	while(1){	
							//PORTB		0	0	0
		if(flag){
			setRedLED();
			flag = 0;
		}else{
			setGreenLED();
			flag = 1;
		}
		
		setYellowLED();
	}
	return 0;
}