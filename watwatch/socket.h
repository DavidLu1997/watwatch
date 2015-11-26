#ifndef SOCKET_H
#define SOCKET_H

#include "track.h"
#include "watch.h"
#include "misc.h"
#include "values.h"

//Variables for displaying steps
int step;
char stringSteps[5];

//Declarations
void initSocket();
void drawMenu();
void drawActiveMenu();

//Draws currently active menu
void drawActiveMenu() {
	if(millis() % MENU_DELAY == 0) {
		switch(activeMenu) {
			case MAIN:
                OrbitOledClear;
				drawMenu();
				break;
			case TRACK:
                digitalWrite(RED_LED, HIGH);
                OrbitOledClear;
				drawTrack();
				break;
			case WATCH:
				drawWatch();
				break;
			case TIMER:
				drawTimer();
				break;
			case ALARM:
				drawAlarm();
				break;
			case STOPWATCH:
				drawStopWatch();
				break;
			case SETTINGS:
				drawSettings();
				break;
			case SETTIME:
				drawSetTimes();
				break;
			case SETSTEPS:
				drawSetSteps();
				break;
			case SETHEARTBEATS:
				drawSetHeartbeats();
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
}

//Initializes socket functions
void initSocket() {
	OrbitOledInit();
	OrbitOledClear();
}

//Draws the current menu item
void drawMenu() {

	//Draws menu every MENU_DELAY
        OrbitOledClear();

        step = getSteps();

        //Displaying steps text
        OrbitOledSetCursor(4 , 1);
        OrbitOledPutString("Steps: ");

        //Displaying steps number
        itoa(step, stringSteps, 10);
        OrbitOledSetCursor(11, 1);
        OrbitOledPutString(stringSteps);

        hours = current.hour;
        minutes = current.minute;
        seconds = current.second;

        //Convert ints to strings, then prints them to the screen
        itoa(hours, stringHours, 10);
        OrbitOledSetCursor(3, 3);
        OrbitOledPutString(stringHours);

        OrbitOledSetCursor(5, 3);
        OrbitOledPutString(":");

        //Prints minutes
        itoa(minutes, stringMinutes, 10);
        OrbitOledSetCursor(7, 3);
        OrbitOledPutString(stringMinutes);

        OrbitOledSetCursor(9, 3);
        OrbitOledPutString(":");

        //Printes seconds
        itoa(seconds, stringSeconds, 10);
        OrbitOledSetCursor(11, 3);
        OrbitOledPutString(stringSeconds);
        OrbitOledUpdate;

    //Bottom button
    GPIOPinTypeGPIOInput(BTN1Port, BTN1);
    btn1 = GPIOPinRead(BTN1Port, BTN1);

    //Top Button
    GPIOPinTypeGPIOInput(BTN2Port, BTN2);
    btn2 = GPIOPinRead(BTN2Port, BTN2);

    //Right Switch
    GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
    swt1 = GPIOPinRead(SWT1Port, SWT1);

    //Goes to track screen
    if (btn1 == BTN1) {
        activeMenu = TRACK;
    }
    //Goes to watch screen
    if (btn2 == BTN2) {
        activeMenu = WATCH;
    }
    //Turn light on when switch is flipped, should actually go to settings during implmentation
    if (swt1 == SWT1) {
        activeMenu = SETTINGS;
    }
    else {
        activeMenu = MAIN;
    }
}


#endif //SOCKET_H
