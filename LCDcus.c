#include "Prototype.h"

//sends custom characters to the LCD
//not done yet
void LCDcus(void)
{
    char popcorn[] = {
        0x15,
        0x0A,
        0x15,
        0x0A,
        0x0E,
        0x0E,
        0x0E,
        0x0E};
    char heart[] = {
        0x00,
        0x00,
        0x1B,
        0x1B,
        0x1F,
        0x0E,
        0x0E,
        0x04};

    LCDcommand(0x40); // CG_RAM incoming custom character
    for (int i = 0; i < 8; i++)
    {
        LCDdata(heart[i]);
    }
    LCDcommand(0x111); //position
    LCDdata(0);
}