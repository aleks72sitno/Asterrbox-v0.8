
/*
 *
 * \author no1wudi
 * \file MPU6050_HW.h
 *
 */

#ifndef __MPU6050_HW_H
#define __MPU6050_HW_H



/*
 * \addtogroup Hardware dependence
 * \brief Include files of the driver,by default,it's for STM32F407,please modify it for your project
 */

#include "CoX/CoX_Peripheral/inc/xhw_types.h"
#include "CoX/CoX_Peripheral/inc/xgpio.h"
#include "CoX/CoX_Peripheral/inc/xi2c.h"
#include "CoX/CoX_Peripheral/inc/xsysctl.h"
#include "CoX/cookie/cookie.h"

/*
 * \addtogroup Hardware dependence
 * \brief Pin map for the microcontroller,by default,it's for STM32F407,please modify it for your project
 */

#define MPU6050SCL 		sSCL
#define MPU6050SDA 		sSDA
#define MPU6050I2C 		sI2C_BASE
#define MPU6050_I2C_Speed 300000

/*\addtogroup Hardware dependence
 * \brief The command of the reading and writing,it's consist of 7-bit I2C address and a read/write bit
 */

#define MPU6050_Address 0x68




/*
 * \addtogroup Chip Init
 * \brief Configure the parameter of the I2C bus to communicate with the chip
 */

void MPUI2CConfig(void);

/*	\addtogroup Chip Init
 * \brief  Read data from MPU6050
 *
 *  \param Address The address of the object register
 *  \return				The data of the object register
 */

unsigned char ReadMPU(unsigned char Address);

/*
 *\brief  Write command or data to the object register
 *
 * \param Address 	The address of the object register
 * \param Value		The value will be written to the object register
 */

void WriteMPU(unsigned char Address, unsigned char Value);

#endif
