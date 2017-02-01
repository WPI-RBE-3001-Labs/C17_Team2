/*
 * PID.c
 *
 *  Created on: Jan 29, 2017
 *      Author: bdknox
 */
#include "arm.h"
#include "button.h"

int testSetPoint = 45;
const int storeSize = 20;
char currentLink = 'L';
//float gainP = 2.5; //2.5 kinda works
//float gainI = 0.1; //0.1; //.1 kinda works
//float gainD = 0.06; //.015 kinda works
//float gainP = 20; //2.5 kinda works
//float gainI = 1.25; //.1 kinda works
//float gainD = 0.5; //.015 kinda works
//float gainP = 3.0; //2.5 kinda works
//float gainI = 0.3; //.1 kinda works
//float gainD = 0.03; //.015 kinda works
float gainP = 67.0; // 80 kinda works
float gainI = 4.0; // 7.5 kinda works
float gainD = 1.75; //.85 kinda works
float history[20];
int value;


struct {float Kp_H; float Ki_H; float Kd_H; float Kp_L; float Ki_L; float Kd_L; } pidConst;

void setConst(char link, float Kp, float Ki, float Kd) {
	//if setConst is used the way its supposed to be used:
	switch (link) {
	case 'H':
		pidConst.Kp_H = Kp;
		pidConst.Ki_H = Ki;
		pidConst.Kd_H = Kd;
		break;
	case 'L':
		pidConst.Kp_L = Kp;
		pidConst.Ki_L = Ki;
		pidConst.Kd_L = Kd;
		break;
	}
	//------------------proper code ends here --------------------
	//	int currentAng = armAngle(getADC(2));
	//	int target = angle;
	//	if (currentAng < target && currentAng >= 0) {
	//		gainP = 3.0*Kp; //part8_3
	//		gainI = 0;
	//		gainD = Kd;
	//	}
	//	else if ((currentAng > target) && currentAng <= 90) {
	//		gainP = 0.7*Kp; //part8_2
	//		gainI = Ki;
	//		gainD = 3.0*Kd;
	//	}
	//	else {
	gainP = Kp; //part8_1
	gainI = Ki;
	gainD = Kd;
	//}
}

int calcError(int setPoint, int actPos) {
	//int armPos = armAngle(getADC(2));
	return setPoint - actPos;  //figure out what's wrong with this
}

void updateHistory(int setPoint, int actPos) {
	float current = calcError(setPoint, actPos);
	for(int i = 0; i < 20; i++) {
		if(i == storeSize - 1) {
			history[i] = current;
		}
		else {
			history[i] = history[i + 1];
		}
	}
}

int sumPastError(int setPoint, int actPos) {
	updateHistory(setPoint, actPos);
	int total = 0;
	for(int i = 0; i < storeSize; i++) {
		total += history[i];
	}
	return total;
}

int calcDifference(int actPos) {
	//int armPos = armAngle(getADC(2));
	return actPos - history[storeSize - 1];
}


signed int calcPID(char link, int setPoint, int actPos) {
	switch (link) {
	case 'L' :
		value = (signed int) (
				pidConst.Kp_L*calcError(setPoint, actPos) +
				pidConst.Ki_L*sumPastError(setPoint, actPos) +
				pidConst.Kd_L*calcDifference(actPos)
		);
		break;
	case 'H' :
		value = (signed int) (
				pidConst.Kp_H*calcError(setPoint, actPos) +
				pidConst.Ki_H*sumPastError(setPoint, actPos) +
				pidConst.Kd_H*calcDifference(actPos)
		);
		break;
	}
	return value;
	}
