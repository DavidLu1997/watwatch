//Track.h
//Used for tracking-related functions

#ifndef TRACK_H
#define TRACK_H

extern "C" {
	#include <delay.h>
	#include <FillPat.h>
	#include <I2CEEPROM.h>
	#include <LaunchPad.h>
	#include <OrbitBoosterPackDefs.h>
	#include <OrbitOled.h>
	#include <OrbitOledChar.h>
	#include <OrbitOledGrph.h>
}
#include "Energia.h"

//Declarations
int getActiveMenu();
char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr);
bool I2CGenIsNotIdle();
int get_accelerometer_internal(int address);
void DeviceInit();
void initTrack();
void setSteps(int s);
void getAccelerationData(int count);
void drawTrack();
int getBPM();
void checkStep();
void checkHeart();
void getTemperature();
int getSteps();
double getDistance();
double getCalories();
void resetSteps();
void setSteps();
void drawSetSteps();
void drawSetHeartbeats();
int getSpeed();

const int chPwrCtlReg = 0x2D;
const int chX0Addr = 0x32;
const int chY0Addr = 0x34;
const int chZ0Addr = 0x36;

char rgchWriteAccl[3];
char rgchReadTemp[] = {0, 0, 0};
char rgchWriteTemp[] = {1, 0x20};
short tempReg;
short tempWhole;
short tempDec;
int i;
char szTemp[6];
int trackScreen = 0;
int speed;
char speedString[3];

#endif // TRACK_H
