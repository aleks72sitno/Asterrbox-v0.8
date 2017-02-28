#include "LM75B.h"

//Init LM75B device
void LM75BInit()
{
	// Initial I2C Port
	xSysCtlPeripheralEnable2(LM75BI2CBase);
	xSysCtlPeripheralEnable(xGPIOSPinToPeripheralId(LM75BSCK_PIN));

	//Map I2C Pin
#if(LM75BI2CBase == xI2C1_BASE)
	xSPinTypeI2C(I2C1SCK, LM75BSCK_PIN);
	xSPinTypeI2C(I2C1SDA, LM75BSDA_PIN);
#endif
#if(LM75BI2CBase == xI2C2_BASE)
	xSPinTypeI2C(I2C2SCK, LM75BSCK_PIN);
	xSPinTypeI2C(I2C2SDA, LM75BSDA_PIN);
#endif
#if(LM75BI2CBase == xI2C3_BASE)
	xSPinTypeI2C(I2C3SCK, LM75BSCK_PIN);
	xSPinTypeI2C(I2C3SDA, LM75BSDA_PIN);
#endif
	//Initialize I2C Module 100K
	I2CInit(LM75BI2CBase, 100000);
	I2CEnable(LM75BI2CBase);
}

//!Reads the current temperature.
float LM75BReadTemperature()
{
    char cmd[2] = {LM75B_Conf, 0x0};

    xI2CMasterWriteBufS1(LM75BI2CBase, LM75B_ADDR, cmd, 2, xfalse);
    cmd[0] = LM75B_Temp;
    xI2CMasterWriteBufS2(LM75BI2CBase, cmd, 1, xfalse);
    xI2CMasterReadBufS1(LM75BI2CBase, LM75B_ADDR, cmd, 2, xfalse);
    return (   (float)((cmd[0]<<8)|cmd[1]) / 256.0   );
}
