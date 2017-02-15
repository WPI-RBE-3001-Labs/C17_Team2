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
	return map(counts, 270.0, 698.0, 0.0, 90.0);
}
int armUAngle(int counts) {
	return map(counts, 270.0, 633.0, -90.0, 0.0);
}
/**
 * @brief Helper function to stop the motors on the arm.
 *
 * @todo Create way to stop the motors using the DAC.
 */
void stopMotors() {
	setDAC(0, 0);
	setDAC(1, 0);
	setDAC(2, 0);
	setDAC(3, 0);
}

/**
 * @brief Drive the arm to a desired angle
 *
 * @param lowerTheta The desired angle for the lower link.
 * @param upperTheta The desired angle for the upper link.
 *
 * @todo Make a way to drive the links to a desired angle.
 */
void gotoAngles(int lowerTheta, int upperTheta) {
	changeADC(2);
	int curLAngle = armLAngle(getADC(2));
	changeADC(3);
	int curHAngle = armUAngle(getADC(3));
	signed int lowVal = calcPID('L', lowerTheta, curLAngle);
	signed int upVal = calcPID('H', upperTheta, curHAngle);
	if (lowVal >= 0) {
		//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(0, lowVal);
		setDAC(1, 0);
	}
	else if (lowVal < 0) {
		//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(1, -lowVal);
		setDAC(0, 0);
	}
	if (upVal >= 0) {
		//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(3, upVal);
		setDAC(2, 0);

	}
	else if (upVal < 0) {
		//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(2, upVal);
		setDAC(3, 0);

	}
}


//float square(float n) {
//	return (float)n*n;
//}

int radToDegree(float rad) {
	return (int)((rad/pi)*180.0);
}

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

/**
 * @brief Drive the end effector of the arm to a desired X and Y position in the workspace.
 *
 * @param x The desired x position for the end effector.
 * @param y The desired y position for the end effector.
 *
 * @todo Use kinematic equations to move the end effector to the desired position.
 */
void gotoXY(int x, int y) {
	while (1 == 1) {
		changeADC(2);
		int curLAngle = armLAngle(getADC(2));
		//clearADC(2);

		changeADC(3);
		int curHAngle = armUAngle(getADC(3));
		//clearADC(3);

		//	numerator1 =   -square(l2) + square(l1) + sqrt((square((float)x) + square((float)(y - l0))));
		//	denominator1 = 2.0*(l1*sqrt((square(x) + square((float)(y - l0)))));
		//	float theta1 = - pi/2 + acos(numerator1/denominator1) + atan2(y - l0, x);
		//
		//	numerator2 =   -sqrt(square((float)x) + square((float) (y - l0))) + square(l1) + square(l2);
		//	denominator2 = 2.0*l1*l2;
		//	float theta2 = - acos(numerator2/denominator2);
		//
		//	signed int thetaL = radToDegree(theta1);
		//	signed int thetaH = radToDegree(theta2);

		//	numerator2 =   (square(x) + square(y) - square(l2) - square(l1));
		//	denominator2 = 2.0*l1*l2;
		//	float theta2 = atan2((sqrt(1-(numerator1/denominator1))),(numerator1/denominator1));
		//
		//	numerator1 =   -sqrt(square((float)x) + square((float) (y - l0))) + square(l1) + square(l2);
		//	denominator1 = 2.0*l1*l2;
		//	float theta1 = - acos(numerator2/denominator2);

		//	signed int thetaL = radToDegree(theta1);
		//	signed int thetaH = radToDegree(theta2);

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
			//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
			setDAC(0, lowVal);
			setDAC(1, 0);
		}
		else if (lowVal < 0) {
			//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
			setDAC(1, -lowVal);
			setDAC(0, 0);
		}
		if (upVal >= 0) {
			//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
			setDAC(3, upVal);
			setDAC(2, 0);

		}
		else if (upVal < 0) {
			//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
			setDAC(2, upVal);
			setDAC(3, 0);

		}
		if(settled(thetaL,curLAngle) && settled(thetaH,curHAngle)){
			break;
		}
		//printf("%d,\t%d\r\n", curLAngle, curHAngle);
//		printf("%f\t%d\t%f\t%d\r\n", thetaL, curLAngle, thetaH, curHAngle);
		//	printf("%d\t%d\r\n", curLAngle, curHAngle);
		//	printf("%f\r\n", thetaL);
	}
}



/**
 * @brief Drive a link (upper or lower) in a desired direction.
 *
 * @param link Which link to control.
 * @param dir Which way to drive the link.
 *
 * @todo Create a way to drive either link in any direction.
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

/**
 * @brief Drive the arm to a "home" position using the potentiometers.  This
 * should be called before using the encoders and just goes to a default position.
 * Once this has been called once, you can initialize/clear the encoders.
 *
 * @todo Drive the arm to a known position using the potentiometers.
 */
void homePos() {
	gotoAngles(0, 0);
	encInit(0);
	resetEncCount(0);
	encInit(1);
	resetEncCount(1);
}


