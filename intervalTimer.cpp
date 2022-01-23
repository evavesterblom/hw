#include "intervalTimer.h"
#include <thread>

intervalTimer::intervalTimer(std::function<void()> callbackFunction, int intervalMillis){
    this->intervalMillis = intervalMillis;
    this->callbackFunction = callbackFunction;
    this->stopped = false;
}

intervalTimer::~intervalTimer(){
    stopped = true;
}


void intervalTimer::run(){
    this->t = std::thread (&intervalTimer::loop, this);
}

void intervalTimer::stop(){
    this->stopped = true;
}

void intervalTimer::loop(){
    while(!stopped){
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMillis));
        callbackFunction();
    }
}