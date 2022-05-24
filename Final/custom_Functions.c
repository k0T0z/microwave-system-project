#include "LCDKeypad.h"

// function that check if the input in Custom state is valid
 int check_Input_arr(unsigned char input){
        int test = (int)(input); // change char to int
        if (!(test >= 48 && test <= 57)){ // check if input is not between 0 and 9
            LCDcommand(Clear); // clear screen
            LCDstring("Err"); // display enterd string on LCD 
	    delayms(2000); // delay for 2 second
	    return 1; // return 1 to temp in main if there is an error
        }else{
            return 0; // return 0 to temp in main if there is no error
        }
}
 
 // function that check if the element in array[0] is < 3 in Custom state
 int check_Input_30(unsigned char input){
        int test = (int)(input); // change char to int
        if (test >= 51){ // check if input >= 3
            LCDcommand(Clear); // clear screen
	    LCDstring("Err"); // display enterd string on LCD 
	    delayms(2000); // delay for 2 second
	    return 1; // return 1 to temp in main if there is an error
        }else{
            return 0; // return 0 to temp in main if there is no error
        }
}
 // function that calculates the total seconds from array
int time_to_second(unsigned char arr[]){
    //'time1''time2' : 'time3''time4'
    int time1 = ((int)(arr[0]) - 48) * 600;
    int time2 = ((int)(arr[1]) - 48) * 60;
    int time3 = ((int)(arr[3]) - 48) * 10;
    int time4 = (int)(arr[4]) - 48;
    unsigned int result;
    result = time1 + time2 + time3 + time4; // add sum to result
    return result;
}

// function that check if the input in Beef and Chicken state is valid
 int check_Input(unsigned char input){
        int test = (int)(input); // change char to int
        if (!(test >= 49 && test <= 57)){ // check if input is not between 1 and 9
            LCDcommand(Clear); // clear screen
	    LCDstring("Err"); // display enterd string on LCD 
	    delayms(2000); // delay for 2 second
	    return 1; // return 1 to temp in main if there is an error
        }else{
            return 0; // return 0 to temp in main if there is no error
        }
}
