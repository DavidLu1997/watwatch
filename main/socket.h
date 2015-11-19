#ifndef SOCKET_H
#define SOCKET_H

#include "track.h"
#include "watch.h"
#include "misc.h"

//Input delay = 50 ms
#define DELAY 50

//Integer IDs for switches
#define SWITCH_A 13
#define SWITCH_B 42

//Integer IDs for buttons
#define BUTTON_A 69
#define BUTTON_B 100

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

}

//Continuously scans for user input, passing it to process
void getInput() {
	int input = 0;
	//TODO: Get input
	if(!input)
		//SUM TING WONG
	process(input);
	sleep(
}

//Highlights item n
void highlightItem(int n){

}

//

#endif //SOCKET_H