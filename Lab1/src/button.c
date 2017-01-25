/*
 * button.c
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "avr/io.h"
#include <RBELib/reg_structs.h>
#include <avr/interrupt.h>
#include "button.h"

int buttonState;
int prevButton;

void initButtons(){
	PORTB = 0x00;
	DDRB = 0x00;
	//printf("%d\r\n", PINBbits._P7);
}

// buttonState doesn't hold when no buttons are pressed like it should
void readButtons(){
	if ((PINB != 100) && (PINB != 164) && (PINB != 196)) {
		buttonState = prevButton;
	}
	else if (PINB == 100) {
		buttonState = 1;
		prevButton = buttonState;
	}
	else if (PINB == 164) {
		buttonState = 20;
		prevButton = buttonState;
	}
	else if (PINB == 196) {
		buttonState = 100;
		prevButton = buttonState;
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
