//Watch.h
//Used for time-related functions
//Please edit with an actual text editor

#ifndef WATCH_H
#define WATCH_H

#include "track.h"
#include "misc.h"
#include "socket.h"

//Function calling delays, ms
#define DRAW_DELAY 50
#define TIME_DELAY 10
#define TIMER_DELAY 1

//Current date
struct date current;

//Alarms
struct date alarms[100];
int alarmSize = 0;

//Initialization function
//Only called once
void initWatch() {
	return;
}

//Receives input in the form of a button/switch/something pressed, and the selected item
void watchInput(int input, int selected) {
	switch(input) {
		case SWITCH_A:
			//TODO: Switch A
			break;
		case SWITCH_B:
			//TODO: Switch B
			break;
		case BUTTON_A:
			//TODO: Button A
			break;
		case BUTTON_B:
			//TODO: Button B
			break;
		case POT:
			//TODO: Smoke Weed
			break;
		default:
			//SUM TING WONG
			//REALLY WONG
			//REALLY REALLY WONG
			//REALLY REALLY REALLY WONG
			//RILEY WONG
			break;
	}
}

//Draws current function, continuously called
//DRAW_DELAY
void drawWatch() {

}

//Checks and updates current time, continuously called
//TIME_DELAY
void updateTime() {
	current = getDate();
}

//Update Timer, continuously called
//TIMER_DELAY
void updateTimer() {
	return;
}

void getwatch() {
  return;
}

void timer() {
  return;
}

//Check alarm, continuously called
//TIME_DELAY
void checkAlarm() {
	return;
}

void setAlarm() {
  return;
}

#endif // WATCH_H
