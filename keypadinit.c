#include "Prototype.h"

// keypad initialization functiom
//  row PE1 → PE4
//  column PC4 → PC7

void keypadinit(void) // row port E , column port C
{
    SYSCTL_RCGCGPIO_R |= 0x14; // enable clock of port E, C
    while ((SYSCTL_PRGPIO_R & 0x14) == 0)
    {
    } // wait until port is activated

    GPIO_PORTE_DIR_R |= 0x1E; // set row pins 1-4 as output
    GPIO_PORTE_DEN_R |= 0x1E; // set row pins 1-4 as digital
    GPIO_PORTE_ODR_R |= 0x1E; // set row pins 1-4 as open drain

    GPIO_PORTC_DIR_R &= ~0xF0; // set column pins 7-4 as input
    GPIO_PORTC_DEN_R |= 0xF0;  // set column pins 7-4 as digital
    GPIO_PORTC_PUR_R |= 0xF0;  // enable pull up resistors for pins 7-4
}