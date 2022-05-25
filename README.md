# Microwave Oven Controller Project

For main structure by saifkandil

Our state model contains 7 different states which are:

```
1 - IDLE
2 - POPCORN
3 - BEEF
4 - CHICKEN
5 - CUSTOM
6 - COOKING
7 - PAUSE 
```

They're defined in main.c as enum called "state"

```c
enum state
{
    IDLE,
    Popcorn,
    Beef,
    Chicken,
    Custom,
    Cooking
};
```

connected in the model as shown below

![image](https://user-images.githubusercontent.com/74428638/170123046-62f1064f-20d5-4d7a-9b2a-4c93a230cf8e.png)

A switch statement which contains some of the states literally

```c
switch (currentState) {
  case IDLE:
    // code
  case POPCORN:
    // code
  case BEEF:
    // code
  case CHICKEN:
    // code
  case CUSTOM:
    // code
  case COOKING:
    // code
}
```

Each case contains a specific functionality in main.c

For IDLE, it contains code that fetches input from Keypad. For POPCORN, it conatins code for popcorn program. For BEEF, it conatins code for beef program. For CHICKEN, it conatins code for chicken program. For CUSTOM, it conatins code for custom program. For COOKING, it conatins code for timer and counting down algorithms.

States are switched by changing the value of the switch case variable which is

```c
unsigned char currentState = IDLE;
```
Its initial value is IDLE by default and its value is updated in IDLE state then switch case is closed and start again - thanks to our external while loop - but now it will enter the switch in another case as currentState variable in updated

```c
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
	LCDcus('F');
	LCDpos(0, 6);
	LCDstring("Err");
	delayms(2000);
	LCDcommand(Clear);
}
```

According to pressed key on the Keypad, the currentState variable will be updated then enter the desired state.
each state contains some algorithms that deal with our LCD like:
```c
LCDcommand(command); // For sending commands to LCD like clearing screen ... etc
```
```c
LCDcus(char); // For printing custom characters on LCD like popcorn icon
```
And many many more

