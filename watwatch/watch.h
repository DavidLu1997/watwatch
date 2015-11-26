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

//Timer Variables
int timeValue;
char timerDisplay[2];
int option = 0;

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
	current = getDate();
	return;
}

//Draws current function, continuously called
//DRAW_DELAY
void drawWatch() {
        //Main Time Submenu
        OrbitOledSetCursor(8, 1);
        OrbitOledPutString("Time: ");

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

	/*char *time;
	sprintf("%d:%d:%d", time, current.hour, current.minute, current.second);
	OrbitOledSetCursor(1, 2);
	OrbitOledPutString(time);*/

	//Bottom button
    GPIOPinTypeGPIOInput(BTN1Port, BTN1);
    btn1 = GPIOPinRead(BTN1Port, BTN1);

    //Top Button
    GPIOPinTypeGPIOInput(BTN2Port, BTN2);
    btn2 = GPIOPinRead(BTN2Port, BTN2);

    //Switches
    GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
    swt1 = GPIOPinRead(SWT1Port, SWT1);
    swt2 = GPIOPinRead(SWT2Port, SWT2);

	//Goes to track screen
    if (btn1 == BTN1) {
        activeMenu = TIMER;
    }
    //Goes to watch screen
    if (btn2 == BTN2) {
        activeMenu = ALARM;
    }
    //Switch to stopwatch submenu
    if (swt1 == SWT1) {
        activeMenu = STOPWATCH;
    }
    if (swt2 == SWT2) {
    	activeMenu = MAIN;
    }
}

//Checks and updates current time, continuously called
void updateTime() {
	updateDate();
	current = getDate();
}

//Draw timer
void drawTimer() {
	    //Display Title
        OrbitOledSetCursor(4 , 1);
        OrbitOledPutString("Timer: ");

        //Read pot
        pot = analogRead(A0);
        pot /= 8;

        //Displays timer value
        timeValue = pot;
        itoa(timeValue,timerDisplay,10);
        OrbitOledSetCursor(7, 1);
        OrbitOledPutString(timerDisplay);

        //When function is first called
        if (option==0) {
	        OrbitOledSetCursor(11,3);
	        OrbitOledPutString("sec");
        }
        else if(option == 1) {
	        OrbitOledSetCursor(11,3);
	        OrbitOledPutString("min");
        }
        else if (option == 2) {
	        OrbitOledSetCursor(11,3);
	        OrbitOledPutString("hour");
        }

        //Bottom button
	    GPIOPinTypeGPIOInput(BTN1Port, BTN1);
	    btn1 = GPIOPinRead(BTN1Port, BTN1);

	    //Top Button
	    GPIOPinTypeGPIOInput(BTN2Port, BTN2);
	    btn2 = GPIOPinRead(BTN2Port, BTN2);

	    //Switches
	    GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
	    swt1 = GPIOPinRead(SWT1Port, SWT1);
	    swt2 = GPIOPinRead(SWT2Port, SWT2);


       //Change type of input when button is pressed, and will loop
       if (btn1==BTN1) {
	         if (option <2) {
	         	option++;
	         }
	         else {
	           option = 0;
	         }
       }

       if(btn2==BTN2) {
         //start counting down...?
       }
       //Return to main
       if (swt2 == SWT2) {
    		activeMenu = MAIN;
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
		activeMenu = WATCH;
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

//Update Timer, continuously called
//TIMER_DELAY
void updateTimer() {
	int i;
	for(i = 0; i < timerSize; i++) {
		timers[i] --;
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
    GPIOPinTypeGPIOInput(BTN1Port, BTN1);
    btn1 = GPIOPinRead(BTN1Port, BTN1);

    //Top Button
    GPIOPinTypeGPIOInput(BTN2Port, BTN2);
    btn2 = GPIOPinRead(BTN2Port, BTN2);

    //Switches
    GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
    swt1 = GPIOPinRead(SWT1Port, SWT1);
    swt2 = GPIOPinRead(SWT2Port, SWT2);

    if (btn1 == BTN1) {
    	pauseStopWatch();
    }
    if (btn2 == BTN2) {
    	resetStopWatch();
    }
    if (swt2 == SWT2) {
    	activeMenu = MAIN;
    }
}

#endif // WATCH_H
