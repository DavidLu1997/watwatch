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

//Function calling delays, ms
#define DRAW_DELAY 50

//Past range to check steps, ms
#define STEP_RANGE 500

//Past range to check temperature
#define TEMP_RANGE 500

//Past Range to store heartbeat data
#define HEART_RANGE 60000 //1 minute

//Acceleration data memory locations
#define	X_ADDR 0x32
#define	Y_ADDR 0x34
#define	Z_ADDR 0x36

//Step Tracking Params
#define STEP_SENSITIVITY 1.0 //Higher the number = less sensitive
#define STEP_DISTANCE 0.7874 //Distance travelled per step in m
#define WEIGHT 70 //Weight of user in kg

//Heart Rate Params
#define BEAT_SENSITIVITY 0.25
#define BEAT_FACTOR 10

//Number of steps since start
int steps = 0;

//Number of heartbeats since start
int beats = 0;

//Heartbeat
int heartBeats[HEART_RANGE / 1000];

//Accelerometer data for past STEP_RANGE
double data[STEP_RANGE];

//Temperature data for past TEMP_RANGE
double temp[TEMP_RANGE];

//Required variables
bool	fClearOled;
char  chSwtCur;
char  chSwtPrev;

//Declarations
char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr);
bool I2CGenIsNotIdle();
void DeviceInit();
void initTrack();
void setSteps(int s);
void getAccelerationData();
void drawTrack(); 
int getBPM();
int checkStep();
void checkHeart();
void getTemperature(); 
int getSteps();
double getDistance(); 
int getCalories();
void resetSteps();
void setSteps();
void drawSetSteps();
void drawSetHeartbeats();

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

  DeviceInit();
	return;
}

//Draws current function, continuously called
//DRAW_DELAY
void drawTrack() {
	const int START_X = 1;
	const int START_Y = 2;

	const int Y_OFFSET = 3;
	//------------LINE 1-------------
	//Number of Steps
	OrbitOledSetCursor(START_X, START_Y);
	OrbitOledPutString("Steps:" + steps);
	//Beats Per min
	OrbitOledSetCursor(START_X + 50, START_Y);
	OrbitOledPutString("BMP:" + getBPM());
	//Temperature
	OrbitOledSetCursor(START_X + 100, START_Y);
	OrbitOledPutString("Temperature:" + getTemperature());
	//--------------LINE 2-----------
	//Distance
	OrbitOledSetCursor(START_X, START_Y + 100);
	OrbitOledPutString("Distance:" + getDistance());
	//Calories
	OrbitOledSetCursor(START_X + 100, START_Y + 100);
	OrbitOledPutString("Calories:" + getCalories());
}

//Draw setSteps
void drawSetSteps() {

}

//Draw setHeartbeats
void drawSetHeartbeats() {

}


//Inputs the acceleration data into the given int[] in the form of
//[0] - X acceleration
//[1] - Y
//[2] - Z
//ACCEL_DELAY
void getAccelerationData(){
  short  dataX, dataY, dataZ;

  char  chPwrCtlReg = 0x2D;
  char  chX0Addr = 0x32;
  char  chY0Addr = 0x34;
  char  chZ0Addr = 0x36;

  char  rgchReadAcclX[] = {
    0, 0, 0            };
  char  rgchWriteAcclX[] = {
    0, 0            };
  char  rgchReadAcclY[] = {
    0, 0, 0            };
  char  rgchWriteAcclY[] = {
    0, 0            };
  char  rgchReadAcclZ[] = {
    0, 0, 0            };
  char  rgchWriteAcclZ[] = {
    0, 0            };

  if(fClearOled == true) {
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
    fClearOled = false;

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

    rgchWriteAcclX[0] = chPwrCtlReg;
    rgchWriteAcclX[1] = 1 << 3;    // sets Accl in measurement mode
    I2CGenTransmit(rgchWriteAcclX, 1, WRITE, ACCLADDR);

    rgchWriteAcclY[0] = chPwrCtlReg;
    rgchWriteAcclY[1] = 1 << 3;    // sets Accl in measurement mode
    I2CGenTransmit(rgchWriteAcclY, 1, WRITE, ACCLADDR);

    rgchWriteAcclZ[0] = chPwrCtlReg;
    rgchWriteAcclZ[1] = 1 << 3;    // sets Accl in measurement mode
    I2CGenTransmit(rgchWriteAcclZ, 1, WRITE, ACCLADDR);

  }

  rgchReadAcclX[0] = chX0Addr;
    I2CGenTransmit(rgchReadAcclX, 2, READ, ACCLADDR);

    dataX = (rgchReadAcclX[2] << 8) | rgchReadAcclX[1];

  rgchReadAcclY[0] = chY0Addr;
    I2CGenTransmit(rgchReadAcclY, 2, READ, ACCLADDR);

    dataX = (rgchReadAcclY[2] << 8) | rgchReadAcclY[1];

  rgchReadAcclZ[0] = chZ0Addr;
    I2CGenTransmit(rgchReadAcclZ, 2, READ, ACCLADDR);

    dataX = (rgchReadAcclZ[2] << 8) | rgchReadAcclZ[1];

  //Store magnitude of acceleration in data
  data[millis() % STEP_RANGE] = sqrt(dataX * dataX + dataY * dataY + dataZ * dataZ);
}


int getBPM(){
	return 60;
}

//Check step, continuously called, returns 1 if step occurred in past STEP_RANGE ms
int checkStep() {
	getAccelerationData();
	//Calculate average acceleration over STEP_RANGE
	int i;
	double avg = 0;
	for(i = 0; i < STEP_RANGE; i++) {
		avg += data[i];
	}
	avg = avg / STEP_RANGE;

	//Greater than sensitivity
	if(avg >= STEP_SENSITIVITY) {
		return 1;
	}

	return 0;
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
	char 	rgchReadTemp[] = {
    0, 0, 0            };
  char 	rgchWriteTemp[] = {
    1, 0x20            };
  short tempReg;
  short	tempWhole;
  short	tempDec;
  int		i;
  char 	szTemp[6];

  if(fClearOled == true) {
    OrbitOledClear();
    OrbitOledMoveTo(0,0);
    OrbitOledSetCursor(0,0);
    fClearOled = false;

    OrbitOledSetCursor(0, 0);
    OrbitOledPutString("ShitTemp: ");

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    GPIOPinTypeI2C(I2CSDAPort, I2CSDA_PIN);
    GPIOPinTypeI2CSCL(I2CSCLPort, I2CSCL_PIN);
    GPIOPinConfigure(I2CSCL);
    GPIOPinConfigure(I2CSDA);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    I2CGenTransmit(rgchWriteTemp, 1, WRITE, TEMPADDR);
  }

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

void DeviceInit()
{
  /*
   * First, Set Up the Clock.
   * Main OSC     -> SYSCTL_OSC_MAIN
   * Runs off 16MHz clock -> SYSCTL_XTAL_16MHZ
   * Use PLL      -> SYSCTL_USE_PLL
   * Divide by 4    -> SYSCTL_SYSDIV_4
   */
  SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_SYSDIV_4);

  /*
   * Enable and Power On All GPIO Ports
   */
  //SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA | SYSCTL_PERIPH_GPIOB | SYSCTL_PERIPH_GPIOC |
  //            SYSCTL_PERIPH_GPIOD | SYSCTL_PERIPH_GPIOE | SYSCTL_PERIPH_GPIOF);

  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE );
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF );
  /*
   * Pad Configure.. Setting as per the Button Pullups on
   * the Launch pad (active low).. changing to pulldowns for Orbit
   */
  GPIOPadConfigSet(SWTPort, SWT1 | SWT2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(BTN1Port, BTN1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
  GPIOPadConfigSet(BTN2Port, BTN2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

  GPIOPadConfigSet(LED1Port, LED1, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED2Port, LED2, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED3Port, LED3, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LED4Port, LED4, GPIO_STRENGTH_8MA_SC, GPIO_PIN_TYPE_STD);

  /*
   * Initialize Switches as Input
   */
  GPIOPinTypeGPIOInput(SWTPort, SWT1 | SWT2);

  /*
   * Initialize Buttons as Input
   */
  GPIOPinTypeGPIOInput(BTN1Port, BTN1);
  GPIOPinTypeGPIOInput(BTN2Port, BTN2);

  /*
   * Initialize LEDs as Output
   */
  GPIOPinTypeGPIOOutput(LED1Port, LED1);
  GPIOPinTypeGPIOOutput(LED2Port, LED2);
  GPIOPinTypeGPIOOutput(LED3Port, LED3);
  GPIOPinTypeGPIOOutput(LED4Port, LED4);

  //Initialize Accelerometer input
  GPIOPinTypeGPIOInput(ACCL_INT2Port, ACCL_INT2);

  //Initialize Thermometer input
  GPIOPinTypeGPIOInput(I2CSDAPort, I2CSDA_PIN);
  GPIOPinTypeGPIOInput(I2CSCLPort, I2CSCL_PIN);

  /*
   * Enable ADC Periph
   */
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

  GPIOPinTypeADC(AINPort, AIN);

  /*
   * Enable ADC with this Sequence
   * 1. ADCSequenceConfigure()
   * 2. ADCSequenceStepConfigure()
   * 3. ADCSequenceEnable()
   * 4. ADCProcessorTrigger();
   * 5. Wait for sample sequence ADCIntStatus();
   * 6. Read From ADC
   */
  ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH0);
  ADCSequenceEnable(ADC0_BASE, 0);

  /*
   * Initialize the OLED
   */
  OrbitOledInit();

  /*
   * Reset flags
   */
  chSwtCur = 0;
  chSwtPrev = 0;
  fClearOled = true;

}


#endif // TRACK_H
