#include "Prototype.h"

// Sends each data and command in two strokes
// 4- bit mode

void LCDnibblewrite(unsigned char data, unsigned char control)
{                                       // control = 0 ? command , control = 1 ? data
    data &= 0xF0;                       // clear lower nibble for control
    control &= 0x0F;                    // clear upper nibble for data
    GPIO_PORTB_DATA_R = data | control; // R/W always = 0 , RS either 1 (data) or 0 (command)
    delayus(1);
    GPIO_PORTB_DATA_R = data | control | Enable; // Pulse E
    delayus(1);
    GPIO_PORTB_DATA_R = data; // turn off enable
    GPIO_PORTB_DATA_R = 0;    // clear data
}