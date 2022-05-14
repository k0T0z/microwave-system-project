#include "tm4c123gh6pm.h"
#include "stdint.h"

void SystemInit() {};

// intalize sw1,sw2
void SW_Init(void ){
    SYSCTL_RCGCGPIO_R |= 0x20; // PortF clock enable
    while ((SYSCTL_PRGPIO_R & 0x20)==0); //Delay
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock PortF Commit register
    GPIO_PORTF_CR_R |= 0x11; // Allow changes to PF41
    GPIO_PORTF_AMSEL_R &= ~0x11; // Disable analog function
    GPIO_PORTF_PCTL_R &= ~0x000F000F; // GPIO clear bit PCTL
    GPIO_PORTF_AFSEL_R &= ~0x011; // No alternate function
    GPIO_PORTF_DIR_R &= ~0x11; // PF41 input
    GPIO_PORTF_DEN_R |= 0x11; // Enable digital for switches
    GPIO_PORTF_DATA_R |= 0x11;// this to set sw1 , sw2 as the simulate being unclicked
}

//intialize switch 3 in PORT E5
void SW3_Init(){
    SYSCTL_RCGCGPIO_R  |= 0x10; // Enable PortE
    while ((SYSCTL_PRGPIO_R &0x10)==0); //wait
    GPIO_PORTE_LOCK_R = 0x4C4F434B;
    GPIO_PORTE_CR_R |= 0x20;
    GPIO_PORTE_AMSEL_R &= ~0x20;
    GPIO_PORTE_PCTL_R &= ~0x00F00000;
    GPIO_PORTE_AFSEL_R &= ~0x20;
    GPIO_PORTE_DIR_R &= ~0x20;
    GPIO_PORTE_PUR_R |= 0x20;
    GPIO_PORTE_DATA_R &= ~0x20; // PE5 = 0 -> closed door
}

unsigned char get_SW1(){
    return GPIO_PORTF_DATA_R & 0x10;
}
unsigned char get_SW2(){
    return GPIO_PORTF_DATA_R & 0x01;
}

unsigned char get_SW3(){
    return GPIO_PORTE_DATA_R & 0x20;
}


