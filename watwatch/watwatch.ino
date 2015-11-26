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
	pinMode(RED_LED, OUTPUT);
	Serial.begin(9600);
  	Serial.println("Timer");
  	OrbitOledInit();
  	
}

void loop() {
	//Serial.println(millis());
	//getAccelerationData();
	//Serial.println(data[millis() % STEP_RANGE]);
	drawMenu();
	updateLoop();
	delay(1);
}

//Update Loop, continuously calls functions that must be updated
//Called every UPDATE_DELAY
void updateLoop() {
	getAccelerationData();
	getTemperature();
	checkStep();
	checkHeart();
	updateTime();
}
