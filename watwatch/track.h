//Track.h
//Used for tracking-related functions

#ifndef TRACK_H
#define TRACK_H

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
#include "Energia.h"

int get_accelerometer_internal(int address);


//Declarations
int getActiveMenu();
char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr);
bool I2CGenIsNotIdle();
void DeviceInit();
void initTrack();
void setSteps(int s);
void getAccelerationData(int count);
void drawTrack();
int getBPM();
void checkStep();
void checkHeart();
void getTemperature();
int getSteps();
double getDistance();
int getCalories();
void resetSteps();
void setSteps();
void drawSetSteps();
void drawSetHeartbeats();

const int chPwrCtlReg = 0x2D;
const int chX0Addr = 0x32;
const int chY0Addr = 0x34;
const int chZ0Addr = 0x36;

char rgchWriteAccl[3];

char 	rgchReadTemp[] = {
    0, 0, 0            };
  char 	rgchWriteTemp[] = {
    1, 0x20            };
  short tempReg;
  short	tempWhole;
  short	tempDec;
  int		i;
  char 	szTemp[6];


  int trackScreen = 0;

// Note, I have no idea how this works but don't touch it!
void setup_accelerometer() {
	/*
	* Enable I2C Peripheral
	*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
	
	/*
	* Set I2C GPIO pins
	*/
	GPIOPinTypeI2C(I2CSDAPort, I2CSDA_PIN);
	GPIOPinTypeI2CSCL(I2CSCLPort, I2CSCL_PIN);
	GPIOPinConfigure(I2CSCL);
	GPIOPinConfigure(I2CSDA);
	
	/*
	* Setup I2C
	*/
	I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
	
	/* Initialize the Accelerometer
	*
	*/
	GPIOPinTypeGPIOInput(ACCL_INT2Port, ACCL_INT2);
	
	rgchWriteAccl[0] = chPwrCtlReg;
	rgchWriteAccl[1] = 1 << 3;		// sets Accl in measurement mode
	I2CGenTransmit(rgchWriteAccl, 1, WRITE, ACCLADDR);
}

int get_accelerometer_x() {
	return get_accelerometer_internal(chX0Addr);
}

int get_accelerometer_y() {
	return get_accelerometer_internal(chY0Addr);
}

int get_accelerometer_z() {
	return get_accelerometer_internal(chZ0Addr);
}

int get_accelerometer_internal(int address) {
	char rgchReadAccl[3];
	rgchReadAccl[0] = address;
	I2CGenTransmit(rgchReadAccl, 2, READ, ACCLADDR);
	return (short) (rgchReadAccl[2] << 8) | rgchReadAccl[1];
}


//Initialization function
//Only called once
void initTrack() {
	int i;
	for(i = 0 ; i < HEART_RANGE / 1000; i++)
		heartBeats[i] = 0;
	for(i = 0; i < STEP_RANGE; i++)
		data[i] = 0;
	for(i = 0; i < TEMP_RANGE; i++)
		temp[i] = 0;

  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);

  setup_accelerometer();
  SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    GPIOPinTypeI2C(I2CSDAPort, I2CSDA_PIN);
    GPIOPinTypeI2CSCL(I2CSCLPort, I2CSCL_PIN);
    GPIOPinConfigure(I2CSCL);
    GPIOPinConfigure(I2CSDA);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    I2CGenTransmit(rgchWriteTemp, 1, WRITE, TEMPADDR);
	return;
}


void drawSetSteps(){
	//Initialization
	char *str;
	pot = analogRead(0);
	btn1 = GPIOPinRead(BTN1Port, BTN1);
	btn2 = GPIOPinRead(BTN2Port, BTN2);
	//Listen for changes in input
	if (btn1 == BTN1){
		steps = pot;
		activeMenu = SETTINGS;
	} else if (btn2 == BTN2){
		activeMenu = SETTINGS;
	}
	//Draws Steps
	sprintf("Steps:%d", str, pot);
	OrbitOledSetCursor(25, 10);
	OrbitOledPutString(str);
}

void drawSetHeartbeats(){
	//Initialization
	char *str;
	pot = analogRead(0);
	btn1 = GPIOPinRead(BTN1Port, BTN1);
	btn2 = GPIOPinRead(BTN2Port, BTN2);
	//Listen for changes in input
	if (btn1 == BTN1){
		beats = pot;
		activeMenu = SETTINGS;
	} else if (btn2 == BTN2){
		activeMenu = SETTINGS;
	} else{
		//Draws Steps
		sprintf("Heartbeat:%d", str, pot);
		OrbitOledSetCursor(25, 10);
		OrbitOledPutString(str);
	}
}


//Inputs the acceleration data into the given int[] in the form of
//[0] - X acceleration
//[1] - Y
//[2] - Z
//ACCEL_DELAY
void getAccelerationData(int count){
  
  data[count] = get_accelerometer_x() + get_accelerometer_y() + get_accelerometer_z();
}

//Draws current function, continuously called
//DRAW_DELAY
void drawTrack() {
	const int START_X = 0;
	const int START_Y = 1;

	//Strings for displaying to screen
	char *stepsStr, *bpmStr, *tempStrDigit, *tempStrDecimal, *distStr, *calStr;

  //Converting values to strings
	itoa(steps, stepsStr, 10);
	itoa(getBPM(), bpmStr, 10);
	itoa((int)temp[millis() % TEMP_RANGE], tempStrDigit, 10);
	itoa((int)(temp[millis() % TEMP_RANGE] * 100) % 100, tempStrDecimal, 10);
	itoa(getDistance(), distStr, 10);
	itoa(getCalories(), calStr, 10);

  if (trackScreen == 0) {
    //First screen of info

  	//Number of Steps
  	OrbitOledSetCursor(START_X, START_Y);
  	OrbitOledPutString("Steps:");
  	OrbitOledSetCursor(START_X + 5, START_Y);
  	OrbitOledPutString(stepsStr);
  	//Beats Per min
  	OrbitOledSetCursor(START_X + 9, START_Y);
  	OrbitOledPutString("BMP:");
  	OrbitOledSetCursor(START_X + 12, START_Y);
  	OrbitOledPutString(bpmStr);
  	//Temperature
  	OrbitOledSetCursor(START_X, START_Y + 2);
  	OrbitOledPutString("Temperature:");
  	OrbitOledSetCursor(START_X + 11, START_Y + 2);
  	OrbitOledPutString(tempStrDigit);
    OrbitOledSetCursor(START_X + 13, START_Y + 2);
    OrbitOledPutString(".");
  	OrbitOledSetCursor(START_X + 1, START_Y + 2);
  	OrbitOledPutString(tempStrDecimal);

  }
  else if (trackScreen == 1) {
  	//2nd screen of info

  	//Distance
  	OrbitOledSetCursor(START_X, START_Y + 100);
  	OrbitOledPutString("Distance:");
  	OrbitOledSetCursor(START_X + 75, START_Y + 100);
  	OrbitOledPutString(distStr);
  	//Calories
  	OrbitOledSetCursor(START_X + 100, START_Y + 100);
  	OrbitOledPutString("Calories:");
  	OrbitOledSetCursor(START_X + 150, START_Y + 100);
  	OrbitOledPutString(calStr);
  }

    //Bottom Button
    btn1 = GPIOPinRead(BTN1Port, BTN1);
        
    //Top Button
    btn2 = GPIOPinRead(BTN2Port, BTN2);

    //Switches
    swt1 = GPIOPinRead(SWT1Port, SWT1);
    swt2 = GPIOPinRead(SWT2Port, SWT2);

    //Goes to track screen
    if (btn1 == BTN1) {
        steps = 0;
    }
    if (btn2 == BTN2) {
        //Reset BPM
    }
    //Return to Main
    if (swt2 == SWT2) {
        activeMenu = MAIN; 
    }
    if (swt1 == SWT1) {
        trackScreen = 1;
    }
    else {
        trackScreen = 0;
    }


}

int getBPM(){
	return 60;
}

//Check step, continuously called, returns 1 if step occurred in past STEP_RANGE ms
void checkStep() {
	//Calculate average acceleration over STEP_RANGE
	int i;
	int avg = 0;
	for(i = 0; i < STEP_RANGE; i++) {
		avg += abs((int)data[i]);
    data[i] = 0;
	}
      //steps = avg;
	avg = avg / (double)STEP_RANGE;
//steps = avg;
        //totalAss += avg;

	//Greater than sensitivity
	if(avg >= STEP_SENSITIVITY) {
                //steps = -1;
		steps++;
	}
        //steps = (int)avg*1000;
        //steps = totalAss / 10000;
//steps++;
}

//Check temperature, continuously called, increments heartBeats if heartbeat occurred in past TEMP_RANGE ms
void checkHeart() {
  double avg = 0;
  int i = 0;
  for(i = 0; i < TEMP_RANGE; i++) {
     avg += temp[i];
  }
  avg /= TEMP_RANGE;
  double avgDiff = 0;
  for(i = 0; i < TEMP_RANGE; i++) {
     avgDiff += fabs(temp[i]-avg);
  }
  avgDiff /= (TEMP_RANGE / BEAT_FACTOR);

  if(avgDiff >= BEAT_SENSITIVITY) {
	heartBeats[millis() / 1000 % (HEART_RANGE / 1000)] += avgDiff / BEAT_SENSITIVITY;
  }
}

//Get temperature data, continuously called
void getTemperature() {
	

  rgchReadTemp[0] = 0;
  I2CGenTransmit(rgchReadTemp, 2, READ, TEMPADDR);

  tempReg = (rgchReadTemp[1] << 8) | rgchReadTemp[2];

  tempWhole = 0;
  tempDec = 0;

  for(i = 0; i < 7; i++) {
    if(tempReg & (1 << (8 + i))) {
      tempWhole += pow(2,i);
    }
  }

  if(tempReg & (1 << 7) ) {
    tempDec += 50;
  }
  if(tempReg & (1 << 6) ) {
    tempDec += 25;
  }
	temp[millis() % TEMP_RANGE] = tempWhole + tempDec / 100.0;
}

//Get current steps
int getSteps() {
	return steps;
}

//Get current distance travelled in m
double getDistance() {
	return steps * STEP_DISTANCE;
}

//Get calories burnt
int getCalories() {
	double kmh = (getDistance() / 1000.0) / (millis() / 1000.0) * 3600;
	//Formula obtained from ShapeSense.com
	return (0.0215 * pow(kmh, 3) - 0.1765 * pow(kmh, 2) + 0.8710 * kmh + 1.8600) * WEIGHT * (millis() / 1000 * 3600);
}

//Reset steps
void resetSteps() {
	steps = 0;
}

//Set steps
void setSteps(int s) {
	steps = s;
}

char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr) {

  int 		i;
  char * 		pbTemp;

  pbTemp = pbData;

  /*Start*/

  /*Send Address High Byte*/
  /* Send Write Block Cmd*/
  I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, WRITE);
  I2CMasterDataPut(I2C0_BASE, *pbTemp);

  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

  DelayMs(1);

  /* Idle wait*/
  while(I2CGenIsNotIdle());

  /* Increment data pointer*/
  pbTemp++;

  /*Execute Read or Write*/

  if(fRW == READ) {

    /* Resend Start condition
	** Then send new control byte
	** then begin reading
	*/
    I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, READ);

    while(I2CMasterBusy(I2C0_BASE));

    /* Begin Reading*/
    for(i = 0; i < cSize; i++) {

      if(cSize == i + 1 && cSize == 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);

        DelayMs(1);

        while(I2CMasterBusy(I2C0_BASE));
      }
      else if(cSize == i + 1 && cSize > 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

        DelayMs(1);

        while(I2CMasterBusy(I2C0_BASE));
      }
      else if(i == 0) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);

        DelayMs(1);

        while(I2CMasterBusy(I2C0_BASE));

        /* Idle wait*/
        while(I2CGenIsNotIdle());
      }
      else {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);

        DelayMs(1);

        while(I2CMasterBusy(I2C0_BASE));

        /* Idle wait */
        while(I2CGenIsNotIdle());
      }

      while(I2CMasterBusy(I2C0_BASE));

      /* Read Data */
      *pbTemp = (char)I2CMasterDataGet(I2C0_BASE);

      pbTemp++;

    }

  }
  else if(fRW == WRITE) {

    /*Loop data bytes */
    for(i = 0; i < cSize; i++) {
      /* Send Data */
      I2CMasterDataPut(I2C0_BASE, *pbTemp);

      while(I2CMasterBusy(I2C0_BASE));

      if(i == cSize - 1) {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

        DelayMs(1);

        while(I2CMasterBusy(I2C0_BASE));
      }
      else {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);

        DelayMs(1);

        while(I2CMasterBusy(I2C0_BASE));

        /* Idle wait */
        while(I2CGenIsNotIdle());
      }

      pbTemp++;
    }

  }

  /*Stop*/

  return 0x00;

}

bool I2CGenIsNotIdle() {

  return !I2CMasterBusBusy(I2C0_BASE);

}


#endif // TRACK_H
