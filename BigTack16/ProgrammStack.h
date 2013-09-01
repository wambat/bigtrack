/*
 * ProgrammStack.h
 *
 * Created: 31.08.2013 23:34:30
 *  Author: wambat
 */ 


#ifndef PROGRAMMSTACK_H_
#define PROGRAMMSTACK_H_

#include "HAL.h"
#include "EERTOSHAL.h"

typedef void (*PPTR)(u08);
#define	ProgramStackSize		16
#define	ProgramKeyCodeSize		16
extern void IdleCommand(u08);
extern void ForwardCommand(u08);
extern void BackwardCommand(u08);
extern void LeftCommand(u08);
extern void RightCommand(u08);
extern void PlaySoundCommand(u08);
extern void FireCommand(u08);
extern void StopMotors(void);
extern void PlayFireSound(void);
extern void StopFire(void);


extern void InitProgramStack(void);
extern void rewind(void);
extern BOOL AddCommand(PPTR, u08);
extern BOOL RunNextCommand(void);
extern PPTR CommandFromCode(u08);
extern volatile BOOL isExecutingCommand;
#endif /* PROGRAMMSTACK_H_ */
