#include "LCDKeypad.h"
#include "SW_init.c"
#include "SW3.c"
#include "buzzer.c"


void one_sec_delay_loading() {
	off(); // for turning all the leds off
	red(); // turning red led on
	wait(partOfSecond);
	off();
	blue();
	wait(partOfSecond);
	off();
	green();
	wait(part2OfSecond);
}

enum state
{
    IDLE,
    Popcorn,
    Beef,
    Chicken,
    Custom,
    Cooking,
    Pause
};


int main() {
	unsigned char input;                  // keypad data will be passed here
    unsigned char currentState = IDLE;    // initialised to IDLE state
    int time = 0;                         // time in seconds
    unsigned int weight = 0;              // weight used in Beef and Chicken states
    char s[5] = {'0', '0', ':', '0', '0'};
	unsigned char key;
	unsigned int temp;
	buzzer_init();
	LCDinit();
	keypadinit();
	SW_Init();
	SW3_Init();
		 
		 
	while (1) {
		switch (currentState) {
/* ================================================================================================================================================================ */
        case IDLE:                        // main state
			LCDcommand(Clear);
			LCDstring("Choose state");
            while (1) {                   // fetching pressed key from keypad
                input = getchar();
                if (input != 0) {         // getchar() returns 0 if nothing is pressed so if the return is not zero break out of the loop
                    LCDcommand(Clear);
                    break;                // you can add msg to the user to  press a key
                }
            }
            if (input == 'A') {
        	    currentState = Popcorn;
            }
            else if (input == 'B') {
                currentState = Beef;
            }
            else if (input == 'C') {
                currentState = Chicken;
            }
            else if (input == 'D') {
                currentState = Custom;
            }
            else {
                LCDstring("Err");
                delayms(2000);                // wait for 2 seconds
                LCDcommand(Clear);            // clear LCD
            }
            break;
/* ================================================================================================================================================================ */
        case Popcorn:
			LCDcommand(Clear);                // clear the screen
            LCDstring("Popcorn");
			while(1){
				if(!get_SW2() && get_SW3()) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
					delayms(2000);
					timer(60);
					break;
				}	
			} 
			break;
            
/* ================================================================================================================================================================ */
        case Beef:
            // getting a valid weight
            LCDcommand(Clear); // clear the screen 
            LCDstring("Beef weight?"); 
            delayms(2000);
						while(1){
							key = getchar();
								if (key != 0)
										{
											temp = check_Input(key);
											if (temp == 1){            // as 1 stands for beef in the keypad
												currentState = Beef;   // channging the current statr to beef
												break;
											}	
											else{
												while(key == 0){key = getchar();}  // this 
												LCDcommand(Clear);      // clear the screen 
												LCDdata(key);
												key -= 48;
												delayms(5000);          // delay for 5 seconds  
												time = 30 * key;
												 if(get_SW3()){
														timer(time);    // set timer for the current time 
													  break;
													}
											}
										}
									}
					break;
						
					
			
       
            

/* ================================================================================================================================================================ */
        case Chicken:
			

/* ================================================================================================================================================================ */
		case Custom:
			
 
/* ================================================================================================================================================================ */
        default: printf("");

		}
			
    }
}

