int custome_Time(unsigned char arr[]){
    int time1 = ((int)(arr[0]) - 48) * 600;
    int time2 = ((int)(arr[1]) - 48) * 60;
    int time3 = ((int)(arr[3]) - 48) * 10;
    int time4 = (int)(arr[4]) - 48;
    int result;
    result = time1 + time2 + time3 + time4;
    
    if(!(arr[0]>=48 && arr[0]<=57 && arr[1]>=48 && arr[1]<=57 && arr[3]>=48 && arr[3]<=57 && arr[4]>=48 && arr[4]<=57)){
        return -1;
    }else{
        return result;
    }
}