///*
// * main.c
// *
// *  Created on: Jan 21, 2017
// *      Author: bdknox
// */
//#include "RBELib/RBELib.h"
//
//void beginTimer() {
//	initTimer(NORMAL, CTC, 1023);
//	//TCCR0A = 0b00000010; need TCCR0A to generate waveform
////	TCCR0A |= (1<<WGM01); but I don't understand why WGM01 and not WGM00; maybe CTC mode?
//	//TCCR0B = 0b00000
////	TCCR0B |= (1<<CS02) | (1<<CS00); CS in TCCR0B are clock set bits
//	//TIMSK0 = 0b00000010;
//}
//
//int main(void) {
//	initRBELib();
//	initADC(4); //needs int channel as arg
//	debugUSARTInit(115200);
//
//
//}

#include "RBELib/RBELib.h"
#include "RBELib/ADC.h"
#include "stdlib.h"
#include "avr/io.h"
#include "button.h"

volatile unsigned short timer0count = 0;
int potCounts;
int potmVolts = 0;
int potDegs;
int potPercent;
int countSec = 0;


void startTimer0(){
	//CTC mode (reset on compare A match)
	TCCR0A |= (1<<WGM01);
	//Enable comparison interrupts
	TIMSK0 |= (1<<OCIE0A);
	//set clock to 72000Hz and start timer
	TCCR0B |= (1<<CS02);
	//trigger interrupt at 1000 Hz
	OCR0A = 71;


	//set I/O pin to digital I/O
	PORTCbits._P0 = 0;
	//set direction as output
	DDRCbits._P0 = OUTPUT;
	//set output off
	PINCbits._P0 = OFF;

	//Global Interrupt Enable
	sei();

}

int main() {
	unsigned char rxChar;
	initRBELib();
	debugUSARTInit(115200);
	initADC(7);
	PORTCbits._P5 = 0; // configuring output port for oscilloscope
	DDRCbits._P5 = 1;
	// By selectively commenting/uncommenting each block of code, each part of the lab's required functionality can be enabled
	rxChar = getCharDebug();
	startTimer0();
	while(1){
	}
	return 0;
}

ISR(TIMER0_COMPA_vect){
	//pulse PINC0
	PORTCbits._P0 = OFF;
	timer0count++; // increment counter
	PORTCbits._P0 = ON;
	//Question 3
	/*readButtons();
	potCounts = getADC(7);
	potPercent = ((potCounts*10)/102);
	if(timer0count == ((1000/buttonState)*potPercent)){
		PINCbits._P5 = 1;
	}
	else{
		PINCbits._P5 = 0;
	}
	printf("%d\r\n", buttonState);
	if(timer0count == 1000){
		timer0count = 0;
	}*/

	//Question 2
	if (timer0count == 100) {  // all of this works for part 2 except timestamp
		potCounts = getADC(7);
		potmVolts = potVolts(potCounts); // determines input in milliVolts
		potDegs = potAngle(potCounts); // determines pot Angle
		countSec = countSec + 1;
		printf("%d,%d,%d,%d\r\n", countSec, potCounts, potmVolts, potDegs);
		//turn clock off
		//TCCR0B &= ~(1<<CS02);
		timer0count = 0;
	}

}
