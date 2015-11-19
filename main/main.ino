extern "C" {
#include <delay.h>
#include <FillPat.h>
#include <I2CEEPROM.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include "watch.h"
#include "track.h"
#include "misc.h"
}

void setup()
{
	Serial.begin(9600);
  	Serial.println("Timer");
}

void loop()
{
	Serial.println(millis());
	sleep(50);
}
