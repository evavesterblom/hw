#include "runningAverage.h"
#include <stdint.h>

void runningAverage::set(uint64_t reading){
    count+=1;
    average = average * (count - 1)/count + (long double)reading/count; //new average = old average * (n-1)/n + new value /n
}

long double runningAverage::getAverage(){
    return average;
}

void runningAverage::reset(){
    average = 0;
    count = 0;
}