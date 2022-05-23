extern int minute;
extern int second;
// used for saving the last value when paused
extern int currentmin;
extern int currentsec;
extern int flag; // flags used to interrupt and control the flow of timer function

int timer(int seconds);
void selection();
void printdata();