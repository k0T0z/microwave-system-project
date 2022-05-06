#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "consts.c" // for constants file

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