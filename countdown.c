#include "Prototype.h"
#include "stdio.h"

void countdown(uint32_t time){
    unsigned char strSec[2] = { '0' ,'0' }; // this arr sec { '0' , '0' , ':', '5' , '9' };
    unsigned char strMin[2] = { '0' , '0' }; // this arr for min { '0' , '0' , ':', '5' , '9' };    
    unsigned char arr[5] = { '0' , '0' , ':', '0' , '0' };
    uint32_t min = 0;
    uint32_t sec = 0;
    for(time; time>0;time-1000) // time decrement 1000 ms = 1s
    {
        time/=1000;
        sec = time % 60;
        min = time / 60;
        sprintf(strSec,"%d",sec); // to convert time to string 
        sprintf(strMin,"%d",min);
        if(min>=0)
        {
            arr[0] = strMin[0];
            arr[1] = strMin[1];// i think it need some fix
            LCDstring(arr);
        }
        else{
            arr[3] = strSec[0];
            arr[4] = strSec[1];
            LCDstring(arr);
        }
    }

}









