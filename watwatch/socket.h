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

//Variables for displaying steps
int step;
char stringSteps[5];

//Button variables
long btn1;
long btn2;

//Switch variables
long swt1;

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

//Declarations
void initSocket();
void drawMenu();


//Initializes socket functions
void initSocket() {
	OrbitOledInit();
	OrbitOledClear();
}

//Draws the current menu item
void drawMenu() {

        //OrbitOledClear();

        step = getSteps();

        //Displaying steps text
        OrbitOledSetCursor(4 , 1);
        OrbitOledPutString("Steps: ");

        //Displaying steps number
        itoa(step, stringSteps, 10);
        OrbitOledSetCursor(11, 1);
        OrbitOledPutString(stringSteps);

        hours = getDate().hour;
        minutes = getDate().minute;
        seconds = getDate().second;
        
        OrbitOledClear();

        //Convert ints to strings, then prints them to the screen
        itoa(hours, stringHours, 10); 
        OrbitOledSetCursor(3, 3);
        OrbitOledPutString(stringHours);
        
        OrbitOledSetCursor(5, 3);
        OrbitOledPutString(":");


        //Convert ints to strings, then prints them to the screen
        itoa(hours, stringHours, 10); 
        OrbitOledSetCursor(3, 2);
        OrbitOledPutString(stringHours);
        

        OrbitOledSetCursor(5, 2);
        OrbitOledPutString(":");
        


        //Prints minutes
        itoa(minutes, stringMinutes, 10);
        OrbitOledSetCursor(7, 3);
        OrbitOledPutString(stringMinutes);

        OrbitOledUpdate;
        
        OrbitOledSetCursor(9, 2);

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

        GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
        swt1 = GPIOPinRead(SWT1Port, SWT1);

        //Goes to track screen
        if (btn1 == BTN1) {

        }
        //Goes to time screen
        if (btn2 == BTN2) {

        }


}


#endif //SOCKET_H

