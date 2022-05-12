#include "stdint.h"
#include "systick_delay.c"
#include "getchar.c"
#include "LCDinit.c"
#include "portF_init.c"
#include "Cooking_Oprations.c"
#include "systick_delay.c"
#include "Prototype.h"


void SystemInit() {} // needed in startup code file

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

enum state{
	IDLE,
	Popcorn,
	Beef,
	Chicken,
	Custom,
	Cooking,
	Pause
};

int main() {
	LCDinit();
	portFInit();
	SW_Init();
	SW3_Init();
	timerInit();
	
	unsigned char input; // keypad data will be passed here
	unsigned static char currentState = IDLE; // initialised to IDLE state
	unsigned int time = 0; // time in seconds
	unsigned int weight = 0; // weight used in Beef and Chicken states
	unsigned char time_1 = '0';
	unsigned char time_2 = '0';
	unsigned char time_3 = '0';
	unsigned char time_4 = '0';
	unsigned char arr[5] = {'0', '0', ':', '0', '0'}; // array of characters used in custom state

	while(1) {

		switch(currentState) {
/* ================================================================================================================================================================ */
		IDLE: // main state
			while(1) { // fetching pressed key from keypad
				input = getchar();
				if(input!=0) { // getchar() returns 0 if nothing is pressed so if the return is not zero break out of the loop
					break;
				}
			}
			if(input == 'A' || input == 'a') {
				currentState = Popcorn;
			} else if (input == 'B' || input == 'b') {
				currentState = Beef;
			} else if (input == 'C' || input == 'c') {
				currentState = Chicken;
			} else if (input == 'D' || input == 'd') {
				currentState = Custom;
			} else {
				lcdString("Err");
				wait(200); // wait for 2 seconds
				LCDcommand(clearScreen); // clear LCD
			}
			break;
/* ================================================================================================================================================================ */
		Popcorn:
			LCDcommand(clearScreen); // clear the screen
			lcdString("POPCORN, START?"); // print on the LCD
			if((!get_SW2())&&(get_SW3())) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
				while (!get_SW2()); // wait for the user to lift his finger
				time = 60; // one minute for popcorn
				currentState = Cooking; // change currentState variable to cooking state, then the switch case will end and enter again in the new state (cooking)
			}
			break;
/* ================================================================================================================================================================ */
		Beef:
			// getting a valid weight
			LCDcommand(clearScreen);
			lcdString("Beef weight?");
			LCDpos(0, 1); // cursor position
				
			while(1) {
				input = getchar();
				weight = Intstr(input);
				if(weight>=1 && weight <= 9) { // if it's a valid input, getout of the loop
					break;
				}
				else if (!(weight>=0 && weight <= 9)){ // if anything but zero and from 1 to 9 ([1,9]+{0})
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			}
			
			// Intstr waits for two arguments where's the second one?

			// input weight from user
			lcdString(input); // After a valid number is entered, clear the LCD display and show the value of the weight on the LCD for 2 seconds
			wait(200);
			
			while (1) {
				if((!get_SW2())&&(get_SW3())) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
					while (!get_SW2()); // wait for the user to lift his finger
					time = 30 * weight; // set time for Beef (0.5 minute for each kilo)
					currentState = Cooking;
					break;
				}
				else if (!get_SW1()) { // more functionality
					while (!get_SW1()); // wait for the user to lift his finger
					currentState = IDLE;
					break;
				}
			}
			break;
/* ================================================================================================================================================================ */
		Chicken:
			
			LCDcommand(clearScreen);
			lcdString("Chicken weight?");
			LCDpos(0, 1); // cursor position
			while(1) {
				input = getchar();
				weight = Intstr(input);
				if(weight>=1 && weight <= 9) { // if it's a valid input, getout of the loop
					break;
				}
				else if (!(weight>=0 && weight <= 9)){ // if anything but zero and from 1 to 9 ([1,9]+{0})
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			}

			// Intstr waits for two arguments where's the second one?
			lcdString(input); // After a valid number is entered, clear the LCD display and show the value of the weight on the LCD for 2 seconds
			wait(200);

			while(1) {
				if((!get_SW2())&&(get_SW3())) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
					while (!get_SW2()); // wait for the usr to lift his finger
					time = 12 * weight; // set time for chicken (0.2 minute for each kilo)
					currentState = Cooking;
				}
				else if(!get_SW1()) { // more functionality
					while (!get_SW1()); // wait for the user to lift his finger
					currentState = IDLE;
					break;
				}
			}
			break;
/* ================================================================================================================================================================ */
		Custom:
			do{
				LCDcommand(clearScreen);
				lcdString("Cooking Time?");
				LCDpos(0, 1);
				lcdString(arr);
				if (time_to_second(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(time_to_second(arr) == -1);

			if(!get_SW1()) { 
				while (!get_SW1()); // wait for the usr to lift his finger
				LCDcommand(clearScreen);
			}
			if((!get_SW2())&&(get_SW3())) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = time_to_second(arr); // function that read the input time
				currentState = Cooking;
			}
				
			do{	
				LCDpos(4, 1);
				time_1 = getchar();
				arr[4] = time_1;  
				LCDpos(0, 1);
				lcdString(arr); // 00:0(time_1)
				if (time_to_second(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(time_to_second(arr) == -1);

			if(!(GPIO_PORTF_DATA_R & SW1)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				LCDcommand(clearScreen);
			}
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = time_to_second(arr);
				currentState = Cooking;
			}

			do{	
				LCDpos(4, 1);
				time_2 = getchar();
				arr[4] = time_2;
				arr[3] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // 00:(time_1)(time_2)
				if (time_to_second(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(time_to_second(arr) == -1);

			if(!(GPIO_PORTF_DATA_R & SW1)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				LCDcommand(clearScreen);
			}
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = time_to_second(arr);
				currentState = Cooking;
			}

			do{
				LCDpos(4, 1);
				time_3 = getchar();
				arr[4] = time_3;
				arr[3] = time_2;
				arr[1] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // 0(time_1):(time_2)(time_3)
				if (time_to_second(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(time_to_second(arr) == -1);

			if(!(GPIO_PORTF_DATA_R & SW1)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				LCDcommand(clearScreen);
			}
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = time_to_second(arr);
				currentState = Cooking;
			}

			do{
				LCDpos(4, 1);
				time_4 = getchar();
				arr[4] = time_4;
				arr[3] = time_3;
				arr[1] = time_2;
				arr[0] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // (time_1)(time_2):(time_3)(time_4)
				if (time_to_second(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(time_to_second(arr) == -1);

			if(!(GPIO_PORTF_DATA_R & SW1)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				LCDcommand(clearScreen);
			}
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = time_to_second(arr);
				currentState = Cooking;
			}

			break;
/* ================================================================================================================================================================ */
		Cooking:
			LCDcommand(clearScreen);
			unsigned int temp_time = time; // temporary copy of time variable
			while (1) {
				if(!get_SW3()) { // check for door
					while (!get_SW3()); // wait for the usr to lift his finger
					currentState = Pause;
					time = temp_time; // saving the current time before changing current state
					break;
				}
				if(!get_SW1()) { // check for pause button
					while (!get_SW1()); // wait for the usr to lift his finger
					currentState = Pause;
					time = temp_time; // saving the current time before changing current state
					break;
				}
				char timeFormat[5]; // 00:00
				unsigned int minutes = temp_time/60; // getting number of minutes from time variable
				unsigned int seconds = temp_time%60; // getting number of seconds from time variable
				if(minutes>9) { // for minutes part
					timeFormat[0] = '0' + minutes/10;
					timeFormat[1] = '0' + minutes%10;
				}
				else {
					timeFormat[0] = '0';
					timeFormat[1] = '0' + minutes;
				}
				if(seconds>9) { // for seconds part
					timeFormat[3] = '0' + seconds/10;
					timeFormat[4] = '0' + seconds%10;
				}
				else {
					timeFormat[3] = '0';
					timeFormat[4] = '0' + seconds;
				}
				timeFormat[2] = ':';
				lcdString(timeFormat);
				if(temp_time == 0) {
					break;
				}
				temp_time--;
				// then for 1 second delay and leds control
				one_sec_delay_loading();
			}
			if (temp_time == 0) {
				LCDcommand(clearScreen); // for clearing the screen after cooking is done then returning back to IDLE
				currentState = IDLE;
			}
			break;
/* ================================================================================================================================================================ */
		Pause:
			// no clearing screen here, we need to keep time on screen
			// inturrept
			while(1) {
				ledBlink();
				if((!get_SW2())&&(get_SW3())) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
					while (!get_SW2()); // wait for the user to lift his finger
					currentState = Cooking;
					break;
				}
				else if (!get_SW1()) { // if sw1 is pressed (cancel cooking)
					while (!get_SW1()); // wait for the user to lift his finger
					currentState = IDLE;
					break;
				}
			}
			break;
/* ================================================================================================================================================================ */
		default:
			printf("default statement");
		}
		

	}
	
}
