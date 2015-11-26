#ifndef SOCKET_H
#define SOCKET_H

#include "track.h"
#include "watch.h"
#include "misc.h"
#include "values.h"

//Variables for displaying steps
int step;
char stringSteps[5];
int set = 0;

//Declarations
void initSocket();
void drawMenu();
void drawActiveMenu();

//LastMS
int last = 0;

//Draws currently active menu
void drawActiveMenu() {

	if(millis() - last >= MENU_DELAY) {
        last = millis();
        OrbitOledClear();
		switch(activeMenu) {
			case MAIN:
				drawMenu();
				break;
			case TRACK:
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
				//drawSettings();
				break;
			case SETTIME:
				//drawSetTimes();
				break;
			case SETSTEPS:
				//drawSetSteps();
				break;
			case SETHEARTBEATS:
				//drawSetHeartbeats();
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

    switch(activeMenu) {
            case MAIN:
                
                //Bottom button
                btn1 = GPIOPinRead(BTN1Port, BTN1);
                //Top Button
                btn2 = GPIOPinRead(BTN2Port, BTN2);

                //Right Switch
                swt1 = GPIOPinRead(SWT1Port, SWT1);

                //Goes to track screen
                if (btn1 == BTN1) {
                    //OrbitOledClear();
                    setActiveMenu(TRACK);
                    break;
                }
                //Goes to watch screen
                if (btn2 == BTN2) {
                    //OrbitOledClear();
                    setActiveMenu(WATCH);
                    set=1;
                    break;
                }
                //Turn light on when switch is flipped, should actually go to settings during implmentation
                if (swt1 == SWT1) {
                    //OrbitOledClear();
                    //setActiveMenu(SETTINGS);
                }
                else {
                    setActiveMenu(MAIN);
                }
                break;
            case TRACK:
                //Bottom Button
                    btn1 = GPIOPinRead(BTN1Port, BTN1);
                        
                    //Top Button
                    btn2 = GPIOPinRead(BTN2Port, BTN2);

                    //Switches
                    swt1 = GPIOPinRead(SWT1Port, SWT1);
                    swt2 = GPIOPinRead(SWT2Port, SWT2);

                    //Resets steps
                    if (btn1 == BTN1) {
                        steps = 0;
                        break;
                    }
                    //Return to Main
                    if (swt2 == SWT2) {
                        setActiveMenu(MAIN); 
                        break;
                    }
                    if (swt1 == SWT1) {
                        trackScreen = 1;
                    }
                    else {
                      //OrbitOledClear();
                        trackScreen = 0;
                    }
                break;
            case WATCH:
                //Bottom button
    
                btn1 = GPIOPinRead(BTN1Port, BTN1);

                //Top Button
                
                btn2 = GPIOPinRead(BTN2Port, BTN2);

                //Switches
                
                swt1 = GPIOPinRead(SWT1Port, SWT1);
                swt2 = GPIOPinRead(SWT2Port, SWT2);

                //Goes to timer screen
                if (btn1 == BTN1) {
                    setActiveMenu(TIMER);
                    break;
                }
                //Goes to alarm screen
                if (btn2 == BTN2) {
                    setActiveMenu(ALARM);
                    break;
                }
                //Switch to stopwatch submenu
                if (swt1 == SWT1) {
                    setActiveMenu(STOPWATCH);
                    break;
                }
                if (swt2 == SWT2) {
                    setActiveMenu(MAIN);
                    break;
                }
                break;
            case TIMER:

            //Bottom button
                btn1 = GPIOPinRead(BTN1Port, BTN1);

                //Top Button
                btn2 = GPIOPinRead(BTN2Port, BTN2);

                //Switches
                swt1 = GPIOPinRead(SWT1Port, SWT1);
                swt2 = GPIOPinRead(SWT2Port, SWT2);


               //Change type of input when button is pressed, and will loop
               if (btn1==BTN1) {
                     switchOption();
                     drawTimer();
               }

               if(btn2==BTN2) {
                    switch(option) {
                        case 0:
                            timeValue *= 1000;
                            break;
                        case 1:
                            timeValue *= 60000;
                            break;
                        case 2:
                            timeValue *= 3600000;
                            break;
                    }
                    timer(timeValue);
               }
               //Return to main
               if (swt2 == SWT2) {
                    setActiveMenu(MAIN);
               }
                break;
            case ALARM:
                break;
            case STOPWATCH:
                break;
            case SETTINGS:
                break;
            case SETTIME:
                break;
            case SETSTEPS:
                break;
            case SETHEARTBEATS:
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

//Initializes socket functions
void initSocket() {
    GPIOPinTypeGPIOInput(BTN1Port, BTN1);
    GPIOPinTypeGPIOInput(BTN2Port, BTN2);
    GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
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
}


#endif //SOCKET_H
