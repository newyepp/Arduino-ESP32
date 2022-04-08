
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void){
	DDRC=0xFF;
	DDRD=0xFF;
	while(1){
		PORTD |= (1<<6);  //Enable on
		//counterclockwise
		PORTC |= (1<<4);
		PORTC &= ~(1<<5);
		_delay_ms(1000);
		PORTC |= (1<<4);// Off
		PORTC |= (1<<5); // Off
		_delay_ms(500);// Off 0.5s
		//clockwise
		PORTC &= ~(1<<4);
		PORTC |= (1<<5);
		_delay_ms(1000);            
		PORTC |= (1<<4);// Off
		PORTC |= (1<<5); // Off
		_delay_ms(500);
		
	}
}
