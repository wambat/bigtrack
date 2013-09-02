/*
 * BigTrack.h
 *
 * Created: 01.09.2013 0:21:50
 *  Author: wambat
 */ 


#ifndef BIGTRACK_H_
#define BIGTRACK_H_


void TryExecuteNextCommand(void);
void AliveFlash(void);
void QKeyboard(void);
void onKeyPress(u16);
void onBump();
void onEncoder();

void toCommandSelectMode(void);
void toParamMode(void);
void toExecuteMode(void);
extern volatile u16 encoderCounter;
#endif /* BIGTRACK_H_ */