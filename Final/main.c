#include "LCDKeypad.h"
#include "timer.h"
#include "buzzer.h"
#include "custom_Functions.h"
#include "LED_control.h"
#include "SW_init.h"

enum state
{
    IDLE,
    Popcorn,
    Beef,
    Chicken,
    Custom,
    Cooking
};


int main() {
	unsigned char input;			   // keypad data will be passed here
	unsigned char currentState = IDLE; // initialised to IDLE state
	int time = 0;					   // time in seconds
	unsigned int weight = 0;		   // weight used in Beef and Chicken states
	char s[5] = {'0', '0', ':', '0', '0'}; // array s[] that will be used in Custom state
	unsigned char key; // variable that holds the data entered on the keypad
	unsigned int temp; // temp variable that holds return value from error functions 
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
		GPIO_PORTF_DATA_R &= ~0xE;
		LCDpos(0, 2);
		LCDstring("Choose state"); // display the intered string on LCD
		while (1)
		{ // fetching pressed key from keypad
			input = getchar();
			if (input != 0)
			{
				LCDcommand(Clear);
				break;
			}
		}
		if (input == 'A')
		{
			currentState = Popcorn;
		}
		else if (input == 'B')
		{
			currentState = Beef;
		}
		else if (input == 'C')
		{
			currentState = Chicken;
		}
		else if (input == 'D')
		{
			currentState = Custom;
		}
		else
		{
			LCDcus('F');
			LCDpos(0, 6);
			LCDstring("Err"); // display the intered string on LCD
			delayms(2000);	   // wait for 2 seconds
			LCDcommand(Clear); // clear LCD
		}
		break;
/* ================================================================================================================================================================ */
        case Popcorn:
		LCDcommand(Clear); // clear the screen
		LCDcus('B'); // display custom character
		LCDpos(0, 4); // change cursor position
		LCDstring("Popcorn"); // display the intered string on LCD
		while (1)
		{
			if (!get_SW2() && get_SW3()) // if sw2 is pressed and door is closed start cooking
			{
				delayms(2000); // delay so that the pressed sw2 doesn't interfere in the timer function
				time = 60; // cooks for 60 second
				currentState = Cooking;
				break;
			}
		}
		break;
            
/* ================================================================================================================================================================ */
        case Beef:
			LCDcommand(Clear); // clear the screen
			LCDcus('D'); // display custom character
			LCDpos(0, 0); // change cursor position
			LCDstring("Beef weight?"); // display the intered string on LCD
			delayms(2000); // delay 2 seconds
			while (1)
			{
				key = getchar(); // key hold the value intered in the keypad, note: key in this state resembles the weight
				if (key != 0) // if key contains data
				{
					temp = check_Input(key); // call function that returns 1 if wrong input is entered
					if (temp == 1)
					{
						currentState = Beef; // return to beginning of Beef state
						break;
					}
					else // valid input is entered 
					{
						while (key == 0) // key conatins no data
						{
							key = getchar(); // key hold the value intered in the keypad
						}
						LCDcommand(Clear); // clear the screen
						LCDdata(key); // display the data in key on LCD
						key -= 48; // data changed to integer
						delayms(2000); // delay 2 seconds
						time = 30 * key; // cooks for weight * 0.5 minutes 
						if(!get_SW3()){ // if door is opened don't change state to cooking
							while(!get_SW3()){ // while the door is opened
							delayms(20); // delay to be able to check sw3 again
							if(get_SW3()) // if door is closed change state to cooking
								break;
							}
						currentState = Cooking;
						break;
						}
						currentState = Cooking;
						break;
					}
				}
			}
			break;
/* ================================================================================================================================================================ */
       case Chicken:
			LCDcommand(Clear); // clear the screen
			LCDcus('C'); // display custom character
			LCDpos(0, 0); // change cursor position
			LCDstring("Chicken weight?"); // display the intered string on LCD
			delayms(2000); // delay 2 seconds
			while (1)
			{
				key = getchar(); // key hold the value intered in the keypad , note: key in this state resembles the weight
				if (key != 0) // if key contains data
				{
					temp = check_Input(key); // call function that returns 1 if wrong input is entered
					if (temp == 1)
					{
						currentState = Chicken; // return to beginning of Chicken state
						break;
					}
					else // valid input is entered 
					{
						while (key == 0) // key conatins no data
						{
							key = getchar(); // key hold the value intered in the keypad
						}
						LCDcommand(Clear); // clear the screen
						LCDdata(key); // display the data in key on LCD
						key -= 48; // data changed to integer
						delayms(2000); // delay 2 seconds
						time = 12 * key; // cooks for weight * 0.5 minutes 
						if(!get_SW3()){ // if door is opened don't change state to cooking
						while(!get_SW3()){ // while the door is opened
						delayms(20); // delay to be able to check sw3 again
						if(get_SW3()) // if door is closed change state to cooking
						break;
							}
							currentState = Cooking;
							break;
						}
						currentState = Cooking;
						break;
					}
				}
			}
			break;
			

/* ================================================================================================================================================================ */
	case Custom:
		LCDcommand(Clear);
			LCDstring("Cooking time?"); // display the intered string on LCD
			delayms(1000); // delay before displaying 00:00
			// sets the array s[] to 00:00
			for (int i = 0; i < 5; i++)
			{
				s[i] = '0';
			}
			s[2] = ':';
			LCDpos(1, 5); // change cursor position, note: 5 to display 00:00 in the center of LCD
			LCDstring(s); // display 00:00 on the LCD
			while (1)
			{
				key = getchar();  // key hold the value intered in the keypad, note: key in this state resembles the time digit
				if (key != 0) // if key contains data
				{
					temp = check_Input_arr(key);  // call function that returns 1 if wrong input is entered
					if (temp == 1)
					{
						currentState = Custom;  // return to begining of Custom state
						break;
					}
					// if array s[] is 00:00, the input taken from the user will be placed in s[4]
					else if (s[0] == '0' && s[1] == '0' && s[3] == '0' && s[4] == '0')
					{
						while (key == 0) // if key doesn't contain data
						{
							key = getchar(); // key contains entered data from the keypad
						}
						LCDcommand(Clear); // clear the screen
						LCDcommand(0xC); // hides the cursor on the LCD
						LCDpos(0, 0); // change cursor position
						LCDstring("Cooking time?"); // display the intered string on LCD
						LCDpos(1, 9); // change cursor position
						s[4] = key; // s[4] contains the data in the key
						LCDdata(s[4]); // store intered data in s[4]
						LCDpos(1, 8); // change cursor position
						LCDdata(s[3]); // double check rest of data be disbled on the LCD
						LCDpos(1, 7);  // change cursor position
						LCDdata(s[2]); // double check rest of data be disbled on the LCD
						LCDpos(1, 6); // change cursor position
						LCDdata(s[1]); // double check rest of data be disbled on the LCD
						LCDpos(1, 5); // change cursor position
						LCDdata(s[0]); // double check rest of data be disbled on the LCD
						time = time_to_second(s); // a function that calculate the total seconds from sent array
						delayms(2000); // delay to give the user time to clear screen and cook
						if (!get_SW1()) // if switch 1 is pressed clear  screen
						{
							LCDcommand(Clear); // clear the screen
							while (1)
							{
								if (!get_SW2() && get_SW3()) // if sw2 is pressed and door is closed start cooking
								{
									delayms(2000); // delay so that the pressed sw2 doesn't interfere in the timer function
									timer(time); // calls function timer and sends the time
									break;
								}
							}
						}
					}
					// if array s[] is 00:0'data', data in s[4] is shifted to s[3] and the new input taken from the user will be placed in s[4]
					else if (s[0] == '0' && s[1] == '0' && s[3] == '0' && s[4] != '0')
					{
						while (key == 0) // if key doesn't contain data
						{
							key = getchar(); // key contains entered data from the keypad
						}
						LCDpos(0, 0); // change cursor position
						LCDstring("Cooking time?"); // display the intered string on LCD
						LCDcommand(0xC); // hides the cursor on the LCD
						s[3] = s[4]; // data in s[4] pushed to s[3]
						LCDpos(1, 9); // change cursor position
						s[4] = key; // s[4] contains the data in the key
						LCDdata(s[4]); // store intered data in s[4]
						LCDpos(1, 8); // change cursor position
						LCDdata(s[3]); // display the change in s[3]
						time = time_to_second(s); // a function that calculate the total seconds from sent array
						delayms(2000); // delay to give the user time to clear screen and cook
						if (!get_SW1()) // if switch 1 is pressed clear  screen
						{
							LCDcommand(Clear); // clear the screen
							while (1)
							{
								if (!get_SW2() && get_SW3()) // if sw2 is pressed and door is closed start cooking
								{
									delayms(2000); // delay so that the pressed sw2 doesn't interfere in the timer function
									timer(time); // calls function timer and sends the time
									break;
								}
							}
						}
					}
					/*if array s[] is 00:'data''don't care',data in s[3] is shifted to s[1], 
					data in s[4] is shifted to s[3], and the new input taken from the user will be placed in s[4]*/
					else if (s[0] == '0' && s[1] == '0' && s[3] != '0')
					{
						while (key == 0) // if key doesn't contain data
						{
							key = getchar(); // key contains entered data from the keypad
						}
						LCDpos(0, 0); // change cursor position
						LCDstring("Cooking time?"); // display the intered string on LCD
						LCDcommand(0xC); // hides the cursor on the LCD
						s[1] = s[3]; // data in s[3] pushed to s[1]
						s[3] = s[4]; // data in s[4] pushed to s[3]
						LCDpos(1, 9); // change cursor position
						s[4] = key; // s[4] contains the data in the key
						LCDdata(s[4]); // store intered data in s[4]
						LCDpos(1, 8); // change cursor position
						LCDdata(s[3]); // display the change in s[3]
						LCDpos(1, 6); // change cursor position
						LCDdata(s[1]); // display the change in s[1]
						time = time_to_second(s); // a function that calculate the total seconds from sent array
						delayms(2000); // delay to give the user time to clear screen and cook
						if (!get_SW1()) // if switch 1 is pressed clear  screen
						{
							LCDcommand(Clear); // clear the screen
							while (1)
							{
								if (!get_SW2() && get_SW3()) // if sw2 is pressed and door is closed start cooking
								{
									delayms(2000); // delay so that the pressed sw2 doesn't interfere in the timer function
									timer(time); // calls function timer and sends the time
									break;
								}
							}
						}
					}
					/* if array s[] is 0'data':'don't care''don't care', data in s[1] is shifted to s[0]
					,data in s[3] is shifted to s[1], data in s[4] is shifted to s[3], and the new input taken from the user will be placed in s[4]*/
					else if (s[0] == '0' && s[1] != '0')
					{
						while (key == 0) // if key doesn't contain data
						{
							key = getchar(); // key contains entered data from the keypad
						}
						LCDpos(0, 0); // change cursor position
						LCDstring("Cooking time?"); // display the intered string on LCD
						LCDcommand(blink); // display back the cursor on the LCD screen
						s[0] = s[1]; // data in s[1] pushed to s[0]
						temp = check_Input_30(s[0]); /* a function the check if the data in s[0] >= 3 print error and return 1, 
						note: this is a way to allow the user to enter time maximum up to 30min*/
						// if temp ==1, print error and return the beginning of Custom state
						if (temp == 1)
						{
							currentState = Custom;
							break;
						}
						s[1] = s[3]; // data in s[3] pushed to s[1]
						s[3] = s[4]; // data in s[4] pushed to s[3]
						LCDpos(1, 9); // change cursor position
						s[4] = key; // s[4] contains the data in the key
						LCDdata(s[4]); // store intered data in s[4]
						LCDpos(1, 8); // change cursor position
						LCDdata(s[3]); // display the change in s[3]
						LCDpos(1, 6); // change cursor position
						LCDdata(s[1]); // display the change in s[1]
						LCDpos(1, 5); // change cursor position
						LCDdata(s[0]); // display the change in s[0]
						time = time_to_second(s); // a function that calculate the total seconds from sent array
						delayms(2000); // delay to give the user time to clear screen and cook
						if (!get_SW1()) // if switch 1 is pressed clear  screen
						{
							LCDcommand(Clear); // clear the screen
							while (1)
							{
								if (!get_SW2() && get_SW3()) // if sw2 is pressed and door is closed start cooking
								{
									delayms(2000); // delay so that the pressed sw2 doesn't interfere in the timer function
									timer(time);  // calls function timer and sends the time
									break;
								}
							}
						}
					}
					/*if array s[] is 'data''don't care':'don't care''don't care'(array full of input data)
					and user enter a new input return back to the beginning of Custom state*/
					else if (s[0] != '0')
					{
						delayms(2000); // delay to give the user time to clear screen and cook
						if (!get_SW1()) // if switch 1 is pressed clear  screen
						{
							LCDcommand(Clear); // clear the screen
							while (1)
							{
								if (!get_SW2() && get_SW3()) // if sw2 is pressed and door is closed start cooking
								{
									delayms(2000); // delay so that the pressed sw2 doesn't interfere in the timer function
									timer(time); // calls function timer and sends the time
									break;
								}
							}
						}
						currentState = Custom; // return back to the beginning of Custom state
						break;
					}
				}
			}
			break;
		
/* ================================================================================================================================================================ */			
 	case Cooking:
		while (1)
		{
			timer(time); // calls the timer function to countdown and takes the time in seconds as a parameter
			break;
		}
		currentState = IDLE; // when finished return to IDLE state
		break;
/* ================================================================================================================================================================ */
       
	}		
    }
}

