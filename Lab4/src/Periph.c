/*
 * Periph.c
 *
 *  Created on: Feb 14, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"

#define CLR_CNTR 0x20
#define WRITE_MDR0 0x88
#define WRITE_MDR1 0x90

/* Function: startTimer0
 * --------------------------------------
 * chan: takes in the channel of the IR
 * returns: nothing
 * purpose: calculates object IR distance using determine constants, given in the docs
 */
int IRDist(int chan) {
	changeADC(chan);
	float volts = (float)(getADC(chan))*0.0048828125;
	float distance = (float)((387.83339)*pow(volts, -1.224))-6.41684;
	return (int)(distance);
}