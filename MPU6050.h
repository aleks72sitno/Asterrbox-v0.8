#ifndef __MPU6050_H
#define __MPU6050_H

/*
 * \author no1wudi
 * \file MPU6050.h
 */

#include "MPU6050_HW.h"

#define DIV_ACCEL_RANGE_2g (float)16384
#define DIV_ACCEL_RANGE_4g (float)8192
#define DIV_ACCEL_RANGE_8g (float)4096
#define DIV_ACCEL_RANGE_16g (float)2048

#define DIV_GYRO_RANGE_250 131
#define DIV_GYRO_RANGE_500 65.5
#define DIV_GYRO_RANGE_1000 32.8
#define DIV_GYRO_RANGE_2000 16.4


#define SELF_TEST_X 0x0D
#define SELF_TEST_Y 0x0E
#define SELF_TEST_Z 0x0F
#define SELF_TEST_A 0x10

#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define FIFO_EN 0x23

#define I2C_MST_CTRL 0x24
#define I2C_SLV0_ADDR 0x25
#define I2C_SLV0_REG  0x26
#define I2C_SLV0_CTRL 0x27
#define I2C_SLV1_ADDR  0x28
#define I2C_SLV1_REG	0x29
#define I2C_SLV1_CTRL 0x2A
#define I2C_SLV2_ADDR  0x2B
#define I2C_SLV2_REG  0x2C
#define I2C_SLV2_CTRL 0x2D
#define I2C_SLV3_ADDR  0x2E
#define I2C_SLV3_REG 0x2F
#define I2C_SLV3_CTRL  0x30
#define I2C_SLV4_ADDR 0x31
#define I2C_SLV4_REG  0x32
#define I2C_SLV4_DO   0x33
#define I2C_SLV4_CTRL 0x34
#define I2C_SLV4_DI   0x35
#define I2C_MST_STATUS 0x36

#define INT_PIN_CFG 0x37
#define INT_ENABLE 0x38
#define INT_STATUS 0x3A

#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define TEMP_OUT_H 0x41
#define TEMP_OUT_L 0x42

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define EXT_SENS_DATA_00 0x49
#define EXT_SENS_DATA_01 0x4A
#define EXT_SENS_DATA_02 0x4B
#define EXT_SENS_DATA_03 0x4C
#define EXT_SENS_DATA_04 0x4D
#define EXT_SENS_DATA_05 0x4E
#define EXT_SENS_DATA_06 0x4F
#define EXT_SENS_DATA_07 0x50
#define EXT_SENS_DATA_08 0x51
#define EXT_SENS_DATA_09 0x52
#define EXT_SENS_DATA_10 0x53
#define EXT_SENS_DATA_11 0x54
#define EXT_SENS_DATA_12 0x55
#define EXT_SENS_DATA_13 0x56
#define EXT_SENS_DATA_14 0x57
#define EXT_SENS_DATA_15 0x58
#define EXT_SENS_DATA_16 0x59
#define EXT_SENS_DATA_17 0x5A
#define EXT_SENS_DATA_18 0x5B
#define EXT_SENS_DATA_19 0x5C
#define EXT_SENS_DATA_20 0x5D
#define EXT_SENS_DATA_21 0x5E
#define EXT_SENS_DATA_22 0x5F
#define EXT_SENS_DATA_23 0x60

#define I2C_SLV0_DO 0x63
#define I2C_SLV1_DO 0x64
#define I2C_SLV2_DO 0x65
#define I2C_SLV3_DO 0x66

#define I2C_MST_DELAY_CTRL 0x67
#define SIGNAL_PATH_RESET 0x68
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
#define FIFO_COUNTH  0x72
#define FIFO_COUNTL  0x73
#define FIFO_R_W 0x74
#define WHO_AM_I 0x75



/*
 *\brief SYNC_SET init type,control the data output switch of the sensor
 */
typedef enum {
	SYNC_Input_Disable = 0x00,
	SYNC_TEMP_OUT = 0x8,
	SYNC_GYRO_XOUT = 0x10,
	SYNC_GYRO_YOUT = 0x18,
	SYNC_GYRO_ZOUT = 0x20,
	SYNC_ACCEL_XOUT = 0x28,
	SYNC_ACCEL_YOUT = 0x30,
	SYNC_ACCEL_ZOUT = 0x38
} SYNC_SET_InitType;

/*
 * \brief DLPF init value,control the DLPF statue
 */
typedef enum {
	DLPF_0 = 0x00,
	DLPF_1 = 0x01,
	DLPF_2 = 0x02,
	DLPF_3 = 0x03,
	DLPF_4 = 0x04,
	DLPF_5 = 0x05,
	DLPF_6 = 0x06,
	DLPF_7 = 0x07
} DLPF_InitType;

/*
 * \brief CONFIG register init tyep ,these value will be written to the register
 */
typedef struct {
	SYNC_SET_InitType SYNC;
	DLPF_InitType DLPF;
} MPU_Register_Config_InitType;

/*
 * \brief Gyroscope self test init value,control the axis which will run self test
 */
typedef enum {
	GYRO_NO_SELF_TEST = 0x00,
	GYRO_X_SELF_TEST = 0x80,
	GYRO_Y_SELF_TEST = 0x40,
	GYRO_Z_SELF_TEST = 0x20
} GYRO_SELF_TEST_InitType;

/*
 * \brief Gyroscope range select.
 */
typedef enum {
	GYRO_RANGE_250 = 0x00,
	GYRO_RANGE_500 = 0x08,
	GYRO_RANGE_1000 = 0x10,
	GYRO_RANGE_2000 = 0x18
} GYRO_RANGE_InitType;

/*
 * \brief GYRO init type,these value will be written to the register
 */
typedef struct {
	GYRO_SELF_TEST_InitType GYRO_SELF_TEST;
	GYRO_RANGE_InitType GYRO_RANGE;
} MPU_Register_GYRO_InitType;

/*
 * \brief Accelerator self test config
 */
typedef enum {
	ACCEL_NO_SELF_TEST = 0x00,
	ACCEL_X_SELF_TEST = 0x80,
	ACCEL_Y_SELF_TEST = 0x40,
	ACCEL_Z_SELF_TEST = 0x20
} ACCEL_SELF_TEST_InitType;

/*
 * \brief Accelerator range select
 */
typedef enum {
	ACCEL_RANGE_2g = 0x00,
	ACCEL_RANGE_4g = 0x08,
	ACCEL_RANGE_8g = 0x10,
	ACCEL_RANGE_16g = 0x18
} ACCEL_RANGE_InitType;

/*
 * \brief ACCEL init type,these value will be written to the register
 */
typedef struct {
	ACCEL_SELF_TEST_InitType ACCEL_SELF_TEST;
	ACCEL_RANGE_InitType ACCEL_RANGE;
} MPU_Register_ACCEL_InitType;

typedef enum {
	TEMP_FIFO_ENABLE = 0x80, TEMP_FIFO_DISABLE = 0x00
} TEMP_FIFO_InitType;

/*
 * \brief FIFO config
 */
typedef enum {
	GYRO_FIFO_DISABLE = 0x00,
	GYRO_X_FIFO = 0x80,
	GYRO_Y_FIFO = 0x40,
	GYRO_Z_FIFO = 0x10
} GYRO_FIFO_InitType;

/*
 * \brief Enable or disable the Accelerator FIFO
 */
typedef enum {
	ACCEL_FIFO_ENABLE = 0x08, ACCEL_FIFO_DISABLE = 0x00
} ACCEL_FIFO_InitType;

typedef struct {
	TEMP_FIFO_InitType TEMP;
	GYRO_FIFO_InitType GYRO;
	ACCEL_FIFO_InitType ACCEL;
} MPU_Register_FIFO_InitType;

/*
 *\brief This function is used to configure the status of the CONFIG register,to configure the DLPF and SYNC
 * \param InitType	The init struct of the CONFIG
 */

void MPU_Register_Config_Init(MPU_Register_Config_InitType * InitType);

/*
 * \brief This function is used to configre the range and self-test of the gyroscope
 * \param InitType	The init struct of the gyroscope
 */
void MPU_Register_GYRO_Init(MPU_Register_GYRO_InitType * InitType);

/*
 * \brief This function is used to configre the range and self-test of the accelerometer
 * \param InitType	The init struct of the accelerometer
 */
void MPU_Register_ACCEL_Init(MPU_Register_ACCEL_InitType * InitType);
/*
 * \brief This function is used to configre the FIFO status of the chip
 * \param InitType	The init struct of the FIFO
 */
void MPU_Register_FIFO_Init(MPU_Register_FIFO_InitType * InitType);

/*
 * \brief Enable and init the MPU6050
 */

void EnableMPU(void);

/*
 * \brief Disable the MPU6050
 */


void DisableMPU(void);

/*
 * \brief Deinit the MPU6050
 */
void DeinitMPU(void);

/*
 * \brief Get the current temperature of the chip,you must enable the temperature forward
 */

float GetMPUTemp(void);

/*
 * \brief Get the raw data of those two register,
 * e.g,data =  GetDataMPU(ACCEL_XOUT_H,ACCEL_XOUT_L),then you get the x-axis value
 * To make the value useful, the useful value is that the data be devided by DIV parameter
 * e.g. data = data / DIV_ACCEL_RANGE_2g ,the DIV parameter determined by the range you setted forward,the the
 * data is the real value can be use.
 */

unsigned short GetDataMPU(unsigned char AddressH, unsigned char AddressL);

#endif
