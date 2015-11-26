//Watch.h
//Used for time-related functions

#ifndef WATCH_H
#define WATCH_H

#include "date.h"
#include "values.h"

//Declarations
void initWatch();
void drawWatch();
void updateTime();
void updateTimer();
void getWatch();
void timer(int s);
void checkAlarm();
void setAlarm(struct date d);
void startStopWatch();
void pauseStopWatch();
void stopStopWatch();
void resetStopWatch();
int getStopWatch();
void drawTimer();
void drawAlarm();
void drawStopWatch();
void flashLED();
void flashRedLED();
void switchUnit();
void stopWatchSwitch();

#endif // WATCH_H
