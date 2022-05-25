#include "tm4c123gh6pm.h"

//Initialize Buzzer in PORT A3

void buzzer_init(){
    SYSCTL_RCGCGPIO_R  |= 0x01; // Enable PortA
    while ((SYSCTL_PRGPIO_R &0x01)==0); //wait
    GPIO_PORTA_CR_R |= 0x08;   //bit 3  2  1  0
    GPIO_PORTA_AMSEL_R &= ~0x08;   //8  4  2  1
    GPIO_PORTA_PCTL_R &= ~0x0000F000;
    GPIO_PORTA_AFSEL_R &= ~0x08;
    GPIO_PORTA_DIR_R |= 0x08; // output
    GPIO_PORTA_DATA_R &= ~0x08;
}

void beep(){
   for(int i = 0; i < 3; i++){
        GPIO_PORTA_DATA_R |= 0x08;
        delayms(1000);
        GPIO_PORTA_DATA_R &= ~0x08;
        delayms(1000);
   }
}
