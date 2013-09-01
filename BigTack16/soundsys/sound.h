/*
 * sound.h
 *
 * Created: 01.09.2013 11:57:56
 *  Author: wambat
 */ 


#ifndef SOUND_H_
#define SOUND_H_
#include "../avrlibdefs.h"
#include "../avrlibtypes.h"
#include "../EERTOS.h"


void InitSoundTick(void);
void stopSound(void);
void playNote(u08);
void playTune(u08, TPTR);
void playNextNote(void);
extern void onSoundPlayed(void);
#endif /* SOUND_H_ */