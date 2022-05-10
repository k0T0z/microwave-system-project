#include "Prototype.h"

// send data to LCD in two strokes
void LCDdata(unsigned char data)
{
    LCDnibblewrite(data & 0xF0, RS); // upper nibble
    LCDnibblewrite(data << 4, RS);   // then lower nibble
    delayus(40);
}