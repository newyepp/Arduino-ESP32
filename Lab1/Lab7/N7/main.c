/*
 * N7.c
 *
 * Created: 28/9/2564 22:06:52
 * Author : New
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "uart_printf.h"

int16_t ref=512;
int16_t error;

void motor_ccw(){
	PORTC &= ~(1<<5);
	PORTC &= ~(1<<4);
	PORTC |= (1<<5);
}
void motor_cw(){
	
	PORTC &= ~(1<<5);
	PORTC &= ~(1<<4);
	PORTC |= (1<<4);
	
}
void motor_stop(){
	PORTC &= ~(1<<5);
	PORTC &= ~(1<<4);
	
	

}
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
	OCR0A=80;
	//ADC
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // CLK/128 = 125kHz
	ADMUX|=(1<<REFS0); // AVCC AREF PIN WITH CAP,use ADC0
	ADCSRA|=(1<<ADEN);//enable ADC
	
	init_usart_printf(115200);
	
	while(1){
		//read ADC and print
		ADCSRA|=(1<<ADSC); //Start
		while(!(ADCSRA&(1<<ADIF))){}; // see if ADC got information
		ADCSRA|=(1<<ADIF); // clear flag after it completed.
		error = ref - ADC;
		printf("error is %d\n",error);
		if(error<0){
			motor_ccw();
			}
		else if(error>0){
			motor_cw();
			}
		else if(error>=0){
			motor_stop();
			}
		
	}
}
