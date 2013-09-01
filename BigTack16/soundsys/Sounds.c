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
#include "Tune2.h"
#include "Tune3.h"
#include "Tune4.h"
#include "Tune5.h"
#include "Tune6.h"
#include "Tune7.h"
#include "Tune8.h"
#include "Tune9.h"

const int *const Sounds[] PROGMEM   = { ReadyTune, Imperial, Tune2, Tune3, Tune4, Tune5,Tune6, Tune7, Tune8, Tune9};