/*
 * soundsys.c
 *
 * Created: 01.09.2013 12:00:42
 *  Author: wambat
 */ 
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "avr/io.h"
#include "sound.h"
#include "sine.h"
#include "notes.h"
#include "Sounds.h"
#include "../HAL.h"
#include "../EERTOS.h"
#define FACT 8
u16 cnt;

const int *pSong;
TPTR callStop;
/*

Function To Initialize TIMER0 In Fast
PWWM Mode.

*/
void InitSoundTick(void)
{

   TCCR0|=1<<WGM01|1<<CS01|1<<CS00;
   //Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32
   //DDRB|=(1<<PB3);
   SOUND_PORT_DDR|=1<< SOUND_PIN;
}
//RTOS Interrupt
ISR(SOUND_ISR)
{
	SOUND_PORT^=1<<SOUND_PIN;
}


void stopSound(void)
{
	TIMSK&=~(1<<OCIE0);
	if(callStop)
		(callStop)();
	callStop=0;
}
void pause(u16 duration)
{
	TIMSK&=~(1<<OCIE0);
	SetTimerTask(playNextNote,(64/duration)*FACT);
}
void playNote(u08 note)
{
	TIMSK|=1<<OCIE0;
	OCR0=note;
}
void playTune(u08 num, TPTR call)
{
	pSong=(int*)pgm_read_word(&Sounds[num]);
    cnt = 0;
	callStop=call;
	playNextNote();
}
void playNextNote(void)
{
	volatile u16 note;
	volatile u16 duration;
	duration=(u16)pgm_read_word(pSong + cnt);
	if(!duration)
	{
		stopSound();
		return;
	}
	note=(u16)pgm_read_word(pSong + cnt + 1);
	if(note==p)
		pause(duration);
	else
		playNote((u08)(note));
	cnt+=2;
	SetTimerTask(playNextNote,(64/duration)*FACT);
}