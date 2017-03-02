/*
 * main.c
 *
 *  Created on: Jan 27, 2017
 *      Author: bdknox
 */

// Libraries
#include "RBELib/RBELib.h"
#include "button.h"
#include "arm.h"
#include "sensors.h"


// potentiometer values
int potCounts;
int potDegs;
int armPos;
int potmVolts;
int strtTime;
int potL1 = 0;
int potL2 = 0;
int dir;
int forLimit = 4096;

// holders
signed int currentVal;
int thisCurrentRaw;
signed int thisCurrent;

// IR counters
int counts = 0;
long total = 0;
int blockCounter = 0;
int blockBool = FALSE;
int blockDist = 1000;
int baseDist = 1000;
unsigned int IRDistBelt = 1000;
int IRDistPick = 1000;
int IRtotal;

// angle calcs
signed int goToAngle = 0;
int gotoX = 5;
int gotoY = 420;

// state machine vars
int timeToPick = FALSE;
int picked = FALSE;
int timeToCheck = TRUE;
int belt = 7;
int base = 6;
volatile int thisCount = 0;
volatile unsigned short timer0count = 0;
int tempBeltDist = 1000;
int tempBaseDist = 1000;
enum {wait, lineUp, grab, close, liftUp, currentSense, depositFront, depositBack} state = wait;
int angles = FALSE;

/* Function: startTimer0
 * --------------------------------------
 * void
 * returns: nothing
 * purpose: initializes timer, comparing interupts, sets clock, and 
 * defines interrupt frequency
 */
void startTimer0(){
	//CTC mode (reset on compare A match)
	TCCR0A |= (1<<WGM01);
	//Enable comparison interrupts
	TIMSK0 |= (1<<OCIE0A);
	//set clock to 18000Hz and start timer
	TCCR0B |= (1<<CS02) | (1<<CS00);
	//trigger interrupt at 100 Hz
	OCR0A = 179;
	//OCR0A = 71;


	//set I/O pin to digital I/O
	PORTCbits._P0 = 0;
	//set direction as output
	DDRCbits._P0 = OUTPUT;
	//	DDRCbits._P3 = INPUT;
	//	DDRCbits._P7 = INPUT;
	//set output off
	PINCbits._P0 = OFF;


	//Global Interrupt Enable
	sei();

}

/* Function: beltRange
 * --------------------------------------
 * value: number that the defines the range of the belt
 * returns: an average, total over 5
 * purpose: determines the range for the conveyor, takes average of values
 * and returns them as int
 */
int beltRange(int value) {
	//	int dist = 0;
	int total = 0;
	int sumCounter = 0;
	while(sumCounter < 5) {
		if(value >= 80){
			total+=value;
			sumCounter++;
		}
	}
	return (int) (total/5);
}

/* Function: grabLowest
 * --------------------------------------
 * beltBase: 
 * returns: the lowest value that is calculated
 * purpose: this holds the lowest value that is observed over a 5 count average,
 * this is used to determine block distance
 */
int grabLowest(char beltBase) { //'b' = belt and 'B' = Base
	int value = 0;
	int low = 1000;
	thisCount = 0;
	if(beltBase == 'b') {
		while(thisCount < 50) {
			printf("%s", "");
			value = beltRange(tempBeltDist);
			if (value < low) {
				low = value;
			}
		}
	}
	else if(beltBase == 'B') {
		while(thisCount < 10) {
			printf("%s", "");
			value = beltRange(tempBaseDist);
			if (value < low) {
				low = value;
			}
		}
	}

	return low;
}

/* Function: inRange
 * --------------------------------------
 * lowest: 
 * returns: a range, if both the lowest +-10 are greater or less than
 * purpose: determing if the returned value is an acceptable range on the conveyor,
 * indicates if reading is a block or not
 */
int inRange(int lowest) {
	int theRange = blockDist;
	return ((lowest < theRange + 10) && (lowest > theRange - 10));
}

/* Function: waitState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 1 of the state machine, sets arm in the up position
 */
void waitState() {
	angles = FALSE;
	unsigned int tempDist = beltRange(tempBeltDist);
	gotoX = 5;
	gotoY = 420;

	if (tempDist <= 155) {
		blockDist = grabLowest('b') + 15;
		state = lineUp;
	}
	setServo(6,30);
	baseDist = 1000;
}

/* Function: lineUpState
 * --------------------------------------
 * xcoord:  
 * returns: nothing
 * purpose: state 2, moves to X position after reading from IR 1,
 * aligns to then move to grabState
 */
void lineUpState(int xcoord){
	gotoX = (int) (1.6*(float)xcoord);
	//	gotoY = (int)(1.9*(float)(xcoord))+45;
	//	gotoY = 2*xcoord+35;
	gotoY = 200;

	baseDist = grabLowest('B');
	if (inRange(baseDist)) {
		state = grab;
	}
}

/* Function: grabState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 3, dropping from line up to ready to grip, 
 * when IR 2 is tripped
 */
void grabState(int xcoord){
	thisCount = 0;
	while(thisCount < 15);

	if (xcoord < 110) {
		gotoY = 130;
		gotoX = (int) (1.825*(float)xcoord);
		thisCount = 15;
	}
	else if (xcoord < 135 && xcoord >= 110) {
		gotoY = 132;
		gotoX = (int) (1.725*(float)xcoord);
		thisCount = 0;
	}
	else {
		gotoY = 135;
		gotoX = (int) (1.6*(float)xcoord);
		thisCount = 0;
	}
	thisCount = 0;

	state = close;

}

/* Function: closeState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 4, the actuation of the gripper
 */
void closeState() {
	while(thisCount < 30); // busy loop, used for timing
	setServo(6,230);
	thisCount = 0;
	while(thisCount < 20); // busy loop, used for timing
	state = liftUp;
}

/* Function: liftUpState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 5, after gripped, lifing from the conveyor
 */
void liftUpState() {


	angles = TRUE;

	gotoX = 45;
	gotoY = -30;

	printf("%s/r/n", "go to saltbae 1");

	thisCount = 0;
	while(thisCount < 75) {
		printf("%s/r/n", "go to saltbae 2");
		printf("%s", "");
	}

	thisCount = 0;
	while(thisCount < 75) {
		printf("%s/r/n", "go to saltbae 3");
		printf("%s", "");
	}
	angles = FALSE;
	gotoX = 299; // das plank
	gotoY = 202; // das plank

	while(thisCount < 100);// {
	thisCount = 0;
	state = currentSense;
}

/* Function: findCurrent
 * --------------------------------------
 * void 
 * returns: holdVal, as a placeholder
 * purpose: finds current based on determined constants using raw and hold values
 * raw values taken from the ADC
 */
int findCurrent() {
	int holdVal = 0;
	int rawHold = 0;
	rawHold = getADC(0);
	holdVal = (signed int) ((3.805556 * (float) rawHold) - 2051.916667);
	return holdVal;
}

/* Function: findAverage
 * --------------------------------------
 * limit: int given for upper value of count 
 * returns: the total over the limit
 * purpose: used to find the average of whatever given
 */
int findAverage(int limit) {
	int total = 0;
	for (int i = 0; i < limit; i++) {
		total+=findCurrent();
	}
	return (int) (total/limit);
}

/* Function: currentSenseState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 6, holds arm at coordinate (20,0), creates maximum torque to measure current
 */
void currentSenseState(){
	angles = TRUE;
	gotoX = 20;
	gotoY = 0;
	thisCount = 0;
	int theCurrent = 0;
	while(thisCount < 100);// {
	//		printf("%s", "");
	//	}

	theCurrent = findAverage(5);
	printf("\v\v\v\v\v\v\v\v\v\v%d\v\v\v\v\v\v\v\r\n", theCurrent);

	angles = FALSE;
	if (theCurrent > 350) {
		state = depositBack;
	}
	else {
		state = depositFront;
	}
}

/* Function: depositFrontState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 7, deposits if the weight it light, goes to coordinates (15,0)
 */
void depositFrontState() {
	angles = TRUE;
	gotoX = 15;
	gotoY = 0;

	thisCount = 0;
	while(thisCount < 75) {
		printf("%s", "");
		setServo(6,30);
	}
	blockDist = 1000;
	baseDist = 1000;
	angles = FALSE;
	state = wait;
}

/* Function: depositBackState
 * --------------------------------------
 * void 
 * returns: nothing
 * purpose: state 8, deposits weight if it is heavy, goes to coordinates (120,80)
 */
void depositBackState() {
	angles = TRUE;
	gotoX = 120;
	gotoY = 80;

	thisCount = 0;
	while(thisCount < 75) {
		printf("%s", "");
	}
	thisCount = 0;
	while(thisCount < 75) {
		printf("%s", "");
	}
	thisCount = 0;
	while(thisCount < 75) {
		printf("%s", "");
	}
	thisCount = 0;
	while(thisCount < 75) {
		printf("%s", "");
	}


	setServo(6,30);
	thisCount = 0;
	while(thisCount < 75); //{
	//printf("%s", "");
	//}
	blockDist = 1000;
	baseDist = 1000;
	state = wait;
}

/* Function: checkArmX
 * --------------------------------------
 * int
 * returns: thisX, 
 * purpose: 
 */
int checkArmX() {
	int thisX = 0;
	for (int i = 0; i < 60; i++) {
		thisX = 90+i;
		thisCount = 0;
		while(thisCount < 5){
			printf("%s", "");
		};
		return thisX;
	}
	for (int i = 60; i >= 0; i--) {
		thisX = 90+i;
		thisCount = 0;
		while(thisCount < 5){
			printf("%s", "");
		};
		return thisX;
	}
	return thisX;
}

int main() {
	//pickState();
	initRBELib();
	debugUSARTInit(115200);
	initADC(2);
	initADC(0);
	initADC(1);
	initADC(3);

	initADC(7); //IR sensor 1 //arbitrary
	initADC(6); //IR sensor 2 //arbitrary //near arm

	initSPI();

	initAltCom(115200);

	setConst('L', 67.0, 4.0, 1.75);
	setConst('H', 67.0, 4.0, 1.75);


	startTimer0();
	setServo(7,0);
	
	// State Machine
	while (1) {
		switch(state) {
		case wait: waitState(); // waiting position at x = 5, y = 420
		break;
		case lineUp: lineUpState(blockDist); // ready state, above the block on conveyor
		break;
		case grab: grabState(blockDist); // drop down to block height once sensed by second IR, prepare for grab
		break;
		case close: closeState(); // actuating servo on pin 7, closing gripper
		break;
		case liftUp: liftUpState(); // once closed, armature lifts off belt
		break;
		case currentSense: currentSenseState(); // straight out position, creating max distance from origin to create measurable torque
		break;
		case depositFront: depositFrontState(); // if the weight is light, the arm deposits it in the front location, beyond the conveyor
		break;
		case depositBack: depositBackState(); // if the weight is heavy, the arm deposits is in the back location, behind the arm
		break;
		}
	}
}

/* Function: 
 * --------------------------------------
 * sets 
 */
ISR(TIMER0_COMPA_vect){
	printf("%d\t%d\t%d\t%d\t%d\t%d\r\n", state, tempBeltDist, blockDist, tempBaseDist, baseDist, findCurrent());

	thisCount++;

	potL1 = getADC(2); // potentiometer one
	potL2 = getADC(3); // potentiometer two

	if(!angles) {
		gotoXY(gotoX, gotoY); // gotoXY, found in motors, constantly updating on timer interrupt
	}
	else {
		gotoAngles(gotoX, gotoY); // gotoAngles, else we use our backup function to go to angles instead of inverse kin
	}

	tempBeltDist = IRDist(7); // IR sensor one
	tempBaseDist = IRDist(6); // IR sensor two

	PORTCbits._P0 = OFF;
	timer0count++; // increment counter
	PORTCbits._P0 = ON;
	if (timer0count == 100) {
		timer0count = 0;
	}
}
