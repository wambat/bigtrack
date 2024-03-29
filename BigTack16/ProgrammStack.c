/*
 * ProgrammStack.c
 *
 * Created: 31.08.2013 23:38:40
 *  Author: wambat
 */ 
#include "ProgrammStack.h"
#include "EERTOS.h"
#include "soundsys/sound.h"
#include "soundsys/Sounds.h"
#include "BigTrack.h"
#include <stdio.h>
#include "Usart.h"
volatile static struct
{
	PPTR Command; 						// ��������� ��������
	u08 Param;							// param
} ProgramStack[ProgramStackSize+1];

volatile static struct
{
	PPTR Command; 						// ��������� ��������
	u08 KeyCode;							// param
} ProgramKeyCodes[ProgramKeyCodeSize+1];
volatile BOOL isExecutingCommand;
volatile u08 currentIndex;
volatile u08 fireCount;
volatile u16 encoderDst;
inline void InitProgramStack(void)
{
	isExecutingCommand=0;
	currentIndex=0;
	encoderDst=0;
	u08	index;
	for(index=0;index!=ProgramStackSize+1;index++)	//
	{
		ProgramStack[index].Command = IdleCommand;
		ProgramStack[index].Param= 0;
	}
	for(index=0;index!=ProgramKeyCodeSize+1;index++)	//
	{
		ProgramKeyCodes[index].Command = IdleCommand;
		ProgramKeyCodes[index].KeyCode= 0;
	}
	ProgramKeyCodes[0].Command=ForwardCommand;
	ProgramKeyCodes[0].KeyCode=2;
	ProgramKeyCodes[1].Command=BackwardCommand;
	ProgramKeyCodes[1].KeyCode=8;
	ProgramKeyCodes[2].Command=RightCommand;
	ProgramKeyCodes[2].KeyCode=6;
	ProgramKeyCodes[3].Command=LeftCommand;
	ProgramKeyCodes[3].KeyCode=4;
	ProgramKeyCodes[4].Command=PlaySoundCommand;
	ProgramKeyCodes[4].KeyCode=1;
	ProgramKeyCodes[5].Command=FireCommand;
	ProgramKeyCodes[5].KeyCode=3;
}
PPTR CommandFromCode(u08 key)
{
	for(int i=0;i<ProgramKeyCodeSize;i++)
	{
		if(ProgramKeyCodes[i].KeyCode==key)
		return ProgramKeyCodes[i].Command;
	}
	return 0x00;
}
BOOL AddCommand(PPTR CMD, u08 param)
{
	u08		index=0;
	u08		nointerrupted = 0;

	if (STATUS_REG & (1<<Interrupt_Flag)) 			// �������� ������� ����������, ���������� ������� ����
	{
		Disable_Interrupt
		nointerrupted = 1;
	}

	for(index=0;index!=ProgramStackSize+1;++index)	// ���� �� ������� ������� ������, �� ���� ����� ������
	{
		if(ProgramStack[index].Command == IdleCommand)
		{
			ProgramStack[index].Command= CMD;			// ��������� ���� �������� ������
			ProgramStack[index].Param= param;		// � ���� �������� �������
			if (nointerrupted) 	Enable_Interrupt	// ��������� ����������
				return 1;									// �����.
		}
		
	}												// ��� ����� ������� return c ����� ������ - ��� ��������� ��������
	return 0;
}

inline BOOL RunNextCommand(void)
{
	//u08		index=0;
	PPTR	CMD = IdleCommand;		// �������������� ����������
	u08		param=0;

	Disable_Interrupt				// ��������� ����������!!!
	CMD = ProgramStack[currentIndex].Command;		// ������� ������ �������� �� �������
	param = ProgramStack[currentIndex].Param;
	if (CMD==IdleCommand||currentIndex>=ProgramStackSize) 			// ���� ��� �����
	{
		Enable_Interrupt			// ��������� ����������
		return 0;
	}
	else
	{
		Enable_Interrupt							// ��������� ����������
		currentIndex++;
		(CMD)(param);								// ��������� � ������
	}
	return 1;
/*
	if (CMD==IdleCommand) 			// ���� ��� �����
	{
		Enable_Interrupt			// ��������� ����������
		return 0;
	}
	else
	{
		for(index=0;index!=ProgramStackSize+1;index++)	// � ��������� ������ �������� ��� �������
		{
			ProgramStack[index]=ProgramStack[index+1];
		}

		ProgramStack[ProgramStackSize].Command= IdleCommand;				// � ��������� ������ ������ �������
		ProgramStack[ProgramStackSize].Param=0;

		Enable_Interrupt							// ��������� ����������
		(CMD)(param);								// ��������� � ������
	}
	return 1;*/
	
}


//������ ��������� - ������� ����.
void  IdleCommand(u08 param)
{
	
}

void ForwardCommand(u08 param)
{
	encoderCounter=0;
	encoderDst=param*ENCODER_MULTIPLIER;
	MOTOR_PORT_DDR=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_0|1<<MOTOR_PIN_2;
	isExecutingCommand=1;
	SetTimerTask(CheckIfReachedDestination,10);
}

void BackwardCommand(u08 param)
{
	encoderCounter=0;
	encoderDst=param*ENCODER_MULTIPLIER;
	MOTOR_PORT_DDR=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_3;
	isExecutingCommand=1;
	SetTimerTask(CheckIfReachedDestination,10);
}

void LeftCommand(u08 param)
{
	encoderCounter=0;
	encoderDst=param*ENCODER_MULTIPLIER;
	MOTOR_PORT_DDR=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_0|1<<MOTOR_PIN_3;
	isExecutingCommand=1;
	SetTimerTask(CheckIfReachedDestination,10);
}

void RightCommand(u08 param)
{
	encoderCounter=0;
	encoderDst=param*ENCODER_MULTIPLIER;
	MOTOR_PORT_DDR=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2;
	isExecutingCommand=1;
	SetTimerTask(CheckIfReachedDestination,10);
}
void CheckIfReachedDestination(void)
{
	if(encoderCounter>encoderDst)
		StopMotors();
	else
		SetTimerTask(CheckIfReachedDestination,10);
}
void StopMotors(void)
{
	char str[25];
	sprintf(str,"Traveled: %d\n",encoderCounter);
	USART_send(str);
	encoderCounter=0;
	encoderDst=0;
	MOTOR_PORT=0<<MOTOR_PIN_0|0<<MOTOR_PIN_1|0<<MOTOR_PIN_2|0<<MOTOR_PIN_3;
	MOTOR_PORT_DDR=0<<MOTOR_PIN_1|0<<MOTOR_PIN_2|0<<MOTOR_PIN_3|0<<MOTOR_PIN_0;
	MOTOR_PORT=0<<MOTOR_PIN_1|0<<MOTOR_PIN_2|0<<MOTOR_PIN_3|0<<MOTOR_PIN_0;
	isExecutingCommand=0;
}
void PlaySoundCommand(u08 param)
{
	isExecutingCommand=1;
	playTune(param,onSoundPlayed);
}
void FireCommand(u08 param)
{
	fireCount=param;
	isExecutingCommand=1;
	//SetTimerTask(PlayFireSound,param*100);
	playNextFire();
}
void playNextFire(void)
{
	fireCount--;
	LED_PORT|=1<<FIRE_LED;
	PlayFireSound();
}
void PlayFireSound(void)
{
	playTune(FIRE_SOUND,StopFire);//StopFire
}
void StopFire(void)
{
	OffFireLED();
	if(fireCount>0)
		SetTimerTask(playNextFire,20);
	else
		isExecutingCommand=0;
}
void OffFireLED(void)
{
	LED_PORT&=~(1<<FIRE_LED);
}
void onSoundPlayed(void)
{
	isExecutingCommand=0;	
}
void rewind(void)
{
	currentIndex=0;
}
void haltAllPeripheral(void)
{
	fireCount=0;
	OffFireLED();
	StopMotors();
	rewind();
}