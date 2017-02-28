
/*
 * \author no1wudi
 * \file MPU6050_HW.c
 */
#include "MPU6050_HW.h"


void MPUI2CConfig() {
	xSysCtlPeripheralEnable(xSYSCTL_PERIPH_I2C0);
	xSPinTypeI2C(I2C0SCK,MPU6050SCL);
	xSPinTypeI2C(I2C0SDA,MPU6050SDA);
	xI2CMasterInit(MPU6050I2C,MPU6050_I2C_Speed);
	xI2CMasterEnable(MPU6050I2C);
}

unsigned char ReadMPU(unsigned char Address) {
	unsigned char Data;
    xI2CMasterEnable(sI2C_BASE);
	xI2CMasterWriteS1(MPU6050I2C,MPU6050_Address,Address,xfalse);
	xI2CMasterReadS1(MPU6050I2C,MPU6050_Address,&Data,xtrue);
    xI2CMasterDisable(sI2C_BASE);
	return Data;
}

void WriteMPU(unsigned char Address, unsigned char Value) {
    xI2CMasterEnable(sI2C_BASE);
	xI2CMasterWriteS1(MPU6050I2C,MPU6050_Address,Address,xfalse);
	xI2CMasterWriteS2(MPU6050I2C,Value,xtrue);
    xI2CMasterDisable(sI2C_BASE);
}
