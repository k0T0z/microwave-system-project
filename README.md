# Microwave Oven Controller Project

For main structure by saifkandil

Our state model contains 7 different states which are:

1 - IDLE
2 - POPCORN
3 - BEEF
4 - CHICKEN
5 - CUSTOM
6 - COOKING
7 - PAUSE 

connected in the model as shown below

![image](https://user-images.githubusercontent.com/74428638/170123046-62f1064f-20d5-4d7a-9b2a-4c93a230cf8e.png)

A switch statement which contains some of the states literally

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

Each case contains a specific functionality in main.c

For IDLE, it contains code that fetches input from Keypad
For POPCORN, it conatins code for popcorn program
For BEEF, it conatins code for beef program
For CHICKEN, it conatins code for chicken program
For CUSTOM, it conatins code for custom program
For COOKING, it conatins code for timer and counting down algorithms

