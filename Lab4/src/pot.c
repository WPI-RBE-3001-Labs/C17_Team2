/*
 * pot.c
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

/* Function: potAngle
 * --------------------------------------
 * pot: potentiometer number
 * returns: pot, the calculated number
 * purpose: determines angle of potentiometer
 */
int potAngle(int pot) {
	pot = pot*27;
	pot = pot/102;
	return pot;
}

/* Function: potVolts
 * --------------------------------------
 * pot: potentiometer number
 * returns: pot, the calculated number
 * purpose: finding the potentiometer volts
 */
int potVolts(int pot) {
	pot = pot*5;
	return pot;
}
