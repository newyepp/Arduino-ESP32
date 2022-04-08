#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart_printf.h"

int main(void){
	DDRB=0xFF;
	//ADCclock = SystemClock/128
	// =16.0/128 = 125k
	ADCSRA|= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); 
	//AVCC with external capacitor at AREF pin.
	//Use ADC0 with single ended input. 
	ADMUX|=(1<<REFS0);
	//enable ADC 
	ADCSRA|= (1<<ADEN);
	init_usart_printf(115200);
	while(1){
		//start conversion
		ADCSRA|= (1<<ADSC);
		//wait for ADC
		while(!(ADCSRA & (1<<ADIF))){};
		//clear flag
			ADCSRA|=(1<<ADIF);
		printf("ADC result is %d\n",ADC);
		_delay_ms(500);
	}
    
}

