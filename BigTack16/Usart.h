/*
 * Usart.h
 *
 * Created: 31.08.2013 14:51:14
 *  Author: wambat
 */ 


#ifndef USART_H_
#define USART_H_
#include "HAL.h"
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void USART_send(char *data);
void initBT(void);
#endif /* USART_H_ */