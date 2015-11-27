#ifndef VALUES_H
#define VALUES_H

struct date {
  int hour;
  int minute;
  int second;
  int ms;
};

//Current date
struct date currentDate = {11, 30, 0, 0};

//Hard coded day of month
//int month[] = {31, (startDate.year % 4 == 0 && startDate.year % 100 != 0) || startDate.year % 400 == 0 ? 29 : 28, 31, 30, 31, 30, 31, 31, 30 ,31, 30, 31};


#define DATE_DELAY 1

//Integer ID for potentiometer
#define POT 420

//Potentiometer
int pot = 0;

//Char variables for time
char stringSeconds[2];
char stringMinutes[2];
char stringHours[2];

//Long variables for time
long hours = 19;
long minutes = 0;
long seconds = 0;

//Buttons and Switches
long btn1;
long btn2;
long swt1;
long swt2;

//Menu definitions
#define MAIN 0
#define TRACK 1
#define WATCH 2
#define TIMER 3
#define ALARM 4
#define STOPWATCH 5
#define SETTINGS 6
#define SETTIME 7
#define SETSTEPS 8
#define SETHEARTBEATS 9

//Active menu
int activeMenu = MAIN;

long lastTimestamp = 0;
long lastTimestampValue = 0;
long lastTimestampAlarm = 0;
long lastStopValue = -2;

//Menu delay
#define MENU_DELAY 500

//Function calling delays, ms
#define DRAW_DELAY 50

//Past range to check steps, ms
#define STEP_RANGE 500

//Past range to check temperature
#define TEMP_RANGE 500

//Past Range to store heartbeat data
#define HEART_RANGE 60000 //1 minute

//Step Tracking Params
#define STEP_SENSITIVITY 300 //Higher the number = less sensitive
#define STEP_DISTANCE 0.7874 //Distance travelled per step in m
#define WEIGHT 70 //Weight of user in kg

//Heart Rate Params
#define BEAT_SENSITIVITY 0.01
#define BEAT_FACTOR 10

//Number of steps since start
int steps = 0;
int totalAss = 0;

//Number of heartbeats since start
int beats = 0;

//Heartbeat
int heartBeats[HEART_RANGE / 1000];

//Accelerometer data for past STEP_RANGE
double data[STEP_RANGE];

//Temperature data for past TEMP_RANGE
double temp[TEMP_RANGE];

//BPM
int bpm = 0;
#define BPM_DELAY 5000
#define BPM_LOW 60
#define BPM_HIGH 80

//Function calling delays, ms
#define DRAW_DELAY 50
#define TIME_DELAY 10
#define TIMER_DELAY 1000
#define STOPWATCH_DELAY 1
#define STEP_DELAY 500
#define FLASH_DELAY 1000
#define ACCELER_DELAY 50

//Timer Variables
int timeValue;
char timerDisplay[2];
int option = 0;

//Current Alarm
#define HOUR 0
#define MIN 1
int currentAlarmVal = -1, unit = HOUR;

//StopWatch
#define PAUSE 0
#define RESET 1

//Current date
struct date current;

//Alarms
#define MAX_ALARMS 100
struct date currentAlarm;
struct date alarms[MAX_ALARMS];
int alarmSize = 0;

//Timers
#define MAX_TIMERS 100
int timers[MAX_TIMERS];
int timerSize = 0;

//Stopwatch
int stopwatch = 0;
bool stopwatchRunning = false;

long flashed = 0;
long flashedRed = 0;

//Variables for displaying steps
int step;
char stringSteps[5];
int set = 0;

//Last
int last = 0;

#endif
