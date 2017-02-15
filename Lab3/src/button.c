/*
 * button.c
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"


int buttonState;
int prevButton;
signed int angle;
signed int prevAngle;
int pawsX = 200;
int pawsY = 200;

void initButtons(){
	//	DDRBbits._P4 = INPUT;
	//	DDRBbits._P5 = INPUT;
	//	DDRBbits._P6 = INPUT;
	//	DDRBbits._P7 = INPUT;
	DDRCbits._P1 = INPUT;
	DDRCbits._P2 = INPUT;
	DDRCbits._P3 = INPUT;
	DDRCbits._P7 = INPUT;
	//printf("%d\r\n", PINBbits._P7);
}

// buttonState doesn't hold when no buttons are pressed like it should
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
	if (PINC == 46) {
		setDAC(0, 0);
		setDAC(1, 0);
	}
	else if (PINC == 166) {
		gotoXY(0,0);
	}
	//		else if (PINC == 162) {
	//			pawsX = 110;
	//			pawsY = 330;
	//		}
	//		else if (PINC == 168) {
	//			pawsX = 250;
	//			pawsY = 150;
	//		}
	//		else{
	//			gotoXY(pawsX,pawsY);
	//		}
}
