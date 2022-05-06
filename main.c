#include "stdint.h"
#include "popcorn.c" // for popcorn function


void SystemInit() {} // needed in startup code file
	

unsigned char keypadFetch(void);
unsigned char sw1Fetch(void);
unsigned char sw2Fetch(void);
unsigned char sw3Fetch(void);



	
int main() {
	unsigned char input = keypadFetch(); // fetching pressed key from keypad
	if(input == 'A') {
		popcorn();
	}
	
	
	
}



