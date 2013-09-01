#ifndef FUGUE1_H
#define FUGUE1_H
#include "notes.h"
const int Imperial[] PROGMEM=
        {
4,a3, 64,p,
4,a3, 64,p, 
4,a3, 64,p, 
6,f3, 64,p, 
16,c4, 64,p,
4,a3, 64,p,
6,f3, 64,p,
16,c4, 64,p,
2,a3, 64,p,
8,p,
4, e4, 64, p,
4, e4, 64, p,
4, e4, 64, p,
6, f4, 64, p,
16, c4, 64, p,
4, cx3, 64, p,
6, f3, 64, p,
16, c4, 64, p,
2, a3, 64, p,
0};

#endif
/*
8,cx3,


beep(speakerPin, eH, 500);
beep(speakerPin, eH, 500);
beep(speakerPin, eH, 500);
beep(speakerPin, fH, 350);
beep(speakerPin, cH, 150);

beep(speakerPin, gS, 500);
beep(speakerPin, f, 350);
beep(speakerPin, cH, 150);
beep(speakerPin, a, 1000);

beep(speakerPin, aH, 500);
beep(speakerPin, a, 350);
beep(speakerPin, a, 150);
beep(speakerPin, aH, 500);
beep(speakerPin, gSH, 250);
beep(speakerPin, gH, 250);

beep(speakerPin, fSH, 125);
beep(speakerPin, fH, 125);
beep(speakerPin, fSH, 250);
delay(250);
beep(speakerPin, aS, 250);
beep(speakerPin, dSH, 500);
beep(speakerPin, dH, 250);
beep(speakerPin, cSH, 250);

beep(speakerPin, cH, 125);
beep(speakerPin, b, 125);
beep(speakerPin, cH, 250);
delay(250);
beep(speakerPin, f, 125);
beep(speakerPin, gS, 500);
beep(speakerPin, f, 375);
beep(speakerPin, a, 125);

beep(speakerPin, cH, 500);
beep(speakerPin, a, 375);
beep(speakerPin, cH, 125);
beep(speakerPin, eH, 1000);

beep(speakerPin, aH, 500);
beep(speakerPin, a, 350);
beep(speakerPin, a, 150);
beep(speakerPin, aH, 500);
beep(speakerPin, gSH, 250);
beep(speakerPin, gH, 250);

beep(speakerPin, fSH, 125);
beep(speakerPin, fH, 125);
beep(speakerPin, fSH, 250);
delay(250);
beep(speakerPin, aS, 250);
beep(speakerPin, dSH, 500);
beep(speakerPin, dH, 250);
beep(speakerPin, cSH, 250);

beep(speakerPin, cH, 125);
beep(speakerPin, b, 125);
beep(speakerPin, cH, 250);
delay(250);
beep(speakerPin, f, 250);
beep(speakerPin, gS, 500);
beep(speakerPin, f, 375);
beep(speakerPin, cH, 125);

beep(speakerPin, a, 500);
beep(speakerPin, f, 375);
beep(speakerPin, c, 125);
beep(speakerPin, a, 1000);
4,a2, 4,b2, 3,c3, 15,d3, 17,c3, 4,b2, 4,e3, 4,a2,
3,d3, 8,e3, 8,d3, 8,c3, 8,b2, 8,g2, 8,a2, 8,b2,
8,c3, 8,b2, 8,c3, 8,d3, 8,e3, 8,d3, 8,e3, 8,fx3,
4,g3, 4,b2, 4,c3, 4,a2, 8,d3, 8,c3, 8,b2, 8,a2,
3,g2, 8,g2, 8,f2, 8,e2, 8,f2, 8,g2, 8,a2, 8,g2,
8,a2, 8,b2, 1,c3, 1,b2, 4,c3, 4,d3, 4,e3, 3,f3,
16,g3, 16,f3, 4,e3, 4,a3, 4,d3, 3,g3, 8,a3, 8,g3,
8,f3, 4,e3, 3,a3, 8,b3, 8,a3, 8,g3, 1,f3, 3,e3,
8,fx3, 1,g3, 2,fx3, 8,g3, 8,f3, 8,e3, 8,d3, 8,c3,
8,d3, 8,c3, 8,b2, 8,a2, 8,c3, 8,b2, 1,a2, 4,c3,
8,a2, 4,gx2, 4,e3, 4,d3, 8,c3, 8,b2, 8,a2, 8,gx2,
8,a2, 8,b2, 8,c3, 8,fx2, 8,gx2, 8,a2, 4,b2, 8,a2,
8,b2, 4,c3, 4,f3, 4,e3, 2,d3, 8,c3, 8,b2, 32,c3,
32,b2, 32,c3, 32,b2, 32,c3, 32,b2, 32,c3, 32,b2, 32,c3,
11,b2, 8,a2, 0,a2, 4,g2, 4,a2, 4,b2, 3,c3, 15,d3,
17,c3, 4,b2, 4,c3, 4,d3, 4,e3, 3,f3, 15,g3, 17,f3,
4,e3, 4,a3, 4,d3, 3,g3, 8,a3, 8,g3, 8,f3, 4,e3,
4,a3, 4,d3, 4,ax3, 4,a3, 8,g3, 8,f3, 8,g3, 8,f3,
8,g3, 8,e3, 8,f3, 8,g3, 37,g3, 34,a3, 13,g3, 15,f3,
17,g3, 8,a3, 8,cx3, 8,d3, 8,g3, 40,f3, 34,e3, 34,f3,
34,e3, 34,f3, 4,e3, 8,d3, 0,d3, 4,g2, 4,a2, 4,b2,
3,c3, 15,d3, 17,c3, 4,b2, 4,e3, 4,a2, 3,d3, 8,e3,
8,d3, 8,c3, 8,b2, 8,c3, 8,d3, 8,e3, 8,f3, 8,g3,
8,a3, 8,g3, 8,f3, 8,e3, 8,d3, 8,c3, 40,c3, 34,b2,
34,c3, 2,b2, 4,c3, 4,d3, 4,g2, 2,c3, 4,b2, 2,c3,
4,b2, 4,ax2, 4,a2, 2,d3, 4,c3, 4,d3, 4,e3, 2,f3,
8,a3, 8,g3, 8,f3, 8,e3, 8,f3, 8,e3, 8,d3, 1,c3,
16,g2, 16,a2, 8,b2, 8,c3, 8,d3, 8,e3, 3,f3, 16,c3,
16,d3, 16,e3, 8,f3, 8,g3, 3,a3, 8,b3, 8,c4, 8,g3,
 
*/