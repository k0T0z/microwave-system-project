#include "tm4c123gh6pm.h"
#include "stdint.h"

void s1Init() {
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x10;
    GPIO_PORTF_AMSEL_R &= ~0x10;
    GPIO_PORTF_PCTL_R &= ~0xF0000;
    GPIO_PORTF_AFSEL_R &= ~0x10;
    GPIO_PORTF_DIR_R &= ~0x10;
    GPIO_PORTF_DEN_R |= 0x10;
}
void s2Init() {
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x01;
    GPIO_PORTF_AMSEL_R &= ~0x01;
    GPIO_PORTF_PCTL_R &= ~0xF;
    GPIO_PORTF_AFSEL_R &= ~0x01;
    GPIO_PORTF_DIR_R &= ~0x01;
    GPIO_PORTF_DEN_R |= 0x01;
}