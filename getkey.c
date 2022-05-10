#include "Prototype.h"

unsigned char getkey(void)
{
    const unsigned char keymap[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'},
    };

    int row, col;
    // check to see if a key is pressed

    GPIO_PORTE_DATA_R = 0; // enable all rows

    col = GPIO_PORTC_DATA_R & 0xF0; // read all columns
    if (col == 0xF0)
        return 0; // no keys are pressed

    while (1)
    {
        row = 0;
        GPIO_PORTE_DATA_R = 0x1D; // enable row 0 (negative logic 1st bit = 0)
        delayus(2);               // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;

        //----------------------------------------------
        row = 1;
        GPIO_PORTE_DATA_R = 0x1B; // enable row 1 (negative logic 2nd bit = 0)
        delayus(2);               // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;

        //-------------------------------------------
        row = 2;
        GPIO_PORTE_DATA_R = 0x17; // enable row 2 (negative logic 3rd bit = 0)
        delayus(2);               // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;
        //----------------------------------------------
        row = 3;
        GPIO_PORTE_DATA_R = 0xF; // enable row 3 (negative logic 4th bit = 0)
        delayus(2);              // wait for signal to settle
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0)
            break;

        return 0; // if no key is pressed
    }
    // get here only when a key is pressed
    if (col == 0xE0)
        return keymap[row][0]; // key in column 0
    if (col == 0xD0)
        return keymap[row][1]; // key in column 1
    if (col == 0xB0)
        return keymap[row][2]; // key in column 2
    if (col == 0x70)
        return keymap[row][3]; // key in column 3

    return 0; // double check
}