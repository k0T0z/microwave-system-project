#include "stdint.h"
#include "popcorn.c" // for popcorn function
#include "systick_delay.c"

#define SW1 0x01
#define SW2 0x10

void SystemInit() {} // needed in startup code file
	

unsigned char keypadFetch(void);
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
	
	while(1) {
		unsigned char input = keypadFetch(); // fetching pressed key from keypad
		unsigned char sw1_in = sw1Fetch();
		unsigned char sw2_in = sw2Fetch();
		unsigned char sw3_in = sw3Fetch();
		unsigned char currentState = IDLE;
		unsigned int time = 0; // time in seconds
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
				lcdString("input error");
				wait(200); // wait for 2 seconds
			}
			break;
		Popcorn:
			lcdString("POPCORN, START?");
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				time = 60;
				currentState = Cooking;
			}
			break;
		Beef:
			lcdString("BEEF, KILOS?");
			// fetching data from keypad to check number of kilos
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				currentState = Cooking;
			}
			break;
		Chicken:
			lcdString("CHICKEN, KILOS?");
			// fetching data from keypad to check number of kilos
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				currentState = Cooking;
			}
			break;
		Custom:
			lcdString("TIME?");
			// fetching data from keypad to check time entered
			if(!(GPIO_PORTF_DATA_R & SW2)) {
				while ((!(GPIO_PORTF_DATA_R & SW2))&&(/* door closed */)); // wait for the usr to lift his finger
				currentState = Cooking;
			}
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
				clear();
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
				blink();
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
		}

	}
	
	
	
}
