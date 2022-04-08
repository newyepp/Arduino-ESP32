/*
 * Test1.c
 *
 * Created: 4/8/2564 14:10:52
 * Author : New
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRD = 0xFF;
	
    while (1) {
		
		PORTD |= (1<<4);
		_delay_ms(1000);
		PORTD &= ~(1<<4);
		_delay_ms(2000); 
		
    }
}

