#include "stdint.h"
#include "popcorn.c" // for popcorn function
#include "consts.c" // for constants file

void SystemInit() {} // needed in startup code file
	

unsigned char keypadFetch(void);
unsigned char sw1Fetch(void);
unsigned char sw2Fetch(void);
unsigned char sw3Fetch(void);
void wait(unsigned int);
void wait10ms(unsigned int);
void timerInit(void);



	
int main() {
	unsigned char input = keypadFetch(); // fetching pressed key from keypad
	if(input == 'A') {
		popcorn();
	}
	
	
	
}

void timerInit() { // initialisation of Systick Timer
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000005;
}


void wait10ms(unsigned int delay) { // using Systick Timer to make delay of 10ms
	NVIC_ST_RELOAD_R = delay-1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R&0x00010000) == 0){};
}

void wait(unsigned int multiple) { // using for loop for more a bigger delay
	unsigned int i;
	for (i = 0 ; i < multiple ; i++) {
		wait10ms(one10ms);
	}
}

