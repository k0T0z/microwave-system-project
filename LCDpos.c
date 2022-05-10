#include "Prototype.h"

// control cursor position in the LCD

void LCDpos(uint8_t col, uint8_t row)
{
    if (row == 0)
        LCDcommand(0x80 + col);
    else
        LCDcommand(0xC0 + col);
}