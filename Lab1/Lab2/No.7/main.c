#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "uart_printf.h"

int16_t ref=512,feedback;
uint8_t gain=1;
int64_t error;


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

void init_timer0(){
	DDRD=0xff; //OC0AonPD6.
	TCCR0B|=(1<<CS02);// Clock value: System clock/256
	TCCR0A|=(1<<WGM01|1<<WGM00);//Fast PWM mode.
	TCCR0A|=(1<<COM0A1);//enable OC0A output.
	TCNT0=0x00;//initialize values.
	TIMSK0=0x00; //no interrupt
	TIFR0=(1<<OCF0A);//clear OCF0A flag by write 1
	OCR0A = 200;
}

void init_adc(){
	DDRB=0xff;
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //ADC CLock 16M/128 = 125k
	ADMUX |= (1<<REFS0); //Use ADC0 is Single ended input
	ADCSRA |= (1<<ADEN)|(1<<ADATE); //enable ADC and ATS
}

uint64_t volatile __millis=0;
ISR (TIMER2_COMPA_vect){
	__millis++;
}

void init_timer2(void){
	TCCR2B=(1<<CS22);  //System divided by 64 (CLK/64).
	TCCR2A|=(1<<WGM21);  //autoreload, TCNT2 reset to 0 when reaches OCR2A
	TIMSK2=(1<<OCIE2A);  //enable interrupt.
	TIFR2=(1<<OCF2A);  //clear flag
	TCNT2=0x00; //reset counter2
	OCR2A=249; //output compare register A (compare value)
	//initialize timer2, interupt every (1/16000000)*64*1000*(249+1) = 1ms
}


int main(void){
	
	init_timer2();
	init_timer0();
	init_adc();
	init_usart_printf(115200);
	ADCSRA |= (1<<ADSC); //Start Conversion
	
	uint64_t o_time,n_time;
	sei();
	o_time = n_time = __millis;

	while (1){
		n_time =  __millis;
		if (n_time-o_time>500){
			ref = 200;
			if (n_time-o_time>1000){
				ref = 800;
				o_time = n_time;
			}
		}
		
		
		
		
		error = ref-ADC;
		feedback = gain*error;
		if (0<feedback){
			motor_ccw();
		}
		else if (0>feedback){
			motor_cw();
		}
		else{
			motor_stop();
		}
		
		
		if(255<abs(feedback)){
			OCR0A = 255;
		}
		else{
			OCR0A = abs(feedback);
		}
		
		
		printf("ref=%d, error=%d, gain=%d\n",(int)ref,(int)error,(int)gain);
	}
	

}