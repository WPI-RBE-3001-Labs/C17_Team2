/*
 * arm.h
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

#ifndef SRC_ARM_H_
#define SRC_ARM_H_


// takes in a number and maps it from one range of values to another
float map(float x, float in_min, float in_max, float out_min, float out_max);

// function takes in potentiometer counts and uses map function
// to find the angle of the arm
int armAngle(int counts);

void moveArm(signed int PIDval);//, char settledYet);

//char settled(int setPoint, int actPos);

#endif /* SRC_ARM_H_ */
