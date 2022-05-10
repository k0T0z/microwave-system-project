int Custome_Time(unsigned char arr[]){
     int time1 = ((int)(arr[0]) - 48) * 600;
     int time2 = ((int)(arr[1]) - 48) * 60;
     int time3 = ((int)(arr[3]) - 48) * 10;
     int time4 = (int)(arr[4]) - 48;
     int result;
     result = time1 + time2 + time3 + time4;

    return result;
}