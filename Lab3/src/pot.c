/*
 * pot.c
 *
 *  Created on: Jan 24, 2017
 *      Author: bdknox
 */

/**
 * @brief Find the angle of the given potentiometer.
 * @param  pot The pot to check.
 * @return angle Angle of the potentiometer.
 *
 * @todo Calculate the angle using the ADC reading.
 */
int potAngle(int pot) {
	pot = pot*27;
	pot = pot/102;
	return pot;
}

/**
 * @brief Find the voltage value of the given potentiometer.
 * @param  pot The pot to get the value of.
 * @return volts Voltage of  potentiometer.
 *
 * @todo Convert the ADC value into a voltage in mV (so no floats needed).
 */
int potVolts(int pot) {
	pot = pot*5;
	return pot;
}
