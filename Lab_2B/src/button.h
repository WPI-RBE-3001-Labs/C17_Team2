/*
 * button.h
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

#ifndef BUTTON_H_
#define BUTTON_H_



extern int buttonState;
extern int prevButton;
extern signed int angle;

// initializes the buttons to be inputs through PortB
void initButtons();

// reads the current value of PortB to determine what button is pressed and sets the state based on that
void readButtons();

#endif /* SRC_BUTTON_H_ */
