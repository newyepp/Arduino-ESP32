//printf using UART for 16.0 XTAL
#include <avr/io.h>
#include <stdio.h>
#include <math.h>


int uart_putchar(char c, FILE *stream);

FILE usart_out =
   FDEV_SETUP_STREAM(uart_putchar, NULL,
   _FDEV_SETUP_WRITE);

int uart_putchar(char c, FILE *stream){
   if(c=='\n'){
       uart_putchar('\r', stream);
   }
   // Wait for empty transmit buffer
   while(!(UCSR0A & (1<<UDRE0)) );	
   UDR0=c;
   return 0;
}
void init_usart_printf(unsigned long baud){
   //Set baud rate, baud=Fosc/(16*(UBRR+1))
	//since Arduino use 16MHz that has error the use rounding
	UBRR0 = round((F_CPU/16.0/baud)-1);
	//UBRR0=round(f);
   //UBRR0=(uint16_t)(F_CPU/16/baud)-1;
   //UBRR0 = 8;	//baud = 115200 bps
   UCSR0B = (1<<TXEN0); 
   //Set frame to 8data, 1stop bit.
   UCSR0C = (1<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);
   stdout = &usart_out;
}
