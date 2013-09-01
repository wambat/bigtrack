#include "HAL.h"
#include "EERTOS.h"
#include "Keyboard.h"
#include "Usart.h"
#include "ProgrammStack.h"
#include "BigTrack.h"
#include <stdio.h>
#include "soundsys/sound.h"
#define COMMAND_SELECT 0
#define PARAM_SELECT 1
#define EXECUTING 2
volatile u16 lastkeyTemp;
volatile u16 lastkey;
volatile PPTR currentCommand;
volatile u08 currentParam;
volatile u08 lastUsart;
volatile u08 mode;
//RTOS Interrupt
ISR(RTOS_ISR)
{
TimerService();
}
//USART
ISR(USART_RXC_vect)
{
	lastUsart=UDR;
	switch(lastUsart)
	{
		case '1' : 
			LED_PORT|= 1<<LED3; 
			USART_Transmit('1');
			break;
		case '0' : 
			LED_PORT&= ~(1<<LED3); 
			USART_Transmit('0');
			break;
		default: 
			USART_Transmit('?');
			break;
	}
	
	
}

// Прототипы задач ============================================================


//============================================================================
//Область задач
//============================================================================

void TryExecuteNextCommand(void)
{
	if(mode==EXECUTING)
		if(!isExecutingCommand)
			if(!RunNextCommand())
				toCommandSelectMode();
	SetTimerTask(TryExecuteNextCommand,10);
}

void Task2 (void)
{
SetTimerTask(Task2,100);
//LED_PORT  &= ~(1<<LED3);
}

void QKeyboard()
{
	lastkey=QueryKeyboard();

	if(lastkey>0)
	{
		if(lastkey!=lastkeyTemp)
		{
			onKeyPress(lastkey);
			
		}
		
	}
	lastkeyTemp=lastkey;
	SetTimerTask(QKeyboard,1);
}

void onKeyPress(u16 key)
{
	u08 n=KeyFromCode(key);
	char str[15];
	sprintf(str,"[%d]Key pressed: %d\n",mode,n);
	USART_send(str);
	if(n==15)
	{
		USART_send("EXE\n");
		toExecuteMode();
	}
	if(mode==COMMAND_SELECT)
	{
		USART_send("CMD\n");
		currentCommand=CommandFromCode(n);
		toParamMode();
		return;
	}
	if(mode==PARAM_SELECT)
	{
		USART_send("PRM\n");
		currentParam=n;
		AddCommand(currentCommand,currentParam);
		toCommandSelectMode();
		return;
	}
}
void toCommandSelectMode(void)
{
	LED_PORT  &=~(1<<LED3);
	mode=COMMAND_SELECT;
}
void toParamMode(void)
{
	LED_PORT  |=1<<LED3;
	mode=PARAM_SELECT;
}
void toExecuteMode(void)
{
	LED_PORT  |=1<<LED3;
	mode=EXECUTING;
}


//==============================================================================
int main(void)
{
	mode=COMMAND_SELECT;
	InitAll();			// Инициализируем периферию
	InitRTOS();			// Инициализируем ядро
	RunRTOS();			// Старт ядра. 
	InitProgramStack();
	InitKeyboard();
	InitSoundTick();
	playTune(NULL);
	//initBT();			// init BT
	// Запуск фоновых задач.
	SetTask(TryExecuteNextCommand);
	SetTask(QKeyboard);

	while(1) 		// Главный цикл диспетчера
	{
		wdt_reset();	// Сброс собачьего таймера
		TaskManager();	// Вызов диспетчера
	}

	return 0;
}
