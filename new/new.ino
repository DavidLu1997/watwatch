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
  
  char *menuArray;
  
  // put your setup code here, to run once:
  OrbitOledInit();
  OrbitOledClear();
}

void loop()
{
  // put your main code here, to run repeatedly:
  OrbitOledSetCursor(0, 0);
  OrbitOledPutString("SUM TING PUSH");
  OrbitOledSetCursor(0, 2);
  OrbitOledPutString("RILEY WONG");
  OrbitOledUpdate();
  
}
