/*
 * arm.c
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "avr/io.h"
#include <RBELib/reg_structs.h>
#include <avr/interrupt.h>

//int map(int x, int min1, int max1, int min2, int max2){
//  return (min2 + (((max2 - min2)* (x - min1))/(max1 - min1)));
//}

void moveArm(signed int PIDval) {
	//if (settledYet == 1) {
		if (PIDval >= 0) {
			//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
			setDAC(0, PIDval);
			setDAC(1, 0);

		}
		else if (PIDval < 0) {
			//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
			setDAC(1, -PIDval);
			setDAC(0, 0);

		}
//	}
}

char settled(int setPoint, int actPos) {
	if (actPos - setPoint < 0) {
		if (actPos - setPoint > -3) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		if (actPos - setPoint < 3) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

//void moveArm(signed int PIDval) {
//		setDAC(0, PIDval);
//}
