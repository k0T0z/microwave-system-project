#include "Prototype.h"

// sends custom characters to the LCD
// not done yet
void LCDcus(char custom)
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

    char chicken[] = {
        0x04,
        0x0E,
        0x1F,
        0x1F,
        0x0E,
        0x04,
        0x04,
        0x0E};

    char beef[] = {
        0x04,
        0x0E,
        0x1B,
        0x1F,
        0x1F,
        0x1F,
        0x0E,
        0x04};

    char clock[] = {
        0x0E,
        0x11,
        0x15,
        0x15,
        0x17,
        0x11,
        0x11,
        0x0E};

    char error[] = {
        0x0E,
        0x0E,
        0x0E,
        0x0E,
        0x0E,
        0x00,
        0x0E,
        0x0E};
    char sandtimer[] = {
        0x1F,
        0x11,
        0x11,
        0x0A,
        0x04,
        0x0A,
        0x15,
        0x1F};
    char alarm[] = {
        0x04,
        0x0E,
        0x0E,
        0x0E,
        0x1F,
        0x00,
        0x04,
        0x00};
    switch (custom)
    {
    case 'A':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(heart[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'B':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(popcorn[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'C':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(chicken[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'D':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(beef[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'E':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(clock[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'F':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(error[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'G':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(sandtimer[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;

    case 'H':
        LCDcommand(0x40); // CG_RAM incoming custom character
        for (int i = 0; i < 8; i++)
        {
            LCDdata(alarm[i]);
        }
        LCDcommand(0x111);
        LCDdata(0);
        break;
    }
}
