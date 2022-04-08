
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void){
    DDRC=0xFF;
    DDRD=0xFF;
	TCCR0B=(1<<CS02); // (clkI/O)/N*256 ;N=256 >> clk = 244.1Hz  (From prescaler)
	TCCR0A=(1<<WGM01|1<<WGM00); // Fast PWM
	//Enable OCR0A Output
	TCCR0A|=(1<<COM0A1);
	TCNT0=0x00;// initialize values
	TIMSK0=0x00;//no interrupt
	TIFR0=(1<<OCF0A);//clear OCR0A flag
    while (1) {
			OCR0A=190; //74.5% duty cycle >>190/255 = 0.745
			PORTD |= (1<<6); //on
			PORTC |= (1<<4);
			PORTC &= ~(1<<5);
		
		
    }
}

