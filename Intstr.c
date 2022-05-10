#include "stdlib.h"

// function used to convert numeric strings to integer

int Intstr(unsigned char *str, unsigned char len) // numeric string to integer
{
    int intvalue;
    intvalue = atoi(str);
    return intvalue;
}