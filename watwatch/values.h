#ifndef VALUES_H
#define VALUES_H

struct date {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int ms;
};

//Hard coded begin date
struct date startDate = {2015, 11, 26, 11, 30, 0, 0};

//Current date
struct date currentDate = startDate;

//Hard coded day of month
int month[] = {31, (startDate.year % 4 == 0 && startDate.year % 100 != 0) || startDate.year % 400 == 0 ? 29 : 28, 31, 30, 31, 30, 31, 31, 30 ,31, 30, 31};


#define DATE_DELAY 1

//Integer ID for potentiometer
#define POT 420

//Potentiometer
int pot = 0;

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

//Menu delay
#define MENU_DELAY 1000

//Function calling delays, ms
#define DRAW_DELAY 50

//Past range to check steps, ms
#define STEP_RANGE 500

//Past range to check temperature
#define TEMP_RANGE 500

//Past Range to store heartbeat data
#define HEART_RANGE 60000 //1 minute

//Acceleration data memory locations
#define	X_ADDR 0x32
#define	Y_ADDR 0x34
#define	Z_ADDR 0x36

//Step Tracking Params
#define STEP_SENSITIVITY 0.1 //Higher the number = less sensitive
#define STEP_DISTANCE 0.7874 //Distance travelled per step in m
#define WEIGHT 70 //Weight of user in kg

//Heart Rate Params
#define BEAT_SENSITIVITY 0.25
#define BEAT_FACTOR 10

//Number of steps since start
int steps = 0;

//Number of heartbeats since start
int beats = 0;

//Heartbeat
int heartBeats[HEART_RANGE / 1000];

//Accelerometer data for past STEP_RANGE
double data[STEP_RANGE];

//Temperature data for past TEMP_RANGE
double temp[TEMP_RANGE];

//Function calling delays, ms
#define DRAW_DELAY 50
#define TIME_DELAY 10
#define TIMER_DELAY 1000
#define STOPWATCH_DELAY 1

#endif
