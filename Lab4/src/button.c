/*
 * button.c
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"

// variables
int buttonState;
int prevButton;
signed int angle;
signed int prevAngle;
int pawsX = 200;
int pawsY = 200;
int val = 0;

void initButtons(){
	//	DDRBbits._P4 = INPUT;
	//	DDRBbits._P5 = INPUT;
	//	DDRBbits._P6 = INPUT;
	//	DDRBbits._P7 = INPUT;

	PORTCbits._P3 = 0;
	PORTCbits._P7 = 0;

	DDRCbits._P1 = INPUT;
	DDRCbits._P2 = INPUT;
	DDRCbits._P3 = INPUT;
	DDRCbits._P7 = INPUT;

	PINCbits._P3 = OFF;
	PINCbits._P7 = OFF;
	//printf("%d\r\n", PINBbits._P7);
}

/* Function: readButtons
 * --------------------------------------
 * void
 * returns: nothing
 * purpose: checks for button press, if given a value then sets action
 * values: 46, 166, 170, and 172
 */
void readButtons(){

	//		// Voltage 0
	//		if (PINC == 46) {
	//			setDAC(0, 0);
	//			setDAC(1, 0);
	//		}
	//		// Voltage -3
	//		else if (PINC == 166) {
	//			setDAC(0, 0);
	//			setDAC(1, 963);
	//		}
	//		// Voltage +3
	//		else if (PINC == 170) {
	//			setDAC(0, 963);
	//			setDAC(1, 0);
	//		}
	//		// Voltage +6
	//		else if (PINC == 172) {
	//			setDAC(0, 1933);
	//			setDAC(1, 0);
	//		}
	// Code for four arm positions
	if (PINC == 58) {
		val = 58;
	}
	else if (PINC == 178) {
		val = 178;
	}

	switch (val) {
	case 58:
		gotoAngles(0,0);
		break;
	case 178:
		gotoAngles(90,0);
		break;
	}

}
