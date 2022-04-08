
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int volatile cmd=-1;
int64_t feedback; 
int16_t ref,error;
uint8_t gain=1;
unsigned char data;
unsigned char d,f;
int uart_putchar(char c, FILE *stream);
FILE usart_out = FDEV_SETUP_STREAM(uart_putchar,NULL, _FDEV_SETUP_WRITE);

ISR(USART_RX_vect){
	unsigned char status;
	cmd=UDR0;
	status=UCSR0A; //read USART status.
	//if error occur.
	if(status&((1<<FE0)|(1<<DOR0)|(1<<UPE0))){
		cmd=-1;
		}else{ //no error
		//cmd is UDR0
	}
}
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

void init_usart(unsigned long baud){
	unsigned int ubrr;
	//Set baud rate, baud=Fosc/(8*(UBRR+1)) (2X mode)
	ubrr=(unsigned int)(F_CPU/8/baud)-1;
	 UBRR0H = (unsigned char)(ubrr>>8); 
	UBRR0L = (unsigned char)ubrr;
	//Double the USART Transmission Speed
	UCSR0A = (1<<U2X0);
	// Enable TX,RX and RX interrupt.
	UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0);
	//Set frame to 8data, 2stop bit
	UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
	stdout = &usart_out;
}


int uart_putchar(char c, FILE *stream){
	 if(c=='\n'){
		uart_putchar('\r', stream);
 }
// Wait for empty transmit buffer
while(!(UCSR0A & (1<<UDRE0)) );
 UDR0=c;
return 0;
}

/*void PWM(int64_t feedback){
	while(1){
		if (255<abs(feedback))
		OCR0A = 255;
		else OCR0A =abs(feedback);
	}
}*/

void action(unsigned char c){
	switch(c){
		case 'd':
		ref = 300;
		break;
		case 'f':
		ref = 700;
		break;
	}
	ADCSRA|=(1<<ADSC); //Start
	while(!(ADCSRA&(1<<ADIF))){}; // see if ADC got information
	ADCSRA|=(1<<ADIF); // clear flag after it completed.
	error = ref - ADC;
	feedback = gain * error;
	if (255<abs(feedback))
	OCR0A = 255;
	else OCR0A =abs(feedback);
	printf("PWM=%d,ref=%d,error=%d,gain=%d\n",(int)OCR0A ,(int)ref,(int)error,(int)gain);
}



int main(void){
	UCSR0B = (1<<RXEN0);
	DDRC=0xFF;
	DDRD=0xFF;
	TCCR0B=(1<<CS02); // (clkI/O)/N*256 ;N=256 >> clk = 244.1Hz  (From prescaler)
	TCCR0A=(1<<WGM01|1<<WGM00); // Fast PWM
	//Enable OCR0A Output
	TCCR0A|=(1<<COM0A1);
	TCNT0=0x00;// initialize values
	TIMSK0=0x00;//no interrupt
	TIFR0=(1<<OCF0A);//clear OCR0A flag
	//ADC
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // CLK/128 = 125kHz
	ADMUX|=(1<<REFS0); // AVCC AREF PIN WITH CAP,use ADC0
	ADCSRA|=(1<<ADEN);//enable ADC
	//USART
	init_usart(115200);	
	sei();
		while(1){
		if (0<=cmd)
		{
			action((unsigned char)cmd);
			cmd = -1;
			//read ADC and print
			
			//return 0;
			}
	}
		
		
		if(feedback<0){
			motor_ccw();
		}
		else if(feedback>0){
			motor_cw();
		}
		else if(feedback>=0){
			motor_stop();
		}
		
		}
		
	
	
