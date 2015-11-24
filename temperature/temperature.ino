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

bool	fClearOled;

void DeviceInit();

char I2CGenTransmit(char * pbData, int cSize, bool fRW, char bAddr);
bool I2CGenIsNotIdle();

void setup()
{
  OrbitOledInit();

  fClearOled = true;
}

void loop()
{
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
    OrbitOledPutString("Temp: ");

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

  sprintf(szTemp, "%d.%d", tempWhole, tempDec);

  if(tempDec == 0) {
    szTemp[4] = ' ';
  }
  szTemp[5] = '\0';

  OrbitOledSetCursor(6,0);

  OrbitOledPutString(szTemp);

  OrbitOledSetCursor(11, 0);

  OrbitOledPutString(" C");
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
