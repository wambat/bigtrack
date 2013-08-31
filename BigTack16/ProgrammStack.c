/*
 * ProgrammStack.c
 *
 * Created: 31.08.2013 23:38:40
 *  Author: wambat
 */ 
#include "ProgrammStack.h"
#include "EERTOS.h"
volatile static struct
{
	PPTR Command; 						// ��������� ��������
	u08 Param;							// param
} ProgramStack[ProgramStackSize+1];

volatile static struct
{
	PPTR Command; 						// ��������� ��������
	u16 KeyCode;							// param
} ProgramKeyCodes[ProgramKeyCodeSize+1];

inline void InitProgramStack(void)
{
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
	ProgramKeyCodes[0].KeyCode=0x0002;
	ProgramKeyCodes[0].Command=BackwardCommand;
	ProgramKeyCodes[0].KeyCode=0x0200;
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
	u08		index=0;
	PPTR	CMD = IdleCommand;		// �������������� ����������
	u08		param=0;

	Disable_Interrupt				// ��������� ����������!!!
	CMD = ProgramStack[0].Command;		// ������� ������ �������� �� �������
	param = ProgramStack[0].Param;

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
	return 1;
}


//������ ��������� - ������� ����.
void  IdleCommand(u08 param)
{
	
}

void ForwardCommand(u08 param)
{
	MOTOR_PORT_DDR=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_1|1<<MOTOR_PIN_2|1<<MOTOR_PIN_3|1<<MOTOR_PIN_0;
	MOTOR_PORT=1<<MOTOR_PIN_0|1<<MOTOR_PIN_2;
	LED_PORT  |=1<<LED3;
	SetTimerTask(StopMotors,param*100);
}

void BackwardCommand(u08 param)
{
	
}

void LeftCommand(u08 param)
{
	
}

void RightCommand(u08 param)
{
	
}

void StopMotors(void)
{
	LED_PORT  &=~(1<<LED3);
	MOTOR_PORT=0<<MOTOR_PIN_0|0<<MOTOR_PIN_1|0<<MOTOR_PIN_2|0<<MOTOR_PIN_3;
	MOTOR_PORT_DDR=0<<MOTOR_PIN_1|0<<MOTOR_PIN_2|0<<MOTOR_PIN_3|0<<MOTOR_PIN_0;
	MOTOR_PORT=0<<MOTOR_PIN_1|0<<MOTOR_PIN_2|0<<MOTOR_PIN_3|0<<MOTOR_PIN_0;
}