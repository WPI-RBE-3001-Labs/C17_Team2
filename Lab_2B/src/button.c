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
	DDRCbits._P3 = INPUT;
	DDRCbits._P5 = INPUT;
	DDRCbits._P7 = INPUT;
	//printf("%d\r\n", PINBbits._P7);
}

// buttonState doesn't hold when no buttons are pressed like it should
void readButtons(){

	//	if (PINCbits._P1 == 0) {
	//		angle = 0;
	//	}
	//	else if (PINCbits._P3 == 0) {
	//		angle = 30;
	//	}
	//	else if (PINCbits._P5 == 0) {
	//		angle = 60;
	//	}
	//	else if (PINCbits._P7 == 0) {
	//		angle = 90;
	//	}
//	if (PINC == 42) {
//		angle = 0;
//		prevAngle = angle;
//	}
//	else if (PINC == 138) {
//		angle = 30;
//		prevAngle = angle;
//	}
//	else if (PINC == 162) {
//		angle = 60;
//		prevAngle = angle;
//	}
//	else if (PINC == 168) {
//		angle = 90;
//		prevAngle = angle;
//	}
//	else{
//		angle = prevAngle;
//	}
	if (PINC == 42) {
			pawsX = 50;
			pawsY = 370;
		}
		else if (PINC == 138) {
			pawsX = 120;
			pawsY = 400;
		}
		else if (PINC == 162) {
			pawsX = 110;
			pawsY = 330;
		}
		else if (PINC == 168) {
			pawsX = 250;
			pawsY = 150;
		}
		else{
			gotoXY(pawsX,pawsY);
		}
	/*// first tried completing this with a state machine, but it didn't work
	switch(PINB){
	case 100:
		buttonState = 1;
		prevButton = buttonState;
		break;
	case 164:
		buttonState = 20;
		prevButton = buttonState;
		break;
	case 196:
		buttonState = 100;
		prevButton = buttonState;
		break;
	default:
		buttonState = prevButton;
		break;
	}
	 */
	//prevButton = buttonState;
}
