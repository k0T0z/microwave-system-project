#include "stdint.h"
#include "systick_delay.c"
#include "getchar.c"
#include "LCDinit.c"
#include "portF_init.c"
#include "Cooking_Oprations.c"
#include "systick_delay.c"
#include "Prototype.h"

#define SW1 0x01
#define SW2 0x10
#define SW3 0x20

void SystemInit() {} // needed in startup code file


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
	
	while(1) {
		unsigned char input = getchar(); // fetching pressed key from keypad
		unsigned char sw1_in = get_SW1();
		unsigned char sw2_in = get_SW2();
		unsigned char sw3_in = get_SW3();
		unsigned char currentState = IDLE;
		unsigned int time = 0; // time in seconds
		unsigned int weight = 0; // weight used in Beef and Chicken
		unsigned char time_1 = '0';
		unsigned char time_2 = '0';
		unsigned char time_3 = '0';
		unsigned char time_4 = '0';
		unsigned char arr[5] = {'0', '0', ':', '0', '0'}; // array of characters used in custom
		switch(currentState) {
		IDLE: 
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
		Popcorn:
			LCDcommand(clearScreen);
			lcdString("POPCORN, START?");
			if(!get_SW2()) { // if sw2 is pressed (start)
				while ((!get_SW2())&&(get_SW3())); // wait for the user to lift his finger
				time = 60; // one minute for popcorn
				currentState = Cooking;
			}
			break;
		Beef:
			do{       									 
				LCDcommand(clearScreen);
				lcdString("Beef weight?");
				LCDpos(0, 1); // cursor position
				input = getchar();
				
				// Intstr waits for two arguments where's the second one?

				weight = Intstr(input); // input weight from user
				lcdString(input); // dispaly input
				if(!(weight >=0 && weight <=9)){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				} 
			} while(!(weight >=0 && weight <=9));
			if((!get_SW2())&&(get_SW3())) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
				while (!get_SW2()); // wait for the user to lift his finger
				time = 30 * weight; // set time for Beef (0.5 minute for each kilo)
				currentState = Cooking;
			}
			break;
		Chicken:
			do{       									 
				LCDcommand(clearScreen);
				lcdString("Chicken weight?");
				LCDpos(0, 1); // cursor position
				input = getchar();
				weight = Intstr(input); // input weight from user
				lcdString(input); // dispaly input
				if(!(weight >=0 && weight <=9)){
					LCDcommand(clearScreen);
					lcdString("Err"); // wrong input
					wait(200);
				} 
			} while(!(weight >=0 && weight <=9));
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = 12 * weight; // set time for chicken
				currentState = Cooking;
			}
			break;
		
		Custom:
			do{
				LCDcommand(clearScreen);
				lcdString("Cooking Time?");
				LCDpos(0, 1);
				lcdString(arr);
				if (custome_Time(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(custome_Time(arr) == -1);
				if(!(GPIO_PORTF_DATA_R & SW1)) { 
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr); // function that read the input time
					currentState = Cooking;
				}
				
			do{	
				LCDpos(4, 1);
				time_1 = getchar();
				arr[4] = time_1;  
				LCDpos(0, 1);
				lcdString(arr); // 00:0(time_1)
				if (custome_Time(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(custome_Time(arr) == -1);
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
					currentState = Cooking;
				}
			do{	
				LCDpos(4, 1);
				time_2 = getchar();
				arr[4] = time_2;
				arr[3] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // 00:(time_1)(time_2)
				if (custome_Time(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(custome_Time(arr) == -1);
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
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
				if (custome_Time(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(custome_Time(arr) == -1);
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
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
				if (custome_Time(arr) == -1){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				}
			} while(custome_Time(arr) == -1);
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
					currentState = Cooking;
				}
			break;
		
		Cooking:
			// always check for door (SW3)
			unsigned int temp_time = time; // temporary copy of time variable
			while (1) {
				if(!get_SW3()) {
				while (!get_SW3()); // wait for the usr to lift his finger
				currentState = Pause;
				time = temp_time; // saving the current time before changing current state
				break;
				}
				if(!get_SW1()) {
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
				off(); // for turning all the leds off
				red();
				wait(partOfSecond);
				off();
				blue();
				wait(partOfSecond);
				off();
				green();
				wait(part2OfSecond);
			}
			if (temp_time == 0) {
				LCDcommand(clearScreen); // for clearing the screen after cooking is done
				currentState = IDLE;
			}
			break;
		Pause:
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
		default:
			printf("");
		}
		

	}
	
}
