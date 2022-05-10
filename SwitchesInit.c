#include "Prototype.h"

// Switches initialization functiom
//  Switch1 PF4
//  Switch2 PF0
//  Switch3 PE5
void Switchinit(void) 
{
    SYSCTL_RCGCGPIO_R |= 0x30; // enable clock of port E , F
    while ((SYSCTL_PRGPIO_R & 0x30) == 0)
    {
    } // wait until ports are activated

    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   // open lock of portF
    GPIO_PORTF_CR_R |= 0x11;            // enable changes on PF0 , PF1
	GPIO_PORTF_DIR_R &= ~0x11;         // set Switches 1,2 as input
	GPIO_PORTF_AFSEL_R &= ~0x11;      // close the alternative functions of PF0 , PF1 
	GPIO_PORTF_PCTL_R &= ~0xF000F;   // select GPIO function for 'PF0 , PF1' (not needed since we closed AFSEL)
	GPIO_PORTF_DEN_R |= 0x11;       // set Switches 1,2 as Digital
	GPIO_PORTF_AMSEL_R &= ~0x11;   // Insure that 'PF0 , PF1' will not deal with analog data(not needed since we set DEN)
	GPIO_PORTF_PUR_R |= 0x11;     // enable pull up resistors for PF0 , PF1

    GPIO_PORTE_CR_R |= 0x20;             // enable changes on PE5 
	GPIO_PORTE_DIR_R &= ~0x20;          // set Switch 3 as input
	GPIO_PORTE_AFSEL_R &= ~0x20;       // close the alternative functions of PE5 
	GPIO_PORTE_PCTL_R &= ~0xF00000;   // select GPIO function for 'PE5' (not needed since we closed AFSEL)
	GPIO_PORTE_DEN_R |= 0x20;        // set Switch 3 as Digital
	GPIO_PORTE_AMSEL_R &= ~0x20;    // Insure that 'PE5' will not deal with analog data(not needed since we set DEN)
	GPIO_PORTE_PUR_R |= 0x20;      // enable pull up resistors for PE5
 
}