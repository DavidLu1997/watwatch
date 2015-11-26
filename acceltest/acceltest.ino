
#include <OrbitBoosterPackDefs.h>
#include "Energia.h"

int get_accelerometer_internal(int address);
void I2CGenTransmit(char *pbData, int cSize, int fRW, char bAddr);
int I2CGenIsNotIdle();

const int chPwrCtlReg = 0x2D;
const int chX0Addr = 0x32;
const int chY0Addr = 0x34;
const int chZ0Addr = 0x36;

char rgchWriteAccl[3];

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

// Below are all pre-made functions! Do not touch, I have no idea how they work!
void I2CGenTransmit(char * pbData, int cSize, int fRW, char bAddr) {
	int i;
	char *pbTemp;
	
	pbTemp = pbData;
	
	/*Send Address High Byte*/
	/* Send Write Block Cmd*/
	I2CMasterSlaveAddrSet(I2C0_BASE, bAddr, WRITE);
	I2CMasterDataPut(I2C0_BASE, *pbTemp);
	
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	
	delay(1);
	
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
	
		delay(1);
	
		while(I2CMasterBusy(I2C0_BASE));
		}
		else if(cSize == i + 1 && cSize > 1) {
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
	
		delay(1);
	
		while(I2CMasterBusy(I2C0_BASE));
		}
		else if(i == 0) {
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
	
		delay(1);
	
		while(I2CMasterBusy(I2C0_BASE));
	
		/* Idle wait*/
		while(I2CGenIsNotIdle());
		}
		else {
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
	
		delay(1);
	
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
	
		delay(1);
	
		while(I2CMasterBusy(I2C0_BASE));
		}
		else {
		I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
	
		delay(1);
	
		while(I2CMasterBusy(I2C0_BASE));
	
		/* Idle wait */
		while(I2CGenIsNotIdle());
		}
	
		pbTemp++;
	}
	
	}
}

int I2CGenIsNotIdle() {
	return !I2CMasterBusBusy(I2C0_BASE);
}

void setup()
{
  setup_accelerometer();
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  analogWrite(GREEN_LED, get_accelerometer_x()/2);
  analogWrite(BLUE_LED, get_accelerometer_y()/2);
  analogWrite(RED_LED, get_accelerometer_z()/2);
  delay(50);
}
