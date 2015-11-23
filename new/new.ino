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
char *menuArray;

void setup()
{
  // put your setup code here, to run once:
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);
  lBtn1 = GPIOPinRead(BTN1Port, BTN1);
  OrbitOledInit();
  OrbitOledClear();
}

void loop()
{
    if (checkStep()) steps++;
    Serial.println("STEPS: " + steps);
    //OrbitOledSetCursor(0, 0);
    //OrbitOledPutString(steps);
    //OritOledUpdate();
    //delay(50);

  long 	lBtn1;
  //Display, pause, then loop through menu options

  delay(1000);
  // put your main code here, to run repeatedly:
  OrbitOledSetCursor(6, 1.5);
  OrbitOledPutString("TIME");
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClear();

  if(lBtn1 == BTN1) {
    OrbitOledClear();
  }

  delay(1000);
  OrbitOledSetCursor(4, 1);
  OrbitOledPutString("STOPWATCH");
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClear();

  delay(1000);
  OrbitOledSetCursor(6, 1);
  OrbitOledPutString("ALARM");
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClear();

  delay(1000);
  OrbitOledSetCursor(6, 1);
  OrbitOledPutString("STEPS");
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClear();

  delay(1000);
  OrbitOledSetCursor(6, 1);
  OrbitOledPutString("TEMP");
  OrbitOledUpdate();
  delay(1000);
  OrbitOledClear();
}
