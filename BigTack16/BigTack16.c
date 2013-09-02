#include "HAL.h"
#include "EERTOS.h"
#include "Keyboard.h"
#include "Usart.h"
#include "ProgrammStack.h"
#include "BigTrack.h"
#include <stdio.h>
#include "soundsys/sound.h"
#include "soundsys/Sounds.h"
#include "Keyboard.h"
#define COMMAND_SELECT 0
#define PARAM_SELECT 1
#define EXECUTING 2
volatile u16 lastkeyTemp;
volatile u16 lastkey;
volatile  u16 encoderCounter;
volatile PPTR currentCommand;
volatile u08 currentParam;
volatile u08 lastUsart;
volatile u08 mode;
//RTOS Interrupt
ISR(RTOS_ISR)
{
	TimerService();
}
//BUMP 
//ISR(SENSOR_INTERRUPT_BUMP_VECTOR)
//{
//	onBump();
//}
//ENCODER
ISR(SENSOR_INTERRUPT_ENCODER_VECTOR)
{
	onEncoder();
}
//USART
ISR(USART_RXC_vect)
{
	lastUsart=UDR;
	switch(lastUsart)
	{
		case '1' : 
			LED_PORT|= 1<<SERVICE_LED; 
			USART_Transmit('1');
			break;
		case '0' : 
			LED_PORT&= ~(1<<SERVICE_LED); 
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

void AliveFlash(void) 
{
	LED_PORT^=1<<SERVICE_LED;
	SetTimerTask(AliveFlash,100);
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
void QBump()
{
	//grounded resets
	
	//USART_Transmit(SENSOR_BUMP_PORT_IN);
	if(~(SENSOR_BUMP_PORT_IN)&(1<<SENSOR_BUMP_PIN))
		onBump();
	SetTimerTask(QBump,3);
}

void onKeyPress(u16 key)
{
	u08 n=KeyFromCode(key);
	char str[25];
	sprintf(str,"[%d]Key pressed: %d(0x%x)\n",mode,n,key);
	USART_send(str);
	if(n==KEY_RUN)
	{
		if(currentCommand&&currentParam>0)
		{
			confirmCommand();
		}
		playTune(KEY_SOUND,0);
		USART_send("EXE\n");
		rewind();
		toExecuteMode();
	}
	if(n==KEY_RESET)
	{
		toCommandSelectMode();
		InitProgramStack();
		playTune(INIT_SOUND,0);
		return;
	}
	if(mode==COMMAND_SELECT)
	{
		playTune(KEY_SOUND,0);
		USART_send("CMD\n");
		currentCommand=CommandFromCode(n);
		currentParam=0;
		toParamMode();
		return;
	}
	if(mode==PARAM_SELECT && n<10)
	{
		
		USART_send("PRM\n");
		if(currentParam>0&& currentParam<=9)
		{
			currentParam=currentParam*10+n;
			confirmCommand();
		}
		else
		{
			playTune(KEY_SOUND,0);
			currentParam=n;
			return;
		}
	}
	if(mode==PARAM_SELECT && n==KEY_ENTER)
	{
		confirmCommand();
	}
}
void confirmCommand(void)
{
	playTune(CONFIRM_SOUND,0);
	AddCommand(currentCommand,currentParam);
	currentCommand=0;
	currentParam=0;
	toCommandSelectMode();
}
void toCommandSelectMode(void)
{
	LED_PORT  &=~(1<<KEYBOARD_LED);
	mode=COMMAND_SELECT;
}
void toParamMode(void)
{
	LED_PORT  |=1<<KEYBOARD_LED;
	mode=PARAM_SELECT;
}
void toExecuteMode(void)
{
	LED_PORT  |=1<<KEYBOARD_LED;
	mode=EXECUTING;
}
void onBump(void)
{
	USART_send("BUMP");
	//playTune(INIT_SOUND,0);
	//InitProgramStack();
	Disable_Interrupt
	haltAllPeripheral();
	rewind();
	toCommandSelectMode();
	Enable_Interrupt
}
void onEncoder(void)
{
	encoderCounter++;
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
	playTune(0,NULL);
	//initBT();			// init BT
	// Запуск фоновых задач.
	SetTask(AliveFlash);
	SetTask(TryExecuteNextCommand);
	SetTask(QKeyboard);
	SetTask(QBump);

	while(1) 		// Главный цикл диспетчера
	{
		wdt_reset();	// Сброс собачьего таймера
		TaskManager();	// Вызов диспетчера
	}

	return 0;
}
