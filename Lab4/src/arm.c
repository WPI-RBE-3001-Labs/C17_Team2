/*
 * arm.c
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"

/* Function: moveArm
 * --------------------------------------
 * PIDval: value of the PID passed once calculated
 * returns: nothing
 * purpose: sets arm to move based on the value given by the PID
 */
void moveArm(signed int PIDval) {
	//if (settledYet == 1) {
		if (PIDval >= 0) {
			//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
			setDAC(3, PIDval);
			setDAC(2, 0);

		}
		else if (PIDval < 0) {
			//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
			setDAC(2, -PIDval);
			setDAC(3, 0);

		}
//	}
}
