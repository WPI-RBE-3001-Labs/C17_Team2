/*
 * DAC.c
 *
 *  Created on: Jan 29, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"

/* Function: setDAC
 * --------------------------------------
 * DACn: first value, accepting the DAC number that is being set
 * SPIval: second value, the number that is given to the SPI to set
 * returns: nothing
 * purpose: sets DAC val that is give to whatever SPIval that is passed
 */
void setDAC(int DACn, int SPIval){
  // sends out 3 "packages" for configuring the DAC
  unsigned char package1 = 0;
  unsigned char package2 = 0;
  unsigned char package3 = 0;
  // temp value for creating the packages from the SPI value
  unsigned long temp = 0;

  // package 1:
  // write to and update (power up) DAC register n
  package1 = (0x30 | DACn);

  // if value is over our max, cap it at 4095
  if(SPIval >= 4096) SPIval = 4095;

  // copy the SPIval
  temp = SPIval;
  // keep the upper 8 bits (drops bottom 4)
  temp = temp >> 4;
  // second package
  package2 = temp;

  // keep only the bottom 4 bits
  temp = SPIval & 0x000F;
  temp = temp << 4;
  // final package
  // the bottom 4 bits are don't cares
  package3 = temp;

  // assert the DAC
    // DAC_SS = 0;
  PORTDbits._P4 = LOW;

  // transmit the 3 packets
  spiTransceive(package1);
  spiTransceive(package2);
  spiTransceive(package3);
  PORTDbits._P4 = HIGH;
  //Toggle the SS line to load and execute
    //  DAC_SS = 1;
    //  DAC_SS = 0;
    //  DAC_SS = 1;
}


