/*
 * motors.c
 *
 *  Created on: Feb 1, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "Math.h"
#include "button.h"

float l0 = 142.868;
float l1 = 152.401;
float l2 = 152.518;

float numerator1;
float numerator2;
float denominator1;
float denominator2;

float pi = 3.14159265;

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min)*(out_max - out_min)/(in_max - in_min) + out_min;
}

int armLAngle(int counts) {
	return map(counts, 264.0, 669.0, 0.0, 90.0);
}
int armUAngle(int counts) {
	return map(counts, 270.0, 633.0, -90.0, 0.0);
}

/* Function: stopMotors
 * --------------------------------------
 * void
 * returns: nothing
 * purpose: sets all motors to stop
 */
void stopMotors() {
	setDAC(0, 0);
	setDAC(1, 0);
	setDAC(2, 0);
	setDAC(3, 0);
}

/* Function: gotoAngles
 * --------------------------------------
 * lowerTheta: value for the lower link
 * upperTheta: value for the upper link
 * returns: nothing
 * purpose: sets DAC until both of the theta values are met using if statements
 */
void gotoAngles(int lowerTheta, int upperTheta) {
	changeADC(2);
	int curLAngle = armLAngle(getADC(2));
	changeADC(3);
	int curHAngle = armUAngle(getADC(3));
	signed int lowVal = calcPID('L', lowerTheta, curLAngle);
	signed int upVal = calcPID('H', upperTheta, curHAngle);
	if (lowVal >= 0) {
		// write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(0, lowVal);
		setDAC(1, 0);
	}
	else if (lowVal < 0) {
		// write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(1, -lowVal);
		setDAC(0, 0);
	}
	if (upVal >= 0) {
		// write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(3, upVal);
		setDAC(2, 0);

	}
	else if (upVal < 0) {
		// write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(2, upVal);
		setDAC(3, 0);
	}
}

/* Function: radToDegree
 * --------------------------------------
 * rad: takes in radians given
 * returns: nothing
 * purpose: converts radians to degrees
 */
int radToDegree(float rad) {
	return (int)((rad/pi)*180.0);
}

/* Function: settled
 * --------------------------------------
 * setPoint: destination point
 * actPos: current position
 * returns: nothing
 * purpose: determines if arm has settled through ifs
 */
char settled(int setPoint, int actPos) {
	if (actPos - setPoint < 0) {
		if (actPos - setPoint > -6) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		if (actPos - setPoint < 6) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

/* Function: gotoXY
 * --------------------------------------
 * x: desired x value
 * y: desired y value
 * returns: nothing
 * purpose: uses inverse kinematics to calculate the arm angles based on the 
 * deisired input of the X and Y, sets DACs to move to those angles once calculated
 */
void gotoXY(int x, int y) {
	changeADC(2);
	int curLAngle = armLAngle(getADC(2));
	// clearADC(2);

	changeADC(3);
	int curHAngle = armUAngle(getADC(3));
	// clearADC(3);

	// Inverse Kinematics Angle Calculations
	float xF = (float) x; // cast to float because integer math overflowed
	float yF = (float) (y - l0); // cast to float because integer math overflowed

	float c2 = (xF*xF + yF*yF - l1*l1 - l2*l2)/(2.0 * l1*l2);
	float s2 = -sqrt(1.0 - c2*c2);
	float thetaH = (atan2(s2,c2)) * 180/pi;
	float thetaL = (atan2(yF,xF) - atan2(l1*s2, l1 + l2*c2)) * 180.0/pi;

	signed int lowVal = calcPID('L', (int) thetaL, curLAngle);
	signed int upVal = calcPID('H', (int) thetaH, curHAngle);

	if (lowVal >= 0) {
		// write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(0, lowVal);
		setDAC(1, 0);
	}
	else if (lowVal < 0) {
		// write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(1, -lowVal);
		setDAC(0, 0);
	}
	if (upVal >= 0) {
		// write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(3, upVal);
		setDAC(2, 0);

	}
	else if (upVal < 0) {
		// write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(2, upVal);
		setDAC(3, 0);

	}

	// print statements to show how we implemented 
	// printf("%d,\t%d\r\n", curLAngle, curHAngle);
	// printf("%f\t%d\t%f\t%d\r\n", thetaL, curLAngle, thetaH, curHAngle);
	// printf("%d\t%d\r\n", curLAngle, curHAngle);
	// printf("%f\r\n", thetaL);
}


/* Function: driveLink
 * --------------------------------------
 * link: the link that is to be driven, either L or H
 * dir: the direction it is driven
 * returns: nothing
 * purpose: sets DAC for both the lower and upper arms
 */
void driveLink(int link, int dir) {
	switch (link) {
	case 'L' :
		if (dir == 1) {
			setDAC(0, 2048);
			setDAC(1, 0);

		}
		else if (dir == 0) {
			setDAC(1, 2048);
			setDAC(0, 0);
		}
		break;
	case 'H' :
		if (dir == 1) {
			setDAC(2, 2048);
			setDAC(3, 0);

		}
		else if (dir == 0) {
			setDAC(3, 2048);
			setDAC(2, 0);
		}
		break;
	}
}

/* Function: homePos
 * --------------------------------------
 * void
 * returns: nothing
 * purpose: returns to the home position by calling gotoAngles
 */
void homePos() {
	gotoAngles(0, 0);
	encInit(0);
	resetEncCount(0);
	encInit(1);
	resetEncCount(1);
}


