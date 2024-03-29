#include "HAL.h"
#include "Usart.h"
/*
 * Keyboard.c
 *
 * Created: 31.08.2013 14:14:03
 *  Author: wambat
 */ 
u16 KeyCodeChart[]={0x4,0x8000,0x4000,0x2000,0x800,0x400,0x200,0x80,0x40,0x20,0x1000,0x1000,0x10,0x8,0x2,0x1};

u08 KeyFromCode(u16 kk)
{
	for(int i=0;i<16;i++)
	{
		if(KeyCodeChart[i]==kk)
			return i;
	}
	return 0xFF;
}
void InitKeyboard()
{
	KEYBOARD_DDR= 1<<KEYBOARD_PIN_0|1<<KEYBOARD_PIN_1|1<<KEYBOARD_PIN_2|1<<KEYBOARD_PIN_3;
	//KEYBOARD_PORT= 1<<KEYBOARD_PIN_4|1<<KEYBOARD_PIN_5|1<<KEYBOARD_PIN_6|1<<KEYBOARD_PIN_7;
}
u16 QueryKeyboard()
{
	u08 read;
	
	u08 currentGround;
	
	u16 ret=0;
	//set them high
	for(currentGround=0;currentGround<4;currentGround++)
	{
		KEYBOARD_DDR= 1<<currentGround;
		KEYBOARD_PORT= ~(1<<(currentGround));
		//wait to set line
		for(int i=0;i<100;i++)
		;
				//
		//now read
		//ret|=(KEYBOARD_PORT_IN>>4)<<(currentGround<<2);
		read=KEYBOARD_PORT_IN;
		//USART_Transmit(((read>>4)^0x0F));
		ret|=((read>>4)^0x0F)<<(currentGround*4);
		
		//ret|=(((read>>4)^0x0F)<<(currentGround*4));
		
	}
	//USART_Transmit(ret);
	//set them low
	KEYBOARD_PORT&=~(1<<KEYBOARD_PIN_0|1<<KEYBOARD_PIN_1|1<<KEYBOARD_PIN_2|1<<KEYBOARD_PIN_3);
	return ret;
}
