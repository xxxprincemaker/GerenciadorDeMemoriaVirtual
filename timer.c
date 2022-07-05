//
// Created by VipSo on 7/5/2022.
//
#include <time.h>

time_t start, end;

double dif;

void startTimer(){
    time(&start);
}
void endTime(){
    time(&end);
    dif = difftime(end, start);
}
double timelapse(){
    return dif;
}

