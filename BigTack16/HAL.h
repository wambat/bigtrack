#ifndef HAL_H
#define HAL_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avrlibdefs.h"
#include "avrlibtypes.h"
//#include "avr/pgmspace.h"
#include <avr/wdt.h>

//Clock Config
#define F_CPU 8000000L

//System Timer Config
#define Prescaler	  		2
#define	TimerDivider  		(F_CPU/Prescaler/1000)		// 1 mS


//USART Config
#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)


//PORT Defines
#define FIRE_LED		5
#define	KEYBOARD_LED    6
#define	SERVICE_LED		7

#define LED_PORT 	PORTD
#define LED_DDR		DDRD
//KEYBOARD
#define KEYBOARD_PORT PORTA
#define KEYBOARD_PORT_IN PINA
#define KEYBOARD_DDR DDRA
#define KEYBOARD_PIN_0 PINA0
#define KEYBOARD_PIN_1 PINA1
#define KEYBOARD_PIN_2 PINA2
#define KEYBOARD_PIN_3 PINA3
#define KEYBOARD_PIN_4 PINA4
#define KEYBOARD_PIN_5 PINA5
#define KEYBOARD_PIN_6 PINA6
#define KEYBOARD_PIN_7 PINA7
//MOTORS
#define MOTOR_PORT PORTB
#define MOTOR_PORT_DDR DDRB
#define MOTOR_PIN_0 PINB0
#define MOTOR_PIN_1 PINB1
#define MOTOR_PIN_2 PINB2
#define MOTOR_PIN_3 PINB3
//SOUND
#define SOUND_PORT PORTD
#define SOUND_PORT_DDR DDRD
#define SOUND_PIN PIND6
#define SOUND_ISR  			TIMER0_COMP_vect
//SENSOR INTERRUPTS
#define SENSOR_INTERRUPT_ENCODER INT0
#define SENSOR_INTERRUPT_ENCODER_VECTOR INT0_vect
//#define SENSOR_INTERRUPT_BUMP INT1
//#define SENSOR_INTERRUPT_BUMP_VECTOR INT1_vect
#define SENSOR_BUMP_PORT PORTD
#define SENSOR_BUMP_DDR DDRD
#define SENSOR_BUMP_PIN PIND4
#define SENSOR_BUMP_PORT_IN PIND
extern void InitAll(void);



#endif
