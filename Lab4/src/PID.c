/*
 * PID.c
 *
 *  Created on: Jan 29, 2017
 *      Author: bdknox
 */
#include "arm.h"
#include "button.h"
#include "RBELib/RBELib.h"

// variables
int calcError(int setPoint, int actPos);
int sumPastError(int setPoint, int actPos, char link);
void updateHistory(int setPoint, int actPos, char link);
int calcDifference(int actPos, char link);
int testSetPoint = 45;
const int storeSize = 20;
char currentLink = 'L';
pidConst pidConsts;
float gainP = 67.0; // 80 kinda works
float gainI = 4.0; // 7.5 kinda works
float gainD = 1.75; //.85 kinda works
float historyL[20];
float historyH[20];
int value;


/* Function: setConst
 * --------------------------------------
 * link: desired link
 * Kp: proportional value
 * Ki: integral value
 * Kd: derivative value
 * returns: nothing
 * purpose: sets the PID constants for the upper and lower links
 */
void setConst(char link, float Kp, float Ki, float Kd) {
	// if setConst is used the way its supposed to be used:
	switch (link) {
	case 'H':
		pidConsts.Kp_H = Kp;
		pidConsts.Ki_H = Ki;
		pidConsts.Kd_H = Kd;
		break;
	case 'L':
		pidConsts.Kp_L = Kp;
		pidConsts.Ki_L = Ki;
		pidConsts.Kd_L = Kd;
		break;
	}
}

/* Function: calcError
 * --------------------------------------
 * setPoint: desired point
 * actPoint: current point
 * returns: desired minus actual points
 * purpose: calculating error through difference in points, actual vs desired
 */
int calcError(int setPoint, int actPos) {
	//int armPos = armAngle(getADC(2));
	return setPoint - actPos;  //figure out what's wrong with this
}

/* Function: updateHistory
 * --------------------------------------
 * setPoint: desired point
 * actPos: actual position
 * link: desired link
 * returns: nothing
 * purpose: counts history of two links and stores current values to history
 */
void updateHistory(int setPoint, int actPos, char link) {
	float current = calcError(setPoint, actPos);
	for(int i = 0; i < 20; i++) {
		if(i == storeSize - 1) {
			if(link == 'L') {
				historyL[i] = current;
			}
			else {
				historyH[i] = current;
			}
		}
		else {
			if(link == 'L') {
				historyL[i] = historyL[i + 1];
			}
			else {
				historyH[i] = historyH[i + 1];
			}
		}
	}
}

/* Function: sumPastError
 * --------------------------------------
 * setPoint: desired position
 * actPos: current position
 * link: desired link
 * returns: total, of past error
 * purpose: sums the error to fulfill the I component of the PID controller
 */
int sumPastError(int setPoint, int actPos, char link) {
	updateHistory(setPoint, actPos, link);
	int total = 0;
	for(int i = 0; i < storeSize; i++) {
		if(link == 'L') {
			total += historyL[i];
		}
		else {
			total += historyH[i];
		}
	}
	return total;
}

/* Function: calcDifference
 * --------------------------------------
 * actPos: current position
 * link: desired link
 * returns: a comparison between actual position and history
 * purpose: compares history of either upper or lower arm, to geterate the D
 * of the PID controller
 */
int calcDifference(int actPos, char link) {
	if(link == 'L') {
		return actPos - historyL[storeSize - 1];
	}
	else {
		return actPos - historyH[storeSize - 1];
	}
}

/* Function: calcPID
 * --------------------------------------
 * link: desired link
 * setPoint: the desired location
 * actPos: the current position
 * returns: nothing
 * purpose: calculates PID for the upper and lower links, providing numbers for the 
 * PID controller values
 */
signed int calcPID(char link, int setPoint, int actPos) {
	switch (link) {
	case 'L' :
		value = (signed int) (
				40.0*calcError(setPoint, actPos) +
				4.0*sumPastError(setPoint, actPos, 'L') +
				1.75*calcDifference(actPos, 'L')
		);
		break;
	case 'H' :
		value = (signed int)(
				40.0*calcError(setPoint, actPos) +
				2.0*sumPastError(setPoint, actPos, 'H') +
				1.0*calcDifference(actPos, 'H')
		);
		break;
	}
	//printf("%d\t%d\r\n", setPoint, actPos);
	return value;
}
