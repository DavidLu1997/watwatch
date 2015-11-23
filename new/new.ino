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


void setup()
{
  
  // put your setup code here, to run once:
  OrbitOledInit();
  OrbitOledClear();
}

void loop()
{
  // put your main code here, to run repeatedly:
  OrbitOledSetCursor(4, 2);
  OrbitOledPutString("TIME");
  OrbitOledUpdate();
  OrbitOledClear();
  
  delay(1000);
  OrbitOledSetCursor(4, 2);
  OrbitOledPutString("STOPWATCH");
  OrbitOledUpdate();
  OrbitOledClear();
  
  delay(1000);
  OrbitOledSetCursor(4, 2);
  OrbitOledPutString("ALARM");
  OrbitOledUpdate();
  OrbitOledClear();
  
  delay(1000);
  OrbitOledSetCursor(4, 2);
  OrbitOledPutString("STEPS");
  OrbitOledUpdate();
  OrbitOledClear();
  
  delay(1000);
  OrbitOledSetCursor(4, 2);
  OrbitOledPutString("TEMP");
  OrbitOledUpdate();
  OrbitOledClear();
}
