/*
 * DAC.c
 *
 *  Created on: Jan 29, 2017
 *      Author: bdknox
 */
/*#include "RBELib/RBELib.h"
#include "stdlib.h"
#include "avr/io.h"

short sendVal;

void setDAC(int DACn, int SPIVal){
	PORTDbits._P4 = LOW;
	spiTransceive(0x30 + DACn);
	sendVal = (short) SPIVal;
	spiTransceive(sendVal<<4);
	sendVal = (short) SPIVal;
	spiTransceive(sendVal<<12);
	PORTDbits._P4 = HIGH;
}
*/
#include "RBELib/RBELib.h"

void setDAC(int DACn, int SPIval){
  //We need to send out 3 "packages" for configuring the DAC
  unsigned char package1 = 0;
  unsigned char package2 = 0;
  unsigned char package3 = 0;
  //Temp value for creating the packages from the SPI value
  unsigned long temp = 0;

  //Package 1 is:
  //Write to and update (power up) DAC register n
  package1 = (0x30 | DACn);

  //If value is over our max, cap it at 4095
  if(SPIval >= 4096) SPIval = 4095;

  //Copy the SPIval
  temp = SPIval;
  //Keep the upper 8 bits (drops bottom 4)
  temp = temp >> 4;
  //This is our second package
  package2 = temp;

  //Keep only the bottom 4 bits
  temp = SPIval & 0x000F;
  temp = temp << 4;
  //This will be our final package
  //The bottom 4 bits are don't cares
  package3 = temp;

  //Assert the DAC
  //DAC_SS = 0;
  PORTDbits._P4 = LOW;

  //transmit the 3 packets
  spiTransceive(package1);
  spiTransceive(package2);
  spiTransceive(package3);
  PORTDbits._P4 = HIGH;
  //Toggle the SS line to load and execute
//  DAC_SS = 1;
//  DAC_SS = 0;
//  DAC_SS = 1;
}


