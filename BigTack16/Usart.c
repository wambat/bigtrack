#include "Usart.h"
/*
 * Usart.c
 *
 * Created: 31.08.2013 14:49:52
 *  Author: wambat
 */ 
void initBT(void)
{
	USART_Transmit('A');
	USART_Transmit('T');
	USART_Transmit(0x0D);
	USART_Transmit(0x0A);
	USART_Transmit('A');
	USART_Transmit('T');
	USART_Transmit('+');
	USART_Transmit('O');
	USART_Transmit('R');
	USART_Transmit('G');
	USART_Transmit('L');
	USART_Transmit(0x0D);
	USART_Transmit(0x0A);
	USART_Transmit('A');
	USART_Transmit('T');
	USART_Transmit('+');
	USART_Transmit('N');
	USART_Transmit('A');
	USART_Transmit('M');
	USART_Transmit('E');
	USART_Transmit('A');
	USART_Transmit('V');
	USART_Transmit('R');
	USART_Transmit(0x0D);
	USART_Transmit(0x0A);
	
}
void USART_Transmit( unsigned char data )
{
	while ((UCSRA & (1 << UDRE)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
	UDR = data;
}
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

