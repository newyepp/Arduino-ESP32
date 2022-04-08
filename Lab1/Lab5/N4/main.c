#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void){
	DDRC=0xFF;
	DDRD=0xFF;
	while(1){
		PORTD |= (1<<6);  // Enable on
		PORTC &= ~(1<<4);
		PORTC |= (1<<5);
		_delay_ms(1000);
		//PORTD &= ~ (1<<6); //Off
		PORTC |= (1<<4);
		PORTC |= (1<<5);
		_delay_ms(1000);//
		
	}
}

