# Microwave Oven Controller Project

For main structure by saifkandil

Our state model contains 7 different states which are IDLE, POPCORN, BEEF, CHICKEN, CUSTOM, COOKING and PAUSE connected in the model as shown

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

each case contains a specific functionality in main.c

