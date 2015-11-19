//Track.h
//Used for tracking-related functions
//Please edit with an actual text editor

#ifndef TRACK_H
#define TRACK_H

#include "watch.h"
#include "misc.h"
#include "socket.h"

//Function calling delays, ms
#define DRAW_DELAY 50
#define STEP_DELAY 100
#define ACCEL_DELAY 1

//Past range to check steps, ms
#define STEP_RANGE 500

//Past range to check temperature
#define TEMP_RANGE 500

//Number of steps since start
int steps = 0;

//Accelerometer data for past STEP_RANGE
double data[STEP_RANGE];

//Temperature data for past TEMP_RANGE
double temp[TEMP_RANGE];

//Receives input
void trackInput(int input, int selected) {
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
void drawTrack() {

}

//Check step, continuously called, returns 1 if step occurred in past STEP_RANGE ms
//STEP_DELAY
int checkStep() {
	return 0;
}

//Get accelerometer data, continuously called
//ACCEL_DELAY
void getData() {
	//TODO: Get accelerometer reading
	data[millis() % STEP_RANGE] = 0.0;
}

//Get current steps
int getSteps() {
	return steps;
}

//Get current distance travelled in m
int getDistance() {
	//TODO: Formula
	return 0;
}

//Get calories burnt
int getCalories() {
	//TODO: Formula
	return 0;
}

//Reset steps
void resetSteps() {
	steps = 0;
}

//Set steps
void setSteps(int s) {
	steps = s;
}

#endif // TRACK_H
