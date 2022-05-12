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

void SystemInit() {} // needed in startup code file
	
unsigned char sw1Fetch(void);
unsigned char sw2Fetch(void);
unsigned char sw3Fetch(void);


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
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = 60;
				currentState = Cooking;
			}
			break;
		
		Beef:
			do{       									 
				LCDcommand(clearScreen);
				lcdString("Beef weight?");
				LCDpos(0, 1); // cursor position
				input = getchar();
				weight = Intstr(input); // input weight from user
				lcdString(input); // dispaly input
				if(!(weight >=0 && weight <=9)){
					LCDcommand(clearScreen);
					lcdString("Err");
					wait(200);
				} 
			} while(!(weight >=0 && weight <=9));
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = 30 * weight; // set time for Beef
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
				if(!(GPIO_PORTF_DATA_R & SW1)) { 
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr); // function that read the input time
					currentState = Cooking;
				}
				LCDpos(4, 1);
				time_1 = getchar();
				arr[4] = time_1;  
				LCDpos(0, 1);
				lcdString(arr); // 00:0(time_1)
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
					currentState = Cooking;
				}
				LCDpos(4, 1);
				time_2 = getchar();
				arr[4] = time_2;
				arr[3] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // 00:(time_1)(time_2)
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
					currentState = Cooking;
				}
				LCDpos(4, 1);
				time_3 = getchar();
				arr[4] = time_3;
				arr[3] = time_2;
				arr[1] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // 0(time_1):(time_2)(time_3)
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
					currentState = Cooking;
				}
				LCDpos(4, 1);
				time_4 = getchar();
				arr[4] = time_4;
				arr[3] = time_3;
				arr[1] = time_2;
				arr[0] = time_1;
				LCDpos(0, 1);
				lcdString(arr); // (time_1)(time_2):(time_3)(time_4)
				if(!(GPIO_PORTF_DATA_R & SW1)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					LCDcommand(clearScreen);
				}
				if(!(GPIO_PORTF_DATA_R & SW2)) {
					while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
					time = custome_Time(arr);
					currentState = Cooking;
				}
			} 
			
			// where's the while part?

			break;
		
		Cooking:
			// always check for door (SW3)
			unsigned int i = time;
			while (i >= 0) {
				if(!(GPIO_PORTF_DATA_R & SW1)) {
				while ((!(GPIO_PORTF_DATA_R & SW1))&&(/* door closed */)); // wait for the usr to lift his finger
				currentState = Pause;
				time = i;
				break;
				}
				char timeFormat[5];
				unsigned int temp = i/60;
				if(temp>9) {
					timeFormat[0] = '0' + temp/10;
					timeFormat[1] = '0' + temp%10;
				}
				else {
					timeFormat[0] = '0';
					timeFormat[1] = '0' + temp;
				}
				lcdString(timeFormat);
				i--;
				// then for 1 second delay and leds control
				clear(); // for turning all the leds off
				red();
				wait(partOfSecond);
				clear();
				blue();
				wait(partOfSecond);
				clear();
				green();
				wait(part2OfSecond);
			}
			break;
		Pause:
			while(1) {
				ledBlink();
				if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				currentState = Cooking;
				break;
				}
				else if (!(GPIO_PORTF_DATA_R & SW1)) {
				while ((!(GPIO_PORTF_DATA_R & SW1))&&(/* door closed */)); // wait for the usr to lift his finger
				currentState = IDLE;
				break;
				}
				else {
					break;
				}
			}
		default:
			printf("");
			
		}
		

	}
	
}
