/*
 * Prak4.c
 *
 * Created: 06.11.2019 10:53:30
 * Author : bh8332s
 */ 

#include <avr/io.h>

void wait_1ms(){
	uint16_t counter = 0;
	while(counter++ < 1000)
		;
}

void waitFor(int32_t ms){
	while(ms-- > 0)
		wait_1ms();
}

int main(void)
{
	
}

