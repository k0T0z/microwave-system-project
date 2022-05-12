#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "systick_delay.c"
#include "consts.c"

void red() {
    GPIO_PORTF_DATA_R |= 0x02;
}

void blue() {
    GPIO_PORTF_DATA_R |= 0x04;
}

void green() {
    GPIO_PORTF_DATA_R |= 0x08;
}

void off() {
    GPIO_PORTF_DATA_R &= ~0x0E;
}

void set() {
    GPIO_PORTF_DATA_R |= 0x0E;
}

void ledBlink() {
    clear();
    for (unsigned int i = 0 ; i < 5 ; i++) {
        GPIO_PORTF_DATA_R ^= 0x0E;
        wait(oneFifthSecond);
    }
}
