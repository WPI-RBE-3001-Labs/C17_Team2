/*
 * SPI.c
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

#include "RBELib/RBELib.h"
#include "avr/io.h"
#include <RBELib/reg_structs.h>
#include <avr/interrupt.h>

/**
 * @brief Initializes the SPI bus for communication with all of your
 * SPI devices.
 *
 * @todo Create the function that will allow you to initialize the SPI
 * in a mode compatible with all devices.  Do not forget to deassert all
 * of your SS lines!
 */
void initSPI() {
	PORTC = 0x00;
	//PORTBbits._P5 = 0;
	//PORTBbits._P7 = 0;
	DDRDbits._P4 = OUTPUT;
	PORTDbits._P4 = HIGH;
	/* Set MOSI and SCK output, all others input */
	DDRB = (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR);//|(1<<SPR0);

	DDRC |= ((1<<DDC0) |// Deasserts spare SS
			(1<<DDC1) | // Deasserts CoProcessor SS
			(1<<DDC2) | // Deasserts spare SS
			(1<<DDC3) | // Deasserts spare SS
			(1<<DDC4) | // Deasserts encoder 1 SS
			(1<<DDC5) | // Deasserts encoder 0 SS
			(1<<DDC6)); // Deasserts spare SS
}


unsigned char spiTransceive(BYTE data) {
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	/* Read the register to see what was sent back*/
	return SPDR;
}
