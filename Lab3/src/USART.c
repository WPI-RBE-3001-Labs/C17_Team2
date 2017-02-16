/*
 * USART.c
 *
 *  Created on: Jan 26, 2015
 *      Author: joest
 */


#include "RBELib/RBELib.h"
#include <avr/io.h>

#define UBRR115200 9
#define UBRR9600 119

void debugUSARTInit(unsigned long baudrate){
	if (baudrate == 115200) {
		UBRR1 = UBRR115200;
	} else if (baudrate == 9600) {
		UBRR1 = UBRR9600;
	} else {
		UBRR1 = UBRR115200; // default if unrecognized setting
	}

	UCSR1B |= (1<<RXEN1) | (1<<TXEN1); // enable transmit and receive
	UCSR1C |= (1<<UCSZ10) | (1<<UCSZ11); // 8 bit char size

}

void putCharDebug(char byteToSend){
	while(UCSR1A & (1<<RXC1)){
		char jon = UDR1;
	}
	UDR1 = byteToSend;
	while(!(UCSR1A & (1<<UDRE1))){

	}

}

unsigned char getCharDebug(void) {
	while(!(UCSR1A & (1<<RXC1))){ // wait for character to be completely received

	}
	char data = UDR1;
	return data; // read and return the character received
}
