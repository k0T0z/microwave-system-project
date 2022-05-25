#include "Prototype.h"
void check_Input(unsigned char input){
    while(1){
        int test = (int)(input); // change char to int
        if (!(test >= 48 && test <= 57)){ // check if input is not between 0 and 9
            LCDcommand(clearScreen);
			lcdString("Err");
			wait(200);
        }else{
            break;
        }
    }
}