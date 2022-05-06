#include "tm4c123gh6pm.h"

void lcdString(char[]);

void popcorn() {
	// here we should change E (enable of LCD) from 0 to 1
	// here we should make delay
	lcdString("POPCORN"); // for sending data to LCD
	// here we should change E (enable of LCD) back to zero
	// here we should start a timer in a specific area on LCD of 1 minute
	// may be we need to always check for conditions while cooking
	
}


