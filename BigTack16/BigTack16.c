#include "HAL.h"
#include "EERTOS.h"
#include "Keyboard.h"
#include "Usart.h"
#include "ProgrammStack.h"
#include "BigTrack.h"
#define COMMAND_SELECT 0
#define PARAM_SELECT 1
#define EXECUTING 2
volatile u16 lastkeyTemp;
volatile u16 lastkey;
volatile u08 currentCommand;
volatile u08 currentParam;
volatile u08 lastUsart;
volatile BOOL mode;
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

void Task1 (void)
{
SetTimerTask(Task2,100);
//LED_PORT  ^=1<<LED3;
}

void Task2 (void)
{
SetTimerTask(Task1,100);
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
	USART_Transmit(n);
	if(mode==COMMAND_SELECT)
	{
		currentCommand=n;
	}
	
}


//==============================================================================
int main(void)
{
	mode=COMMAND_SELECT;
	InitAll();			// Инициализируем периферию
	InitRTOS();			// Инициализируем ядро
	RunRTOS();			// Старт ядра. 
	InitKeyboard();
	//initBT();			// init BT
	// Запуск фоновых задач.
	SetTask(Task1);
	SetTask(QKeyboard);

	while(1) 		// Главный цикл диспетчера
	{
		wdt_reset();	// Сброс собачьего таймера
		TaskManager();	// Вызов диспетчера
	}

	return 0;
}
