#include "HAL.h"
inline void InitAll(void)
{

//InitUSART
UBRRL = LO(bauddivider);
UBRRH = HI(bauddivider);

UCSRA = 0;
UCSRB = 1<<RXEN|1<<TXEN|1<<RXCIE|0<<TXCIE;
UCSRC = 1<<URSEL|1<<UCSZ0|1<<UCSZ1;

//InitPort
LED_DDR |= 1<<FIRE_LED|1<<SERVICE_LED|1<<KEYBOARD_LED;//|1<<I_L|1<<I_C;

}



