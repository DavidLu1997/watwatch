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

#include "watch.h"
#include "track.h"
#include "misc.h"
#include "socket.h"

#define UPDATE_DELAY 1

void setup()
{
	//Initialize all functions
	pinMode(RED_LED, OUTPUT);
  	initSocket();
  	initTrack();
  	initWatch();
}

void loop() {
	drawMenu();
	updateLoop();
	delay(1);
}

void drawActiveMenu() {
	
}

//Update Loop, continuously calls functions that must be updated
//Called every UPDATE_DELAY
void updateLoop() {
	getAccelerationData();
	getTemperature();
	checkStep();
	checkHeart();
	updateTime();

	if(stopwatchRunning) {
		runStopWatch();
	}
}
