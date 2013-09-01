/*
 * Sounds.c
 *
 * Created: 01.09.2013 15:58:14
 *  Author: wambat
 */ 
#include "../avrlibdefs.h"
#include "../avrlibtypes.h"
#include "avr/pgmspace.h"
#include "imperial.h"
#include "ReadyTune.h"
const int *const Sounds[] PROGMEM   = { ReadyTune, Imperial, 0};