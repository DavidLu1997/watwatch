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
#include "date.h"
#include "socket.h"
#include "values.h"

#define UPDATE_DELAY 1

int lastMS = 0;
int lastMS1 = 0;
int lastMS2 = 0;

void setup()
{
	//Initialize all functions
	pinMode(RED_LED, OUTPUT);
	pinMode(GREEN_LED, OUTPUT);
	pinMode(BLUE_LED, OUTPUT);
  	initSocket();
  	initTrack();
  	initWatch();
  	lastMS = millis();
  lastMS1 = millis();
  lastMS2 = millis();
  randomSeed(analogRead(1));
  activeMenu = MAIN;
}

void loop() {
	drawActiveMenu();
	updateLoop();
	//digitalWrite(GREEN_LED, HIGH);
	delay(UPDATE_DELAY);
}

//Update Loop, continuously calls functions that must be updated
//Called every UPDATE_DELAY
void updateLoop() {
	if(millis() - lastMS2 >= ACCELER_DELAY){
	  getAccelerationData(millis() % STEP_RANGE);
          getTemperature();
          lastMS2 = millis();
      }
	if(millis() - lastMS >= STEP_DELAY) {
		checkStep();
                checkHeart();
                
		lastMS = millis();
	}
        if(millis() - lastMS1 >= BPM_DELAY) {
           getBPM();
          lastMS1 = millis(); 
        }
	//checkHeart();
	updateTime();
        updateTimer();
        checkAlarm();

	if(stopwatchRunning) {
		runStopWatch();
	}
}
