/*
 * motors.c
 *
 *  Created on: Feb 1, 2017
 *      Author: bdknox
 */
float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return (x - in_min)*(out_max - out_min)/(in_max - in_min) + out_min;
}

int armLAngle(int counts) {
	return map(counts, 270.0, 698.0, 0.0, 90.0);
}
int armUAngle(int counts) {
	return map(counts, 270.0, 633.0, 0.0, 90.0);
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
	//int curLAngle = armLAngle(getADC(2));
	changeADC(3);
	int curHAngle = armUAngle(getADC(3));
	//signed int lowVal = calcPID('L', lowerTheta, curLAngle);
	signed int upVal = calcPID('H', upperTheta, curHAngle);
	/*if (lowVal >= 0) {
		//write to DAC_0 calcPID('L', 45, armAngle(getADC(2))
		setDAC(0, lowVal);
		setDAC(1, 0);
	}
	else if (lowVal < 0) {
		//write to DAC_1 (-)calcPID('L', 45, armAngle(getADC(2))
		setDAC(1, -lowVal);
		setDAC(0, 0);
	}*/
	if (upVal >= 0) {
		setDAC(2, upVal);
		setDAC(3, 0);

	}
	else if (upVal < 0) {
		setDAC(3, -upVal);
		setDAC(2, 0);

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
}
