#include<Arduino.h>
#include "TimerManager.h"
#include "Control.h"

Timer timer;

unsigned long startTime = 0;
unsigned long duration = 0;

bool targetState = false;
bool timerRunning = false;

void Timer::startTimer(unsigned long timeMs, bool state){
    startTime = millis();
    duration = timeMs;
    targetState = state;
    timerRunning = true;
}

int Timer::remainingSec(){
   if(!timerRunning) return 0;

   unsigned long elapsed = millis() - startTime;

   if(elapsed >= duration) return 0;

   return (duration - elapsed) / 1000;
}

bool Timer::getTargetState(){
    return targetState;
}

void Timer::loop(){
    if(timerRunning && millis() - startTime >= duration){
        targetState?control.on():control.off();
        timerRunning = false;
    }
}
