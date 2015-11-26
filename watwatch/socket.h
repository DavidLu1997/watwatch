#ifndef SOCKET_H
#define SOCKET_H

#include "track.h"
#include "watch.h"
#include "misc.h"

//Integer IDs for buttons
#define BUTTON_A 69
#define BUTTON_B 100

//Input delay = 50 ms
#define DELAY 50

//Integer IDs for switches
#define SWITCH_A 13
#define SWITCH_B 42

//Button variables
long btn1;
long btn2;

//Int variables for time
long hours = 19;
long minutes = 0;
long seconds = 0;

//Char variables for time
char stringSeconds[2];
char stringMinutes[2];
char stringHours[2];

//Integer ID for potentiometer
#define POT 420

//Potentiometer
int pot = 0;

//Current process, each process is assigned an ID above
int currentProcess = 0;

//Process IDs
#define TRACK 22
#define WATCH 68
#define MISC 15
#define IDLE 10

//Selected item
int selected = 0;

//Item IDs
#define TIME 1
#define STOPWATCH 2
#define ALARM 3
#define STEPS 4
#define TEMP 5
#define HEART 6
#define FITNESS 7

void trackInput(int input, int selected);
void watchInput(int input, int selected);
void miscInput(int input, int selected);

//Processes input given in the form of an action (int), and its size
void process(int input) {
	switch(currentProcess) {
		case TRACK:
			trackInput(input, selected);
			break;
		case WATCH:
			watchInput(input, selected);
			break;
		case MISC:
			miscInput(input, selected);
			break;
		case IDLE:
			//DO SOMETHING
			break;
		default:
			//SUM TING WONG
			//REALLY WONG
			//REALLY REALLY WONG
			break;
	}
}

//Draws the current menu item
void drawMenu() {
        hours = getDate().hour;
        minutes = getDate().minute;
        seconds = getDate().second;

        OrbitOledClear();
        //Convert ints to strings, then prints them to the screen
        itoa(hours, stringHours, 10);
        OrbitOledSetCursor(3, 2);
        OrbitOledPutString(stringHours);

        OrbitOledSetCursor(5, 2);
        OrbitOledPutString(":");

        //Prints minutes
        itoa(minutes, stringMinutes, 10);
        OrbitOledSetCursor(7, 2);
        OrbitOledPutString(stringMinutes);
        OrbitOledUpdate;

        OrbitOledSetCursor(9, 2);
        OrbitOledPutString(":");

        //Printes seconds
        itoa(seconds, stringSeconds, 10);
        OrbitOledSetCursor(11, 2);
        OrbitOledPutString(stringSeconds);
        OrbitOledUpdate;

        //Bottom button
        GPIOPinTypeGPIOInput(BTN1Port, BTN1);
        btn1 = GPIOPinRead(BTN1Port, BTN1);

        //Top Button
        GPIOPinTypeGPIOInput(BTN2Port, BTN2);
        btn2 = GPIOPinRead(BTN2Port, BTN2);

}

//Continuously scans for user input, passing it to process
//DELAY
void getInput() {
	int input = 0;
	//TODO: Get input
	if(!input)
		//SUM TING WONG
	process(input);
	sleep(DELAY);
}

//Highlights item n
void highlightItem(int n){

}


#endif //SOCKET_H
