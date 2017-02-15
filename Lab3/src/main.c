/*
 * main.c
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "button.h"
#include "arm.h"
#include "sensors.h"

volatile unsigned short timer0count = 0;
int potCounts;
int potDegs;
int armPos;
int potmVolts;
int strtTime;
int dir;
int forLimit = 4096;
signed int currentVal;
int thisCurrentRaw;
signed int thisCurrent;
char isSettled = 0;
signed int testVal;
int counts = 0;
long total = 0;
int potL1 = 0;
signed int Ax = 0;
signed int Ay = 0;
signed int Az = 0;
signed int goToAngle = 0;//----------------------------------------------------------

void startTimer0(){
	//CTC mode (reset on compare A match)
	TCCR0A |= (1<<WGM01);
	//Enable comparison interrupts
	TIMSK0 |= (1<<OCIE0A);
	//set clock to 18000Hz and start timer
	TCCR0B |= (1<<CS02) | (1<<CS00);
	//trigger interrupt at 100 Hz
	OCR0A = 179;
	//OCR0A = 71;


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

	initRBELib();
	debugUSARTInit(115200);
	initADC(2);
	//initADC(0);
	//initADC(3);
	initSPI();
	encInit(0);
	resetEncCount(0);
	initButtons();
	setConst('L', 67.0, 4.0, 1.75);
	setConst('H', 67.0, 4.0, 1.75);

	//PORTAbits._P2 = 0;
	//PORTAbits._P3 = 0;
	//DDRAbits._P2 = OUTPUT;
	//DDRAbits._P3 = OUTPUT;
	startTimer0();
	while(1) {

	}

}

ISR(TIMER0_COMPA_vect){
	//pulse PINC0
	Ax = getAccel(0);
	Ay = getAccel(1);
	Az = getAccel(2);
	potL1 = getADC(2);
	encInit(0);
	counts = encCount(0);
	total += counts;
	printf("%ld,\t%d,\t%d,\t%d,\t%d\r\n", total, potL1, Ax, Ay, Az);
	readButtons();
	PORTCbits._P0 = OFF;
	timer0count++; // increment counter
	PORTCbits._P0 = ON;

}
