/*
 * ADC.c
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "avr/io.h"
#include <RBELib/reg_structs.h>
#include <avr/interrupt.h>

void initADC(int channel) {
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enable ADC and conversion complete interrupt
	ADMUX |= (1<<REFS0) | (channel&0x07); // enable external ref. voltage; use only 3 lowest bits, single conversion
	PRR &= ~(1<<PRADC); // turn power reduction mode off
}

void clearADC(int channel) {
	ADCSRA &= ~(1<<ADEN); // disables ADC
	ADMUX |= (0x1F); // connects ADC to Ground (0 V)
}

unsigned short getADC(int channel) {
	ADMUX &= ~(0x07); // set all bits for channel select to 0
	ADMUX |= (channel&0x07); // use only 3 lowest bits, single conversion
	ADCSRA |= (1<<ADSC); // start conversion
	char counts = 0;
	while (ADSC == 1) { // wait until conversion is complete
		counts++;
	}
	return ADC;
}
