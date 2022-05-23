#include "LCDKeypad.h"
#include "timer.h"

// Standalone timer function can be reused in any other application
// as the control in entirely inside the function
// we decided on this design instead of hardware interrupts
// because it makes the implementation easier and the code simpler
// in addition its more modular and can be used in other applications
// or even other microcontrollers with minimal changes

// Global variables hold the current value of timer
int minute = 0;
int second = 0;
// used for saving the last value when paused
int currentmin;
int currentsec;
int flag = 0; // flags used to interrupt and control the flow of timer function

int timer(int seconds)
{
  minute = (int)seconds / 60; // seperate input to seconds and minutes
  second = seconds - minute * 60;

  led_Init();
  while (1)
  {
    while (get_SW1() && get_SW2() && get_SW3() && flag == 0)
    {
      // as long as no switches are pressed and flag is set to zero
      // the timer decrements normally and the microwave is running
      green();                       // green LED on when microwave is running
      if (minute == 0 && second < 1) // when the timer finishes
      {
        minute = second = 0; // clears the variables
        flag = 1;            // interrupts the timer
        printdata();         // print 00:00 for 1 seconds
        delayms(1000);
        LCDcommand(Clear); // clear the LCD
        ledbuzzer();       // buzzer and blinking
				flag = 0;
        return main();     // return to idle state
      }
      if (minute < 0) // handles when minutes go below zero
      {
        minute = 0;
      }
      if (second < 0) // handles when seconds go below zero
      {
        second = 59;
        --minute;
      }
      printdata();   // print current time on screen
      delayms(1000); // delay 1 second
      --second;      // decrements seconds after each second
    }

    selection(); // go to select function

    if (flag == 1)
    {
      delayms(2000);
      if (!get_SW1() && get_SW2() && get_SW3())
      {
        // if sw1 is pressed second time exit timer function
        minute = 0;
        second = 0; // clears the timer
        printdata();
        delayms(2000);             // wait 2 seconds
        LCDcommand(Clear);         // clear the LCD
        beep();                    // buzzzer
        GPIO_PORTF_DATA_R &= ~0xE; // clear LEDs when cooking stops
        break;                     // exits timer function
      }
    }
  }
  flag = 0;
  return main();
}

void printdata()
{
  LCDcommand(Clear); // clear screen
  LCDcus('G');       // prints custom character "Sand timer"
  char buffer[6];
  sprintf(buffer, "%02d:%02d", minute, second); // send a formatted string to buffer
  LCDpos(0, 5);                                 // control the position on LCD
  LCDstring(buffer);                            // print the string.
  return;
}

void selection() // timer functions
{
  while (1)
  {
    while (get_SW1() && get_SW2() && get_SW3()) // as long as timer is in pause state blink
    {
      ledBlink();
    }

    if (get_SW1() && !get_SW2() && get_SW3()) // resume when sw2 is pressed and door closed
    {
      minute = currentmin; // continue from saved value
      second = currentsec;
      flag = 0;
      break;
    }
    else if (get_SW2() && !get_SW1() || !get_SW3()) // pause when sw1 is pressed or when door opened
    {
      currentmin = minute; // save last value to global variable
      currentsec = second;
      flag = 1;
      delayms(200); // debounce the switch to differentiate 1st and second press
      break;
    }
    else if (get_SW3() && !get_SW1() && !get_SW2()) // clear
    {
      minute = second = 0;
      flag = 1;
      printdata();
      break;
    }
  }
  return;
}
