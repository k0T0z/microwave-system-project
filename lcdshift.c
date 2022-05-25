#include "Prototype.h"


unsigned char *Lcdshift(void){
    unsigned char arr[5] = {'0', '0', ':', '0', '0'};

    while(1){
        getkey();
        return arr;
    }
}