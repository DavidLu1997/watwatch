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

//#define MENU_DELAY 500;

void setup()
{
	pinMode(RED_LED, OUTPUT);
	Serial.begin(9600);
  	Serial.println("Timer");
  	OrbitOledInit();
  	
}

void loop()
{
	//Serial.println(millis());
	//getAccelerationData();
	//Serial.println(data[millis() % STEP_RANGE]);
	drawMenu();
	delay(100);
}

