/*
 * Keyboard.h
 *
 * Created: 31.08.2013 14:14:45
 *  Author: wambat
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include "HAL.h"
void InitKeyboard(void);
u16 QueryKeyboard(void);
u08 KeyFromCode(u16 kk);

#endif /* KEYBOARD_H_ */