//Watch.h
//Used for time-related functions

#ifndef WATCH_H
#define WATCH_H

#include "misc.h"
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

//Current date
struct date current;

//Alarms
#define MAX_ALARMS 100
struct date alarms[MAX_ALARMS];
int alarmSize = 0;

//Timers
#define MAX_TIMERS 100
int timers[MAX_TIMERS];
int timerSize = 0;

//Current Alarm
#define HOUR 0
#define MIN 1
int currentAlarm = -1, unit = HOUR;

//Stopwatch
int stopwatch = 0;
bool stopwatchRunning = false;

//Initialization function
//Only called once
void initWatch() {
	GPIOPinTypeGPIOInput(BTN1Port, BTN1);
	GPIOPinTypeGPIOInput(BTN2Port, BTN2);
	GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
	current = getDate();
	int i;
	for(i = 0; i < MAX_TIMERS; i++) {
		timers[i] = -1;
	}
	return;
}

//Draws current function, continuously called
//DRAW_DELAY
void drawWatch() {
		OrbitOledClear();
        //Main Time Submenu
        OrbitOledSetCursor(8, 1);
        OrbitOledPutString("Time");

        hours = current.hour;
        minutes = current.minute;
        seconds = current.second;

        //Displaying Time
        itoa(hours, stringHours, 10);
        OrbitOledSetCursor(1, 3);
        OrbitOledPutString(stringHours);

        OrbitOledSetCursor(5,3);
        OrbitOledPutString(":");

        itoa(minutes, stringMinutes, 10);
        OrbitOledSetCursor(7, 3);
        OrbitOledPutString(stringMinutes);

        OrbitOledSetCursor(11,3);
        OrbitOledPutString(":");

        itoa(seconds,stringSeconds,10);
        OrbitOledSetCursor(13,3);
        OrbitOledPutString(stringSeconds);
}

//Checks and updates current time, continuously called
void updateTime() {
	updateDate();
	current = getDate();
}

//Draw timer
void drawTimer() {
	    //Display Title
        OrbitOledSetCursor(3 , 1);
        OrbitOledPutString("Timer: ");

        //Read pot
        pot = analogRead(A0);
        pot = map(pot, 0, 1023, 0, 500);

        //Displays timer value
        timeValue = pot / 4;
        itoa(timeValue,timerDisplay,10);
        OrbitOledSetCursor(3, 3);
        OrbitOledPutString(timerDisplay);

        //When function is first called
        if (option==0) {
	        OrbitOledSetCursor(8,3);
	        OrbitOledPutString("s");
        }
        else if(option == 1) {
	        OrbitOledSetCursor(8,3);
	        OrbitOledPutString("m");
        }
        else if (option == 2) {
	        OrbitOledSetCursor(8,3);
	        OrbitOledPutString("h");
        }

}

void switchOption() {
	long time = millis();
    if((time - lastTimestampValue)>200){
        option++;
        if(option > 2)
        	option = 0;
        lastTimestampValue = time;
    }
}


//Page to select alarm
void drawAlarm(){
	//TODO: IDK what the UI for this should be
}

//Draw alarm
void setAlarm(int alarm) {
	const int MAX_POT_VAL = 5000; //Maybe its more?
	//Checks input
	int pot = analogRead(0);
	long val1 = GPIOPinRead(BTN1Port, BTN1);
	long val2 = GPIOPinRead(BTN2Port, BTN2);
	if (val1 == BTN1){
		unit = !unit;
	} else if (val2 == BTN2){
		setActiveMenu(WATCH);
	}
	if (unit == HOUR){
		alarms[alarm].hour = ((double)pot) * 24 / MAX_POT_VAL;
	} else{
		alarms[alarm].minute = ((double)pot) * 60 / MAX_POT_VAL;
	}
	//Prints stuff
	char *str;
	sprintf("Alarm: %d:%d", str, alarms[alarm].hour, alarms[alarm].minute);
	OrbitOledSetCursor(10, 10);
	OrbitOledPutString(str);
}

long flashed = 0;

void flashLED() {
	digitalWrite(BLUE_LED, HIGH);
	flashed = millis();
}

//Update Timer, continuously called
//TIMER_DELAY
void updateTimer() {
	if(millis() - flashed >= FLASH_DELAY) {
		digitalWrite(BLUE_LED, LOW);
		flashed = millis();
	}
	int i;
	for(i = 0; i < timerSize; i++) {
		if(timers[i] == -1)
			continue;
		timers[i] --;
		if(timers[i] <= 0) {
			timers[i] = -1;
			flashLED();
		}
	}
	return;
}

//Creates a new timer with s seconds left
void timer(int s) {
	if(timerSize < MAX_TIMERS) {
		timers[timerSize] = s;
		timerSize++;
	}
	else {
		//SUM TING WONG
		//REALLY WONG
		//REALLY REALLY WONG
		//REALLY REALLY REALLY WONG
		//RILEY WONG
	}
  return;
}

//Check alarm, continuously called
//TIME_DELAY
void checkAlarm() {
	int i;
	for(i = 0; i < alarmSize; i++) {
		if(timeElapsedMs(alarms[i], getDate()) >= 0) {
			//RING RING RING RING RING BANANA PHONE
			//TODO: Flash LEDs
		}
	}
	return;
}

void setAlarm(struct date d) {
	if(alarmSize + 1 < MAX_ALARMS) {
		alarms[alarmSize + 1] = d;
		alarmSize++;
	}
	else {
		//SUM TING WONG
		//REALLY WONG
		//REALLY REALLY WONG
		//REALLY REALLY REALLY WONG
		//RILEY WONG

		//How do you make more than MAX_ALARMS alarms???
	}
	return;
}

//startStopWatch, starts the stopwatch
void startStopWatch() {
	stopwatchRunning = true;
	//TODO: Continuously call stopwatch
}

//resetStopWatch, resets the stopwatch
void resetStopWatch() {
	stopwatch = 0;
	stopwatchRunning = false;
}

//pauseStopWatch, pauses the stopwatch
void pauseStopWatch() {
	stopwatchRunning = false;
}

//runStopWatch, runs the stopwatch
//STOPWATCH_DELAY
void runStopWatch() {
	if(stopwatchRunning) {
		stopwatch++;
	}
}

//getStopWatch, gets the current stopwatch value, ms
int getStopWatch() {
	return stopwatch;
}

void drawStopWatch(){
	const int START_X = 1;
	const int START_Y = 2;
	int time = getStopWatch();
	int hours = time / 3600000;
	int minutes = (time % 3600000) / 60000;
	int seconds = (time % 60000) / 1000;
	int ms = time % 1000;
	char *str;
	OrbitOledSetCursor(START_X, START_Y);
	if (hours){
		sprintf("%d:%d:%d:%d", str, hours, minutes, seconds, ms);
	}else if (minutes){
		sprintf("%d:%d:%d", str, minutes, seconds, ms);
	}else if (seconds){
		sprintf("%d:%d", str, seconds, ms);
	}else{
		sprintf("%d", str, ms);
	}
	OrbitOledPutString(str);

	//Bottom button
    btn1 = GPIOPinRead(BTN1Port, BTN1);

    //Top Button
    btn2 = GPIOPinRead(BTN2Port, BTN2);

    //Switches
    swt1 = GPIOPinRead(SWT1Port, SWT1);
    swt2 = GPIOPinRead(SWT2Port, SWT2);

    if (btn1 == BTN1) {
    	pauseStopWatch();
    }
    if (btn2 == BTN2) {
    	resetStopWatch();
    }
    if (swt2 == SWT2) {
    	setActiveMenu(MAIN);
    }
}

#endif // WATCH_H
