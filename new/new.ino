extern "C" {
    #include <delay.h>
    #include <FillPat.h>
    #include <I2CEEPROM.h>
    #include <LaunchPad.h>
    #include <OrbitBoosterPackDefs.h>
    #include <OrbitOled.h>
    #include <OrbitOledChar.h>
    #include <OrbitOledGrph.h>
    #include <track.h>
}

int steps = 0;

void setup(){

  char *menuArray;

  // put your setup code here, to run once:
  OrbitOledInit();
  OrbitOledClear();
}

void loop()
{
    if (checkStep()) steps++;
    // put your main code here, to run repeatedly:
    OrbitOledSetCursor(0, 0);
    OrbitOledPutString(steps);
    OritOledUpdate();
    delay(50);
}
