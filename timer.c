#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "Cooking_Oprations.c"
//there is another include for getkey()

unsigned int time[4];

void shift(){
    for (int i = 0; i < 3; i++)
    {
        time[i] = time[i+1];
    }
}


int main(){
    int shift_time;
    //1)get the input
    for (int i = 0; i < 4; i++)
        {
            scanf("%i",&time[i]); // time[i] = getkey();
        }
    scanf("%i",&shift_time); //excepected SW2 is pressed, if not ?

    //let the user toy with keypad until he press start (SW2)
    while (shift_time != 88){ //get_SW2() != 0 ,, assume SW2 code is 88
        shift();
        time[3] = shift_time;
        scanf("%i",&shift_time);
    }



    printf("%i%i:%i%i ", time[0], time[1], time[2], time[3]);

    //get the systick timer
    //int systick_timer = time[1] * 10 * 60 + time[2] * 60 + time[3] * 10 + time[4];




}
