
#include "Prototype.h"

// tests if a key is pressed it returns true otherwise it returns false
unsigned char keypress(void)
{
    int col;
    // check if a key is pressed
    GPIO_PORTE_DATA_R = 0;          // enable all rows
    col = GPIO_PORTC_DATA_R & 0xF0; // read all columns
    if (col == 0xF0)
    {
        return 0; // not pressed
    }
    else
    {
        return 1; // pressed
    }
}