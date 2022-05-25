#include "stdlib.h"

// function used to convert numeric strings to integer

int Intstr(unsigned char *str) // numeric string to integer
{
    int intvalue;
    intvalue = atoi(str);
    return intvalue;
}

//, unsigned char len -> you didn't use it :)
