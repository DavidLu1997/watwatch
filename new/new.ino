    
      extern "C" {
      //#include "track.h"
      #include <delay.h>
      #include <FillPat.h>
      #include <I2CEEPROM.h>
      #include <LaunchPad.h>
      #include <OrbitBoosterPackDefs.h>
      #include <OrbitOled.h>
      #include <OrbitOledChar.h>
      #include <OrbitOledGrph.h>
      #include <stdlib.h>
      #include <stdbool.h>
      }
      
      //Variables
      int option = 0;
      int screen = 0;
      long lBtn2;
      long lBtn1;
      long hours = 19;
      long minutes = 0;
      long seconds = 0;
      long milliseconds;
      char stringSeconds[2];
      char stringMinutes[2];
      char stringHours[2];
      
      char stringValue[3];
      int value;
      int extraValue = 81;
      bool increasing = true;
      
      
      //Switch variables
      long swt2;
      
      int pot = 0;
      
      void setup()
      {
        Serial.begin(9600);
        pinMode(RED_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
        pinMode(BLUE_LED, OUTPUT);
        // put your setup code here, to run once:
        OrbitOledInit();
        OrbitOledClear();
      }
      
      void loop()
      {
        //Bottom button
        GPIOPinTypeGPIOInput(BTN1Port, BTN1);
        lBtn1 = GPIOPinRead(BTN1Port, BTN1);
        
        //Top Button
        GPIOPinTypeGPIOInput(BTN2Port, BTN2);
        lBtn2 = GPIOPinRead(BTN2Port, BTN2);
        
          
        GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);
        swt2 = GPIOPinRead(SWT2Port, SWT2);
        if (swt2 == SWT2) {
          digitalWrite(RED_LED, HIGH);
          increasing = true;
        }
        else {
          digitalWrite(RED_LED, LOW);
          increasing = false;
        }
        OrbitOledClear();

        
        pot = analogRead(A0);
        pot /= 50;
        if (increasing) {
          value +=pot;
        }
        else
          value -= pot;
        
        //Displaying steps number
        itoa(pot, stringValue, 10);
        OrbitOledSetCursor(5, 1);
        OrbitOledPutString(stringValue);
        
        /* //Read potentiometer value
        pot = analogRead(A0);
        pot = pot / 4;
        analogWrite(BLUE_LED, pot);
        
        if (screen == 0) {
          screen = 0;
        //Display menu option based on current value of i, which is adjusted when button is clicked
          if (option == 0) {
            OrbitOledSetCursor(6, 1.5);
            OrbitOledPutString("TIME");
            OrbitOledUpdate();
          }
          else if (option==1) {
            OrbitOledSetCursor(4, 1);
            OrbitOledPutString("STOPWATCH");
            OrbitOledUpdate();          
          }
          else if (option==2) {
            OrbitOledSetCursor(5, 1);
            OrbitOledPutString("ALARM");
            OrbitOledUpdate();          
          }
          else if (option==3) {
             OrbitOledSetCursor(6, 1);
             OrbitOledPutString("STEPS");
             OrbitOledUpdate();           
          }
          else if (option==4) {
             OrbitOledSetCursor(2, 1);
             OrbitOledPutString("TEMPERATURE");
             OrbitOledUpdate();
          }
        
          //Making a selection
          if (lBtn1 == BTN1) {
            digitalWrite(RED_LED, HIGH);
            //TIME
            if (option == 0) {
                //Screen 1 displays time
                screen = 1;  
            }
            //STOPWATCH
            else if (option == 1) {
              screen = 2;
            }
            //ALARM
            else if (option == 2) {
            
            }
            //STEPS
            else if (option == 3) {
            
            }
            //TEMP
            else if (option == 4) {
            
            }
            //Should not exceed list of options
              delay(500);
              digitalWrite(RED_LED, LOW);
            
          }
        
          //Cycle through menu options
          if (lBtn2 == BTN2) {
            digitalWrite(GREEN_LED, HIGH);
            //Increase i when button is clicked
            if (option < 4) {
               option++;
               OrbitOledClear();
               delay(300);
            }
            //Reset to 0 so that it'll loop through the options
            else if (option == 4) {
               option = 0;
               OrbitOledClear();
               delay(300);
            }
            digitalWrite(GREEN_LED, LOW);
            }
        
        
          delay(200);
          OrbitOledClear();
        }
        else if (screen == 1) {
            OrbitOledClear();
            milliseconds = millis();
            seconds = milliseconds/1000;
            minutes = seconds/60;
            seconds = seconds % 60;
            hours = minutes/60;
            minutes = minutes % 60;
            
            //Convert ints to strings, then prints them to the screen
            itoa(hours, stringHours, 10); 
            OrbitOledSetCursor(3, 2);
            OrbitOledPutString(stringHours);
            
            OrbitOledSetCursor(5, 2);
            OrbitOledPutString(":");
            
            //Prints minutes
            itoa(minutes, stringMinutes, 10);
            OrbitOledSetCursor(7, 2);
            OrbitOledPutString(stringMinutes);
            OrbitOledUpdate;
            
            OrbitOledSetCursor(9, 2);
            OrbitOledPutString(":");
            
            //Printes seconds
            itoa(seconds, stringSeconds, 10);
            OrbitOledSetCursor(11, 2);
            OrbitOledPutString(stringSeconds);
            OrbitOledUpdate;
            
            //Making a selection
            if (lBtn1 == BTN1) {
              screen = 0;
              option = 0;
              delay(100);
              OrbitOledClear();
            }
        }
        else if (screen == 2) {
          OrbitOledClear();
          milliseconds = millis();
          //Convert ints to strings, then prints them to the screen
            itoa(hours, stringHours, 10); 
            OrbitOledSetCursor(3, 2);
            OrbitOledPutString("0");
            
            OrbitOledSetCursor(5, 2);
            OrbitOledPutString(":");
            
            //Prints minutes
            itoa(minutes, stringMinutes, 10);
            OrbitOledSetCursor(7, 2);
            OrbitOledPutString("0");
            OrbitOledUpdate;
            
            OrbitOledSetCursor(9, 2);
            OrbitOledPutString(":");
            
            //Printes seconds
            itoa(seconds, stringSeconds, 10);
            OrbitOledSetCursor(11, 2);
            OrbitOledPutString("0");
            OrbitOledUpdate;
            
            //Making a selection
            if (lBtn1 == BTN1) {
              screen = 0;
              option = 1;
              delay(100);
              OrbitOledClear();
            }
        }*/
      
        
        
        /* /Leave for Stopwatch effect
        OrbitOledClear();
        delay(10);*/
        
      }

