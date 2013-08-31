#include "EERTOSHAL.h"

//RTOS ������ ���������� �������
inline void RunRTOS (void)
{
TCCR2 = 1<<WGM21|6<<CS20; 				// Freq = CK/64 - ���������� ����� � ������������
										// ��������� ����� ���������� �������� ���������
TCNT2 = 0;								// ���������� ��������� �������� ���������
OCR2  = LO(TimerDivider); 				// ���������� �������� � ������� ���������
TIMSK = 0<<TOIE0|1<<OCF2|0<<TOIE0;		// ��������� ���������� RTOS - ������ ��

sei();
}
