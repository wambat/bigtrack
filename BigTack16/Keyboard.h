/*
 * Keyboard.h
 *
 * Created: 31.08.2013 14:14:45
 *  Author: wambat
 */ 


#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include "HAL.h"

#define KEY_RESET 10
#define KEY_CLEAR 11
#define KEY_TEST 12
#define KEY_DOUBLE 13
#define KEY_ENTER 14
#define KEY_RUN 15

void InitKeyboard(void);
u16 QueryKeyboard(void);
u08 KeyFromCode(u16 kk);

#endif /* KEYBOARD_H_ */