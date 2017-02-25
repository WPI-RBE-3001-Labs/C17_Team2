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
int potL2 = 0;
signed int goToAngle = 0;
long blockCounter = 0;
int blockBool = FALSE;
int blockDist = 10000;

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
//	DDRCbits._P3 = INPUT;
//	DDRCbits._P7 = INPUT;
	//set output off
	PINCbits._P0 = OFF;


	//Global Interrupt Enable
	sei();

}

int main() {

	initRBELib();
	debugUSARTInit(115200);
	initADC(2);
	initADC(0);
	initADC(3);

	initADC(7); //IR sensor 1 //arbitrary
	initADC(6); //IR sensor 2 //arbitrary //near arm

	initSPI();
//	initButtons();
	initAltCom(115200);

	setConst('L', 67.0, 4.0, 1.75);
	setConst('H', 67.0, 4.0, 1.75);

	//gotoXY(0, 448);

	startTimer0();
	while (1) {

		setServo(7,0);

		//currentVal = calcPID('L', 45, armLAngle(potL1));
		//printf("\t%d\t", currentVal);

	}
}

ISR(TIMER0_COMPA_vect){
	potL1 = getADC(2);
	potL2 = getADC(3);
//	printf("\t%s\t", "Timer Interrupt, bicth");
	gotoXY(200, 200);

	/*
	setServo(7,0);
	setServo(6,060);
	int IRDistBelt = IRDist(7);
	if (IRDistBelt <= 150){
		blockBool = TRUE;
	}
	if (blockBool) {
		blockCounter++;
	}
	if (IRDistBelt < blockDist) {
		blockDist = IRDistBelt;
	}
	*/
//	printf("%d,\t%d,\t%d,\t%d\r\n", potL1, armLAngle(potL1), potL2, armUAngle(potL2));
//	printf("%d,\%d\r\n", IRDist(7), IRDist(6));
//	printf("%d,\t%d,\r\n", armLAngle(potL1), armUAngle(potL2));
	//readButtons();
	PORTCbits._P0 = OFF;
	timer0count++; // increment counter
	PORTCbits._P0 = ON;
}
