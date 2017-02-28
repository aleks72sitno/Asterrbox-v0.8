/*
 * \author no1wudi
 * \file MPU6050.c
 */

#include "MPU6050.h"

void EnableMPU() {
	MPUI2CConfig();
	WriteMPU(PWR_MGMT_1, 0x00);
}

void DisableMPU() {
	WriteMPU(PWR_MGMT_2, 0x40);
}

void DeinitMPU() {
	WriteMPU(PWR_MGMT_2, 0xC0);
}

float GetMPUTemp() {
	float temp;
	temp = GetDataMPU(TEMP_OUT_H,TEMP_OUT_L);
	temp = temp / 340 + 36.53;
	return temp;
}

void MPU_Register_FIFO_Init(MPU_Register_FIFO_InitType * InitType) {
	WriteMPU(FIFO_EN,
			((InitType->ACCEL) | (InitType->GYRO) | (InitType->TEMP)));
}


void MPU_Register_Config_Init(MPU_Register_Config_InitType * InitType) {
	WriteMPU(CONFIG, ((InitType->DLPF) | (InitType->SYNC)));
}

void MPU_Register_GYRO_Init(MPU_Register_GYRO_InitType * InitType) {
	WriteMPU(GYRO_CONFIG,
			((InitType->GYRO_SELF_TEST) | (InitType->GYRO_RANGE)));
}

void MPU_Register_ACCEL_Init(MPU_Register_ACCEL_InitType * InitType) {
	WriteMPU(ACCEL_CONFIG,
			((InitType->ACCEL_SELF_TEST) | (InitType->ACCEL_RANGE)));
}





unsigned short GetDataMPU(unsigned char AddressH, unsigned char AddressL) {
	unsigned short DataH, DataL;
	DataH = ReadMPU(AddressH);
	DataL = ReadMPU(AddressL);
	return ((DataH << 8) + DataL);
}
