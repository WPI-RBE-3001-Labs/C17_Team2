/*
 * sensors.c
 *
 *  Created on: Feb 14, 2017
 *      Author: bdknox
 */
#include "RBELib/RBELib.h"

// variables
long currentCount;
long lastCount0 = 0;
long lastCount1 = 0;
long difference;

/* Function: EncoderCounts
 * --------------------------------------
 * __chan: channel of the encoder
 * returns: difference, between the values
 * purpose: to track encoder counts and return how many have elapsed
 * since last called
 */
int EncoderCounts(int __chan) {
	if (__chan == 0){
		currentCount = encCount(0);
		difference = currentCount - lastCount0;
		lastCount0 = currentCount;
	}
	else if(__chan == 1) {
		currentCount = encCount(1);
		difference = currentCount - lastCount1;
		lastCount1 = currentCount;
	}
	else {
		difference = -1;
	}
	return difference;
}

/* Function: GetAcceleration
 * --------------------------------------
 * __axis: determines which axis is in question
 * returns: accelVal, the value of the acceleration
 * purpose: to determine the acceleration of the accelerometer
 */
int GetAcceleration(int __axis) {
	int accelVal = 0x0000;
	int temp1 = 0x0000;
	int temp2 = 0x0000;
	PORTDbits._P7 = 0;
	spiTransceive(0x06);
	if (__axis == 0) {
		temp1 = spiTransceive(0x00);
		temp2 = spiTransceive(0x00);
	}
	else if (__axis == 1) {
		temp1 = spiTransceive(0x01);
		temp2 = spiTransceive(0x00);
	}
	else if (__axis == 2) {
		temp1 = spiTransceive(0x02);
		temp2 = spiTransceive(0x00);
	}
	PORTDbits._P7 = 1;
	accelVal |= (temp1<<8) | (temp2);
	return accelVal;
}
