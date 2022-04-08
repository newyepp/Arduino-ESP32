

#include <avr/io.h>
#include "uart_printf.h"
#include <util/delay.h>


int main(void)
{
	init_usart_printf(9600);
	while (1) {
		printf("Hi u623040488-8\n");
		printf("%s %s\n",__DATE__,__TIME__);
		_delay_ms(2000);
	}
}
