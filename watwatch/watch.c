#include "watch.h"

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
        OrbitOledSetCursor(1, 1);
        OrbitOledPutString("Current Time");

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

void switchUnit() {
	long time = millis();
    if((time - lastTimestampAlarm)>200){
        unit = !unit;
        lastTimestampAlarm = time;
    }
}


//Page to select alarm
void drawAlarm(){
	//Checks input
	int pot = analogRead(A0);

	if (unit == HOUR){
                currentAlarm.hour = map(pot, 0, 1023, 0, 23) / 4;
            } else{
                currentAlarm.minute = map(pot, 0, 1023, 0, 59) / 4;
            }
	
	//Prints stuff
	char str[50];
	sprintf(str, "Alarm: %d:%d", currentAlarm.hour, currentAlarm.minute);
	OrbitOledSetCursor(1, 1);
	OrbitOledPutString(str);
	sprintf(str, "h  m");
	OrbitOledSetCursor(8, 3);
	OrbitOledPutString(str);
}

void flashLED() {
    digitalWrite(BLUE_LED, HIGH);
    flashed = millis();
}

void flashRedLED() {
    digitalWrite(RED_LED, HIGH);
    flashedRed = millis();
    delay(1000);
    digitalWrite(RED_LED, LOW);
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

void switchOption() {
    long time = millis();
    if((time - lastTimestampValue)>200){
        option++;
        if(option > 2)
            option = 0;
        lastTimestampValue = time;
    }
}

//Check alarm, continuously called
//TIME_DELAY
void checkAlarm() {
    int i;
    for(i = 0; i < alarmSize; i++) {
        if(alarms[i].ms == -1)
            continue;
        if(getDate().minute - alarms[i].minute >= 0) {
            flashRedLED();
            alarms[i].ms = -1;
        }
    }
    return;
}

void setAlarm(struct date d) {
    if(alarmSize + 1 <= MAX_ALARMS) {
        alarms[alarmSize] = d;
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
    lastStopValue = 0;
}

//pauseStopWatch, pauses/starts the stopwatch
void pauseStopWatch() {
    stopwatchRunning = !stopwatchRunning;
    lastStopValue = 0;
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

void stopWatchSwitch(int v) {
    long time = millis();
    if((time - lastStopValue)>200){
        if(v == PAUSE)
            pauseStopWatch();
        if(v == RESET)
            resetStopWatch();
    }
}

void drawStopWatch(){
    const int START_X = 1;
    const int START_Y = 2;
    int t = getStopWatch();
    int hours = t / 3600000;
    int minutes = (t % 3600000) / 60000;
    int seconds = (t % 60000) / 1000;
    int ms = t % 1000;
    char str[50];
    OrbitOledSetCursor(START_X, START_Y - 1);
    OrbitOledPutString("Stopwatch");
    OrbitOledSetCursor(START_X, START_Y);
    sprintf(str, "%d:%d:%d:%d", hours, minutes, seconds, ms);
    OrbitOledPutString(str);
    OrbitOledSetCursor(START_X, START_Y + 1);
    OrbitOledPutString("h m s ms");
    if(lastStopValue == -2)
        startStopWatch();
}
