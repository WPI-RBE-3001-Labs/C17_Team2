/*
 * main.c
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "button.h"
#include "arm.h"

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
signed int goToAngle = 0;//----------------------------------------------------------

void startTimer0(){
	//CTC mode (reset on compare A match)
	TCCR0A |= (1<<WGM01);
	//Enable comparison interrupts
	TIMSK0 |= (1<<OCIE0A);
	//set clock to 18000Hz and start timer
	TCCR0B |= (1<<CS02); //| (1<<CS00);
	//trigger interrupt at 100 Hz
	//OCR0A = 179;
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

	initRBELib();
	debugUSARTInit(115200);
	initADC(2);
	initADC(0);
	initADC(3);
	initSPI();
	initButtons();
	setConst('L', 67.0, 4.0, 1.75);
	setConst('H', 67.0, 4.0, 1.75);

	//PORTAbits._P2 = 0;
	//PORTAbits._P3 = 0;
	//DDRAbits._P2 = OUTPUT;
	//DDRAbits._P3 = OUTPUT;

	while(1) {
		startTimer0();
		//printf("%d,%d\r\n", angle,PINC);
		//changeADC(3);

		gotoXY(0,448);

		gotoXY(304,0);

		//Triangle Below:
		//gotoAngles(90, -90);
//		gotoXY(50, 370); //vertex

//		gotoXY(64, 376);
//		gotoXY(85, 385);
//		gotoXY(106, 394);

//		gotoXY(120, 400); //vertex

//		gotoXY(118, 386);
//		gotoXY(115, 365);
//		gotoXY(112, 344);

//		gotoXY(110, 330); //vertex

//		gotoXY(98, 338);
//		gotoXY(80, 350);
//		gotoXY(62, 362);
		//testVal = calcPID('H', 0, armUAngle(getADC(3)));
		//moveArm(testVal);
		//printf("%d,%d\r\n", testVal, armUAngle(getADC(3)));





	}


	//	while(1) {
	//		potCounts = getADC(2);
	//		armPos = armAngle((float)potCounts);
	//		potmVolts = potVolts(potCounts);
	//		printf("%d,%d,%d\r\n", potCounts, potmVolts, armPos);
	//		_delay_ms(100);
	//	}

/*

		while(1) {
			//Do some clock ticks or something
			startTimer0();
			int jon = 0;
			for(int i = 0; i < forLimit; i++) {
				strtTime = timer0count;
				if (i < forLimit/2) {
					dir = 1;
				}
				else {
					dir = -1;
				}
				jon += dir;
				printf("%d\r\n", jon);
				setDAC(0, jon);
				setDAC(1,(forLimit/2 - jon));
				//while(strtTime + 1 > timer0count){

				//}
				//timer0count = 0;
			}
		}
		*/
}

ISR(TIMER0_COMPA_vect){
	//pulse PINC0
//	readButtons();
//	goToAngle = angle;
	PORTCbits._P0 = OFF;
	timer0count++; // increment counter
	PORTCbits._P0 = ON;
//	changeADC(2);
	//_delay_ms(100);
	// ----------------------  input values here? syntax error ... pidConsts = {}
//	setConst('L', 67.0, 4.0, 1.75);
	//currentVal = calcPID('L', goToAngle, armAngle(getADC(2)));
	//isSettled = settled(armAngle(getADC(2)), goToAngle);
	//moveArm(currentVal);
//	changeADC(0);
//	thisCurrentRaw = getADC(0);

	//Here is the raw current response -> actual current piece-wise conversion
/*	if (armLAngle(getADC(2)) > 70 || armLAngle(getADC(2)) < 20) {
		thisCurrent = (signed int) ((3.805556 * (float) thisCurrentRaw) - 2051.916667);
	}
	else {
		thisCurrent = (signed int) ((3.888889 * (float) thisCurrentRaw) - 2116.66667);
	}
	//-----------------------------------------------------------------------
	potCounts = getADC(2);
	potmVolts = potVolts(potCounts);
//	printf("%s%d \t%s%d \t%s%d%s \t%s%d%s \t%s%d\r\n", "PIDval: ",
//			currentVal, "potRaw: ", getADC(2), "armAngle: ", armAngle(getADC(2)),
//			" deg", "actualCurrent: ", thisCurrent, " mA", "Raw: ", thisCurrentRaw);
	//printf("%d,%d,%d,%d\r\n", goToAngle, armAngle(getADC(2)), currentVal, thisCurrent);*/
}
