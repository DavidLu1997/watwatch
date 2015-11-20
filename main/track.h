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
#define TEMP_DELAY 1

//Past range to check steps, ms
#define STEP_RANGE 500

//Past range to check temperature
#define TEMP_RANGE 500

//Past Range to store heartbeat data
#define HEART_RANGE 60000 //1 minute

//Acceleration data memory locations
#define	X_ADDR = 0x32;
#define	Y_ADDR = 0x34;
#define	Z_ADDR = 0x36;

//Step Tracking Params
#define STEP_SENSITIVITY = 1.0; //Higher the number = less sensitive

//Number of steps since start
int steps = 0;

//Number of heartbeats since start
int beats = 0;

//TODO: Initialize all arrays and shit

//Heartbeat per second
int heartBeats[HEART_RANGE / 1000];

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
	int data[3];
	getAccelerationData(data);
	for (int i = 0; i < 3; i++){
		if (data[i] > STEP_SENSITIVITY){ //If the acceleration recorded is greater than the threshhold
			return 1;
		}
	}
	return 0;
}

//Check temperature, continuously called, returns 1 if heartbeat occurred in past TEMP_RANGE ms
//TEMP_DELAY
int checkHeart() {
	heartBeats[millis() / 1000 % HEART_RANGe]++;
	return 0;
}

//Get accelerometer data, continuously called
//ACCEL_DELAY
void getData() {
	//TODO: Get accelerometer reading
	data[millis() % STEP_RANGE] = 0.0;
}

//Get temperature data, continuously called
//TEMP_DELAY
void getTemperature() {
	//TODO: Get accelerometer reading
	data[millis() % TEMP_RANGE] = 0.0;
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

//Inputs the acceleration data into the given int[] in the form of
//[0] - X acceleration
//[1] - Y
//[2] - Z
void getAccelerationData(int[] data){
	//Probably can be done in a loop, but this is probably more readable
	char rgchReadAcclX[3] = {0};
	char rgchReadAcclX[3] = {0};
	char rgchReadAcclX[3] = {0};

	rgchReadAcclX[0] = X_ADDR;
	rgchReadAcclY[0] = Y_ADDR;
	rgchReadAcclZ[0] = Z_ADDR;

	I2CGenTransmit(rgchReadAcclX, 2, READ, ACCLADDR);
	I2CGenTransmit(rgchReadAcclY, 2, READ, ACCLADDR);
	I2CGenTransmit(rgchReadAcclZ, 2, READ, ACCLADDR);

	data[0] = (rgchReadAcclX[2] << 8) | rgchReadAccX[1];
	data[1] = (rgchReadAcclY[2] << 8) | rgchReadAcclY[1];
	data[2] = (rgchReadAcclZ[2] << 8) | rgchReadAcclZ[1];
}

//TODO: Put the in the setup code
void initAccelerometer(){
	GPIOPinTypeGPIOInput(ACCL_INT2Port, ACCL_INT2);
}

#endif // TRACK_H
