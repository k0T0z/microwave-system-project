#include "Prototype.h"

//sends complete strings from charactersyp the LCD
void LCDstring(unsigned char *str, unsigned char len)
{
    for (char i = 0; i < len; i++)
    {
        LCDdata(str[i]);
    }
}