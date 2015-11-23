
  extern "C" {
  #include "track.h"
  #include <delay.h>
  #include <FillPat.h>
  #include <I2CEEPROM.h>
  #include <LaunchPad.h>
  #include <OrbitBoosterPackDefs.h>
  #include <OrbitOled.h>
  #include <OrbitOledChar.h>
  #include <OrbitOledGrph.h>
  }
  
  //Variables
  int i = 0;
  long 	lBtn2;
  long lBtn1;
  
  
  void setup()
  {
    
    // put your setup code here, to run once:
    
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
    
    //Bottom button
    GPIOPinTypeGPIOInput(BTN1Port, BTN1);
    lBtn1 = GPIOPinRead(BTN1Port, BTN1);
    
    //Top Button
    GPIOPinTypeGPIOInput(BTN2Port, BTN2);
    lBtn2 = GPIOPinRead(BTN2Port, BTN2);
    
    //Display menu option based on current value of i, which is adjusted when button is clicked
    if (i == 0) {
      OrbitOledSetCursor(6, 1.5);
      OrbitOledPutString("TIME");
      OrbitOledUpdate();
    }
    else if (i==1) {
        OrbitOledSetCursor(4, 1);
        OrbitOledPutString("STOPWATCH");
        OrbitOledUpdate();
    }
    else if (i==2) {
        OrbitOledSetCursor(5, 1);
        OrbitOledPutString("ALARM");
        OrbitOledUpdate();
    }
    else if (i==3) {
         OrbitOledSetCursor(6, 1);
         OrbitOledPutString("STEPS");
         OrbitOledUpdate();
    }
    else if (i==4) {
       OrbitOledSetCursor(6, 1);
       OrbitOledPutString("TEMP");
       OrbitOledUpdate();
    }
    
    
    if(lBtn2 == BTN2) {
      //Increase i when button is clicked
      if (i < 4) {
         i++;
         OrbitOledClear();
         delay(200);
      }
      //Reset to 0 so that it'll loop through the options
      else if (i == 4) {
        i = 0;
        OrbitOledClear();
        delay(200);
      }
    }
  }

