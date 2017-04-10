#ifndef HARDWARE_H_
#define HARDWARE_H_

#define F_CPU 8000000UL

#include "usart/uart_text_io.h"
#include "relay/relay.h"

#define USART_BAUDRATE 115200L

//System Timer Config
#define Prescaler	  		64
#define	TimerDivider  		(F_CPU/Prescaler/1000)		// 1 mS

//#define STATUS_PORT PORTD
//#define STATUS_DDR	DDRD
//#define STATUS_PIN	PIND4

#define RELAY_PORT	PORTD
#define RELAY_DDR	DDRD
#define RELAY_PIN	PIND5

//#define PIN1_DDR	DDRD
//#define PIN1_PORT	PORTD
//#define PIN1_PIN	PIND2
//
//#define PIN2_DDR	DDRD
//#define PIN2_PORT	PORTD
//#define PIN2_PIN	PIND3
//
//#define PIN3_DDR	DDRB
//#define PIN3_PORT	PORTB
//#define PIN3_PIN	PINB3
//
//#define PIN4_DDR	DDRB
//#define PIN4_PORT	PORTB
//#define PIN4_PIN	PINB4

#endif /* HARDWARE_H_ */