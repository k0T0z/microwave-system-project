#include "Prototype.h"

// sends commands to the LCD in two strokes

void LCDcommand(unsigned char command)
{
    LCDnibblewrite(command & 0xF0, 0); // upper nibble first
    LCDnibblewrite(command << 4, 0);   // then lower nibble

    if (command < 4)
    { // command 1 and 2 needs upto 1.64ms rest needs 40us
        delayms(2);
    }
    else
    {
        delayus(40);
    }
}