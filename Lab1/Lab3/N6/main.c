
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include "uart_printf.h"
#include <util/delay.h>


int main(void)
{
	init_usart_printf(9600);
	while (1) {
		//printf("Hi u623040488-8\n");
		printf("623040488-8 compiled at %s %s\n",__DATE__,__TIME__);
		_delay_ms(1000);
	}
}

