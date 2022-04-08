/*
 * No.6.c
 *
 * Created: 17/8/2564 20:46:47
 * Author : New
 */ 

#define F_CPU = 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


uint64_t volatile __millis=0;
ISR (TIMER2_COMPA_vect){__millis++;}

void init_timer2(){
	TCCR2B=(1<<CS22); //System divided by 64 (CLK/64).
	TCCR2A|=(1<<WGM21); //autoreload, TCNT2 reset to 0 when reaches OCR2A
	TIMSK2=(1<<OCIE2A); //enable interrupt.
	TIFR2=(1<<OCF2A); //clear flag
	TCNT2=0x00; //reset counter2
	OCR2A=249; //output compare register A (compare value)
	//initialize timer2, interupt every (1/16000000)*64*1000*(249+1) = 1ms
}

int main(void)
{
	uint64_t o_time1,n_time1,o_time2,n_time2;
	DDRC=0xFF; // output led
	sei();//enable global interrupt
	init_timer2();
	o_time1=__millis;
	n_time1=__millis;
	o_time2=__millis;
	n_time2=__millis;
	
	while (1) {
		n_time1=__millis ;
		n_time2=__millis ;
		if(n_time1-o_time1>150)//Blink_0.3S>> on 0.15 off 0.15
		{
			PORTC^=(1<<5);//LED1>>bit5
			o_time1=n_time1;
			
		}
		if(n_time2-o_time2>500)//Blink_1S>> on 0.5 off 0.5
		{
			PORTC^=(1<<4);//LED2>>bit4
			o_time2=n_time2;
			
		}
		
		
		
		
		
	}
}

