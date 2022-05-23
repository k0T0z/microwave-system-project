#include "LCDKeypad.h"
#include "SW_init.c"
#include "SW3.c"
#include "buzzer.c"

 
 
 
 
 
  
void timer(int seconds);
void selection();
void printdata();
 
 




unsigned char key = 0 ; 

 
enum state
{
    IDLE,
    Popcorn,
    Beef,
    Chicken,
    Custom,
    Cooking,
    Pause
};

//int timer(int seconds);
//int selection();
//int printdata();

//Global variables
int minute = 0; 
int second = 0;
//used for saving the last value when paused
int currentmin; 
int currentsec;
int flag = 0; // flags used to interrupt and control the flow of timer function

void timer(int seconds)

{
    minute = (int)seconds / 60;
    second = seconds - minute * 60;
    
    while (1)
    {
        while (get_SW1() && get_SW2() && get_SW3() && flag == 0) 
        {   
            if (minute == 0 && second < 1)
            {
                minute = second = 0;
                flag = 1;
                printdata();
								delayms(1000);
								LCDcommand(Clear);
								beep();
								main();
            }
            if (minute < 0)
            {
                minute = 0;
            }
            if (second < 0)
            {
                second = 59;
                --minute;
            }
            printdata();
            delayms(1000); // delay 1 second
            --second;
        }
        

        selection();
				 if (flag == 1) 
      {
				delayms(2000);
        if(!get_SW1() && get_SW2() && get_SW3()){
          LCDcommand(Clear);
					beep();
					break;
        }
      }
        if (flag == 2)
        {
            flag = 0;
            break;
        }
				}
	  main(); 
}

void selection() // timer functions
{
   while(1){
   if (get_SW1() && !get_SW2() && get_SW3())
    {
        currentmin = minute;
        currentsec = second;
        flag = 0;
				break;
    }
    else if (get_SW2() && !get_SW1() || !get_SW3()){
        currentmin = minute;
        currentsec = second;
        flag = 1;
				break;
    }
    else if (!get_SW3() && !get_SW1() && get_SW2()){
        minute = second = 0;
        flag = 1;
        printdata();
				break;
       
    }
    else if (!get_SW1() && get_SW3() && !get_SW2()){
        flag = 2;
				break;
        
    }
		
    //else if (key == '#'){
        //goto IDLE ;
        
    //}
     
		}
	 return;
		
	 }

void printdata()
{
    LCDcommand(Clear);
		LCDcus('G');
    char buffer[10];
    sprintf(buffer, "%02d:%02d", minute, second);
		LCDpos(0,5);
    LCDstring(buffer);
		return;

}



int time_to_second(unsigned char arr[]){
    int time1 = ((int)(arr[0]) - 48) * 600;
    int time2 = ((int)(arr[1]) - 48) * 60;
    int time3 = ((int)(arr[3]) - 48) * 10;
    int time4 = (int)(arr[4]) - 48;
    unsigned int result;
    result = time1 + time2 + time3 + time4;
    return result;
}
		


int main()
	{
		unsigned char input;               // keypad data will be passed here
    unsigned char currentState = IDLE; // initialised to IDLE state
    int time = 0;             // time in seconds
    unsigned int weight = 0;           // weight used in Beef and Chicken states
    char s[5] = {'0', '0', ':', '0', '0'};
		unsigned char key;
		unsigned int temp;
		buzzer_init();
		LCDinit();
    keypadinit();
		SW_Init();
		SW3_Init();
		 
		 
		 

    

    while (1)
    {
				
			
        switch (currentState)
        {
            /* ================================================================================================================================================================ */
        case IDLE: // main state
					LCDcommand(Clear);
					LCDstring("Choose state");
            while (1)
            { // fetching pressed key from keypad
                input = getchar();
                if (input != 0)
                { // getchar() returns 0 if nothing is pressed so if the return is not zero break out of the loop
                    LCDcommand(Clear);
                    
                    // you can add msg to the user to  press a key
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
                LCDstring("Err");
                delayms(2000);     // wait for 2 seconds
                LCDcommand(Clear); // clear LCD
            }
            break;
            /* ================================================================================================================================================================ */
        case Popcorn:
						
            LCDcommand(Clear); // clear the screen
            LCDstring("Popcorn");
						while(1){
						if(!get_SW2() && get_SW3()) { // if sw2 is pressed (start) and sw3 is not pressed (door closed)
						delayms(2000);
						timer(60);
						break;
						}	
				} 
						break;
            
            /* ================================================================================================================================================================ */
         case Beef:
            // getting a valid weight
            LCDcommand(Clear);
            LCDstring("Beef weight?");
            delayms(2000);
			while(1){
				key = getchar();
				if (key != 0)
				{
					temp = check_Input(key);
					if (temp == 1){
						currentState = Beef;
						break;
					}	
					else{
						while(key == 0){key = getchar();}
						LCDcommand(Clear);
						LCDdata(key);
						key -= 48;
						delayms(5000);
						time = 30 * key;
						if(get_SW3()){
							timer(time);
							break;
						}
					}
				}
			}
			break;		
            /* ================================================================================================================================================================ */
         	case Chicken:
				LCDcommand(Clear);
				LCDstring("Chicken weight?");
				delayms(2000);
				while(1){
					key = getchar();
					if (key != 0)
					{
						temp = check_Input(key);
						if (temp == 1){
							currentState = Chicken;
							break;
						}	
						else{
							while(key == 0){key = getchar();}
							LCDcommand(Clear);
							LCDdata(key);
							key -= 48;
							delayms(2000);
							time = 12 * key;
							if(get_SW3()){
								timer(time);
								break;
							}
						}
					}
				}
				break;

             
				    /* ================================================================================================================================================================ */
			case Custom:
			LCDcommand(Clear);
            LCDstring("Cooking time?");
            delayms(1000);
			for (int i = 0; i < 5 ; i++)
            {
                s[i]='0';
							
            }
			s[2] = ':';
			LCDpos(1,0);
			LCDstring(s);
				
			while(1){
				key = getchar();
				if (key != 0)
				{
					temp = check_Input_arr(key);
					if (temp == 1){
					currentState = Custom;
					break;
					}												
					else if (s[0] == '0' && s[1] == '0' && s[2] == ':' && s[3] == '0' && s[4] == '0')
					{ 
						while(key == 0){key = getchar();}
						LCDcommand(Clear);
						LCDpos(0,0);
						LCDstring("Cooking time?");
						LCDpos(1,4);
						s[4] = key;
						LCDdata(s[4]);
						LCDpos(1,3);
						LCDdata(s[3]);
						LCDpos(1,2);
						LCDdata(s[2]);
						LCDpos(1,1);
						LCDdata(s[1]);
						LCDpos(1,0);
						LCDdata(s[0]);
						time = time_to_second(s);
						delayms(2000);
						if (!get_SW1()){
							LCDcommand(Clear);
							while(1){
								if(!get_SW2() && get_SW3()) {
									delayms(2000);
									timer(time);
									break;
								}	
							}
						}
					}
					else if(s[0] == '0' && s[1] == '0' && s[2] == ':' && s[3] == '0' && s[4] != '0')
					{
						while(key == 0){key = getchar();}
						LCDpos(0,0);
						LCDstring("Cooking time?");
						s[3] = s[4];
						LCDpos(1,4);
						s[4] = key;
						LCDdata(s[4]);
						LCDpos(1,3);
						LCDdata(s[3]);
						time = time_to_second(s);
						delayms(2000);
						if (!get_SW1()){
							LCDcommand(Clear);
							while(1){
								if(!get_SW2() && get_SW3()) {
									delayms(2000);
									timer(time);
									break;
								}	
							}
						}
					}
					else if(s[0] == '0' && s[1] == '0' && s[2] == ':' && s[3] != '0')
					{
						while(key == 0){key = getchar();}
						LCDpos(0,0);
						LCDstring("Cooking time?");
						s[1] = s[3];
						s[3] = s[4];
						LCDpos(1,4);
						s[4] = key;
						LCDdata(s[4]);
						LCDpos(1,3);
						LCDdata(s[3]);
						LCDpos(1,2);
						LCDdata(s[2]);
						LCDpos(1,1);
						LCDdata(s[1]);
						time = time_to_second(s);
						delayms(2000);
						if (!get_SW1()){
							LCDcommand(Clear);
							while(1){
								if(!get_SW2() && get_SW3()) {
									delayms(2000);
									timer(time);
									break;
								}	
							}
						}
					}
					else if (s[0] == '0' && s[1] != '0')
					{
						while(key == 0){key = getchar();}
						LCDpos(0,0);
						LCDstring("Cooking time?");
						s[0] = s[1];
						s[1]= s[3];
						s[3] = s[4];
						LCDpos(1,4);
						s[4] = key;
						LCDdata(s[4]);
						LCDpos(1,3);
						LCDdata(s[3]);
						LCDpos(1,2);
						LCDdata(s[2]);
						LCDpos(1,1);
						LCDdata(s[1]);
						LCDpos(1,0);
						LCDdata(s[0]);
						time = time_to_second(s);
						delayms(2000);
						if (!get_SW1()){
							LCDcommand(Clear);
							while(1){
								if(!get_SW2() && get_SW3()) {
									delayms(2000);
									timer(time);
									break;
								}	
							}
						}
					}
							
					else if (s[0] != '0'){
						delayms(2000);
						if (!get_SW1()){
							LCDcommand(Clear);
							while(1){
								if(!get_SW2() && get_SW3()) {
									delayms(2000);
									timer(time);
									currentState = IDLE;
									break;
								}	
							}
						}
						currentState = Custom;
						break;												
					}
				}
			}
			break;
										
				 
				 
 
            /* ================================================================================================================================================================ */
        }
			
    }
}

	

	
